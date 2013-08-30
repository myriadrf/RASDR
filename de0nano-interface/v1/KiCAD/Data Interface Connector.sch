EESchema Schematic File Version 2  date 10/25/2012 4:28:48 PM
LIBS:DigitalInterface_v1.0-cache
LIBS:DigitalInterface_v1.0-cache
EELAYER 25  0
EELAYER END
$Descr User 8263 11692
encoding utf-8
Sheet 2 7
Title "Digital Interface v1.0"
Date "25 oct 2012"
Rev "3"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 3500 3700
Wire Wire Line
	3500 4000 3500 3100
Wire Wire Line
	3500 4000 3600 4000
Wire Wire Line
	5200 4600 5400 4600
Wire Wire Line
	5200 5100 5400 5100
Wire Wire Line
	3400 4300 3600 4300
Wire Wire Line
	3400 4600 3600 4600
Wire Wire Line
	3400 5100 3600 5100
Wire Wire Line
	3400 5600 3600 5600
Wire Wire Line
	3400 5900 3600 5900
Wire Wire Line
	3400 6400 3600 6400
Wire Wire Line
	3400 6700 3600 6700
Wire Wire Line
	3600 7000 3400 7000
Wire Wire Line
	3400 7200 3600 7200
Wire Wire Line
	3400 7700 3600 7700
Wire Wire Line
	3600 8000 3400 8000
Wire Wire Line
	5200 7200 5400 7200
Wire Wire Line
	5200 6700 5400 6700
Wire Wire Line
	5400 4300 5200 4300
Wire Wire Line
	5400 5400 5200 5400
Wire Wire Line
	5400 5700 5200 5700
Wire Wire Line
	5400 6500 5200 6500
Wire Wire Line
	5400 6300 5200 6300
Connection ~ 5300 6600
Wire Wire Line
	5200 6600 5300 6600
Wire Wire Line
	5550 4800 5200 4800
Wire Wire Line
	3600 7400 3200 7400
Wire Wire Line
	5200 6100 5600 6100
Wire Wire Line
	5200 5800 5300 5800
Wire Wire Line
	5300 5800 5300 6900
Wire Wire Line
	5300 6900 5200 6900
Wire Wire Line
	5300 7700 5200 7700
Wire Wire Line
	3600 6100 3200 6100
Wire Wire Line
	3600 4800 3200 4800
Wire Wire Line
	3600 5300 3500 5300
Wire Wire Line
	3500 5300 3500 4500
Wire Wire Line
	3600 3500 3200 3500
Wire Wire Line
	3500 3700 3600 3700
Wire Wire Line
	3500 3100 3600 3100
Connection ~ 5300 3500
Wire Wire Line
	5200 4000 5300 4000
Wire Wire Line
	5300 4000 5300 3100
Wire Wire Line
	5300 3100 5200 3100
Connection ~ 3500 2900
Wire Wire Line
	3600 2900 3500 2900
Wire Wire Line
	5200 3000 5300 3000
Wire Wire Line
	5300 3000 5300 2500
Wire Wire Line
	5300 2500 3500 2500
Wire Wire Line
	3500 2500 3500 3000
Wire Wire Line
	3500 3000 3600 3000
Wire Wire Line
	3650 2050 3950 2050
Wire Wire Line
	5200 2900 5300 2900
Connection ~ 5300 2900
Wire Wire Line
	3950 2150 3850 2150
Wire Wire Line
	3850 2150 3850 2500
Connection ~ 3850 2500
Wire Wire Line
	5200 3700 5300 3700
Connection ~ 5300 3700
Wire Wire Line
	5600 3500 5200 3500
Connection ~ 3500 3500
Wire Wire Line
	3500 4500 3600 4500
Connection ~ 3500 4800
Wire Wire Line
	3600 5800 3500 5800
Wire Wire Line
	3500 5800 3500 6900
Wire Wire Line
	3500 6900 3600 6900
Connection ~ 3500 6100
Wire Wire Line
	3500 6600 3600 6600
Connection ~ 3500 6600
Wire Wire Line
	5300 7400 5300 7900
Wire Wire Line
	5300 7900 5200 7900
Connection ~ 5300 7700
Connection ~ 5300 6100
Wire Wire Line
	5200 7400 5600 7400
Connection ~ 5300 7400
Wire Wire Line
	5200 5300 5300 5300
Wire Wire Line
	5300 5300 5300 4500
Wire Wire Line
	5300 4500 5200 4500
Connection ~ 5300 4800
Wire Wire Line
	5400 6400 5200 6400
