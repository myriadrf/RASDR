# DigiRED Driver Repository

The RASDR project gratefully acknowledges Cypress Semiconductor Corporation for enabling the development of the RASDR Firmware and Windows Support (*).

The 'digired-windows.zip' contains a folder named 'rasdr-March2015Drivers_Signed/' that includes the driver files.  The directory structure for the driver files is as follows:

      license.txt                - Cypress Semiconductor License Agreement
      README.md                  - This file
      docs/                      - screenshots and installation aids
      win7/                      - Windows 7 (32-bit and 64-bit) driver files
      wlh/                       - Windows Vista driver files
      wxp/                       - Windows XP (32-bit only) driver files

Ensure that you have unzipped these files to your local hard drive, and plug in your DigiRED board.  When the Windows device installer prompts you, provide the folder to the correct one for your OS (Windows 7, Vista or Windows XP) as described above.  You should see roughly what is described in the screenshots in the docs/.

NOTE: These drivers have been signed as of March 2015, and operate with the RASDR RX firmware VID=1D50,PID=6099,'RASDR Radio Astronomy SDR Rx Interface'

NOTE: Windows 8 users may try to use the Windows 7 drivers.  Testing on Windows 8 has not been extensive, please provide feedback.

NOTE: This folder is intended for developer use, primarily.  Users are encouraged to obtain software releases via http://rasdr.org

(*) Please see http://www.cypress.com/index.cfm?docID=45919
