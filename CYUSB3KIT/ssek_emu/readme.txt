
                        CYPRESS SEMICONDUCTOR CORPORATION
                                    FX3 SDK

USB BULK SOURCE SINK LED EXAMPLE
-------------------------------

  This example illustrates on how to configure the GPIO as an output and drive the LED.
  The LED will blink at 50ms rate if the FX3 DVK is connected to a SuperSpeed USB port. The LED
  will always turn ON if connected to a HighSpeed USB port and will be OFF of connected to a
  FullSpeed USB port. The user can also change the LED on-time and off-time by using the vendor
  command (0xAA). Refer to the FX3 DVK User-Guide on how to change the blinking rate of the LED
  using the vendor request. 
   
  This example illustrates the use of the FX3 firmware APIs to implement
  a data source and data sink over a pair of USB Bulk endpoints.

  The device enumerates as a vendor specific USB device with a pair of Bulk
  endpoints (1-OUT and 1-IN). The OUT endpoint acts as data sink and the IN
  endpoint acts as data source to the PC Host.

  The source and sink is achieved with the help of a a DMA MANUAL IN Channel 
  and a DMA MANUAL OUT Channel. 
  Any data received from the host through the DMA MANUAL IN channel is 
  discarded. 
  A constant data pattern is continuously loaded into the DMA MANUAL OUT 
  channel and sent to the host. 

  Files:

    * cyfx_gcc_startup.S   : Start-up code for the ARM-9 core on the FX3 device.
      This assembly source file follows the syntax for the GNU assembler.

    * cyfxbulksrcsink.h    : Constant definitions for the bulk source sink 
      application. The USB connection speed, numbers and properties of the 
      endpoints etc. can be selected through definitions in this file.

    * cyfxbulkdscr.c       : C source file containing the USB descriptors that
      are used by this firmware example. VID and PID is defined in this file.

    * cyfxtx.c             : ThreadX RTOS wrappers and utility functions required
      by the FX3 API library.

    * cyfxbulksrcsink.c    : Main C source file that implements the bulk source sink
      example.
	  : Lines 633-648 in cybulksrcsink.c ontain the code for initialising
  	  the GPIO54 as output pin. 
  	  :	Lines 813-823 in cybulksrcsink.c (BulkSrcSinkAppThread_Entry function) contain the
  	  code for GPIO toggling for blinking the LED.
  	  : Lines 977-1003 contains the vendor command implementation for changing the 
  	  LED ON-time and OFF-time. User can add their own vendor commands in the 
  	  same way.

    * makefile             : GNU make compliant build script for compiling this
      example.

  PERFORMANCE OPTIMIZATIONS

  The data transfer performance obtained using the firmware example depends on the
  endpoint burst length, as well as the size and number of DMA buffers used. These
  parameters can be varied through constants defined in the cyfxbulksrcsink.h header
  file. It is also possible to set them through the compiler command line. by adding
  them to the list of Pre-processor definitions in the Eclipse build settings.

  1. CY_FX_EP_BURST_LENGTH           : Defines the burst size for the endpoints.
                                       Set to 16 KB by default.
  2. CY_FX_BULKSRCSINK_DMA_BUF_SIZE  : Size of the DMA buffers used for the endpoints.
                                       Set to 32 KB by default.
  3. CY_FX_BULKSRCSINK_DMA_BUF_COUNT : Number of DMA buffers used for each endpoint.
                                       Set to 2 by default.

[]

