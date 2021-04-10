EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x03_Male J24
U 1 1 5E631D0A
P 7150 3500
F 0 "J24" H 7258 3781 50  0000 C CNN
F 1 "Conn_01x03_Male" H 7258 3690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7150 3500 50  0001 C CNN
F 3 "~" H 7150 3500 50  0001 C CNN
	1    7150 3500
	1    0    0    -1  
$EndComp
Text GLabel 7500 3400 2    50   Input ~ 0
USB_RX
Wire Wire Line
	7500 3400 7350 3400
Wire Wire Line
	7500 3500 7350 3500
Text GLabel 7500 3500 2    50   Output ~ 0
USB_TX
$Comp
L power:GND #PWR035
U 1 1 5E633ADA
P 7400 3650
F 0 "#PWR035" H 7400 3400 50  0001 C CNN
F 1 "GND" H 7405 3477 50  0000 C CNN
F 2 "" H 7400 3650 50  0001 C CNN
F 3 "" H 7400 3650 50  0001 C CNN
	1    7400 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3600 7400 3600
Wire Wire Line
	7400 3600 7400 3650
Text GLabel 5600 1750 1    50   Input ~ 0
VBUS1
Text GLabel 4400 5300 1    50   Input ~ 0
VBUS1
Wire Notes Line
	1300 850  1300 6800
Wire Notes Line
	6650 850  1300 850 
Wire Notes Line
	6650 6800 6650 850 
Wire Notes Line
	1300 6800 6650 6800
Text GLabel 6250 6200 3    50   3State ~ 0
progstm_Rx
Text GLabel 5750 6200 3    50   3State ~ 0
progstm_Tx
Text GLabel 4350 1850 2    50   3State ~ 0
progstm_Rx
Text GLabel 2650 1950 0    50   3State ~ 0
progstm_Tx
$Comp
L STM32F103RB-rescue:440247-2-USB_MINI_B-SNAPEDA-Door_Locking-rescue P2
U 1 1 5FA67A9A
P 4600 5600
F 0 "P2" H 4930 5646 50  0000 L CNN
F 1 "440247-2" H 4930 5555 50  0000 L CNN
F 2 "440247-2:TE_440247-2" H 4600 5600 50  0001 L BNN
F 3 "TE Connectivity" H 4600 5600 50  0001 L BNN
F 4 "None" H 4600 5600 50  0001 L BNN "Field4"
F 5 "440247-2" H 4600 5600 50  0001 L BNN "Field5"
F 6 "Unavailable" H 4600 5600 50  0001 L BNN "Field6"
F 7 "Mini USB B Type RCPT" H 4600 5600 50  0001 L BNN "Field7"
F 8 "440247-2" H 4600 5600 50  0001 L BNN "Field8"
F 9 "None" H 4600 5600 50  0001 L BNN "Field9"
F 10 "https://www.te.com/usa-en/product-440247-2.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 4600 5600 50  0001 L BNN "Field10"
	1    4600 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R6
U 1 1 5FA67A89
P 4550 2350
F 0 "R6" V 4345 2350 50  0000 C CNN
F 1 "10K" V 4436 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4590 2340 50  0001 C CNN
F 3 "~" H 4550 2350 50  0001 C CNN
	1    4550 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5800 4400 5900
Wire Wire Line
	4400 5900 4400 6000
Connection ~ 4400 5900
Wire Wire Line
	4350 5900 4400 5900
Wire Wire Line
	4350 5950 4350 5900
Wire Wire Line
	4300 5950 4350 5950
Wire Wire Line
	4300 5700 4400 5700
Wire Wire Line
	4300 5750 4300 5700
$Comp
L Device:R_Small R5
U 1 1 5FA67A78
P 4300 5850
F 0 "R5" H 4359 5896 50  0000 L CNN
F 1 "100k" H 4359 5805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4300 5850 50  0001 C CNN
F 3 "~" H 4300 5850 50  0001 C CNN
	1    4300 5850
	-1   0    0    1   
