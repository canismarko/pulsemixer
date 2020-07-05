EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date "2020-06-26"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0114
U 1 1 5EF2F217
P 6550 1150
F 0 "#PWR0114" H 6550 900 50  0001 C CNN
F 1 "GND" V 6555 1022 50  0000 R CNN
F 2 "" H 6550 1150 50  0001 C CNN
F 3 "" H 6550 1150 50  0001 C CNN
	1    6550 1150
	-1   0    0    1   
$EndComp
Text Label 7350 2950 2    50   ~ 0
INTBTN
Text Label 7350 2850 2    50   ~ 0
INTVOL
Text Label 2350 1200 2    50   ~ 0
LCD_V0
$Comp
L power:GND #PWR0102
U 1 1 5F0452C1
P 2150 900
F 0 "#PWR0102" H 2150 650 50  0001 C CNN
F 1 "GND" V 2150 700 50  0000 C CNN
F 2 "" H 2150 900 50  0001 C CNN
F 3 "" H 2150 900 50  0001 C CNN
	1    2150 900 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 900  1950 900 
Wire Wire Line
	1950 1100 1850 1100
Wire Wire Line
	1850 1000 1950 1000
Connection ~ 1950 1000
Wire Wire Line
	1950 1000 1950 1100
Wire Wire Line
	1850 900  1950 900 
Connection ~ 1950 900 
Wire Wire Line
	1950 900  1950 1000
Wire Wire Line
	1850 800  2150 800 
Wire Wire Line
	1850 1200 2350 1200
Text Label 2350 1400 2    50   ~ 0
SCK
Text Label 2350 1300 2    50   ~ 0
SDA
Wire Wire Line
	1850 1300 2350 1300
Wire Wire Line
	1850 1400 2350 1400
Text Label 5100 2150 0    50   ~ 0
SDA
Text Label 5100 2050 0    50   ~ 0
SCK
Wire Wire Line
	6050 2050 5700 2050
Wire Wire Line
	6050 2150 5350 2150
$Comp
L power:+5V #PWR0101
U 1 1 5F051CEA
P 2150 800
F 0 "#PWR0101" H 2150 650 50  0001 C CNN
F 1 "+5V" V 2150 900 50  0000 L CNN
F 2 "" H 2150 800 50  0001 C CNN
F 3 "" H 2150 800 50  0001 C CNN
	1    2150 800 
	0    1    1    0   
$EndComp
$Comp
L Device:R R102
U 1 1 5F055ADD
P 5700 1800
F 0 "R102" H 5770 1846 50  0000 L CNN
F 1 "4.7K" H 5770 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5630 1800 50  0001 C CNN
F 3 "~" H 5700 1800 50  0001 C CNN
	1    5700 1800
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R101
U 1 1 5F0560CA
P 5350 1800
F 0 "R101" H 5420 1846 50  0000 L CNN
F 1 "4.7K" H 5420 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5280 1800 50  0001 C CNN
F 3 "~" H 5350 1800 50  0001 C CNN
	1    5350 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5700 1950 5700 2050
Connection ~ 5700 2050
Wire Wire Line
	5700 2050 5100 2050
Wire Wire Line
	5350 1950 5350 2150
Connection ~ 5350 2150
Wire Wire Line
	5350 2150 5100 2150
$Comp
L power:+5V #PWR0109
U 1 1 5F05785F
P 5100 1550
F 0 "#PWR0109" H 5100 1400 50  0001 C CNN
F 1 "+5V" V 5115 1678 50  0000 L CNN
F 2 "" H 5100 1550 50  0001 C CNN
F 3 "" H 5100 1550 50  0001 C CNN
	1    5100 1550
	0    -1   1    0   
$EndComp
Wire Wire Line
	5100 1550 5350 1550
Wire Wire Line
	5700 1550 5700 1650
Wire Wire Line
	5350 1650 5350 1550
Connection ~ 5350 1550
Wire Wire Line
	5350 1550 5700 1550
