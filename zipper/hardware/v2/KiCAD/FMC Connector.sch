EESchema Schematic File Version 2
LIBS:Zipper-cache
LIBS:Zipper-cache
EELAYER 27 0
EELAYER END
$Descr User 8263 11692
encoding utf-8
Sheet 4 9
Title "Zipper v.2"
Date "7 jan 2014"
Rev "2"
Comp ""
Comment1 "THIS WORK IS COVERED UNDER A CREATIVE COMMONS LICENSE (CC BY 3.0)"
Comment2 "Copyright 2013 AZIO Electronics Co., Ltd."
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1900 2150 2    45   Output ~ 0
RESET_C
Text GLabel 1900 2950 2    45   Output ~ 0
SPI_NCS_0_C
Text GLabel 1900 3050 2    45   BiDi ~ 0
SPI_MISO_C
Text GLabel 1900 3350 2    45   Output ~ 0
SPI_CLK_C
Text GLabel 1900 3450 2    45   Output ~ 0
SPI_MOSI_C
NoConn ~ 1700 5050
NoConn ~ 1700 1350
NoConn ~ 1700 1450
NoConn ~ 1700 4550
$Comp
L GND #PWR034
U 1 1 51DABAFD
P 1800 5300
F 0 "#PWR034" H 1800 5400 40  0001 C CNN
F 1 "GND" H 1800 5230 40  0000 C CNN
F 2 "" H 1800 5300 60  0000 C CNN
F 3 "" H 1800 5300 60  0000 C CNN
	1    1800 5300
	1    0    0    -1  
$EndComp
Text GLabel 1900 2650 2    45   Output ~ 0
GPIO0_C
Text GLabel 1900 2550 2    45   Output ~ 0
GPIO1_C
Text GLabel 1900 2250 2    45   Output ~ 0
GPIO2_C
Text GLabel 4550 1950 2    45   Input ~ 0
RXIQSEL_F
Text GLabel 4550 2050 2    45   Output ~ 0
RXEN_F
Text GLabel 4550 3850 2    45   Input ~ 0
RXD0_F
Text GLabel 4550 3750 2    45   Input ~ 0
RXD1_F
Text GLabel 4550 3550 2    45   Input ~ 0
RXD2_F
Text GLabel 4550 3450 2    45   Input ~ 0
RXD3_F
Text GLabel 4550 3250 2    45   Input ~ 0
RXD4_F
Text GLabel 4550 3150 2    45   Input ~ 0
RXD5_F
Text GLabel 4550 2950 2    45   Input ~ 0
RXD6_F
Text GLabel 4550 2850 2    45   Input ~ 0
RXD7_F
Text GLabel 4550 2650 2    45   Input ~ 0
RXD8_F
Text GLabel 4550 2550 2    45   Input ~ 0
RXD9_F
Text GLabel 4550 2350 2    45   Input ~ 0
RXD10_F
Text GLabel 4550 2250 2    45   Input ~ 0
RXD11_F
NoConn ~ 4350 1250
NoConn ~ 4350 1550
NoConn ~ 4350 1650
NoConn ~ 4350 4050
NoConn ~ 4350 4150
NoConn ~ 4350 4250
NoConn ~ 4350 4350
NoConn ~ 4350 4450
NoConn ~ 4350 4550
NoConn ~ 4350 4650
$Comp
L GND #PWR035
U 1 1 51DAC71E
P 4450 5300
F 0 "#PWR035" H 4450 5400 40  0001 C CNN
F 1 "GND" H 4450 5230 40  0000 C CNN
F 2 "" H 4450 5300 60  0000 C CNN
F 3 "" H 4450 5300 60  0000 C CNN
	1    4450 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2150 1900 2150
Wire Wire Line
	1700 2950 1900 2950
Wire Wire Line
	1700 3050 1900 3050
Wire Wire Line
	1700 3350 1900 3350
Wire Wire Line
	1700 3450 1900 3450
Wire Wire Line
	1700 4650 2350 4650
Wire Wire Line
	1900 4650 1900 4850
