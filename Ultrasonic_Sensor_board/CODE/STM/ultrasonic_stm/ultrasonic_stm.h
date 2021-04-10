#include <ArduinoJson.h>

/*#define*/
#define no_of_sensor 7
#define serial_baud_rate 115200
#define esp_baud_rate 115200
#define esp_serial Serial2
#define stm_serial Serial

/*Variable Declaration*/
int USSE[] = {PB14, PC13, PB8, PB6, PB4, PC9, PA11, PC10,PB12,PC7}; //Echo pin for ultrasonic sensor
int USST[] = {PB15, PC12, PB9, PB7, PB5, PC8, PA12, PC11,PB13,PC6}; //Trigger pin for ultrasonic sensor
long duration[7], distance[7];
int mac_set = 0;
uint16_t timeout_sensor = 31000;
int first_time = 0;
float speed_of_sound = 29.1;
int divide = 2;
int delay_millisecond = 10;
int absolute_zero = 0;
int not_mac_set = 0;
const byte MaxByteArraySize = 6;
byte byteArray[MaxByteArraySize] = {0};
int ONE = 1;

/*JSON Document*/
StaticJsonDocument<1024> root;
StaticJsonDocument<1024> send_data;