$EndComp
Text GLabel 4400 5600 0    50   Input ~ 0
1d+
Text GLabel 3700 5100 3    50   Input ~ 0
1d+
Text GLabel 3700 5550 1    50   Input ~ 0
1d-
Text GLabel 4400 5500 0    50   Input ~ 0
1d-
$Comp
L power:GND #PWR0109
U 1 1 5FA67A6A
P 3450 5600
F 0 "#PWR0109" H 3450 5350 50  0001 C CNN
F 1 "GND" H 3455 5427 50  0000 C CNN
F 2 "" H 3450 5600 50  0001 C CNN
F 3 "" H 3450 5600 50  0001 C CNN
	1    3450 5600
	1    0    0    -1  
$EndComp
Text GLabel 2450 6150 0    50   BiDi ~ 0
USB1_D-
Text GLabel 2450 5100 0    50   BiDi ~ 0
USB1_D+
Wire Wire Line
	2450 6150 2850 6150
Wire Wire Line
	2450 5100 2850 5100
Wire Wire Line
	3050 5100 3700 5100
$Comp
L Power_Protection:USBLC6-2SC6 U6
U 1 1 5FA67A5B
P 2950 5600
F 0 "U6" H 2950 6281 50  0000 C CNN
F 1 "USBLC6-2SC6" H 2950 6190 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 2200 6000 50  0001 C CNN
F 3 "http://www2.st.com/resource/en/datasheet/CD00050750.pdf" H 3150 5950 50  0001 C CNN
	1    2950 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 6150 2850 6100
Wire Wire Line
	3700 6100 3700 5550
Wire Wire Line
	3050 6100 3700 6100
Text GLabel 2450 5400 1    50   Input ~ 0
5v
Wire Wire Line
	2450 5400 2450 5600
Wire Wire Line
	5400 3300 5700 3300
Wire Wire Line
	5400 3250 5400 3300
Text GLabel 5400 3250 1    50   Input ~ 0
5v
Connection ~ 5400 3300
Wire Wire Line
	5100 3300 5400 3300
$Comp
L power:GND #PWR0108
U 1 1 5FA67A47
P 5600 2650
F 0 "#PWR0108" H 5600 2400 50  0001 C CNN
F 1 "GND" H 5605 2477 50  0000 C CNN
F 2 "" H 5600 2650 50  0001 C CNN
F 3 "" H 5600 2650 50  0001 C CNN
	1    5600 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5FA67A33
P 5600 1950
F 0 "R7" H 5659 1996 50  0000 L CNN
F 1 "1k" H 5659 1905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5600 1950 50  0001 C CNN
F 3 "~" H 5600 1950 50  0001 C CNN
	1    5600 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2650 5600 2400
Wire Wire Line
	5600 2050 5600 2100
Wire Wire Line
	5600 1850 5600 1750
$Comp
L Device:LED D4
U 1 1 5FA67A26
P 5600 2250
F 0 "D4" H 5593 2466 50  0000 C CNN
F 1 "LED" H 5593 2375 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 5600 2250 50  0001 C CNN
F 3 "~" H 5600 2250 50  0001 C CNN
	1    5600 2250
	0    -1   -1   0   
$EndComp
Text GLabel 4550 1650 2    50   Input ~ 0
5v
$Comp
L Device:R_Small R9
U 1 1 5FA67A1B
P 6250 5500
F 0 "R9" H 6309 5546 50  0000 L CNN
F 1 "1k" H 6309 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6250 5500 50  0001 C CNN
F 3 "~" H 6250 5500 50  0001 C CNN
	1    6250 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5FA67A11
P 5750 5500
F 0 "R8" H 5809 5546 50  0000 L CNN
F 1 "1k" H 5809 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5750 5500 50  0001 C CNN
F 3 "~" H 5750 5500 50  0001 C CNN
	1    5750 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5FA67A07
P 2500 1450
F 0 "R4" V 2304 1450 50  0000 C CNN
F 1 "4.7K" V 2395 1450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2500 1450 50  0001 C CNN
F 3 "~" H 2500 1450 50  0001 C CNN
	1    2500 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5300 4400 5400
$Comp
L power:GND #PWR0105
U 1 1 5FA679D8
P 4400 6000
F 0 "#PWR0105" H 4400 5750 50  0001 C CNN
F 1 "GND" H 4405 5827 50  0000 C CNN
F 2 "" H 4400 6000 50  0001 C CNN
F 3 "" H 4400 6000 50  0001 C CNN
	1    4400 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1650 4200 1650
Wire Wire Line
	4350 1550 4350 1650
