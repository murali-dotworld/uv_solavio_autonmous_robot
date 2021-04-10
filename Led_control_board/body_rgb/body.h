#include <ESP8266WiFi.h>
#include <espnow.h>
#include<ArduinoJson.h>
#include "FastLED.h"
#include<EEPROM.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#define NUM_LEDS 200
#define DATA_PIN1 5
#define DATA_PIN2 4
#define DATA_PIN3 14
#define DATA_PIN4 12
#define serial_baud_rate 115200
#define light1 1
#define light2 2
#define light3 3
#define light4 4
#define round_led 1
#define fadein 2
#define fadeout 3
#define blinkOn 4
#define blinkOff 5
#define split_led 6
#define police_led 7
#define fade 8
#define reverse_on 9
#define esp_serial Serial

CRGBArray<NUM_LEDS> leds1;
CRGBArray<NUM_LEDS> leds2;
CRGBArray<NUM_LEDS> leds3;
CRGBArray<NUM_LEDS> leds4;
CLEDController *controllers[4];

uint16_t ota_timeout=5000;
uint8_t gBrightness = 255;
int dev_millis = 300;
uint8_t broadcastAddress[] = {0x53, 0xAA, 0xB5, 0x1B, 0x98, 0xCD}; //83:7d:3a:15:ab:55
uint8_t newMACAddress[] = {0x32, 0xAE, 0xA4, 0x07, 0x0D, 0x64};
int absolute_zero = 0 , true_case = 1;
byte led_mode;
StaticJsonDocument<512> doc;
StaticJsonDocument<512> send_data; 
StaticJsonDocument<512> root; 
int first_time = 0;
int slave_id = 5;
int8_t f_inc = 0;
int f1  = 0;
int f2  = 0;
int f3  = 0;
int f4  = 0;
int fade_in = 0;
int fade_out = 255;
int fade_in1 = 0;
int fade_in2 = 0;
int fade_in3 = 0;
int fade_in4 = 0;
int fade_out1 = 255;
int fade_out2 = 255;
int fade_out3 = 255;
int fade_out4 = 255;
int led_count1 = 0;
int led_count2 = 0;
int led_count3 = 0;
int led_count4 = 0;
int r_speed1 = 0;
int f_back1 = 0;
int r_speed2 = 0;
int f_back2 = 0;
int r_speed3 = 0;
int f_back3 = 0;
int r_speed4 = 0;
int f_back4 = 0;
int8_t f_inc1 = 0;
int8_t f_inc2 = 0;
int8_t f_inc3 = 0;
int8_t f_inc4 = 0;
int mac_address_count = 2;
String r_mode = "";
const char* ssid = "uv_solavia_autonomous1_esp";
const char* password = "123456789";
unsigned long int wifi_conn_millis = millis();
unsigned long int init_millis = millis();
bool ota_flg =false;
float led_colour[3];
float led_colour1[3];
float led_colour2[3];
float led_colour3[3];
float led_colour4[3];
char incomingReadings[150], outgoingReading[150], convert[250];
boolean stringComplete = false;

unsigned int long startmillis = 0;

bool r_bcount1 = 0;
bool r_bcount2 = 0;
bool r_bcount3 = 0;
bool r_bcount4 = 0;

byte led_mode1 = 0;
byte led_mode2 = 0;
byte led_mode3 = 0;
byte led_mode4 = 0;

int light = 0;
int modes = 0;

String led  = "";
String led1 = "";
String led2 = "";
String led3 = "";
String led4 = "";
String mastermac = "", check = "";
String r_mode1 = "" ;
String r_mode2 = "" ;
String r_mode3 = "" ;
String r_mode4 = "" ;

float inc[3];
bool r_bcount = 0;
int8_t hue = 0;
int a = 0;

const byte MaxByteArraySize = 6;
byte byteArray[MaxByteArraySize] = {0};


void hexCharacterStringToBytes(byte *byteArray, const char *hexString);
byte nibble(char c);


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

  return 0;// Not a valid hexadecimal character
}

void rond(float r[], int led, int led_count, int r_speed, int f_back)
{
  for (int i = 0; i < led_count; i++)
  {
    if (led == 1)
    {
      leds1.fadeToBlackBy(f_back);
      leds1[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "round")
      {
        break;
      }
    }
    else if (led == 2)
    {
      leds2.fadeToBlackBy(f_back);
      leds2[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode2 != "round")
      {
        break;
      }
    }
    else if (led == 3)
    {
      leds3.fadeToBlackBy(f_back);
      leds3[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode3 != "round")
      {
        break;
      }
    }
    else if (led == 4)
    {
      leds4.fadeToBlackBy(f_back);
      leds4[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode4 != "round")
      {
        break;
      }
    }
  }
}

