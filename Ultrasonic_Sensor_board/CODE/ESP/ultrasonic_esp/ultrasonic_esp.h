#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>
#include<EEPROM.h>
#define esp_serial Serial
#define serial_baud_rate 115200
SoftwareSerial ESPserial(5,4); // RX | TX

/*Variable Declaration*/
int first_time = 0;
const byte MaxByteArraySize = 6;
byte byteArray[MaxByteArraySize] = {0};
String mastermac="",master_mac,send_string,check;
char incomingReadings[150], outgoingReading[150],convert[250];
int slave_id = 2;
int first_time_1 = 0;
int absolute_zero = 0;
long delay_time = 5000;
int eeprom_begin = 512;
byte empty_eeprom = 255;
int ZERO = 0,ONE = 1,mac_address_max_count = 2;

/*Function Declaration*/
void hexCharacterStringToBytes(byte *byteArray, const char *hexString);
byte nibble(char c);


/*JSON Declaration*/
StaticJsonDocument<250> doc;
StaticJsonDocument<1024> send_data;
StaticJsonDocument<1024> root;

/*MAC ADDRESS Declaration*/
uint8_t broadcastAddress[] = {0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t newMACAddress[]= {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x65};


/*Convert String data to byte array*/
void hexCharacterStringToBytes(byte *byteArray, const char *hexString)
{
  bool oddLength = strlen(hexString) & 1;
  byte currentByte = 0;
  byte byteIndex = 0;
  for (byte charIndex = 0; charIndex < strlen(hexString); charIndex++)
  {
    bool oddCharIndex = charIndex & 1;
    if (oddLength)
    {
      if (oddCharIndex)
      {
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
    else
    {
      if (!oddCharIndex)
      {
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
  }
}

/*Convertion for String data to byte array*/
byte nibble(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  return 0;  // Not a valid hexadecimal character
}