Wire Wire Line
	1900 4850 1700 4850
Connection ~ 1900 4650
Wire Wire Line
	1700 1250 1800 1250
Wire Wire Line
	1800 1250 1800 5250
Wire Wire Line
	1700 1550 1800 1550
Connection ~ 1800 1550
Wire Wire Line
	1700 1650 1800 1650
Connection ~ 1800 1650
Wire Wire Line
	1700 1950 1800 1950
Connection ~ 1800 1950
Wire Wire Line
	1700 2050 1800 2050
Connection ~ 1800 2050
Wire Wire Line
	1700 2350 1800 2350
Connection ~ 1800 2350
Wire Wire Line
	1700 2450 1800 2450
Connection ~ 1800 2450
Wire Wire Line
	1700 2750 1800 2750
Connection ~ 1800 2750
Wire Wire Line
	1700 2850 1800 2850
Connection ~ 1800 2850
Wire Wire Line
	1700 3150 1800 3150
Connection ~ 1800 3150
Wire Wire Line
	1700 3250 1800 3250
Connection ~ 1800 3250
Wire Wire Line
	1700 3550 1800 3550
Connection ~ 1800 3550
Wire Wire Line
	1700 3650 1800 3650
Connection ~ 1800 3650
Wire Wire Line
	1700 3950 1800 3950
Connection ~ 1800 3950
Wire Wire Line
	1700 4050 1800 4050
Connection ~ 1800 4050
Wire Wire Line
	1700 4350 1800 4350
Connection ~ 1800 4350
Wire Wire Line
	1700 4450 1800 4450
Connection ~ 1800 4450
Wire Wire Line
	1700 4750 1800 4750
Connection ~ 1800 4750
Wire Wire Line
	1700 4950 1800 4950
Connection ~ 1800 4950
Wire Wire Line
	1700 5150 1800 5150
Connection ~ 1800 5150
Wire Wire Line
	1700 2250 1900 2250
Wire Wire Line
	1700 2550 1900 2550
Wire Wire Line
	1700 2650 1900 2650
Wire Wire Line
	4550 1950 4350 1950
Wire Wire Line
	4350 2050 4550 2050
Wire Wire Line
	4550 3450 4350 3450
Wire Wire Line
	4550 3550 4350 3550
Wire Wire Line
	4550 3750 4350 3750
Wire Wire Line
	4550 3850 4350 3850
Wire Wire Line
	4350 1350 4450 1350
Wire Wire Line
	4450 1350 4450 5250
Wire Wire Line
	4350 1450 4450 1450
Connection ~ 4450 1450
Wire Wire Line
	4350 1750 4450 1750
Connection ~ 4450 1750
Wire Wire Line
	4350 1850 4450 1850
Connection ~ 4450 1850
Wire Wire Line
	4350 2150 4450 2150
Connection ~ 4450 2150
Wire Wire Line
	4350 2450 4450 2450
Connection ~ 4450 2450
Wire Wire Line
	4350 2750 4450 2750
Connection ~ 4450 2750
Wire Wire Line
	4350 3050 4450 3050
Connection ~ 4450 3050
Wire Wire Line
	4350 3350 4450 3350
Connection ~ 4450 3350
Wire Wire Line
	4350 3650 4450 3650
Connection ~ 4450 3650
Wire Wire Line
	4350 3950 4450 3950
Connection ~ 4450 3950
Wire Wire Line
	4350 5050 4450 5050
Connection ~ 4450 5050
Wire Wire Line
	4350 4850 4450 4850
Connection ~ 4450 4850
$Comp
L GND #PWR036
U 1 1 51DAD29C
P 1800 10550
F 0 "#PWR036" H 1800 10650 40  0001 C CNN
F 1 "GND" H 1800 10480 40  0000 C CNN
F 2 "" H 1800 10550 60  0000 C CNN
F 3 "" H 1800 10550 60  0000 C CNN
	1    1800 10550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 6700 1800 6700
Wire Wire Line
	1800 6700 1800 10500
Wire Wire Line
	1700 7000 1800 7000