void split(float r[], int led, int led_count, int r_speed, int f_back)
{
  if (led == 1)
  {
    for (int i = 0 ; i <= led_count / 2; i++)
    {
      leds1.fadeToBlackBy(f_back);
      leds1[i] = CRGB(r[0], r[1], r[2]);
      leds1(led_count / 2 - 1 , led_count ) = leds1(led_count / 2, 0);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "s_on")
      {
        break;
      }
    }
  }
  else if (led == 2)
  {
    for (int i = 0 ; i <= led_count / 2; i++)
    {
      leds2.fadeToBlackBy(f_back);
      leds2[i] = CRGB(r[0], r[1], r[2]);
      leds2(led_count / 2 - 1 , led_count ) = leds2(led_count / 2, 0);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "s_on")
      {
        break;
      }
    }
  }
  else if (led == 3)
  {
    for (int i = 0 ; i <= led_count / 2; i++)
    {
      leds3.fadeToBlackBy(f_back);
      leds3[i] = CRGB(255, 0, 0);
      leds3(led_count / 2 - 1 , led_count ) = leds3(led_count / 2, 0);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "s_on")
      {
        break;
      }
    }
  }
  else if (led == 4)
  {
    for (int i = 0 ; i <= led_count / 2; i++)
    {
      leds4.fadeToBlackBy(f_back);
      leds4[i] = CRGB(255, 0, 0);
      leds4(led_count / 2 - 1 , led_count ) = leds4(led_count / 2, 0);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "s_on")
      {
        break;
      }
    }
  }
}

void reverse(float r[], int led, int led_count,int r_speed, int f_back)
{
  if (led == 1)
  {
    for (int i = led_count; i > 0; i--)
    {
      leds1[i] = CRGB(r[0], r[1], r[2]);
      leds1.fadeToBlackBy(f_back);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode1 != "reverse")
      {
        break;
      }
    }
  }
  else if (led == 2)
  {
    for (int i = led_count; i > 0; i--)
    {
      leds2.fadeToBlackBy(f_back);
      leds2[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode2 != "reverse")
      {
        break;
      }
    }
  }
  else if (led == 3)
  {
    for (int i = led_count; i > 0; i--)
    {
      leds3.fadeToBlackBy(f_back);
      leds3[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode3 != "reverse")
      {
        break;
      }
    }
  }
  else if (led == 4)
  {
    for (int i = led_count; i > 0; i--)
    {
      leds4.fadeToBlackBy(f_back);
      leds4[i] = CRGB(r[0], r[1], r[2]);
      FastLED.delay(r_speed);
      FastLED.show();
      if (r_mode4 != "reverse")
      {
        break;
      }
    }
  }
}

void police(int led, int led_count)
{
  unsigned long int startmillis1 = millis() / dev_millis;

  if (((startmillis1 % 2) == 1) && (r_bcount == 0))
  {
    if (led == 1)
    {
      leds1(0, led_count / 2) = CRGB(255, 0, 0);
      leds1(led_count / 2, led_count - 1) = CRGB(0, 0, 0);
      FastLED.show();
      r_bcount = 1;
    }
    else if (led == 2)
    {
      leds2(0, led_count / 2) = CRGB(255, 0, 0);
      leds2(led_count / 2, led_count - 1) = CRGB(0, 0, 0);
      FastLED.show();
      r_bcount = 1;
    }
    else if (led == 3)
    {
      leds3(0, led_count / 2) = CRGB(255, 0, 0);
      leds3(led_count / 2, led_count - 1) = CRGB(0, 0, 0);
      FastLED.show();
      r_bcount = 1;
    }
    else if (led == 4)
    {
      leds4(0, led_count / 2) = CRGB(255, 0, 0);
      leds4(led_count / 2, led_count - 1) = CRGB(0, 0, 0);
      FastLED.show();
      r_bcount = 1;
    }
  }
  else if (((startmillis1 % 2) == 0) && (r_bcount == 1))
  {
    if (led == 1)
    {
      leds1(0, led_count / 2) = CRGB(0, 0, 0);
      leds1(led_count / 2, led_count - 1) = CRGB(0, 0, 255);
      FastLED.show();
      r_bcount = 0;
    }
    else if (led == 2)
    {
      leds2(0, led_count / 2) = CRGB(0, 0, 0);
      leds2(led_count / 2, led_count - 1) = CRGB(0, 0, 255);
      FastLED.show();
      r_bcount = 0;
    }
    else if (led == 3)
    {
      leds3(0, led_count / 2) = CRGB(0, 0, 0);
      leds3(led_count / 2, led_count - 1) = CRGB(0, 0, 255);
      FastLED.show();
      r_bcount = 0;
    }
    else if (led == 4)
    {
      leds4(0, led_count / 2) = CRGB(0, 0, 0);
      leds4(led_count / 2, led_count - 1) = CRGB(0, 0, 255);
      FastLED.show();
      r_bcount = 0;
    }
  }
}