Wire Wire Line
	4200 1550 4350 1550
Wire Wire Line
	4350 1850 4200 1850
Text GLabel 4450 1450 2    50   Input ~ 0
VDD1
Wire Wire Line
	4450 1450 4200 1450
Text GLabel 2400 2450 0    50   BiDi ~ 0
USB1_D-
Text GLabel 2400 2350 0    50   BiDi ~ 0
USB1_D+
Wire Wire Line
	2400 2350 2800 2350
Wire Wire Line
	2400 2450 2800 2450
Wire Wire Line
	4200 2550 4200 2650
$Comp
L STM32F103RB-rescue:CP2102-GM-CP2102-GM-Door_Locking-rescue U7
U 1 1 5FA679C1
P 3500 2050
F 0 "U7" H 3500 2917 50  0000 C CNN
F 1 "CP2102-GM" H 3500 2826 50  0000 C CNN
F 2 "CP2102-GM:QFN50P500X500X100-29N" H 3500 2050 50  0001 L BNN
F 3 "Silicon Labs" H 3500 2050 50  0001 L BNN
F 4 "336-1160-5-ND" H 3500 2050 50  0001 L BNN "Field4"
F 5 "Microcontroller Solutions - Interface Products USB to UART Bdg Chip" H 3500 2050 50  0001 L BNN "Field5"
F 6 "https://www.digikey.in/product-detail/en/silicon-labs/CP2102-GM/336-1160-5-ND/696598?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 3500 2050 50  0001 L BNN "Field6"
F 7 "CP2102-GM" H 3500 2050 50  0001 L BNN "Field7"
F 8 "QFN-28 Silicon Labs" H 3500 2050 50  0001 L BNN "Field8"
	1    3500 2050
	1    0    0    -1  
$EndComp
$Comp
L STM32F103RB-rescue:TAJA105M020RNJ-c1206_smd_tantalum-Door_Locking-rescue C3
U 1 1 5FA679B2
P 3650 3400
F 0 "C3" V 3946 3270 50  0000 R CNN
F 1 "4.7uF/25V" V 3855 3270 50  0000 R CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A_Pad1.58x1.35mm_HandSolder" H 4000 3450 50  0001 L CNN
F 3 "http://www.farnell.com/datasheets/1680476.pdf" H 4000 3350 50  0001 L CNN
F 4 "AVX - TAJA105M020RNJ - CAP, TANT, 1UF, 20V, CASE A" H 4000 3250 50  0001 L CNN "Description"
F 5 "1.8" H 4000 3150 50  0001 L CNN "Height"
F 6 "AVX" H 4000 3050 50  0001 L CNN "Manufacturer_Name"
F 7 "TAJA105M020RNJ" H 4000 2950 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "581-TAJA105M020" H 4000 2850 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-TAJA105M020" H 4000 2750 50  0001 L CNN "Mouser Price/Stock"
F 10 "1360152" H 4000 2650 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/1360152" H 4000 2550 50  0001 L CNN "RS Price/Stock"
	1    3650 3400
	0    1    1    0   
$EndComp
$Comp
L STM32F103RB-rescue:TAJA105M020RNJ-c1206_smd_tantalum-Door_Locking-rescue C5
U 1 1 5FA679A0
P 5100 3300
F 0 "C5" V 5396 3170 50  0000 R CNN
F 1 "1uF/25V" V 5305 3170 50  0000 R CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A_Pad1.58x1.35mm_HandSolder" H 5450 3350 50  0001 L CNN
F 3 "http://www.farnell.com/datasheets/1680476.pdf" H 5450 3250 50  0001 L CNN
F 4 "AVX - TAJA105M020RNJ - CAP, TANT, 1UF, 20V, CASE A" H 5450 3150 50  0001 L CNN "Description"
F 5 "1.8" H 5450 3050 50  0001 L CNN "Height"
F 6 "AVX" H 5450 2950 50  0001 L CNN "Manufacturer_Name"
F 7 "TAJA105M020RNJ" H 5450 2850 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "581-TAJA105M020" H 5450 2750 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=581-TAJA105M020" H 5450 2650 50  0001 L CNN "Mouser Price/Stock"
F 10 "1360152" H 5450 2550 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/1360152" H 5450 2450 50  0001 L CNN "RS Price/Stock"
	1    5100 3300
	0    1    1    0   
