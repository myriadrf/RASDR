EESchema Schematic File Version 2
LIBS:Zipper-cache
LIBS:Zipper-cache
EELAYER 27 0
EELAYER END
$Descr User 8263 11692
encoding utf-8
Sheet 3 9
Title "Zipper v.2"
Date "22 oct 2013"
Rev "0"
Comp ""
Comment1 "THIS WORK IS COVERED UNDER A CREATIVE COMMONS LICENSE (CC BY 3.0)"
Comment2 "Copyright 2013 AZIO Electronics Co., Ltd."
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3550 6500 2    45   BiDi ~ 0
GPIO2_C
Text GLabel 3150 5475 2    45   Output ~ 0
RESET_C
Text GLabel 1225 5550 0    45   Output ~ 0
SPI_MOSI_C
Text GLabel 3675 5550 2    45   BiDi ~ 0
SPI_MISO_C
Text GLabel 1725 5475 0    45   Output ~ 0
SPI_NCS_0_C
Text GLabel 1675 6425 0    45   BiDi ~ 0
GPIO1_C
Text GLabel 3150 5025 2    45   Input ~ 0
RXD11_H
Text GLabel 3150 4575 2    45   Input ~ 0
RXD7_H
Text GLabel 3150 4350 2    45   Input ~ 0
RXD5_H
Text GLabel 3150 4125 2    45   Input ~ 0
RXD3_H
Text GLabel 3150 3900 2    45   Input ~ 0
RXD1_H
Text GLabel 3650 5100 2    45   Input ~ 0
RXD10_H
Text GLabel 3600 4875 2    45   Input ~ 0
RXD8_H
Text GLabel 3600 4650 2    45   Input ~ 0
RXD6_H
Text GLabel 3650 5325 2    45   Input ~ 0
RXIQSEL_H
Text GLabel 3600 4425 2    45   Input ~ 0
RXD4_H
Text GLabel 1725 4800 0    45   Output ~ 0
TXD8_H
Text GLabel 1725 4575 0    45   Output ~ 0
TXD6_H
Text GLabel 1725 4125 0    45   Output ~ 0
TXD2_H
Text GLabel 1300 5325 0    45   Output ~ 0
TXIQSEL_H
Text GLabel 1725 5700 0    45   Output ~ 0
SPI_CLK_C
Text GLabel 3150 5250 2    45   Output ~ 0
RXEN_H
Text GLabel 1725 5250 0    45   Output ~ 0
TXEN_H
Text GLabel 3150 6425 2    45   BiDi ~ 0
GPIO0_C
Text GLabel 3150 4800 2    45   Input ~ 0
RXD9_H
Text GLabel 1725 5025 0    45   Output ~ 0
TXD10_H
Text GLabel 1300 5100 0    45   Output ~ 0
TXD11_H
Text GLabel 1300 3975 0    45   Output ~ 0
TXD1_H
Text GLabel 1300 4200 0    45   Output ~ 0
TXD3_H
Text GLabel 1300 4425 0    45   Output ~ 0
TXD5_H
Text GLabel 1300 4875 0    45   Output ~ 0
TXD9_H
Text GLabel 1300 4650 0    45   Output ~ 0
TXD7_H
Text GLabel 3600 4200 2    45   Input ~ 0
RXD2_H
Text GLabel 3600 3975 2    45   Input ~ 0
RXD0_H
Text GLabel 1725 4350 0    45   Output ~ 0
TXD4_H
Text GLabel 1725 3900 0    45   Output ~ 0
TXD0_H
$Comp
L GND #021
U 1 1 4FE81BE7
P 3050 6275
F 0 "#021" H 3100 6325 50  0001 C CNN
F 1 "GND" H 3050 6215 50  0000 C CNN
F 2 "" H 3050 6275 60  0001 C CNN
F 3 "" H 3050 6275 60  0001 C CNN
	1    3050 6275
	1    0    0    -1  