$Sheet
S 700  1950 1150 950 
U 5F07127F
F0 "Channel1" 50
F1 "pulsemixer_channel.sch" 50
F2 "SCK" I R 1850 2600 50 
F3 "SDA" I R 1850 2500 50 
F4 "A0" I R 1850 2100 50 
F5 "A1" I R 1850 2200 50 
F6 "A2" I R 1850 2300 50 
F7 "INT_VOL" I R 1850 2700 50 
F8 "INT_BTN" I R 1850 2800 50 
F9 "RESET" I R 1850 2000 50 
F10 "LCD_V0" I R 1850 2400 50 
$EndSheet
Text Label 2150 2400 2    50   ~ 0
LCD_V0
$Comp
L power:GND #PWR0104
U 1 1 5F07128E
P 2150 2200
F 0 "#PWR0104" H 2150 1950 50  0001 C CNN
F 1 "GND" V 2150 2000 50  0000 C CNN
F 2 "" H 2150 2200 50  0001 C CNN
F 3 "" H 2150 2200 50  0001 C CNN
	1    2150 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 2300 1850 2300
Wire Wire Line
	1850 2200 1950 2200
Wire Wire Line
	1950 2200 1950 2300
Wire Wire Line
	1850 2000 1950 2000
Wire Wire Line
	1850 2400 2150 2400
Text Label 2150 2600 2    50   ~ 0
SCK
Text Label 2150 2500 2    50   ~ 0
SDA
Wire Wire Line
	1850 2500 2150 2500
Wire Wire Line
	1850 2600 2150 2600
$Comp
L power:+5V #PWR0103
U 1 1 5F0712A8
P 2150 2000
F 0 "#PWR0103" H 2150 1850 50  0001 C CNN
F 1 "+5V" V 2150 2100 50  0000 L CNN
F 2 "" H 2150 2000 50  0001 C CNN
F 3 "" H 2150 2000 50  0001 C CNN
	1    2150 2000
	0    1    1    0   
$EndComp
$Sheet
S 700  3150 1150 950 
U 5F077D2B
F0 "Channel2" 50
F1 "pulsemixer_channel.sch" 50
F2 "SCK" I R 1850 3800 50 
F3 "SDA" I R 1850 3700 50 
F4 "A0" I R 1850 3300 50 
F5 "A1" I R 1850 3400 50 
F6 "A2" I R 1850 3500 50 
F7 "INT_VOL" I R 1850 3900 50 
F8 "INT_BTN" I R 1850 4000 50 
F9 "RESET" I R 1850 3200 50 
F10 "LCD_V0" I R 1850 3600 50 
$EndSheet
Text Label 2150 3600 2    50   ~ 0
LCD_V0
$Comp
L power:GND #PWR0106
U 1 1 5F077D3A
P 2150 3300
F 0 "#PWR0106" H 2150 3050 50  0001 C CNN
F 1 "GND" V 2150 3100 50  0000 C CNN
F 2 "" H 2150 3300 50  0001 C CNN
F 3 "" H 2150 3300 50  0001 C CNN
	1    2150 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1850 3400 1950 3400
Wire Wire Line
	1850 3200 1950 3200
Wire Wire Line
	1850 3600 2150 3600
Text Label 2150 3800 2    50   ~ 0
SCK
Text Label 2150 3700 2    50   ~ 0
SDA
Wire Wire Line
	1850 3700 2150 3700
Wire Wire Line
	1850 3800 2150 3800
$Comp
L power:+5V #PWR0105
U 1 1 5F077D54
P 2150 3200
F 0 "#PWR0105" H 2150 3050 50  0001 C CNN
F 1 "+5V" V 2150 3300 50  0000 L CNN
F 2 "" H 2150 3200 50  0001 C CNN
F 3 "" H 2150 3200 50  0001 C CNN
	1    2150 3200
	0    1    1    0   
$EndComp
$Sheet
S 700  4350 1150 950 
U 5F077D67
F0 "Channel3" 50
F1 "pulsemixer_channel.sch" 50
F2 "SCK" I R 1850 5000 50 
F3 "SDA" I R 1850 4900 50 
F4 "A0" I R 1850 4500 50 
F5 "A1" I R 1850 4600 50 
F6 "A2" I R 1850 4700 50 
F7 "INT_VOL" I R 1850 5100 50 
F8 "INT_BTN" I R 1850 5200 50 
F9 "RESET" I R 1850 4400 50 
F10 "LCD_V0" I R 1850 4800 50 
$EndSheet
Text Label 2150 4800 2    50   ~ 0
LCD_V0
$Comp
L power:GND #PWR0108
U 1 1 5F077D76
P 2150 4600
F 0 "#PWR0108" H 2150 4350 50  0001 C CNN
F 1 "GND" V 2150 4400 50  0000 C CNN
F 2 "" H 2150 4600 50  0001 C CNN
F 3 "" H 2150 4600 50  0001 C CNN
	1    2150 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2050 4700 1850 4700