void leds_off(int led_count)
{
  fill_solid(leds1, led_count, CRGB(0, 0, 0));
  controllers[0]->showLeds(gBrightness);
  fill_solid(leds2, led_count, CRGB(0, 0, 0));
  controllers[1]->showLeds(gBrightness);
  fill_solid(leds3, led_count, CRGB(0, 0, 0));
  controllers[2]->showLeds(gBrightness);
  fill_solid(leds4, led_count, CRGB(0, 0, 0));
  controllers[3]->showLeds(gBrightness);      // now, let's first 20 leds to the top 20 leds,wLeds(gBrightness);
}


void blinkOn1(float r1[], int led_count)
{
  //Serial.println(r1[0]);
  unsigned long int startmillis1 = millis() / dev_millis;

  if (((startmillis1 % 2) == 1) && (r_bcount1 == 0))
  {
    fill_solid(leds1, led_count, CRGB(r1[0], r1[1], r1[2]));
    controllers[0]->showLeds(gBrightness);
    r_bcount1 = 1;
  }
  else if (((startmillis1 % 2) == 0) && (r_bcount1 == 1))
  {
    fill_solid(leds1, led_count, CRGB(0, 0, 0));
    controllers[0]->showLeds(gBrightness);
    r_bcount1 = 0;
  }
}


void blinkOn2(float r2[], int led_count)
{
  unsigned long int startmillis1 = millis() / dev_millis;

  if (((startmillis1 % 2) == 1) && (r_bcount2 == 0))
  {
    fill_solid(leds2, led_count, CRGB(r2[0], r2[1], r2[2]));
    controllers[1]->showLeds(gBrightness);
    r_bcount2 = 1;
  }
  else if (((startmillis1 % 2) == 0) && (r_bcount2 == 1))
  {
    fill_solid(leds2, led_count, CRGB(0, 0, 0));
    controllers[1]->showLeds(gBrightness);
    r_bcount2 = 0;
  }
}


void blinkOn3(float r3[], int led_count)
{
  unsigned long int startmillis1 = millis() / dev_millis;

  if (((startmillis1 % 2) == 1) && (r_bcount3 == 0))
  {
    fill_solid(leds3, led_count, CRGB(r3[0], r3[1], r3[2]));
    controllers[2]->showLeds(gBrightness);
    r_bcount3 = 1;
  }
  else if (((startmillis1 % 2) == 0) && (r_bcount3 == 1))
  {
    fill_solid(leds3, led_count, CRGB(0, 0, 0));
    controllers[2]->showLeds(gBrightness);
    r_bcount3 = 0;
  }
}


void blinkOn4(float r4[], int led_count)
{
  unsigned long int startmillis1 = millis() / dev_millis;

  if (((startmillis1 % 2) == 1) && (r_bcount4 == 0))
  {
    fill_solid(leds4, led_count, CRGB(r4[0], r4[1], r4[2]));
    controllers[3]->showLeds(gBrightness);
    r_bcount4 = 1;
  }
  else if (((startmillis1 % 2) == 0) && (r_bcount4 == 1))
  {
    fill_solid(leds4, led_count, CRGB(0, 0, 0));
    controllers[3]->showLeds(gBrightness);
    r_bcount4 = 0;
  }
}

void blinkOff1(float r1[], int led_count)
{
  fill_solid(leds1, led_count, CRGB(r1[0], r1[1], r1[2]));
  controllers[0]->showLeds(gBrightness);
}

void blinkOff2(float r2[], int led_count)
{
  fill_solid(leds2, led_count, CRGB(r2[0], r2[1], r2[2]));
  controllers[1]->showLeds(gBrightness);
}


void blinkOff3(float r3[], int led_count)
{
  fill_solid(leds3, led_count, CRGB(r3[0], r3[1], r3[2]));
  controllers[2]->showLeds(gBrightness);
}


void blinkOff4(float r4[], int led_count)
{
  fill_solid(leds4, led_count, CRGB(r4[0], r4[1], r4[2]));
  controllers[3]->showLeds(gBrightness);

}


