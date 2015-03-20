 2000  git clone http://git.code.sf.net/p/fx3load/code fx3load
 2001  cd fx3load/
 2005  make clean
 2006  make
 2008  ./fxload --help
 2013  dmesg
[ 3441.110798] usb 2-1.3.1.1: new high-speed USB device number 6 using ehci-pci
[ 3441.219961] usb 2-1.3.1.1: New USB device found, idVendor=04b4, idProduct=00f3
[ 3441.219973] usb 2-1.3.1.1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[ 3441.219979] usb 2-1.3.1.1: Product: WestBridge 
[ 3441.219983] usb 2-1.3.1.1: Manufacturer: Cypress
[ 3441.219988] usb 2-1.3.1.1: SerialNumber: 0000000004BE

 2014  lsusb -d 04b4:
>>> TOO
 2020  sudo ./fxload -D /dev/bus/usb/002/006 -I ../RASDR/DigiRED/firmware/bin/usb_rx.img -t fx3
 2021  dmesg
[ 5296.605878] usb 2-1.3.1.1: USB disconnect, device number 6
[ 5296.870163] usb 2-1.3.1.1: new high-speed USB device number 7 using ehci-pci
[ 5296.980047] usb 2-1.3.1.1: New USB device found, idVendor=1d50, idProduct=6099
[ 5296.980059] usb 2-1.3.1.1: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[ 5296.980065] usb 2-1.3.1.1: Product: DigiRed_RX
[ 5296.980069] usb 2-1.3.1.1: Manufacturer: SARA
 2022  lsusb -d 
Bus 002 Device 007: ID 1d50:6099 OpenMoko, Inc. 

