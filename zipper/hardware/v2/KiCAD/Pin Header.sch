EESchema Schematic File Version 2
LIBS:Zipper-cache
LIBS:Zipper-cache
EELAYER 27 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 9 10
Title "Zipper"
Date "15 jul 2013"
Rev "0"
Comp "OSH"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PINHEADER2X22 J7
U 1 1 51DAF584
P 3950 3950
F 0 "J7" H 4050 4000 60  0000 C CNN
F 1 "PINHEADER2X22" V 4050 2900 60  0000 C CNN
F 2 "Pin Header 2 x 22 SMD" H 4000 4050 60  0001 C CNN
F 3 "" H 3950 3950 60  0000 C CNN
F 4 "RS" H 4150 4100 60  0001 C CNN "Vendor"
F 5 "155-923" H 4250 4200 60  0001 C CNN "Vendor Part Number"
F 6 "Kontek" H 4350 4300 60  0001 C CNN "Manufacturer"
F 7 "6739810180440" H 4450 4400 60  0001 C CNN "Manufacturer Part Number"
F 8 "Pinheader, 2x22, straight, 2.54mm pitch, SMD" H 4550 4500 60  0001 C CNN "Description"
F 9 "Pin Header 2 x 22 SMD" H 4650 4600 60  0001 C CNN "Component Value"
	1    3950 3950
	1    0    0    -1  
$EndComp
Text GLabel 4575 4000 2    45   Output ~ 0
RXD1_H
Text GLabel 4575 4100 2    45   Output ~ 0
RXD3_H
Text GLabel 4575 4200 2    45   Output ~ 0
RXD5_H
Text GLabel 3575 4300 0    45   Output ~ 0
RXD6_H
Text GLabel 4575 4300 2    45   Output ~ 0
RXD7_H
Text GLabel 4575 4500 2    45   Output ~ 0
RXD11_H
Text GLabel 4575 4400 2    45   Output ~ 0
RXD9_H
Text GLabel 4575 4600 2    45   Output ~ 0
RXCLK
Text GLabel 4575 4700 2    45   Output ~ 0
RXIQSEL_H
Text GLabel 4575 4800 2    45   Input ~ 0
RXEN_H
Text GLabel 3575 4100 0    45   Output ~ 0
RXD2_H
Text GLabel 3575 4200 0    45   Output ~ 0
RXD4_H
Text GLabel 3575 4000 0    45   Output ~ 0
RXD0_H
Text GLabel 3575 4400 0    45   Output ~ 0
RXD8_H
Text GLabel 3575 4500 0    45   Output ~ 0
RXD10_H
Text GLabel 3575 5000 0    45   Input ~ 0
TXD0_H
Text GLabel 3575 5100 0    45   Input ~ 0
TXD2_H
Text GLabel 3575 5200 0    45   Input ~ 0
TXD4_H
Text GLabel 3575 5300 0    45   Input ~ 0
TXD6_H
Text GLabel 3575 5400 0    45   Input ~ 0
TXD8_H
Text GLabel 3575 5500 0    45   Input ~ 0
TXD10_H
Text GLabel 4575 5000 2    45   Input ~ 0
TXD1_H
Text GLabel 4575 5100 2    45   Input ~ 0
TXD3_H
Text GLabel 4575 5200 2    45   Input ~ 0
TXD5_H
Text GLabel 4575 5300 2    45   Input ~ 0
TXD7_H
Text GLabel 4575 5400 2    45   Input ~ 0
TXD9_H
Text GLabel 4575 5500 2    45   Input ~ 0
TXD11_H
Wire Wire Line
	4575 4000 4300 4000
Wire Wire Line
	4575 4100 4300 4100
Wire Wire Line
	4575 4200 4300 4200
Wire Wire Line
	4575 4300 4300 4300
Wire Wire Line
	4575 4400 4300 4400
Wire Wire Line
	4575 4500 4300 4500
Wire Wire Line
	4575 4600 4300 4600
Wire Wire Line
	4575 4700 4300 4700