$EndComp
$Comp
L GND #022
U 1 1 4FE81B84
P 1850 3750
F 0 "#022" H 1900 3800 50  0001 C CNN
F 1 "GND" H 1850 3690 50  0000 C CNN
F 2 "" H 1850 3750 60  0001 C CNN
F 3 "" H 1850 3750 60  0001 C CNN
	1    1850 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #023
U 1 1 4FE81B78
P 3025 3750
F 0 "#023" H 3075 3800 50  0001 C CNN
F 1 "GND" H 3025 3690 50  0000 C CNN
F 2 "" H 3025 3750 60  0001 C CNN
F 3 "" H 3025 3750 60  0001 C CNN
	1    3025 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #024
U 1 1 51DAAE06
P 3025 8800
F 0 "#024" H 3075 8850 50  0001 C CNN
F 1 "GND" H 3025 8740 50  0000 C CNN
F 2 "" H 3025 8800 60  0001 C CNN
F 3 "" H 3025 8800 60  0001 C CNN
	1    3025 8800
	1    0    0    -1  
$EndComp
$Comp
L GND #025
U 1 1 51DAAEE6
P 1850 8800
F 0 "#025" H 1900 8850 50  0001 C CNN
F 1 "GND" H 1850 8740 50  0000 C CNN
F 2 "" H 1850 8800 60  0001 C CNN
F 3 "" H 1850 8800 60  0001 C CNN
	1    1850 8800
	1    0    0    -1  
$EndComp
$Comp
L GND #026
U 1 1 51DAAF3C
P 1825 6275
F 0 "#026" H 1875 6325 50  0001 C CNN
F 1 "GND" H 1825 6215 50  0000 C CNN
F 2 "" H 1825 6275 60  0001 C CNN
F 3 "" H 1825 6275 60  0001 C CNN
	1    1825 6275
	1    0    0    -1  