Connection ~ 1800 7000
Wire Wire Line
	1700 7300 1800 7300
Connection ~ 1800 7300
Wire Wire Line
	1700 7600 1800 7600
Connection ~ 1800 7600
Wire Wire Line
	1700 7900 1800 7900
Connection ~ 1800 7900
Wire Wire Line
	1700 8200 1800 8200
Connection ~ 1800 8200
Wire Wire Line
	1700 8500 1800 8500
Connection ~ 1800 8500
Wire Wire Line
	1700 8800 1800 8800
Connection ~ 1800 8800
Wire Wire Line
	1700 9100 1800 9100
Connection ~ 1800 9100
Wire Wire Line
	1700 9400 1800 9400
Connection ~ 1800 9400
Wire Wire Line
	1700 9700 1800 9700
Connection ~ 1800 9700
Wire Wire Line
	1700 10000 1800 10000
Connection ~ 1800 10000
Wire Wire Line
	1700 10300 1800 10300
Connection ~ 1800 10300
NoConn ~ 1700 10400
NoConn ~ 1700 10200
NoConn ~ 1700 10100
NoConn ~ 1700 9900
NoConn ~ 1700 9800
NoConn ~ 1700 9600
NoConn ~ 1700 9500
NoConn ~ 1700 9300
NoConn ~ 1700 9000
NoConn ~ 1700 8700
NoConn ~ 1700 8400
NoConn ~ 1700 8300
NoConn ~ 1700 8100
NoConn ~ 1700 8000
NoConn ~ 1700 7800
NoConn ~ 1700 7700
NoConn ~ 1700 7400
NoConn ~ 1700 6800
$Comp
L GND #PWR037
U 1 1 51DADE62
P 6750 5300
F 0 "#PWR037" H 6750 5400 40  0001 C CNN
F 1 "GND" H 6750 5230 40  0000 C CNN
F 2 "" H 6750 5300 60  0000 C CNN
F 3 "" H 6750 5300 60  0000 C CNN
	1    6750 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1250 6750 1250
Wire Wire Line
	6750 1250 6750 5250
Wire Wire Line
	6650 1950 6750 1950
Connection ~ 6750 1950
Wire Wire Line
	6650 1550 6750 1550
Connection ~ 6750 1550
Wire Wire Line
	6650 1650 6750 1650
Connection ~ 6750 1650
Wire Wire Line
	6650 2250 6750 2250
Connection ~ 6750 2250
Wire Wire Line
	6650 2550 6750 2550
Connection ~ 6750 2550
Wire Wire Line
	6650 2850 6750 2850
Connection ~ 6750 2850
Wire Wire Line
	6650 3150 6750 3150
Connection ~ 6750 3150
Wire Wire Line
	6650 3450 6750 3450
Connection ~ 6750 3450
Wire Wire Line
	6650 3750 6750 3750
Connection ~ 6750 3750
Wire Wire Line
	6650 4050 6750 4050
Connection ~ 6750 4050
Wire Wire Line
	6650 4350 6750 4350
Connection ~ 6750 4350
Wire Wire Line
	6650 4650 6750 4650
Connection ~ 6750 4650
Wire Wire Line
	6650 4950 6750 4950
Connection ~ 6750 4950
Wire Wire Line
	6650 5150 6750 5150
Connection ~ 6750 5150
NoConn ~ 4350 4750
NoConn ~ 4350 4950
NoConn ~ 4350 5150
Text GLabel 6850 2350 2    45   Output ~ 0
TXD11_F
Wire Wire Line
	6650 2350 6850 2350
Text GLabel 6850 2450 2    45   Output ~ 0
TXD10_F
Wire Wire Line
	6650 2450 6850 2450
Text GLabel 6850 2650 2    45   Output ~ 0
TXD9_F
Wire Wire Line
	6650 2650 6850 2650
Text GLabel 6850 2750 2    45   Output ~ 0
TXD8_F
Wire Wire Line
	6650 2750 6850 2750
Text GLabel 6850 2950 2    45   Output ~ 0
TXD7_F
Wire Wire Line
	6650 2950 6850 2950
