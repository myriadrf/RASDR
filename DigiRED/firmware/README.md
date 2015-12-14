# DigiRED Firmware

The RASDR project gratefully acknowledges OpenMoko for providing USB Vendor ID and Product IDs(*).

This firmware was built using the Cypress EZ-USB SDK (**) v1.3.3 which provides WHQL drivers for Windows 8.1, 8 as well as 7 and XP, both 32-bit and 64-bit variants.

The directory structure for the firmware design is as follows:

      firmware/bin/              - Current firmware binary (released)
          error-codes.txt        - Description of blink codes for device firmware error TRAPs
          vendor-commands.txt    - Description of vendor commands that the firmware processes
          license.txt            - Cypress Semiconductor License Agreement
          readme.txt             - Usage and Installation Information
          usb_rx.img             - Current firmware downloadable binary

      firmware/src/              - Current firmware source code (released)
          usb_rx.zip             - archive library that can be imported into a EZ-USB project workspace

      firmware/usb_rx/           - Current firmware source code (in development)
          .cproject              - Eclipse project file
          .project               - Eclipse project file
          COPYING                - License agreement
          cyfxgpif2config.h      - GPIF-II Configuration File to program the device ports
          cyfxtx.c               - Application constants (co-ordinate with fx3.ld)
          cyfx_app.c             - Application code file
          cyfx_app.h             - Application header file
          cyfx_dscr.c            - Application USB Descriptors
          cyfx_gcc_startup.S     - Application bootstrap code (boilerplate)
          error-codes.txt        - Description of blink codes for device firmware error TRAPs
          fx3.ld                 - Linker and Memory map (co-ordinate with cyfxtx.c)
          license.txt            - License agreement
          makefile               - Project build file
          readme.txt             - Firmware provenance and description
          vendor-commands.txt    - description of vendor commands that the firmware processes

(*)  http://wiki.openmoko.org/wiki/USB_Product_IDs
(**) Please see http://www.cypress.com/?rid=57990


