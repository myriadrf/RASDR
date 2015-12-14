
                        CYPRESS SEMICONDUCTOR CORPORATION
                                    FX3 SDK

DIGIRED RX Interface Firmware
-----------------------------

  This application, derived from the synchronous slave fifo protocol example,
  implements the interface needed to connect a LMS6002D FPRF Device to USB3.

  A master device that implements the Cypress defined Sync Slave FIFO
  protocol is required to perform data transfers with this application.

  This application example does the following:

  1. Configures the GPIF II interface to implement the Sync Slave FIFO
     protocol.

  2. Enumerates as a vendor specific USB device with two bulk endpoints
     (1-OUT and 1-IN).

  3. Create an AUTO DMA channel to enable the following data paths:
     a. No data is accepted from the USB host via the 1-OUT endpoint.
     b. All data received from the master device on the slave port through
        socket 0 is forwarded to the USB host through the 1-IN endpoint.

  4. When any data packet is received through one of the ingress sockets,
     the application is notified and forwards the data to the recipient
     through a DMA callback function.
     
  5. Vendor commands are implemented to perform various functions such
     as LMS6002D register access, device reset, and I2C operations.

  Files:

    * cyfx_gcc_startup.S   : Start-up code for the ARM-9 core on the FX3
      device.  This assembly source file follows the syntax for the GNU
      assembler.

    * cyfx_app.h           : C header file that defines constants used by
      this example implementation.  Can be modified to select USB connection
      speed, endpoint numbers and properties etc.

    * cyfx_dscr.c          : C source file that contains USB descriptors
      used by this example. VID and PID is defined in this file.

    * cyfxgpif2config.h    : C header file that contains the data required
      to configure the GPIF interface to implement the Sync. Slave FIFO
      protocol.

    * cyfxtx.c             : C source file that provides ThreadX RTOS wrapper
      functions and other utilites required by the FX3 firmware library.

    * cyfx_app.c           : Main C source file that implements this example.

    * makefile             : GNU make compliant build script for compiling
      this example.

[]