Wire Wire Line
	5400 5900 5200 5900
Wire Wire Line
	5400 5600 5200 5600
Wire Wire Line
	5400 4100 5200 4100
Wire Wire Line
	5400 4400 5200 4400
Wire Wire Line
	5200 7000 5400 7000
Wire Wire Line
	5400 7800 5200 7800
Wire Wire Line
	5400 8000 5200 8000
Wire Wire Line
	3400 7600 3600 7600
Wire Wire Line
	3400 7100 3600 7100
Wire Wire Line
	3400 6500 3600 6500
Wire Wire Line
	3400 6300 3600 6300
Wire Wire Line
	3400 5700 3600 5700
Wire Wire Line
	3400 5200 3600 5200
Wire Wire Line
	3400 5000 3600 5000
Wire Wire Line
	3400 4400 3600 4400
Wire Wire Line
	5200 5200 5400 5200
Wire Wire Line
	5200 5000 5400 5000
Wire Wire Line
	5200 7100 5400 7100
$Comp
L +5V #PWR01
U 1 1 4FF2DEE3
P 3650 2050
F 0 "#PWR01" H 3650 2240 20  0001 C CNN
F 1 "+5V" V 3750 2100 50  0000 C CNN
	1    3650 2050
	0    -1   -1   0   
$EndComp
Text GLabel 5400 8000 2    45   Output ~ 0
TXEN
Text GLabel 5400 7800 2    45   Output ~ 0
CLK_IN
Text GLabel 5400 7200 2    45   Output ~ 0
GPIO2
Text GLabel 5400 7100 2    45   Output ~ 0
GPIO1
Text GLabel 5400 7000 2    45   Output ~ 0
GPIO0
Text GLabel 5400 6700 2    45   Input ~ 0
RXCLK
Text GLabel 5400 6500 2    45   Input ~ 0
RXD10
Text GLabel 5400 6400 2    45   Input ~ 0
RXD8
Text GLabel 5400 6300 2    45   Input ~ 0
RXD6
Text GLabel 5400 5900 2    45   Input ~ 0
RXD4
Text GLabel 5400 5700 2    45   Input ~ 0
RXD2
Text GLabel 5400 5600 2    45   Input ~ 0
RXD0
Text GLabel 5400 5400 2    45   Input ~ 0
RXIQSEL
Text GLabel 5400 5200 2    45   Input ~ 0
TXD10
Text GLabel 5400 5100 2    45   Input ~ 0
TXD8
Text GLabel 5400 5000 2    45   Input ~ 0
TXD6
Text GLabel 5400 4600 2    45   Output ~ 0
TXD4
Text GLabel 5400 4400 2    45   Output ~ 0
TXD2
Text GLabel 5400 4300 2    45   Output ~ 0
TXD0
Text GLabel 5400 4100 2    45   Output ~ 0
TXIQSEL
Text GLabel 3400 8000 0    45   Output ~ 0
RXEN
Text GLabel 3400 7700 0    45   Output ~ 0
SPI_NCS0
Text GLabel 3400 7600 0    45   Output ~ 0
SPI_CLK
Text GLabel 3400 7200 0    45   Output ~ 0
SPI_MISO
Text GLabel 3400 7100 0    45   Output ~ 0
SPI_MOSI
Text GLabel 3400 7000 0    45   Output ~ 0
RESET
Text GLabel 3400 6700 0    45   Input ~ 0
TXCLK
Text GLabel 3400 6500 0    45   Input ~ 0
RXD11
Text GLabel 3400 6400 0    45   Input ~ 0
RXD9
Text GLabel 3400 6300 0    45   Input ~ 0
RXD7
Text GLabel 3400 5900 0    45   Input ~ 0
RXD5
Text GLabel 3400 5700 0    45   Input ~ 0
RXD3
Text GLabel 3400 5600 0    45   Input ~ 0
RXD1
Text GLabel 3400 5200 0    45   Output ~ 0
TXD11
Text GLabel 3400 5100 0    45   Output ~ 0
TXD9
Text GLabel 3400 5000 0    45   Output ~ 0
TXD7
Text GLabel 3400 4600 0    45   Output ~ 0
TXD5
Text GLabel 3400 4400 0    45   Output ~ 0
TXD3
Text GLabel 3400 4300 0    45   Output ~ 0
TXD1
$Comp
L FX10B-80S/8-SV J2
U 1 1 4FE9526C
P 4400 5400
F 0 "J2" H 4700 8200 60  0000 C CNN
F 1 "FX10B-80S/8-SV" H 4410 2530 60  0000 C CNN
F 2 "SMD_FX10B-80S/8-SV" H 4400 5400 60  0001 C CNN
F 4 "CONN; RECEPT; 80POS; W/POST; SMD" H 4400 5400 60  0001 C CNN "Description"
F 5 "FX10A-80S/8-SV(71)" H 4400 5400 60  0001 C CNN "Manufacturer Part Number"
F 6 "HIROSE" H 4400 5400 60  0001 C CNN "Manufacturer"
F 7 "DigiKey" H 4400 5400 60  0001 C CNN "Vendor"
F 8 "H11232-ND" H 4400 5400 60  0001 C CNN "FieVendor Part Number "
	1    4400 5400
	1    0    0    -1  