Wire Wire Line
	1850 4600 1950 4600
Wire Wire Line
	1850 4500 1950 4500
Wire Wire Line
	1950 4500 1950 4600
Wire Wire Line
	1850 4400 1950 4400
Wire Wire Line
	1850 4800 2150 4800
Text Label 2150 5000 2    50   ~ 0
SCK
Text Label 2150 4900 2    50   ~ 0
SDA
Wire Wire Line
	1850 4900 2150 4900
Wire Wire Line
	1850 5000 2150 5000
$Comp
L power:+5V #PWR0107
U 1 1 5F077D90
P 2150 4400
F 0 "#PWR0107" H 2150 4250 50  0001 C CNN
F 1 "+5V" V 2150 4500 50  0000 L CNN
F 2 "" H 2150 4400 50  0001 C CNN
F 3 "" H 2150 4400 50  0001 C CNN
	1    2150 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 2100 1950 2100
Wire Wire Line
	1950 2100 1950 2000
Connection ~ 1950 2000
Wire Wire Line
	1950 2000 2150 2000
Wire Wire Line
	1950 2200 2150 2200
Connection ~ 1950 2200
Wire Wire Line
	1850 3300 2050 3300
Wire Wire Line
	2050 3500 2050 3300
Wire Wire Line
	1850 3500 2050 3500
Connection ~ 2050 3300
Wire Wire Line
	1950 3400 1950 3200
Connection ~ 1950 3200
Wire Wire Line
	1950 3200 2150 3200
Wire Wire Line
	2050 3300 2150 3300
Wire Wire Line
	1950 4500 1950 4400
Connection ~ 1950 4500
Connection ~ 1950 4400
Wire Wire Line
	1950 4400 2150 4400
$Comp
L Device:R_POT RV101
U 1 1 5F0A72F9
P 8500 3750
F 0 "RV101" H 8430 3704 50  0000 R CNN
F 1 "10K" H 8430 3795 50  0000 R CNN
F 2 "pulsemixer_pcb:TRIM_3352T-1-103LF" H 8500 3750 50  0001 C CNN
F 3 "~" H 8500 3750 50  0001 C CNN
	1    8500 3750
	-1   0    0    1   
$EndComp
Text Label 8050 3750 0    50   ~ 0
LCD_V0
Wire Wire Line
	8050 3750 8350 3750
$Comp
L power:+5V #PWR0110
U 1 1 5F0AB525
P 8500 3500
F 0 "#PWR0110" H 8500 3350 50  0001 C CNN
F 1 "+5V" H 8515 3673 50  0000 C CNN
F 2 "" H 8500 3500 50  0001 C CNN
F 3 "" H 8500 3500 50  0001 C CNN
	1    8500 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5F0AB985
P 8500 4000
F 0 "#PWR0111" H 8500 3750 50  0001 C CNN
F 1 "GND" H 8505 3827 50  0000 C CNN
F 2 "" H 8500 4000 50  0001 C CNN
F 3 "" H 8500 4000 50  0001 C CNN
	1    8500 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3900 8500 4000
Wire Wire Line
	8500 3600 8500 3500
Wire Notes Line
	7900 3150 7900 4300
Wire Notes Line
	7900 4300 8800 4300
Wire Notes Line
	8800 4300 8800 3150
Wire Notes Line
	8800 3150 7900 3150
Text Notes 7950 3250 0    50   ~ 0
LCD Contrast Pot
$Comp
L freetronics_schematic:SW_PUSHBUTTON SW103
U 1 1 5F0C25B5
P 9300 2250
F 0 "SW103" H 9300 2515 50  0000 C CNN
F 1 "SW_STRM_DEV" H 9300 2424 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 9300 2250 60  0001 C CNN
F 3 "" H 9300 2250 60  0000 C CNN
	1    9300 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R105
