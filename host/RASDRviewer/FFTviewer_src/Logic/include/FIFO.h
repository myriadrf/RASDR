// -----------------------------------------------------------------------------
// FILE: 		FIFO.h
// DESCRIPTION:	templates for data buffer FIFO
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef FIFO_H
#define FIFO_H

#include <pthread.h>
#include <semaphore.h>

/**
	Blocking FIFO, blocks reader if no items are left in buffer.
*/
template<class T>
class blockingFIFO
{
public:
	/**
		@brief Creates FIFO of given size
		@param size maximum number of elements in FIFO, must be power of 2!
	*/
	blockingFIFO(int size, int packetSize) : size(size), m_packetSize(packetSize)
	{
	    frozen = false;
		elements = new T*[size];
		for(int i=0; i<size; ++i)
            elements[i] = new T(packetSize);
		sizeMask = size-1;
		init();
	}
	/**
		@brief Deletes elements inside FIFO
	*/
	~blockingFIFO()
	{
		delete []elements;
		pthread_mutex_destroy(&mutex);
		sem_destroy(&semHasElements);
	}
	/**
		@brief Takes one elements from fifo and copies it to obj
		@param *obj pointer to object where to copy element from fifo

		If no items are left inside FIFO the reader is blocked until some items are pushed into
		FIFO or the FIFO is unblocked by calling unblock().
	*/
	void pop(T* obj)
	{
		pthread_mutex_lock(&mutex);
		if( filled <= 0 && !frozen)
		{
			consumerWaiting = true;
			pthread_mutex_unlock(&mutex);
			sem_wait(&semHasElements);
			pthread_mutex_lock(&mutex);
		}
		*obj = *elements[readPos];
		++readPos;
		readPos &= sizeMask;
		--filled;
		pthread_mutex_unlock(&mutex);
	}

	/**
		@brief Copies given object and pushes it into FIFO.
		@param *obj pointer to object which to copy to FIFO
	*/
	void push(T* obj)
	{
		pthread_mutex_lock(&mutex);
        if(frozen)
        {
            pthread_mutex_unlock(&mutex);
            return;
        }
		*elements[writePos] = *obj;
		++writePos;
		writePos &= sizeMask;
		if(filled < size)
			++filled;
		if(consumerWaiting)
		{
			consumerWaiting = false;
			sem_post(&semHasElements);
		}
		pthread_mutex_unlock(&mutex);
	}
	/**
		@brief Returns elements count inside FIFO
		@return element count
	*/
	int length()
	{
		int elementsFilled;
		pthread_mutex_lock(&mutex);
		elementsFilled = filled;
		pthread_mutex_unlock(&mutex);
		return elementsFilled;
	}
	/**
		@brief Deletes all elements inside FIFO
	*/
	void reset()
	{
	    sem_post(&semHasElements);
		sem_destroy(&semHasElements);
		pthread_mutex_destroy(&mutex);
		init();
	}

	/**
		@brief Unblocks waiting reader
	*/
	void unblock()
	{
		if(consumerWaiting)
		{
			consumerWaiting = false;
			sem_post(&semHasElements);
		}
	}

    /**
        Stops writing operations to fifo, but doesn't block writer
    */
	void freeze()
	{
		pthread_mutex_lock(&mutex);
        frozen = true;
		pthread_mutex_unlock(&mutex);
	}

    /**
        Allows writing operations to fifo after freezing
    */
	void unfreeze()
	{
		pthread_mutex_lock(&mutex);
        frozen = false;
		pthread_mutex_unlock(&mutex);
	}

    const int m_packetSize;
private:
	/**
		Setups index counters and mutex.
	*/
	void init()
	{
		consumerWaiting = false;
		filled = 0;
		readPos = 0;
		writePos = 0;
		pthread_mutex_init(&mutex, 0);
		sem_init(&semHasElements, 0, 0);
	}

	T** elements;
	int size;
	int sizeMask;
	int readPos;
	int writePos;
	int filled;
	bool consumerWaiting;
	bool frozen;
	pthread_mutex_t mutex;
	sem_t semHasElements;
};

#endif