$EndComp
NoConn ~ 1925 2125
NoConn ~ 1925 2200
NoConn ~ 1925 2275
NoConn ~ 1925 2350
NoConn ~ 1925 2425
NoConn ~ 1925 2500
NoConn ~ 1925 2575
NoConn ~ 1925 2650
NoConn ~ 1925 2725
NoConn ~ 1925 2800
NoConn ~ 1925 2875
NoConn ~ 1925 2950
NoConn ~ 1925 3025
NoConn ~ 1925 3100
NoConn ~ 1925 3175
NoConn ~ 1925 3250
NoConn ~ 1925 3325
NoConn ~ 1925 3400
NoConn ~ 2950 3550
NoConn ~ 2950 3475
NoConn ~ 2950 3400
NoConn ~ 2950 3325
NoConn ~ 2950 3250
NoConn ~ 2950 3175
NoConn ~ 2950 3100
NoConn ~ 2950 3025
NoConn ~ 2950 2950
NoConn ~ 2950 2875
NoConn ~ 2950 2800
NoConn ~ 2950 2725
NoConn ~ 2950 2650
NoConn ~ 2950 2575
NoConn ~ 2950 2500
NoConn ~ 2950 2425
NoConn ~ 2950 2350
NoConn ~ 2950 2275
NoConn ~ 2950 2200
NoConn ~ 2950 2125
NoConn ~ 2950 4050
NoConn ~ 2950 4275
NoConn ~ 2950 4500
NoConn ~ 2950 4725
NoConn ~ 2950 5175
NoConn ~ 2950 5400
NoConn ~ 2950 5625
NoConn ~ 2950 5775
NoConn ~ 2950 5850
NoConn ~ 2950 5925
NoConn ~ 2950 6075
NoConn ~ 1925 6950
NoConn ~ 1925 7100
NoConn ~ 1925 7175
NoConn ~ 1925 7325
NoConn ~ 1925 7400
NoConn ~ 1925 7550
NoConn ~ 1925 7625
NoConn ~ 1925 7775
NoConn ~ 1925 7850
NoConn ~ 1925 8000
NoConn ~ 1925 8075
NoConn ~ 1925 8225
NoConn ~ 1925 8300
NoConn ~ 1925 8450
NoConn ~ 1925 8525
NoConn ~ 2950 8600
NoConn ~ 2950 8525
NoConn ~ 2950 8450
NoConn ~ 2950 8375
NoConn ~ 2950 8300
NoConn ~ 2950 8225
NoConn ~ 2950 8150
NoConn ~ 2950 8075
NoConn ~ 2950 8000
NoConn ~ 2950 7925
NoConn ~ 2950 7850
NoConn ~ 2950 7775
NoConn ~ 2950 7700
NoConn ~ 2950 7625
NoConn ~ 2950 7550
NoConn ~ 2950 7475
NoConn ~ 2950 7400
NoConn ~ 2950 7325
NoConn ~ 2950 7250
NoConn ~ 2950 7175
NoConn ~ 2950 7100
NoConn ~ 2950 7025
NoConn ~ 2950 6950
NoConn ~ 2950 6725
NoConn ~ 2950 6575
Text GLabel 1700 6000 0    45   Input ~ 0
RXCLK_C
NoConn ~ 1925 3475
NoConn ~ 1925 3550
Text GLabel 3150 6000 2    45   Input ~ 0
TXCLK_C
Text GLabel 3125 5700 2    45   Output ~ 0
SPI_NCS_1_C
Text GLabel 3175 6650 2    45   Output ~ 0
SPI_NCS_2_C
NoConn ~ 2950 4950
NoConn ~ 1925 5775
NoConn ~ 1925 5925
$Comp
L +12V #PWR027
U 1 1 51DC44FA
P 1750 1700
F 0 "#PWR027" H 1800 1675 20  0001 C CNN
F 1 "+12V" H 1750 1825 39  0000 C CNN
F 2 "~" H 1750 1700 60  0000 C CNN
F 3 "~" H 1750 1700 60  0000 C CNN
	1    1750 1700
	1    0    0    -1  