U 1 1 5F0C2970
P 8450 2150
F 0 "R105" V 8243 2150 50  0000 C CNN
F 1 "10K" V 8334 2150 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 8380 2150 50  0001 C CNN
F 3 "~" H 8450 2150 50  0001 C CNN
	1    8450 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 2150 8600 2150
$Comp
L power:GND #PWR0116
U 1 1 5F0CD387
P 9800 2250
F 0 "#PWR0116" H 9800 2000 50  0001 C CNN
F 1 "GND" V 9805 2122 50  0000 R CNN
F 2 "" H 9800 2250 50  0001 C CNN
F 3 "" H 9800 2250 50  0001 C CNN
	1    9800 2250
	0    -1   -1   0   
$EndComp
Text Label 7050 2250 0    50   ~ 0
STRM_DEV
Wire Wire Line
	9600 2250 9700 2250
Text Label 7050 2350 0    50   ~ 0
STRM_DEV_LED
$Comp
L freetronics_schematic:SW_PUSHBUTTON SW101
U 1 1 5F0FEA67
P 9300 1450
F 0 "SW101" H 9300 1715 50  0000 C CNN
F 1 "SW_PG_RIGHT" H 9300 1624 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 9300 1450 60  0001 C CNN
F 3 "" H 9300 1450 60  0000 C CNN
	1    9300 1450
	1    0    0    -1  
$EndComp
$Comp
L freetronics_schematic:SW_PUSHBUTTON SW102
U 1 1 5F0FEEA0
P 9300 1850
F 0 "SW102" H 9300 2115 50  0000 C CNN
F 1 "SW_PG_LEFT" H 9300 2024 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 9300 1850 60  0001 C CNN
F 3 "" H 9300 1850 60  0000 C CNN
	1    9300 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2250 9700 1850
Wire Wire Line
	9700 1850 9600 1850
Connection ~ 9700 2250
Wire Wire Line
	9700 2250 9800 2250
Wire Wire Line
	9700 1850 9700 1450
Wire Wire Line
	9700 1450 9600 1450
Connection ~ 9700 1850
Wire Wire Line
	7050 2250 8200 2250
Wire Wire Line
	8300 2150 8200 2150
Wire Wire Line
	8200 2150 8200 2250
Connection ~ 8200 2250
Wire Wire Line
	8200 2250 9000 2250
Wire Wire Line
	9000 1850 8200 1850
Wire Wire Line
	9000 1450 8200 1450
$Comp
L Device:R R104
U 1 1 5F12D626
P 8450 1750
F 0 "R104" V 8243 1750 50  0000 C CNN
F 1 "10K" V 8334 1750 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 8380 1750 50  0001 C CNN
F 3 "~" H 8450 1750 50  0001 C CNN
	1    8450 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 1750 8600 1750
Wire Wire Line
	8300 1750 8200 1750
Wire Wire Line
	8200 1750 8200 1850
$Comp
L Device:R R103
U 1 1 5F131AF4
P 8450 1350
F 0 "R103" V 8243 1350 50  0000 C CNN
F 1 "10K" V 8334 1350 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 8380 1350 50  0001 C CNN
F 3 "~" H 8450 1350 50  0001 C CNN
	1    8450 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 1350 8600 1350
Wire Wire Line
	8300 1350 8200 1350
Wire Wire Line
	8200 1350 8200 1450
$Comp
L power:+5V #PWR0117
U 1 1 5F15B93A
P 9800 2400
F 0 "#PWR0117" H 9800 2250 50  0001 C CNN
F 1 "+5V" V 9815 2528 50  0000 L CNN
F 2 "" H 9800 2400 50  0001 C CNN
F 3 "" H 9800 2400 50  0001 C CNN
	1    9800 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 2400 8700 2400
Wire Wire Line
	8700 2400 8700 2150
Wire Wire Line
	8700 2150 8700 1750
Connection ~ 8700 2150
Wire Wire Line
	8700 1350 8700 1750
Connection ~ 8700 1750
Text Label 7050 2050 0    50   ~ 0
PAGE_RIGHT_BTN
Text Label 7050 2150 0    50   ~ 0
PAGE_LEFT_BTN
$Comp
L power:+5V #PWR0113
U 1 1 5EF2D970
P 6350 3950
F 0 "#PWR0113" H 6350 3800 50  0001 C CNN
F 1 "+5V" V 6365 4078 50  0000 L CNN
F 2 "" H 6350 3950 50  0001 C CNN
F 3 "" H 6350 3950 50  0001 C CNN
	1    6350 3950
	-1   0    0    1   
