# Compiler, tools and options

CXX           = g++-mp-4.7
CXXFLAGS      = -m64 -pipe -std=c++11 -Wall -Wno-sign-compare -W -fPIE -g
INCPATH       = -I/usr/include/ooml

LINK          = g++-mp-4.7
LFLAGS        = -m64
LIBS          = -lOOMLCore -lOOMLComponents -lOOMLParts 

DEL_FILE      = rm -f



# Files

OBJECTS       = main.o casefactory.o
BOARD         = rasdr2.h posts.h
TARGET        = casefactory



# Rules

all: $(TARGET)


main.o: main.cpp geom.h boarddescription.h $(BOARD) casefactory.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

casefactory.o: casefactory.cpp casefactory.h geom.h boarddescription.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o casefactory.o casefactory.cpp


$(TARGET):  $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)


clean:
	-$(DEL_FILE) $(OBJECTS)
	
distclean: clean
	-$(DEL_FILE) $(TARGET)

