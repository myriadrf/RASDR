# RASDR HOST Software - Cypress Control Application for Firmware Load

The RASDR project gratefully acknowledges Cypress Semiconductor Corporation for enabling the development of the RASDR Firmware and Windows Support (*).

The directory structure for the driver files is as follows:

      license.txt                - Cypress Semiconductor License Agreement
      README.md                  - This file
      CyControl.zip              - Archive containing CyControl.exe and supporting files

When extracted, the archive will contain the following files:

      BulkLoop.exe
      CyBootProgrammer.img
      cycommonlibrary.dll
      cyconsoletool.exe
      CyControl.exe              - Program to use to update firmware
      cyframework.dll
      cygpif2.dll
      cygpif2codegenerator.dll
      cygpif2libviews.dll
      cygpif2timingmodel.dll
      cygpif2views.dll
      cygraphicaltool.exe
      cyprjmgmt.dll
      cyuiframework.dll
      CyUSB.dll
      Microsoft.mshtml.dll
      Streamer.exe

Of these, the one to use is 'CyControl.exe'.  This program will identify the RASDR board and allow you to (re-)program its firmware.  You will also have needed to have DigiRED/firwmare/bin/ extracted/copied to your desktop somewhere.

The basic procedure is as follows:

## Programming RASDR firwmare

 1. connect RASDR to the RX side of the USB3 connection (see 'rasdr-connect.png')
 2. start 'CyControl.exe' and observe that the Cypress USB Bootloader is recognized (see 'rasdr-unprogrammed.png')
 3. fit a jumper onto J2 while the rasdr board is powered on (see 'rasdr-fit-J2.png')
 4. in CyControl, select 'Program->FX3->SPI Flash' (see 'rasdr-cycontrol-program-spi.png')
 5. the device will be programmed with the Cypress USB BootProgrammer, and re-enumerate (see 'rasdr-cycontrol-bootloader-loaded.png')
 6. in CyControl, a window will pop-up asking for you to provide the location of 'usb_rx.img' (see 'rasdr-cycontrol-programmer-select-file.png'.
   a. if this does not occur, then select 'Program->FX3->SPI Flash' *again* (see 'rasdr-cycontrol-program-spi.png')
   b. pick the 'usb_rx.img' from the location you downloaded/extracted the files (**)
 7. You should see 'Programming of SPI Flash in Progress...' at the bottom of the window, then 'Programming of SPI Flash Succeeded'.
 8. Leave the jumper fitted on to J2 and disconnect the USB interface, ensuring that the board is powered off
 9. Plug the USB TX port into a POWERED USB2.0 HUB
   a. the leds D6 should go OUT, and D8 should blink at approximately 2Hz (D3 and D5 should stay lit)
 10. Plug the USB RX port into your PC (either USB2 or USB3)
   a. you should see 'RASDR Radio Astronomy SDR Rx Interface' in the CyControl center (see 'rasdr-cycontrol-driver-loaded-ok.png')

Once your 'CyControl' program shows 'RASDR Radio Astronomy SDR Rx Interface', you should be able to use RASDRviewer to operate your RASDR board.


## Troubleshooting

Certain DigiRED boards fail to load from SPI flash.  This is a problem with certain pullups being mis-installed and will be corrected in the production release of the boards.  If this is your situation, you can still use RASDR by following this 'Alternate' procedure until your boards are corrected.

 11. In CyControl, select 'Program->FX3->RAM', and pick the location of 'usb_rx.img'
 12. when complete, you should see 'RASDR Radio Astronomy SDR Rx Interface' in the CyControl window (see 'rasdr-cycontrol-driver-loaded-ok.png')
   a. You will need to use this procedure each time you disconnect power from your RASDR board

If your device says that 'DigiRED_RX' failed to load properly, then it is possible that you have "extra" files in the USB device drivers (perhaps from other installations of FX3 devices which are capturing the DigiRED).  To determine if this is the case, open a DOS console and execute the following command:

dos> find /i "1d50" c:\windows\inf\*.inf

If *MORE THAN ONE* file produces an output, then there is a good chance that conflicting drivers are installed.  If this is your situation, please contact the RASDR team for assistance.


## Licensing

The RASDR project gratefully acknowledges Cypress Semiconductor Corporation for enabling the development of the RASDR Firmware and Windows Support (**).  These files and the firware source code are derivative works distributed with permission under Case #2427983098.

For details of software licensing please see the associated license.txt file(s).

(*) https://github.com/myriadrf/RASDR/tree/master/DigiRED/firmware/bin
(**) Please see http://www.cypress.com/?rid=57990