$EndComp
$Sheet
S 700  750  1150 950 
U 5EF5CDBF
F0 "Channel0" 50
F1 "pulsemixer_channel.sch" 50
F2 "SCK" I R 1850 1400 50 
F3 "SDA" I R 1850 1300 50 
F4 "A0" I R 1850 900 50 
F5 "A1" I R 1850 1000 50 
F6 "A2" I R 1850 1100 50 
F7 "INT_VOL" I R 1850 1500 50 
F8 "INT_BTN" I R 1850 1600 50 
F9 "RESET" I R 1850 800 50 
F10 "LCD_V0" I R 1850 1200 50 
$EndSheet
Wire Wire Line
	6450 1550 6450 1450
Wire Wire Line
	6450 1450 6550 1450
Connection ~ 6550 1450
Wire Wire Line
	6550 1450 6550 1550
$Comp
L Device:R R106
U 1 1 5F2017D9
P 8450 2600
F 0 "R106" H 8380 2554 50  0000 R CNN
F 1 "150" H 8380 2645 50  0000 R CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 8380 2600 50  0001 C CNN
F 3 "~" H 8450 2600 50  0001 C CNN
	1    8450 2600
	0    1    -1   0   
$EndComp
$Comp
L Device:LED D109
U 1 1 5F203208
P 8850 2600
F 0 "D109" V 8889 2482 50  0000 R CNN
F 1 "LED" V 8798 2482 50  0000 R CNN
F 2 "LEDs:LED_1206_HandSoldering" H 8850 2600 50  0001 C CNN
F 3 "~" H 8850 2600 50  0001 C CNN
	1    8850 2600
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5F2036B3
P 9100 2600
F 0 "#PWR0115" H 9100 2350 50  0001 C CNN
F 1 "GND" H 9105 2427 50  0000 C CNN
F 2 "" H 9100 2600 50  0001 C CNN
F 3 "" H 9100 2600 50  0001 C CNN
	1    9100 2600
	0    -1   1    0   
$EndComp
Wire Wire Line
	9000 2600 9100 2600
Wire Wire Line
	8600 2600 8700 2600
Wire Wire Line
	7750 2350 7750 2600
Wire Wire Line
	7050 2350 7750 2350
$Comp
L MCU_Module:Arduino_Nano_v3.x A101
U 1 1 5F2142C3
P 6550 2550
F 0 "A101" H 6300 1600 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 6150 1500 50  0000 C CNN
F 2 "pulsemixer_pcb:SHIELD_ARDUINO_NANO" H 6550 2550 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6550 2550 50  0001 C CNN
	1    6550 2550
	-1   0    0    1   
$EndComp
NoConn ~ 6450 3550
NoConn ~ 6650 3550
Wire Wire Line
	7050 2150 8100 2150
Wire Wire Line
	8100 2150 8100 1850
Wire Wire Line
	8100 1850 8200 1850
Connection ~ 8200 1850
Wire Wire Line
	7050 2050 8000 2050
Wire Wire Line
	8000 2050 8000 1450
Wire Wire Line
	8000 1450 8200 1450
Connection ~ 8200 1450
NoConn ~ 6050 2750
NoConn ~ 6050 2550
NoConn ~ 6050 2450
NoConn ~ 6050 2350
NoConn ~ 6050 2250
NoConn ~ 6050 1950
NoConn ~ 6050 1850
NoConn ~ 6050 3050
NoConn ~ 6050 3150
NoConn ~ 7050 3150
NoConn ~ 7050 3050
NoConn ~ 7050 1850
NoConn ~ 7050 1950
Wire Wire Line
	6550 1250 6550 1450
Wire Wire Line
	6550 1150 6550 1250
Connection ~ 6550 1250
Wire Wire Line
	6550 1250 6450 1250
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F1E9722
P 6450 1250
F 0 "#FLG0101" H 6450 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 6450 1423 50  0000 C CNN
F 2 "" H 6450 1250 50  0001 C CNN
F 3 "~" H 6450 1250 50  0001 C CNN
	1    6450 1250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7750 2600 8300 2600
Wire Notes Line
	7900 1000 7900 3000
Wire Notes Line
	7900 3000 10200 3000