Text GLabel 6850 3050 2    45   Output ~ 0
TXD6_F
Wire Wire Line
	6650 3050 6850 3050
Text GLabel 6850 3250 2    45   Output ~ 0
TXD5_F
Wire Wire Line
	6650 3250 6850 3250
Text GLabel 6850 3350 2    45   Output ~ 0
TXD4_F
Wire Wire Line
	6650 3350 6850 3350
Text GLabel 6850 3550 2    45   Output ~ 0
TXD3_F
Wire Wire Line
	6850 3550 6650 3550
Text GLabel 6850 3650 2    45   Output ~ 0
TXD2_F
Wire Wire Line
	6650 3650 6850 3650
Text GLabel 6850 3850 2    45   Output ~ 0
TXD1_F
Wire Wire Line
	6650 3850 6850 3850
Text GLabel 6850 3950 2    45   Output ~ 0
TXD0_F
Wire Wire Line
	6650 3950 6850 3950
Text GLabel 6850 4150 2    45   Output ~ 0
TXEN_F
Wire Wire Line
	6650 4150 6850 4150
Text GLabel 6850 4250 2    45   Input ~ 0
TXIQSEL_F
Wire Wire Line
	6650 4250 6850 4250
NoConn ~ 6650 1350
NoConn ~ 6650 1450
NoConn ~ 6650 1750
NoConn ~ 6650 1850
NoConn ~ 6650 2050
NoConn ~ 6650 2150
NoConn ~ 6650 4550
NoConn ~ 6650 4450
NoConn ~ 6650 5050
NoConn ~ 6650 4750
Text GLabel 1975 7500 2    45   Input ~ 0
TXCLK_C
Text GLabel 1975 7100 2    45   Input ~ 0
RXCLK_C
Text GLabel 2000 8600 2    45   Output ~ 0
SPI_NCS_1_C
Text GLabel 2000 8900 2    45   Output ~ 0
SPI_NCS_2_C
NoConn ~ 1700 6500
NoConn ~ 1700 6600
NoConn ~ 1700 6900
NoConn ~ 1700 3850
NoConn ~ 6650 4850
Wire Wire Line
	1975 7500 1700 7500
Wire Wire Line
	1700 7100 1975 7100
NoConn ~ 1700 7200
Wire Wire Line
	1700 8900 2000 8900
Wire Wire Line
	1700 8600 2000 8600
$Comp
L +12V #PWR038
U 1 1 51DC4509
P 2350 4650
F 0 "#PWR038" H 2400 4625 20  0001 C CNN
F 1 "+12V" V 2350 4850 39  0000 C CNN
F 2 "~" H 2350 4650 60  0000 C CNN
F 3 "~" H 2350 4650 60  0000 C CNN
	1    2350 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 2850 4350 2850
Wire Wire Line
	4550 2950 4350 2950
Wire Wire Line
	4550 3150 4350 3150
Wire Wire Line
	4550 3250 4350 3250
Wire Wire Line
	4550 2250 4350 2250
Wire Wire Line
	4550 2350 4350 2350
Wire Wire Line
	4350 2550 4550 2550
Wire Wire Line
	4550 2650 4350 2650
$Comp
L ASP-134604-01 J4
U 4 1 51F80BB1
P 1050 6400
F 0 "J4" H 1200 6500 60  0000 C CNN
F 1 "ASP-134604-01" H 1450 2150 60  0001 C CNN
F 2 "FMC" H 1300 6400 60  0001 C CNN
F 3 "" H 1300 6400 60  0000 C CNN
F 4 "FMC" H 1300 6600 60  0001 C CNN "Description"
F 5 "ASP-134604-01" H 1400 6700 60  0001 C CNN "Manufacturer Part Number"
F 6 "Samtec" H 1300 6600 60  0001 C CNN "Manufacturer"
F 7 "Samtec" H 1600 6900 60  0001 C CNN "Vendor"
F 8 "ASP-134604-01" H 1700 7000 60  0001 C CNN "Vendor Part Number"
F 9 "ASP-134604-01" H 1300 2200 50  0000 C CNN "Component Value"
	4    1050 6400
	1    0    0    -1  