$EndComp
Text GLabel 4775 8050 0    45   BiDi ~ 0
GPIO2_C
Text GLabel 6425 8550 2    45   Output ~ 0
RESET_C
Text GLabel 6400 8450 2    45   BiDi ~ 0
SPI_MISO_C
Text GLabel 6450 6950 2    45   Input ~ 0
RXD11_H
Text GLabel 6450 6750 2    45   Input ~ 0
RXD7_H
Text GLabel 6450 6650 2    45   Input ~ 0
RXD5_H
Text GLabel 6450 6550 2    45   Input ~ 0
RXD3_H
Text GLabel 6450 6450 2    45   Input ~ 0
RXD1_H
Text GLabel 5175 6950 0    45   Input ~ 0
RXD10_H
Text GLabel 5175 6850 0    45   Input ~ 0
RXD8_H
Text GLabel 5175 6750 0    45   Input ~ 0
RXD6_H
Text GLabel 6875 7150 2    45   Input ~ 0
RXIQSEL_H
Text GLabel 5175 6650 0    45   Input ~ 0
RXD4_H
Text GLabel 6875 7250 2    45   Output ~ 0
RXEN_H
Text GLabel 4800 7050 0    45   BiDi ~ 0
GPIO0_C
Text GLabel 6450 6850 2    45   Input ~ 0
RXD9_H
Text GLabel 5175 6550 0    45   Input ~ 0
RXD2_H
Text GLabel 5175 6450 0    45   Input ~ 0
RXD0_H
Text GLabel 6900 8050 2    45   Input ~ 0
TXCLK_C
Text GLabel 5175 8150 0    45   Output ~ 0
SPI_NCS_1_C
Text GLabel 5175 8250 0    45   Output ~ 0
SPI_NCS_2_C
Text GLabel 5175 8550 0    45   Output ~ 0
SPI_MOSI_C
Text GLabel 6425 8350 2    45   Output ~ 0
SPI_NCS_0_C
Text GLabel 4800 7250 0    45   BiDi ~ 0
GPIO1_C
Text GLabel 5175 7850 0    45   Output ~ 0
TXD8_H
Text GLabel 5175 7750 0    45   Output ~ 0
TXD6_H
Text GLabel 5175 7550 0    45   Output ~ 0
TXD2_H
Text GLabel 6900 8150 2    45   Output ~ 0
TXIQSEL_H
Text GLabel 5175 8450 0    45   Output ~ 0
SPI_CLK_C
Text GLabel 6900 8250 2    45   Output ~ 0
TXEN_H
Text GLabel 5175 7950 0    45   Output ~ 0
TXD10_H
Text GLabel 6450 7950 2    45   Output ~ 0
TXD11_H
Text GLabel 6450 7450 2    45   Output ~ 0
TXD1_H
Text GLabel 6450 7550 2    45   Output ~ 0
TXD3_H
Text GLabel 6450 7650 2    45   Output ~ 0
TXD5_H
Text GLabel 6450 7850 2    45   Output ~ 0
TXD9_H
Text GLabel 6450 7750 2    45   Output ~ 0
TXD7_H
Text GLabel 5175 7650 0    45   Output ~ 0
TXD4_H
Text GLabel 5175 7450 0    45   Output ~ 0
TXD0_H
Text GLabel 6875 7050 2    45   Input ~ 0
RXCLK_C
$Comp
L GND #028
U 1 1 51E55CD0
P 5375 7350
F 0 "#028" H 5425 7400 50  0001 C CNN
F 1 "GND" H 5375 7290 50  0000 C CNN
F 2 "" H 5375 7350 60  0001 C CNN
F 3 "" H 5375 7350 60  0001 C CNN
	1    5375 7350
	0    1    1    0   
$EndComp
$Comp
L GND #029
U 1 1 51E55CD6
P 6250 7350
F 0 "#029" H 6300 7400 50  0001 C CNN
F 1 "GND" H 6250 7290 50  0000 C CNN
F 2 "" H 6250 7350 60  0001 C CNN
F 3 "" H 6250 7350 60  0001 C CNN
	1    6250 7350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1925 4350 1725 4350
Wire Wire Line
	1300 4650 1925 4650
Wire Wire Line
	1300 4425 1925 4425
Wire Wire Line
	1725 5025 1925 5025
Wire Wire Line
	3150 4800 2950 4800
Wire Wire Line
	2950 6425 3150 6425
Wire Wire Line
	2950 5250 3150 5250
Wire Wire Line
	1225 5550 1925 5550
Wire Wire Line
	2950 5550 3675 5550
Wire Wire Line
	1675 6425 1925 6425
Wire Wire Line
	2950 4575 3150 4575
Wire Wire Line
	2950 4200 3600 4200
Wire Wire Line
	2950 5100 3650 5100
Wire Wire Line
	2950 4650 3600 4650
Wire Wire Line
	1925 4800 1725 4800
Wire Wire Line
	1925 4125 1725 4125
Wire Wire Line
	1300 5325 1925 5325
Wire Wire Line
	1925 4575 1725 4575
Wire Wire Line
	2950 4350 3150 4350
Wire Wire Line
	2950 5325 3650 5325
Wire Wire Line
	2950 4875 3600 4875
Wire Wire Line
	2950 3975 3600 3975
Wire Wire Line
	2950 4425 3600 4425
Wire Wire Line
	2950 5025 3150 5025
Wire Wire Line
	1925 5475 1725 5475
Wire Wire Line
	2950 6500 3550 6500
Wire Wire Line
	2950 5475 3150 5475
Wire Wire Line
	1725 5700 1925 5700