Wire Notes Line
	10200 3000 10200 1000
Wire Notes Line
	10200 1000 7900 1000
Text Notes 7950 1100 0    50   ~ 0
Master Controls
Wire Notes Line
	4650 750  7700 750 
Wire Notes Line
	7700 750  7700 4400
Wire Notes Line
	7700 4400 4650 4400
Wire Notes Line
	4650 4400 4650 750 
Text Notes 4700 850  0    50   ~ 0
Arduino Nano MCU
$Comp
L Device:C C101
U 1 1 5F3A4DCE
P 6200 3850
F 0 "C101" V 6452 3850 50  0000 C CNN
F 1 "10µ" V 6361 3850 50  0000 C CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.00mm" H 6238 3700 50  0001 C CNN
F 3 "~" H 6200 3850 50  0001 C CNN
	1    6200 3850
	0    1    -1   0   
$EndComp
Connection ~ 6350 3850
Wire Wire Line
	6350 3850 6350 3950
Wire Wire Line
	6350 3550 6350 3850
$Comp
L power:GND #PWR0112
U 1 1 5F3C7B34
P 5950 3850
F 0 "#PWR0112" H 5950 3600 50  0001 C CNN
F 1 "GND" V 5955 3722 50  0000 R CNN
F 2 "" H 5950 3850 50  0001 C CNN
F 3 "" H 5950 3850 50  0001 C CNN
	1    5950 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 3850 6050 3850
Wire Wire Line
	2050 4700 2050 4600
Wire Wire Line
	2050 4600 2150 4600
$Comp
L pulsemixer_pcb:SN74LHC08DR U101
U 1 1 5F0146C3
P 1700 6050
F 0 "U101" H 1700 6250 50  0000 C CNN
F 1 "SN74LHC08DR" H 1700 5850 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 1700 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls00" V 1700 6050 50  0001 C CNN
	1    1700 6050
	1    0    0    -1  
$EndComp
$Comp
L pulsemixer_pcb:SN74LHC08DR U101
U 2 1 5F01611C
P 1700 6600
F 0 "U101" H 1700 6800 50  0000 C CNN
F 1 "SN74LHC08DR" H 1700 6400 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 1700 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls00" V 1700 6600 50  0001 C CNN
	2    1700 6600
	1    0    0    -1  
$EndComp
$Comp
L pulsemixer_pcb:SN74LHC08DR U101
U 3 1 5F0168EE
P 3350 6050
F 0 "U101" H 3350 6250 50  0000 C CNN
F 1 "SN74LHC08DR" H 3350 5850 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 3350 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls00" V 3350 6050 50  0001 C CNN
	3    3350 6050
	1    0    0    -1  
$EndComp
$Comp
L pulsemixer_pcb:SN74LHC08DR U101
U 4 1 5F026371
P 3350 6600
F 0 "U101" H 3350 6800 50  0000 C CNN
F 1 "SN74LHC08DR" H 3350 6400 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 3350 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls00" V 3350 6600 50  0001 C CNN
	4    3350 6600
	1    0    0    -1  
$EndComp
Text Label 7350 2450 2    50   ~ 0
INTCH0
Text Label 7350 2550 2    50   ~ 0
INTCH1
Text Label 7350 2650 2    50   ~ 0
INTCH2
Text Label 7350 2750 2    50   ~ 0
INTCH3
Wire Wire Line
	7050 2750 7350 2750
Wire Wire Line
	7350 2650 7050 2650
Wire Wire Line
	7050 2550 7350 2550
Wire Wire Line
	7350 2450 7050 2450
Wire Wire Line
	7350 2850 7050 2850
Wire Wire Line
	7050 2950 7350 2950
$Comp
L pulsemixer_pcb:SN74LHC08DR U101
U 5 1 5F06B4E4
P 2400 7250
F 0 "U101" H 2400 7617 50  0000 C CNN
F 1 "SN74LHC08DR" H 2400 7526 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 2400 7250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74ls00" V 2400 7250 50  0001 C CNN
	5    2400 7250
	1    0    0    -1  
$EndComp
Text Label 2350 1500 2    50   ~ 0
INTVOL_CH0
Text Label 2350 1600 2    50   ~ 0
INTBTN_CH0
Wire Wire Line
	1850 1600 2350 1600