$EndComp
$Comp
L ASP-134604-01 J4
U 3 1 51F80BE4
P 6000 1150
F 0 "J4" H 6150 1250 60  0000 C CNN
F 1 "ASP-134604-01" H 6400 -3100 60  0001 C CNN
F 2 "FMC" H 6250 1150 60  0001 C CNN
F 3 "" H 6250 1150 60  0000 C CNN
F 4 "FMC" H 6250 1350 60  0001 C CNN "Description"
F 5 "ASP-134604-01" H 6350 1450 60  0001 C CNN "Manufacturer Part Number"
F 6 "Samtec" H 6250 1350 60  0001 C CNN "Manufacturer"
F 7 "Samtec" H 6550 1650 60  0001 C CNN "Vendor"
F 8 "ASP-134604-01" H 6650 1750 60  0001 C CNN "Vendor Part Number"
F 9 "ASP-134604-01" H 6250 -3050 50  0000 C CNN "Component Value"
	3    6000 1150
	1    0    0    -1  
$EndComp
$Comp
L ASP-134604-01 J4
U 2 1 51F80C17
P 3700 1150
F 0 "J4" H 3850 1250 60  0000 C CNN
F 1 "ASP-134604-01" H 4100 -3100 60  0001 C CNN
F 2 "FMC" H 3950 1150 60  0001 C CNN
F 3 "" H 3950 1150 60  0000 C CNN
F 4 "FMC" H 3950 1350 60  0001 C CNN "Description"
F 5 "ASP-134604-01" H 4050 1450 60  0001 C CNN "Manufacturer Part Number"
F 6 "Samtec" H 3950 1350 60  0001 C CNN "Manufacturer"
F 7 "Samtec" H 4250 1650 60  0001 C CNN "Vendor"
F 8 "ASP-134604-01" H 4350 1750 60  0001 C CNN "Vendor Part Number"
F 9 "ASP-134604-01" H 3950 -3050 50  0000 C CNN "Component Value"
	2    3700 1150
	1    0    0    -1  
$EndComp
$Comp
L ASP-134604-01 J4
U 1 1 51F80C4A
P 1050 1150
F 0 "J4" H 1200 1250 60  0000 C CNN
F 1 "ASP-134604-01" H 1450 -3100 60  0001 C CNN
F 2 "FMC" H 1300 1150 60  0001 C CNN
F 3 "~" H 1300 1150 60  0000 C CNN
F 4 "ASP-134604-01" H 1400 1450 60  0001 C CNN "Manufacturer Part Number"
F 5 "ASP-134604-01" H 1700 1750 60  0001 C CNN "Vendor Part Number"
F 6 "FMC" H 1300 1350 60  0001 C CNN "Description"
F 7 "Samtec" H 1600 1650 60  0001 C CNN "Vendor"
F 8 "Samtec" H 1300 1350 60  0001 C CNN "Manufacturer"
F 9 "ASP-134604-01" H 1300 -3050 50  0000 C CNN "Component Value"
	1    1050 1150
	1    0    0    -1  
$EndComp
Text GLabel 2050 1750 2    45   BiDi ~ 0
MIPI_CLK_C
Text GLabel 2050 1850 2    45   BiDi ~ 0
MIPI_DATA_C
Wire Wire Line
	2050 1750 1700 1750
Wire Wire Line
	2050 1850 1700 1850
Text GLabel 1900 3750 2    45   Output ~ 0
GPIO3_C
Wire Wire Line
	1900 3750 1700 3750
Text GLabel 2000 4150 2    45   BiDi ~ 0
SDA_C
Text GLabel 2000 4250 2    45   BiDi ~ 0
SCL_C
Wire Wire Line
	2000 4150 1700 4150
Wire Wire Line
	2000 4250 1700 4250
Text GLabel 2000 9200 2    45   Output ~ 0
SPI_NCS_3
Wire Wire Line
	2000 9200 1700 9200
$EndSCHEMATC
