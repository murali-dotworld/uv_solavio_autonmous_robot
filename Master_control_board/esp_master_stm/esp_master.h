#include<ESP8266WiFi.h>
#include<espnow.h>
#include<ArduinoJson.h>
#define esp_baud_rate 115200
#define esp_serial Serial

uint8_t newMACAddress[] = {0xC8, 0x2B, 0x96, 0x30, 0x1C, 0x7F};
uint8_t broadcastAddress1[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x60};     //Docking
uint8_t broadcastAddress2[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x61};     //Ring
uint8_t broadcastAddress3[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x62};     //Wheel left
uint8_t broadcastAddress4[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x63};     //Wheel right
uint8_t broadcastAddress5[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x64};     //Body
uint8_t broadcastAddress6[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x65};     //Indicator left
uint8_t broadcastAddress7[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x66};     //Indicator right

StaticJsonDocument<512> send_data;
StaticJsonDocument<512> root;
StaticJsonDocument<512> serial_json;

#define True           true
#define fail          "fail"
#define dockingon     "dock" //2
#define predocking    "predocking"//3
#define docking       "success"//4
#define detch         "undock"//5
#define relayon       "relay_on"//6
#define relayoff      "relay_off"//7
#define alive         "Alive?"//99
#define ping          "ping"          //8
#define reached       "reached"
#define undocksuc     "success"
#define docker        "docker"
#define robot         "robot"
#define force         "f_undock"
#define dockmode_on   "dockmode_on"
#define dockmode_off  "dockmode_off"
#define set_mac       "set"

char incomingReadings[250], outgoingReading[250];
String mac_address = "", esp_data = "";
int mac_address_count = 3, absolute_zero = 0;
int wheel_board_no = 2, wheel_port_no, wheel_mode_no, wheel_colour_no;
float wheel_colour1[3];
bool wheel_response;
int left_wheel_status = 0, right_wheel_status = 0;