Wire Wire Line
	2350 1500 1850 1500
Text Label 2350 2700 2    50   ~ 0
INTVOL_CH1
Text Label 2350 2800 2    50   ~ 0
INTBTN_CH1
Wire Wire Line
	1850 2800 2350 2800
Wire Wire Line
	2350 2700 1850 2700
Text Label 2350 3900 2    50   ~ 0
INTVOL_CH2
Text Label 2350 4000 2    50   ~ 0
INTBTN_CH2
Wire Wire Line
	1850 4000 2350 4000
Wire Wire Line
	2350 3900 1850 3900
Text Label 2350 5100 2    50   ~ 0
INTVOL_CH3
Text Label 2350 5200 2    50   ~ 0
INTBTN_CH3
Wire Wire Line
	1850 5200 2350 5200
Wire Wire Line
	2350 5100 1850 5100
Text Label 900  6150 0    50   ~ 0
INTVOL_CH0
Text Label 900  5950 0    50   ~ 0
INTBTN_CH0
Wire Wire Line
	1400 5950 900  5950
Wire Wire Line
	900  6150 1400 6150
Text Label 900  6700 0    50   ~ 0
INTVOL_CH1
Text Label 900  6500 0    50   ~ 0
INTBTN_CH1
Wire Wire Line
	1400 6500 900  6500
Wire Wire Line
	900  6700 1400 6700
Text Label 2550 6150 0    50   ~ 0
INTVOL_CH2
Text Label 2550 5950 0    50   ~ 0
INTBTN_CH2
Wire Wire Line
	3050 5950 2550 5950
Wire Wire Line
	2550 6150 3050 6150
Text Label 2550 6700 0    50   ~ 0
INTVOL_CH3
Text Label 2550 6500 0    50   ~ 0
INTBTN_CH3
Wire Wire Line
	3050 6500 2550 6500
Wire Wire Line
	2550 6700 3050 6700
Text Label 2350 6050 2    50   ~ 0
INTCH0
Text Label 2350 6600 2    50   ~ 0
INTCH1
Text Label 4000 6050 2    50   ~ 0
INTCH2
Text Label 4000 6600 2    50   ~ 0
INTCH3
Wire Wire Line
	4000 6600 3650 6600
Wire Wire Line
	4000 6050 3650 6050
Wire Wire Line
	2350 6050 2000 6050
Wire Wire Line
	2350 6600 2000 6600
$Comp
L power:+5V #PWR0134
U 1 1 5F1BC250
P 1700 7250
F 0 "#PWR0134" H 1700 7100 50  0001 C CNN
F 1 "+5V" V 1715 7378 50  0000 L CNN
F 2 "" H 1700 7250 50  0001 C CNN
F 3 "" H 1700 7250 50  0001 C CNN
	1    1700 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1700 7250 1800 7250
$Comp
L power:GND #PWR0135
U 1 1 5F1C8D0E
P 3100 7250
F 0 "#PWR0135" H 3100 7000 50  0001 C CNN
F 1 "GND" V 3105 7122 50  0000 R CNN
F 2 "" H 3100 7250 50  0001 C CNN
F 3 "" H 3100 7250 50  0001 C CNN
	1    3100 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 7250 3000 7250
$Comp
L pulsemixer_pcb:SN74HC21DR U102
U 1 1 5F1DAD0A
P 5650 5950
F 0 "U102" H 5650 6325 50  0000 C CNN
F 1 "SN74HC21DR" H 5650 6234 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 5650 5950 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4011bms-12bms-23bms.pdf" V 5650 5950 50  0001 C CNN
	1    5650 5950
	1    0    0    -1  
$EndComp
$Comp
L pulsemixer_pcb:SN74HC21DR U102
U 2 1 5F1DC053
P 5650 6600
F 0 "U102" H 5650 6975 50  0000 C CNN
F 1 "SN74HC21DR" H 5650 6884 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 5650 6600 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4011bms-12bms-23bms.pdf" V 5650 6600 50  0001 C CNN
	2    5650 6600
	1    0    0    -1  
$EndComp
$Comp
L pulsemixer_pcb:SN74HC21DR U102
U 3 1 5F1DDB9F
P 5650 7250
F 0 "U102" H 5650 7617 50  0000 C CNN
F 1 "SN74HC21DR" H 5650 7526 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" V 5650 7250 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4011bms-12bms-23bms.pdf" V 5650 7250 50  0001 C CNN
	3    5650 7250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C102
