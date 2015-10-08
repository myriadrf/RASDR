# DigiRED Firmware

The RASDR project gratefully acknowledges OpenMoko for providing USB Vendor ID and Product IDs(*).

This firmware was built using the Cypress EZ-USB SDK (**) v1.3.3 which provides WHQL drivers for Windows 8.1, 8 as well as 7 and XP, both 32-bit and 64-bit variants.

The directory structure for the firmware design is as follows:

      firmware/bin/
          error-codes.txt        - description of blink codes for device firmware error TRAPs
          vendor-commands.txt    - description of vendor commands that the firmware processes
          license.txt            - Cypress Semiconductor License Agreement
          readme.txt             - Usage and Installation Information
          usb_rx.img             - Current firmware downloadable binary
 
      firmware/src/
          usb_rx.zip             - Current firmware source code

(*)  http://wiki.openmoko.org/wiki/USB_Product_IDs
(**) Please see http://www.cypress.com/?rid=57990