Wire Wire Line
	4575 4800 4300 4800
Wire Wire Line
	3575 4000 3800 4000
Wire Wire Line
	3575 4100 3800 4100
Wire Wire Line
	3575 4200 3800 4200
Wire Wire Line
	3575 4300 3800 4300
Wire Wire Line
	3575 4400 3800 4400
Wire Wire Line
	3575 4500 3800 4500
Wire Wire Line
	3800 5000 3575 5000
Wire Wire Line
	4300 5000 4575 5000
Wire Wire Line
	4575 5100 4300 5100
Wire Wire Line
	4575 5200 4300 5200
Wire Wire Line
	4575 5300 4300 5300
Wire Wire Line
	4575 5400 4300 5400
Wire Wire Line
	4575 5500 4300 5500
Wire Wire Line
	3575 5100 3800 5100
Wire Wire Line
	3575 5200 3800 5200
Wire Wire Line
	3575 5300 3800 5300
Wire Wire Line
	3575 5400 3800 5400
Wire Wire Line
	3575 5500 3800 5500
Text GLabel 4575 5600 2    45   Input ~ 0
TXCLK
Wire Wire Line
	4300 5600 4575 5600
Text GLabel 4575 5700 2    45   Output ~ 0
TXIQSEL_H
Wire Wire Line
	4575 5700 4300 5700
$Comp
L GND #PWR0100
U 1 1 51DAF7CF
P 4450 6225
F 0 "#PWR0100" H 4450 6325 40  0001 C CNN
F 1 "GND" H 4450 6155 40  0000 C CNN
F 2 "" H 4450 6225 60  0000 C CNN
F 3 "" H 4450 6225 60  0000 C CNN
	1    4450 6225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0101
U 1 1 51DAF7DE
P 3675 6225
F 0 "#PWR0101" H 3675 6325 40  0001 C CNN
F 1 "GND" H 3675 6155 40  0000 C CNN
F 2 "" H 3675 6225 60  0000 C CNN
F 3 "" H 3675 6225 60  0000 C CNN
	1    3675 6225
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4900 4450 4900
Wire Wire Line
	4450 4900 4450 6175
Wire Wire Line
	3800 4900 3675 4900
Wire Wire Line
	3675 4900 3675 6175
Text GLabel 4575 5800 2    45   Input ~ 0
TXEN_H
Wire Wire Line
	4300 5800 4575 5800
Text GLabel 4575 5900 2    45   Input ~ 0
SPI_NCSO
Wire Wire Line
	4575 5900 4300 5900
Text GLabel 4575 6000 2    45   BiDi ~ 0
SPI_MISO
Wire Wire Line
	4300 6000 4575 6000
Text GLabel 4575 6100 2    45   Input ~ 0
RESET_H
Wire Wire Line
	4300 6100 4575 6100
Wire Wire Line
	3800 6000 3575 6000
Text GLabel 3575 6100 0    45   Input ~ 0
SPI_MOSI
Wire Wire Line
	3800 6100 3575 6100
Text GLabel 3575 6000 0    45   Input ~ 0
SPI_CLK
Wire Wire Line
	3800 5900 3675 5900
Connection ~ 3675 5900
Wire Wire Line
	3800 5600 3675 5600
Connection ~ 3675 5600
Text GLabel 3575 5700 0    45   Input ~ 0
SPI_NCSO_1
Text GLabel 3575 5800 0    45   Input ~ 0
SPI_NCSO_2
Wire Wire Line
	3575 5700 3800 5700
Wire Wire Line
	3800 5800 3575 5800
Text GLabel 3250 4600 0    45   Input ~ 0
GPIO0
Text GLabel 3250 4700 0    45   Input ~ 0
GPIO1
Text GLabel 3250 4800 0    45   Input ~ 0
GPIO2
Wire Wire Line
	3250 4600 3800 4600
Wire Wire Line
	3250 4700 3800 4700
Wire Wire Line
	3250 4800 3800 4800
$EndSCHEMATC
