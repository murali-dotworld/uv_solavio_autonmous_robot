#include "STM_master.h"


/*Setup to Serial begin and I/O pins*/
void setup()
{
  disableDebugPorts();
  stm_serial.begin(stm_baud_rate);                            //Serial for stm
  esp_serial.begin(esp_baud_rate);                           //Serial for esp
  Serial3.begin(115200);
  pinMode(PIR_read, INPUT_PULLDOWN);
  pinMode(docking_relay, OUTPUT);                             //Docking Relay
  pinMode(dock_battery, INPUT);                               //Docking input
  pinMode(battery, INPUT);                                    //Battery voltage Reading
  pinMode(top_light_relay , OUTPUT);
  pinMode(centre_light_relay, OUTPUT);
  pinMode(bottom_light_relay, OUTPUT);
  digitalWrite(top_light_relay, LOW);
  digitalWrite(bottom_light_relay, LOW);
  digitalWrite(centre_light_relay, LOW);
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/*battery check for 24V*/
float batteryCheck()
{
  float battery_volt = map(float(analogRead(battery)), adc_min, adc_max, min_per, max_per);
  return battery_volt;
}


/*docker Voltage check for 24V*/
float dock_batteryCheck()
{
  float dock_battery_volt = map(float(analogRead(dock_battery)), adc_min, adc_max, min_per, max_per);
  return dock_battery_volt;
}

void pir_detect()
{
  if ((light_bottom_status == true) || (light_top_status == true) || (light_centre_status == true))
  {
    int pir_digital_status = digitalRead(PIR_read);
    if (pir_digital_status == HIGH)
    {
      digital_count++;
      if(digital_count>=10)
      {
        digitalReadStatus = 1;
      }
    }
    else
    {
      digital_count = 0;
      digitalReadStatus = 0;
    }
    if(digitalReadStatus == 1)
    {
      pir_status = true;
      digitalWrite(top_light_relay, LOW);
      digitalWrite(bottom_light_relay, LOW);
      digitalWrite(centre_light_relay, LOW);
      motion_detection_flag = true;
      //Serial.println(pir_digital_status);
      digital_count = 0;
      digitalReadStatus = 0;
    }
    if (motion_detection_flag == true)
    {
      if (pir_digital_status == LOW)
      {
        count++;
        Serial3.println(count);
        if (count >= 7000)
        {
          pin_state = 1;
        }
      }
      else
      {
        count = 0;
      }
      if (pin_state == 1)
      {
        pir_status = false;
        if (light_bottom_status == true)
        {
          digitalWrite(bottom_light_relay, HIGH);
        }
        if (light_top_status == true)
        {
          digitalWrite(top_light_relay, HIGH);
        }
        if (light_centre_status == true)
        {
          digitalWrite(centre_light_relay, HIGH);
        }
        count = 0;
        motion_detection_flag = false;
        pin_state = 0;
      }
    }
  }
}

void loop()
{
  pir_detect();
  if (stm_serial.available() > 0)                             //If stm serial is available.
  {
    String inp = stm_serial.readStringUntil('\n');
    doc.clear();
    deserializeJson(doc, inp);
    if (doc.containsKey("status"))                            //Status to check the alive state.
    {
      reply_json["status"] = true;
      serializeJson(reply_json, Serial);
      Serial.println();
      doc.clear();
      reply_json.clear();
    }

    else if (doc.containsKey("data_fetch"))                   //Data fetch to check the battery status.
    {
      reply_json.clear();
      float battery_percentage = analogRead(battery);
      reply_json["battery"] = battery_percentage;
      reply_json["pir"] = pir_status;
      serializeJson(reply_json, Serial);
      Serial.println();
      reply_json.clear();
      if (pir_status == true)
      {
        pir_status = false;
      }
    }

    else if (doc.containsKey("docking"))                    //Docking process.
    {
      String dock_data = doc["docking"];
      if (dock_data == dockmode_on)
      {
        sendroot.clear();
        sendroot["docking"] = dockmode_on;
        sendroot["slave"] = docking_board;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
        sendroot["dockmode_on"] = true;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
      }

      if (dock_data == dockmode_off)
      {
        sendroot.clear();
        sendroot["docking"] = dockmode_off;
        sendroot["slave"] = docking_board;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
        sendroot["dockmode_off"] = true;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
      }
      if (dock_data == dockingon)
      {
        sendroot["docking"] = True;
        serializeJson(sendroot, Serial);
        Serial.println();
        doc["slave"] = docking_board;
        doc["docking"] = dockingon;
        serializeJson(doc, Serial2);
        Serial2.println();
        sendroot.clear();
        doc.clear();
      }
      else if (dock_data == alive)
      {
        sendroot["slave"] = docking_board;
        sendroot["docking"] = alive;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
      }
      else if (dock_data == detch)
      {
        sendroot["undocking"] = True;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
        sendroot["slave"] = docking_board;
        sendroot["docking"] = detch;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
      }
      else if (dock_data == force)
      {
        digitalWrite(docking_relay, LOW);
        sendroot["undocking"] = undocksuc;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
      }
      else if (dock_data == set_mac)
      {
        sendroot["slave"] = docking_board;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
      }
    }
    else if (doc.containsKey("top"))
    {
      bool top_status = doc["top"];
      bool centre_status = doc["centre"];
      bool bottom_status = doc["bottom"];
      if (top_status == true)
      {
        light_top_status = true;
        digitalWrite(top_light_relay, HIGH);
      }
      else if (top_status == false)
      {
        light_top_status = false;
        digitalWrite(top_light_relay, LOW);
      }
      if (centre_status == true)
      {
        light_centre_status = true;
        digitalWrite(centre_light_relay, HIGH);
      }
      else if (centre_status == false)
      {
        light_centre_status = false;
        digitalWrite(centre_light_relay, LOW);
      }
      if (bottom_status == true)
      {
        light_bottom_status = true;
        digitalWrite(bottom_light_relay, HIGH);
      }
      else if (bottom_status == false)
      {
        light_bottom_status = false;
        digitalWrite(bottom_light_relay, LOW);
      }
      reply_json.clear();
      reply_json["uv_light"] = true;
      serializeJson(reply_json, Serial);
      Serial.println();
    }

    else if (doc.containsKey("board_no"))
    {
      serializeJson(doc, Serial2);
      Serial2.println();
    }
    Serial.flush();
    doc.clear();
  }

  if (esp_serial.available() > absolute_zero)                                 //Return acknowledgment of a get a master mac of the slave
  {
    root.clear();
    String inp = esp_serial.readStringUntil('\n');
    deserializeJson(root, inp);
    bool h = root["response"];
    if (root.containsKey("docking"))
    {
      String json_data = root["docking"];
      get_data = json_data;
      if (get_data == dockingon)
      {
        sendroot.clear();
        sendroot["docking"] = predocking;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot["slave"] = docking_board;
        serializeJson(sendroot, Serial2);
        Serial2.println();
        sendroot.clear();
      }
      else if (get_data == relayon)
      {
        delay(100);
        float dockingVolt = dock_batteryCheck();
        if (dockingVolt > 28 && dockingVolt < 30)                           //Docking Voltage less than 105 and greater than 80
        {
          sendroot["docking"] = docking;
          serializeJson(sendroot, Serial);
          Serial.println();
          sendroot.clear();
          sendroot["docking"] = docking;
          sendroot["slave"] = docking_board;
          serializeJson(sendroot, Serial2);
          Serial2.println();
          sendroot.clear();
        }
        else
        {
          digitalWrite(docking_relay, LOW);
          sendroot["docking"] = fail;
          sendroot["reason"] = robot;
          serializeJson(sendroot, Serial);
          Serial.println();
          sendroot["slave"] = docking_board;
          serializeJson(sendroot, Serial2);
          Serial2.println();
          sendroot.clear();
        }
      }
      else if (get_data == docking)
      {
        digitalWrite(docking_relay, HIGH);
      }
      else if (get_data == fail)
      {
        sendroot["docking"] = fail;
        sendroot["reason"] = root["reason"];
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
        digitalWrite(docking_relay, LOW);
      }
    }
    else if (root.containsKey("dockpin"))
    {
      sendroot.clear();
      sendroot["dockpin"] = root["dockpin"];
      serializeJson(sendroot, Serial);
      Serial.println();
      sendroot.clear();
    }
    else if ((root.containsKey("docker")) || (root.containsKey("robot")))
    {
      serializeJson(root, Serial);
      Serial.println();
      sendroot.clear();
    }
    else if (root.containsKey("undocking"))
    {
      String undock = root["undocking"];
      if (undock == undocksuc)
      {
        digitalWrite(docking_relay, LOW);
        sendroot["undocking"] = undocksuc;
        serializeJson(sendroot, Serial);
        Serial.println();
        sendroot.clear();
      }
    }
    else if (root.containsKey("board_no"))
    {
      Serial.println(inp);
    }
  }
}