$EndComp
$Comp
L JUMPER2 J1
U 1 1 4FE9526B
P 4200 2100
F 0 "J1" H 4200 2240 50  0000 C CNN
F 1 "PINHD-1X2" H 4200 1900 60  0001 C CNN
F 2 "TH_PINHD-1X2_V" H 4200 2100 60  0001 C CNN
F 4 "HEADER; 1ROW; 2WAY" H 4200 2100 60  0001 C CNN "Description"
F 5 "M20-9990246" H 4200 2100 60  0001 C CNN "Manufacturer Part Number"
F 6 "HARWIN" H 4200 2100 60  0001 C CNN "Manufacturer"
F 7 "Farnell" H 4200 2100 60  0001 C CNN "Vendor"
F 8 "1022247" H 4200 2100 60  0001 C CNN "Vendor Part Number"
	1    4200 2100
	-1   0    0    -1  
$EndComp
$Comp
L GND #02
U 1 1 4FE95269
P 5650 3500
F 0 "#02" H 5700 3550 50  0001 C CNN
F 1 "GND" H 5650 3440 50  0000 C CNN
	1    5650 3500
	0    -1   -1   0   
$EndComp
$Comp
L GND #03
U 1 1 4FE95268
P 5600 4800
F 0 "#03" H 5650 4850 50  0001 C CNN
F 1 "GND" H 5600 4740 50  0000 C CNN
	1    5600 4800
	0    -1   -1   0   
$EndComp
$Comp
L GND #04
U 1 1 4FE95267
P 5650 6100
F 0 "#04" H 5700 6150 50  0001 C CNN
F 1 "GND" H 5650 6040 50  0000 C CNN
	1    5650 6100
	0    -1   -1   0   
$EndComp
$Comp
L GND #05
U 1 1 4FE95266
P 5650 7400
F 0 "#05" H 5700 7450 50  0001 C CNN
F 1 "GND" H 5650 7340 50  0000 C CNN
	1    5650 7400
	0    -1   -1   0   
$EndComp
$Comp
L GND #06
U 1 1 4FE95265
P 3150 7400
F 0 "#06" H 3200 7450 50  0001 C CNN
F 1 "GND" H 3150 7340 50  0000 C CNN
	1    3150 7400
	0    1    1    0   
$EndComp
$Comp
L GND #07
U 1 1 4FE95264
P 3150 6100
F 0 "#07" H 3200 6150 50  0001 C CNN
F 1 "GND" H 3150 6040 50  0000 C CNN
	1    3150 6100
	0    1    1    0   
$EndComp
$Comp
L GND #08
U 1 1 4FE95263
P 3150 4800
F 0 "#08" H 3200 4850 50  0001 C CNN
F 1 "GND" H 3150 4740 50  0000 C CNN
	1    3150 4800
	0    1    1    0   
$EndComp
$Comp
L GND #09
U 1 1 4FE95262
P 3150 3500
F 0 "#09" H 3200 3550 50  0001 C CNN
F 1 "GND" H 3150 3440 50  0000 C CNN
	1    3150 3500
	0    1    1    0   
$EndComp
NoConn ~ 5200 3200
NoConn ~ 5200 3300
NoConn ~ 5200 3800
NoConn ~ 5200 3900
NoConn ~ 5200 4200
NoConn ~ 5200 5500
NoConn ~ 5200 6800
NoConn ~ 5200 7600
NoConn ~ 3600 7900
NoConn ~ 3600 7800
NoConn ~ 3600 5400
NoConn ~ 3600 5500
NoConn ~ 3600 4100
NoConn ~ 3600 4200
NoConn ~ 3600 3800
NoConn ~ 3600 3900
NoConn ~ 3600 3200
NoConn ~ 3600 3300
NoConn ~ 3600 6800
$EndSCHEMATC