Wire Wire Line
	1925 5250 1725 5250
Wire Wire Line
	1300 5100 1925 5100
Wire Wire Line
	1300 4200 1925 4200
Wire Wire Line
	1300 4875 1925 4875
Wire Wire Line
	3150 4125 2950 4125
Wire Wire Line
	3150 3900 2950 3900
Wire Wire Line
	1725 3900 1925 3900
Wire Wire Line
	1300 3975 1925 3975
Wire Wire Line
	2950 3625 3025 3625
Wire Wire Line
	3025 3625 3025 3700
Wire Wire Line
	3025 3700 2950 3700
Wire Wire Line
	1925 3625 1850 3625
Wire Wire Line
	1850 3625 1850 3700
Wire Wire Line
	1850 3700 1925 3700
Wire Wire Line
	2950 6150 3050 6150
Wire Wire Line
	3050 6150 3050 6225
Wire Wire Line
	3050 6225 2950 6225
Wire Wire Line
	1925 6150 1825 6150
Wire Wire Line
	1825 6150 1825 6225
Wire Wire Line
	1825 6225 1925 6225
Wire Wire Line
	2950 8675 3025 8675
Wire Wire Line
	3025 8675 3025 8750
Wire Wire Line
	3025 8750 2950 8750
Wire Wire Line
	1925 8675 1850 8675
Wire Wire Line
	1850 8600 1850 8750
Wire Wire Line
	1850 8750 1925 8750
Wire Wire Line
	1925 8600 1850 8600
Connection ~ 1850 8675
Wire Wire Line
	1925 4050 1750 4050
Wire Wire Line
	1750 1700 1750 8375
Wire Wire Line
	1750 4275 1925 4275
Connection ~ 1750 4050
Wire Wire Line
	1750 4500 1925 4500
Connection ~ 1750 4275
Wire Wire Line
	1750 4725 1925 4725
Connection ~ 1750 4500
Wire Wire Line
	1750 4950 1925 4950
Connection ~ 1750 4725
Wire Wire Line
	1750 5175 1925 5175
Connection ~ 1750 4950
Wire Wire Line
	1750 5400 1925 5400
Connection ~ 1750 5175
Wire Wire Line
	1750 5625 1925 5625
Connection ~ 1750 5400
Wire Wire Line
	1750 5850 1925 5850
Connection ~ 1750 5625
Wire Wire Line
	1750 6075 1925 6075
Connection ~ 1750 5850
Wire Wire Line
	1750 6575 1925 6575
Connection ~ 1750 6075
Wire Wire Line
	1750 6800 1925 6800
Connection ~ 1750 6575
Wire Wire Line
	1750 7025 1925 7025
Connection ~ 1750 6800
Wire Wire Line
	1750 7250 1925 7250
Connection ~ 1750 7025
Wire Wire Line
	1750 7475 1925 7475
Connection ~ 1750 7250
Wire Wire Line
	1750 7700 1925 7700
Connection ~ 1750 7475
Wire Wire Line
	1750 7925 1925 7925
Connection ~ 1750 7700
Wire Wire Line
	1750 8150 1925 8150
Connection ~ 1750 7925
Wire Wire Line
	1750 8375 1925 8375
Connection ~ 1750 8150
Wire Wire Line
	1925 6000 1700 6000
Wire Wire Line
	2950 6000 3150 6000
Wire Wire Line
	3125 5700 2950 5700
Wire Wire Line
	2950 6650 3175 6650
Wire Wire Line
	5175 6450 5575 6450
Wire Wire Line
	5175 6550 5575 6550
Wire Wire Line
	5175 6650 5575 6650
Wire Wire Line
	5175 6750 5575 6750
Wire Wire Line
	5175 6850 5575 6850
Wire Wire Line
	5175 6950 5575 6950
Wire Wire Line
	4800 7250 5575 7250
Wire Wire Line
	5575 7450 5175 7450
