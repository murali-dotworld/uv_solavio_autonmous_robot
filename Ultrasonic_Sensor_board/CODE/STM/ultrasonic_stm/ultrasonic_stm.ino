#include "ultrasonic_stm.h"

/*Function Declaration*/
void sensor_processed_data(void);


/*Setup */
void setup()
{
  disableDebugPorts();
  stm_serial.begin(serial_baud_rate);
  Serial3.begin(esp_baud_rate);
  for (int i = absolute_zero; i < no_of_sensor; i++)                              //Trigger pins
  {
    pinMode(USST[i], OUTPUT);
  }
  for (int i = absolute_zero; i < no_of_sensor; i++)                              //Echo pins
  {
    pinMode(USSE[i], INPUT);
  }
}


/*Sensor Data*/
void sensor_processed_data(void)
{
  for (int i = absolute_zero; i < no_of_sensor; i++)
  {
    digitalWrite(USST[i], LOW);
    delayMicroseconds(delay_millisecond);
    digitalWrite(USST[i], HIGH);
    delayMicroseconds(delay_millisecond);
    digitalWrite(USST[i], LOW);
    duration[i] = pulseIn(USSE[i], HIGH, timeout_sensor);
    distance[i] = (duration[i] / divide) / speed_of_sound;                        //Distance calcualation method
    root["dis"][i] = distance[i];
  }
}


void loop()
{
  sensor_processed_data();
  root["status"] = "ultrasonic";
  serializeJson(root, Serial3);                                       //Serializing Ultrasonic Json data to the ESP Serial
  Serial3.println();
  serializeJson(root, Serial);                                       //Serializing Ultrasonic Json data to the ESP Serial
  Serial.println();
  root.clear();
}