U 1 1 5F1DF7E5
P 2400 7600
F 0 "C102" V 2652 7600 50  0000 C CNN
F 1 "0.1µ" V 2561 7600 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2438 7450 50  0001 C CNN
F 3 "~" H 2400 7600 50  0001 C CNN
	1    2400 7600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 7250 3000 7600
Wire Wire Line
	3000 7600 2550 7600
Connection ~ 3000 7250
Wire Wire Line
	3000 7250 2900 7250
Wire Wire Line
	2250 7600 1800 7600
Wire Wire Line
	1800 7600 1800 7250
Connection ~ 1800 7250
Wire Wire Line
	1800 7250 1900 7250
$Comp
L power:+5V #PWR0136
U 1 1 5F206ED3
P 4950 7250
F 0 "#PWR0136" H 4950 7100 50  0001 C CNN
F 1 "+5V" V 4965 7378 50  0000 L CNN
F 2 "" H 4950 7250 50  0001 C CNN
F 3 "" H 4950 7250 50  0001 C CNN
	1    4950 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 7250 5050 7250
$Comp
L power:GND #PWR0137
U 1 1 5F206EDA
P 6350 7250
F 0 "#PWR0137" H 6350 7000 50  0001 C CNN
F 1 "GND" V 6355 7122 50  0000 R CNN
F 2 "" H 6350 7250 50  0001 C CNN
F 3 "" H 6350 7250 50  0001 C CNN
	1    6350 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 7250 6250 7250
$Comp
L Device:C C103
U 1 1 5F206EE1
P 5650 7600
F 0 "C103" V 5902 7600 50  0000 C CNN
F 1 "0.1µ" V 5811 7600 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5688 7450 50  0001 C CNN
F 3 "~" H 5650 7600 50  0001 C CNN
	1    5650 7600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 7250 6250 7600
Wire Wire Line
	6250 7600 5800 7600
Connection ~ 6250 7250
Wire Wire Line
	6250 7250 6150 7250
Wire Wire Line
	5500 7600 5050 7600
Wire Wire Line
	5050 7600 5050 7250
Connection ~ 5050 7250
Wire Wire Line
	5050 7250 5150 7250
Text Label 4850 5800 0    50   ~ 0
INTVOL_CH0
Text Label 4850 5900 0    50   ~ 0
INTVOL_CH1
Text Label 4850 6000 0    50   ~ 0
INTVOL_CH2
Text Label 4850 6100 0    50   ~ 0
INTVOL_CH3
Text Label 4850 6450 0    50   ~ 0
INTBTN_CH0
Text Label 4850 6550 0    50   ~ 0
INTBTN_CH1
Text Label 4850 6650 0    50   ~ 0
INTBTN_CH2
Text Label 4850 6750 0    50   ~ 0
INTBTN_CH3
Wire Wire Line
	4850 5900 5350 5900
Wire Wire Line
	4850 6000 5350 6000
Wire Wire Line
	4850 6100 5350 6100
Wire Wire Line
	4850 6450 5350 6450
Wire Wire Line
	4850 6550 5350 6550
Wire Wire Line
	4850 6650 5350 6650
Wire Wire Line
	4850 6750 5350 6750
Wire Wire Line
	4850 5800 5350 5800
Text Label 6250 5950 2    50   ~ 0
INTVOL
Wire Wire Line
	6250 5950 5950 5950
Text Label 6250 6600 2    50   ~ 0
INTBTN
Wire Wire Line
	6250 6600 5950 6600
Wire Notes Line
	850  5750 850  7750
Wire Notes Line
	850  7750 4100 7750
Wire Notes Line
	4100 7750 4100 5750
Wire Notes Line
	4100 5750 850  5750
Text Notes 850  5750 0    50   ~ 0
Per-Channel Interrupt Logic
Wire Notes Line
	4750 5450 4750 7750
Wire Notes Line
	4750 7750 6750 7750
Wire Notes Line
	6750 7750 6750 5450
Wire Notes Line
	6750 5450 4750 5450
Text Notes 4750 5450 0    50   ~ 0
Volume/Button Interrupt Logic
$EndSCHEMATC