Wire Wire Line
	5175 7550 5575 7550
Wire Wire Line
	5575 7650 5175 7650
Wire Wire Line
	5175 7750 5575 7750
Wire Wire Line
	5575 7850 5175 7850
Wire Wire Line
	5175 7950 5575 7950
Wire Wire Line
	5575 8150 5175 8150
Wire Wire Line
	5175 8250 5575 8250
Wire Wire Line
	5575 8450 5175 8450
Wire Wire Line
	5175 8550 5575 8550
Wire Wire Line
	6075 8550 6425 8550
Wire Wire Line
	6400 8450 6075 8450
Wire Wire Line
	6075 8350 6425 8350
Wire Wire Line
	6900 8250 6075 8250
Wire Wire Line
	6900 8150 6075 8150
Wire Wire Line
	6075 8050 6900 8050
Wire Wire Line
	6450 7950 6075 7950
Wire Wire Line
	6075 7850 6450 7850
Wire Wire Line
	6075 7750 6450 7750
Wire Wire Line
	6450 7650 6075 7650
Wire Wire Line
	6075 7550 6450 7550
Wire Wire Line
	6450 7450 6075 7450
Wire Wire Line
	6875 7250 6075 7250
Wire Wire Line
	6075 7150 6875 7150
Wire Wire Line
	6875 7050 6075 7050
Wire Wire Line
	6075 6950 6450 6950
Wire Wire Line
	6450 6850 6075 6850
Wire Wire Line
	6075 6750 6450 6750
Wire Wire Line
	6450 6650 6075 6650
Wire Wire Line
	6075 6550 6450 6550
Wire Wire Line
	6450 6450 6075 6450
Wire Wire Line
	6075 7350 6200 7350
$Comp
L PWR_FLAG #FLG030
U 1 1 51E9E8BD
P 2025 1625
F 0 "#FLG030" H 2025 1550 30  0001 C CNN
F 1 "PWR_FLAG" H 2025 1675 30  0000 C CNN
F 2 "~" H 2025 1625 60  0000 C CNN
F 3 "~" H 2025 1625 60  0000 C CNN
	1    2025 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2025 1650 2025 1800
Connection ~ 1750 1800
Wire Wire Line
	2025 1800 1750 1800
$Comp
L ASP-122952-01_(HSMC) J3
U 1 1 51F7F379
P 2450 4525
F 0 "J3" H 2400 7125 60  0000 C CNN
F 1 "ASP-122952-01_(HSMC)" H 2450 7225 60  0001 C CNN
F 2 "HSMC" H 2400 7125 60  0001 C CNN
F 3 "" H 2675 4500 60  0000 C CNN
F 4 "HSMC" H 2500 7425 60  0001 C CNN "Description"
F 5 "ASP-122952-01" H 2600 7525 60  0001 C CNN "Manufacturer Part Number"
F 6 "Samtec" H 2700 7625 60  0001 C CNN "Manufacturer"
F 7 "Samtec" H 2800 7725 60  0001 C CNN "Vendor"
F 8 "ASP-122952-01" H 2900 7825 60  0001 C CNN "Vendor Part Number"
F 9 "ASP-122952-01_(HSMC)" H 2450 125 50  0000 C CNN "Component Value"
	1    2450 4525
	1    0    0    -1  
$EndComp
Text GLabel 1325 6500 0    45   BiDi ~ 0
GPIO3_C
Wire Wire Line
	1325 6500 1925 6500
Text GLabel 1675 6650 0    45   BiDi ~ 0
MIPI_CLK_C
Text GLabel 1225 6725 0    45   BiDi ~ 0
MIPI_DATA_C
Wire Wire Line
	1225 6725 1925 6725
Wire Wire Line
	1675 6650 1925 6650