void fadeIn1(float r1[], int led_count)
{
  if (fade_in1 < 255)
  {
    fade_in1 = fade_in1 + 3;
    //Serial.println(f);
    fill_solid(leds1, led_count, CRGB(r1[0], r1[1], r1[2]));
    controllers[0]->showLeds(fade_in1);
    delay(6);
    if (fade_in1 == 255) fade_in1 = 0, led1 = "";
  }
}

void fadeIn2(float r2[], int led_count)
{
  if (fade_in2 < 255)
  {
    fade_in2 = fade_in2 + 3;
    //Serial.println(f);
    fill_solid(leds2, led_count, CRGB(r2[0], r2[1], r2[2]));
    controllers[1]->showLeds(fade_in2);
    delay(6);
    if (fade_in2 == 255) fade_in2 = 0, led2 = "";
  }
}

void fadeIn3(float r3[], int led_count)
{
  if (fade_in3 < 255)
  {
    fade_in3 = fade_in3 + 3;
    //Serial.println(f);
    fill_solid(leds3, led_count, CRGB(r3[0], r3[1], r3[2]));
    controllers[2]->showLeds(fade_in3);
    delay(6);
    if (fade_in == 255) fade_in3 = 0, led3 = "";
  }
}

void fadeIn4(float r4[], int led_count)
{
  if (fade_in4 < 255)
  {
    fade_in4 = fade_in4 + 3;
    //Serial.println(f);
    fill_solid(leds4, led_count, CRGB(r4[0], r4[1], r4[2]));
    controllers[3]->showLeds(fade_in4);
    delay(6);
    if (fade_in == 255) fade_in4 = 0, led4 = "";
  }
}

void fadeOut1(float r1[], int led_count)
{
  if (fade_out1 > 5)
  {
    fade_out1 = fade_out1 - 3;
    //Serial.println(f);
    fill_solid(leds1, led_count, CRGB(r1[0], r1[1], r1[2]));
    controllers[0]->showLeds(fade_out1);
    delay(6);
    if (fade_out1 < 5) fade_out1 = 255, led1 = "";
  }
}
void fadeOut2(float r2[], int led_count)
{
  if (fade_out2 > 5)
  {
    fade_out2 = fade_out2 - 3;
    //Serial.println(f);
    fill_solid(leds2, led_count, CRGB(r2[0], r2[1], r2[2]));
    controllers[1]->showLeds(fade_out2);
    delay(6);
    if (fade_out2 < 5) fade_out2 = 255, led2 = "";
  }
}

void fadeOut3(float r3[], int led_count)
{
  if (fade_out3 > 5)
  {
    fade_out3 = fade_out3 - 3;
    //Serial.println(f);
    fill_solid(leds3, led_count, CRGB(r3[0], r3[1], r3[2]));
    controllers[2]->showLeds(fade_out3);
    delay(6);
    if (fade_out3 < 5) fade_out3 = 255, led3 = "";
  }
}

void fadeOut4(float r4[], int led_count)
{
  if (fade_out4 > 5)
  {
    fade_out = fade_out - 3;
    //Serial.println(f);
    fill_solid(leds4, led_count, CRGB(r4[0], r4[1], r4[2]));
    controllers[3]->showLeds(fade_out4);
    delay(6);
    if (fade_out4 < 5) fade_out4 = 255, led4 = "";
  }
}

void fade1(float r1[], int led_count)
{
  f1 = f_inc1++ * 2;
  if (f1 < 0) f1 = f1 * (-1);
  if (f1 == 256) f1 = 255;

  fill_solid(leds1, led_count, CRGB(r1[0], r1[1], r1[2]));
  controllers[0]->showLeds(f1);
  delay(6);
}
void fade2(float r2[], int led_count)
{

  f2 = f_inc2++ * 2;
  if (f2 < 0) f2 = f2 * (-1);
  if (f2 == 256) f2 = 255;
  fill_solid(leds2, led_count, CRGB(r2[0], r2[1], r2[2]));
  controllers[1]->showLeds(f2);
  delay(6);
}

void fade3(float r3[], int led_count)
{
  f3 = f_inc3++ * 2;
  if (f3 < 0) f3 = f3 * (-1);
  if (f3 == 256) f3 = 255;
  fill_solid(leds3, led_count, CRGB(r3[0], r3[1], r3[2]));
  controllers[2]->showLeds(f3);
  delay(6);
}

void fade4(float r4[], int led_count)
{

  f4 = f_inc4++ * 2;
  if (f4 < 0) f4 = f4 * (-1);
  if (f4 == 256) f4 = 255;
  fill_solid(leds4, led_count, CRGB(r4[0], r4[1], r4[2]));
  controllers[3]->showLeds(f4);
  delay(6);
}