$EndComp
Connection ~ 4350 1650
Wire Wire Line
	4550 1650 4350 1650
Wire Wire Line
	5450 3800 5700 3800
Wire Wire Line
	5450 3900 5450 3800
$Comp
L power:GND #PWR0104
U 1 1 5FA67988
P 5450 3900
F 0 "#PWR0104" H 5450 3650 50  0001 C CNN
F 1 "GND" H 5455 3727 50  0000 C CNN
F 2 "" H 5450 3900 50  0001 C CNN
F 3 "" H 5450 3900 50  0001 C CNN
	1    5450 3900
	1    0    0    -1  
$EndComp
Connection ~ 5450 3800
Wire Wire Line
	5100 3800 5450 3800
$Comp
L pspice:C C6
U 1 1 5FA6797D
P 5700 3550
F 0 "C6" H 5878 3596 50  0000 L CNN
F 1 "100nF" H 5878 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5700 3550 50  0001 C CNN
F 3 "~" H 5700 3550 50  0001 C CNN
	1    5700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3900 4000 3900
Wire Wire Line
	4000 3900 4250 3900
Connection ~ 4000 3900
Wire Wire Line
	4000 4000 4000 3900
$Comp
L power:GND #PWR0103
U 1 1 5FA67971
P 4000 4000
F 0 "#PWR0103" H 4000 3750 50  0001 C CNN
F 1 "GND" H 4005 3827 50  0000 C CNN
F 2 "" H 4000 4000 50  0001 C CNN
F 3 "" H 4000 4000 50  0001 C CNN
	1    4000 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3400 4250 3400
Wire Wire Line
	3950 3300 3950 3400
Text GLabel 3950 3300 1    50   Input ~ 0
VDD1
Connection ~ 3950 3400
Wire Wire Line
	3650 3400 3950 3400
$Comp
L pspice:C C4
U 1 1 5FA67962
P 4250 3650
F 0 "C4" H 4428 3696 50  0000 L CNN
F 1 "100nF" H 4428 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4250 3650 50  0001 C CNN
F 3 "~" H 4250 3650 50  0001 C CNN
	1    4250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 6200 6250 5950
Wire Wire Line
	5750 6200 5750 5950
Wire Wire Line
	6250 5600 6250 5650
Wire Wire Line
	6250 5400 6250 5300
Wire Wire Line
	5750 5600 5750 5650
Wire Wire Line
	5750 5400 5750 5300
Text GLabel 6250 5300 1    50   Input ~ 0
3v3
Text GLabel 5750 5300 1    50   Input ~ 0
3v3
$Comp
L Device:LED D6
U 1 1 5FA6794E
P 6250 5800
F 0 "D6" H 6243 6016 50  0000 C CNN
F 1 "LED" H 6243 5925 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6250 5800 50  0001 C CNN
F 3 "~" H 6250 5800 50  0001 C CNN
	1    6250 5800
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D5
U 1 1 5FA67944
P 5750 5800
F 0 "D5" H 5743 6016 50  0000 C CNN
F 1 "LED" H 5743 5925 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 5750 5800 50  0001 C CNN
F 3 "~" H 5750 5800 50  0001 C CNN
	1    5750 5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 1950 2800 1950
$Comp
L power:GND #PWR0102
U 1 1 5FA67938
P 4200 2650
F 0 "#PWR0102" H 4200 2400 50  0001 C CNN
F 1 "GND" H 4205 2477 50  0000 C CNN
F 2 "" H 4200 2650 50  0001 C CNN
F 3 "" H 4200 2650 50  0001 C CNN
	1    4200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2350 4700 2350
$Comp
L power:GND #PWR0101
U 1 1 5FA6792D
P 4850 2350
F 0 "#PWR0101" H 4850 2100 50  0001 C CNN
F 1 "GND" H 4855 2177 50  0000 C CNN
F 2 "" H 4850 2350 50  0001 C CNN
F 3 "" H 4850 2350 50  0001 C CNN
	1    4850 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 2350 4200 2350
Wire Wire Line
	2600 1450 2800 1450
Wire Wire Line
	2250 1450 2400 1450
Text GLabel 2250 1450 0    50   Input ~ 0
VDD1
$EndSCHEMATC