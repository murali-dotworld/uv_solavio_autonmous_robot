#include <ESP8266WiFi.h>
#include <espnow.h>
#include<ArduinoJson.h>
#define esp_baud_rate 115200
#define emergency_switch 13
#define emergency_relay 5
#define esp_serial Serial
int relay1 = 4;
int relay2 = 0;
int switch_off = 0;
int switch_on = 1;
int emergency_status = 0;
int mac_address_count = 3;
int absolute_zero = 0;
int ultrasonic_count = 7;
bool soft_emg_status;
uint8_t broadcastAddress[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x65};
uint8_t newMACAddress[] = {0x8C, 0xAA, 0xB5, 0x1B, 0x4C, 0x41};//2c:f4:32:2f:14:9c
StaticJsonDocument<250> send_data;
StaticJsonDocument<250> doc;
StaticJsonDocument<250> serial_json;
StaticJsonDocument<250> root;
char incomingReadings[150], outgoingReading[150];
String mac_address = "";
