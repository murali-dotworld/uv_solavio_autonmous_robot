#include<ArduinoJson.h>
#include "Arduino.h"
#define stm_baud_rate 115200
#define esp_baud_rate 115200
#define stm_serial Serial
#define esp_serial Serial2
#define docking_relay PA11
#define dock_battery PA7
#define PIR_read PA6
#define bottom_light_relay PB13
#define centre_light_relay PA14
#define top_light_relay PA15
#define battery PA1

StaticJsonDocument<512> doc;
StaticJsonDocument<512> reply_json;
StaticJsonDocument<512> sendroot;
StaticJsonDocument<512> root;

int battery_percentage;
int docking_voltage_percentage;
int on_state = 1, off_state = 0;
int absolute_zero = 0;
String get_data = "";
float global_battery_percentage = 0, total_battery_voltage = 0;
bool light_top_status = false;
bool light_centre_status = false;
bool light_bottom_status = false;
bool pir_status = false;
int count =0,pin_state = 0;
bool motion_detection_flag = false;
int digitalReadStatus = 0;
int digital_count = 0;
//*************************Battery variables**************************************//
#define adc_min          2589.00
#define adc_max          3532.00
#define min_per          22.00
#define max_per          30.00
#define batvolt_max      90


//**************************docking variables*************************************//
#define True          true    
#define fail          "fail"  
#define dockingon     "dock" //2
#define predocking    "predocking"//3
#define docking       "success"//4
#define detch         "undock"//5
#define relayon       "relay_on"//6
#define alive         "Alive?"//99
#define undocksuc     "success"
#define docker        "docker"
#define robot         "robot"
#define force         "f_undock"
#define dockmode_on   "dockmode_on"
#define dockmode_off  "dockmode_off"
#define set_mac       "set"

//********************************Board Details**********************************//
#define docking_board 1
#define rgb_board1 2
#define rgb_board2 3
#define rgb_board3 4