Text GLabel 3450 6875 2    45   BiDi ~ 0
SCL_C
Text GLabel 3150 6800 2    45   BiDi ~ 0
SDA_C
Wire Wire Line
	3150 6800 2950 6800
Wire Wire Line
	3450 6875 2950 6875
Wire Wire Line
	5575 7150 5450 7150
Wire Wire Line
	5450 7150 5450 6200
$Comp
L VDIO #PWR031
U 1 1 5261A1C3
P 5450 6200
F 0 "#PWR031" H 5500 6175 20  0001 C CNN
F 1 "VDIO" H 5450 6325 50  0000 C CNN
F 2 "~" H 5450 6200 60  0000 C CNN
F 3 "~" H 5450 6200 60  0000 C CNN
	1    5450 6200
	1    0    0    -1  
$EndComp
Text GLabel 4775 8350 0    45   BiDi ~ 0
GPIO3_C
Wire Wire Line
	4775 8050 5575 8050
Wire Wire Line
	4775 8350 5575 8350
Wire Wire Line
	4800 7050 5575 7050
Text GLabel 5425 8650 0    45   BiDi ~ 0
MIPI_CLK_C
Text GLabel 5425 8750 0    45   BiDi ~ 0
MIPI_DATA_C
Wire Wire Line
	5575 8650 5425 8650
Wire Wire Line
	5425 8750 5575 8750
Text GLabel 6325 8750 2    45   BiDi ~ 0
SCL_C
Text GLabel 6325 8650 2    45   BiDi ~ 0
SDA_C
Wire Wire Line
	6075 8650 6325 8650
Wire Wire Line
	6075 8750 6325 8750
$Comp
L PINHEADER2X25 J7
U 1 1 52622759
P 5725 6400
F 0 "J7" H 5825 6450 50  0000 C CNN
F 1 "PINHEADER2X25" V 5825 5350 60  0000 C CNN
F 2 "PinHeader2x25SMD" H 5825 6600 60  0001 C CNN
F 3 "" H 5725 6400 60  0000 C CNN
F 4 "DOUBLE ROW, SMT HEADER, -2X50 W, TIN PLATED," H 5675 6700 60  0001 C CNN "Description"
F 5 "95278-101-50LF" H 5775 6800 60  0001 C CNN "Manufacturer Part Number"
F 6 "FCI" H 5775 6900 60  0001 C CNN "Manufacturer"
F 7 "RS" H 5775 7000 60  0001 C CNN "Vendor"
F 8 "673-7341" H 5775 7100 60  0001 C CNN "Vendor Part Number"
F 9 "Pin Header 2x25 SMD" H 5800 3850 50  0000 C CNN "Component Value"
	1    5725 6400
	1    0    0    -1  
$EndComp
$Comp
L GND #032
U 1 1 526227AB
P 5250 8975
F 0 "#032" H 5300 9025 50  0001 C CNN
F 1 "GND" H 5250 8915 50  0000 C CNN
F 2 "" H 5250 8975 60  0001 C CNN
F 3 "" H 5250 8975 60  0001 C CNN
	1    5250 8975
	1    0    0    -1  
$EndComp
$Comp
L GND #033
U 1 1 526227B2
P 6350 8975
F 0 "#033" H 6400 9025 50  0001 C CNN
F 1 "GND" H 6350 8915 50  0000 C CNN
F 2 "" H 6350 8975 60  0001 C CNN
F 3 "" H 6350 8975 60  0001 C CNN
	1    6350 8975
	1    0    0    -1  
$EndComp
Wire Wire Line
	6075 8850 6350 8850
Wire Wire Line
	6350 8850 6350 8925
Wire Wire Line
	5250 8925 5250 8850
Wire Wire Line
	5250 8850 5575 8850
Wire Wire Line
	5575 7350 5425 7350
Text GLabel 1650 6875 0    45   Output ~ 0
SPI_NCS_3
Wire Wire Line
	1925 6875 1650 6875
$EndSCHEMATC
