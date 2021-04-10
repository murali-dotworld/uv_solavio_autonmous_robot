/*  1-SUCCESS
    2-DOCKING ON
    3-PREDOCKING
    4-DOCKING
    5-DETACH
    6-RELAY ON 1 SEC
    7-RELAY OFF
    8-PING
    9-ROBO_fail
    0-dockerside voltage failure
    99-healthcheckup
    12-docker check
*/
//{"docking":"reached"}
//{"docking":"undock"}

#include "esp_master.h"
void setup()
{
  esp_serial.begin(esp_baud_rate);                                                        //Serial for ESP
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);
  if (esp_now_init() != 0) return;
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);                   //Peer to Peer connection with the slave with mac address
  esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress3, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress4, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress5, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress6, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress7, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  String full_mac_address = WiFi.macAddress();
  for (int i = absolute_zero; i < full_mac_address.length(); i = i + mac_address_count)  //Change the mac Address into the string
  {
    mac_address = mac_address + full_mac_address[i];
    mac_address = mac_address + full_mac_address[i + 1];
  }
  mac_address.toUpperCase();
}

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)                        //Data recieve from the Slave
{
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  deserializeJson(root, incomingReadings);
  String mastermac = root["master_mac"];
  if (mastermac == mac_address)                                       //Check the master mac of the slave is correct or not
  {
    if (root.containsKey("slave"))
    {
      int slave = root["slave"];
      if (slave == 1)
      {
        if (root.containsKey("data"))
        {
          int data = root["data"];
          if (data == 1)
          {
            esp_data = dockmode_on;
          }
          if (data == 2)
          {
            esp_data = dockingon;
          }
          else if (data == 6)
          {
            esp_data = relayon;
          }
          else if (data == 7)
          {
            esp_data = relayoff;
          }
          else if (data == 4)
          {
            esp_data = docking;
          }
          else if (data == 8)
          {
            esp_data = dockmode_off;
          }
          else if (data == 5)
          {
            esp_data = detch;
          }
          else if (data == 99)
          {
            send_data["docker"] = 1;
            serializeJson(send_data, Serial);
            Serial.println();
            send_data.clear();
          }
          else if (data == 11)
          {
            esp_data = fail;
          }
          else if (data == 12)
          {
            esp_data = robot;
          }
        }
        root.clear();
      }
    }
    if (root.containsKey("set"))
    {
      int slave = root["slave"];
      if (slave == 1)
      {
        send_data["docking"] = "success";
        serializeJson(send_data, Serial);
        Serial.println();
        send_data.clear();
      }
      if (slave == 2)
      {
        send_data["wheel"] = "success";
        serializeJson(send_data, Serial);
        Serial.println();
        send_data.clear();
      }
      if (slave == 3)
      {
        send_data["ring"] = "success";
        serializeJson(send_data, Serial);
        Serial.println();
        send_data.clear();
      }
      if (slave == 4)
      {
        send_data["body"] = "success";
        serializeJson(send_data, Serial);
        Serial.println();
        send_data.clear();
      }
    }
    if (root.containsKey("ota"))
    {
      send_data["ota"] = root["ota"];
      send_data["board_no"] = root["board_no"];
      serializeJson(send_data, Serial);
      Serial.println();
      root.clear();
      send_data.clear();
    }
    else if (root.containsKey("board_no"))
    {
      send_data["board_no"] = root["board_no"];
      send_data["port_no"] = root["port_no"];
      send_data["mode_no"] = root["mode_no"];
      send_data["colour1"] = root["colour1"];
      send_data["colour2"] = root["colour2"];
      send_data["no_of_led"] = root["no_of_led"];
      send_data["r_speed"] = root["r_speed"];
      send_data["f_back"] = root["f_back"];
      send_data["response"] = true;
      serializeJson(send_data, Serial);
      Serial.println();
      root.clear();
      send_data.clear();
    }
  }
}

void loop()
{
  if (esp_serial.available() > absolute_zero)
  {
    root.clear();
    send_data.clear();
    String data = Serial.readStringUntil('\n');
    DeserializationError error = deserializeJson(root, data);
    if (root.containsKey("docking"))
    {
      String get_data = root["docking"];
      if (get_data == dockmode_on)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 1;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      if (get_data == dockmode_off)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 8;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      if (get_data == dockingon)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 2;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      else if (get_data == predocking)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 3;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      else if (get_data == fail)
      {
        String reason = root["reason"];
        if (reason == robot)
        {
          send_data["slave"] = 1;
          send_data["mastermac"] = mac_address;
          send_data["data"] = 9;
          serializeJson(send_data, outgoingReading);
          esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
          send_data.clear();
          root.clear();
        }
      }
      else if (get_data == docking)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 4;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      else if (get_data == alive)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 99;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        serial_json["robot"] = 1;
        serializeJson(serial_json, Serial);
        Serial.println();
        send_data.clear();
        root.clear();
      }
      else if (get_data == detch)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 5;
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      else if (get_data == set_mac)
      {
        send_data["slave"] = 1;
        send_data["mastermac"] = mac_address;
        send_data["data"] = 100;
        send_data["set"] = root["set"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress1, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
        root.clear();
      }
      send_data.clear();
    }
    if (root.containsKey("ota"))
    {
      int board_no = root["board_no"];
      if (board_no == 1)
      {
        send_data["ota"] = root["ota"];
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["timeout"] = root["timeout"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress2, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 2)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["ota"] = root["ota"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress3, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 3)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["ota"] = root["ota"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress5, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 4)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["ota"] = root["ota"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress6, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 5)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["ota"] = root["ota"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress6, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 6)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["ota"] = root["ota"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress4, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      root.clear();
      send_data.clear();
    }
    else if (root.containsKey("board_no"))
    {
      int board_no = root["board_no"];
      if (board_no == 1)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress2, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 2)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress3, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 3)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress5, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 4)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress6, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 5)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress6, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
      if (board_no == 6)
      {
        send_data["board_no"] = root["board_no"];
        send_data["master_mac"] = mac_address;
        send_data["port_no"] = root["port_no"];
        send_data["mode_no"] = root["mode_no"];
        send_data["colour1"] = root["colour1"];
        send_data["colour2"] = root["colour2"];
        send_data["no_of_led"] = root["no_of_led"];
        send_data["r_speed"] = root["r_speed"];
        send_data["f_back"] = root["f_back"];
        serializeJson(send_data, outgoingReading);
        esp_now_send(broadcastAddress4, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        send_data.clear();
      }
    }
  }
  if (esp_data == dockmode_on)
  {
    esp_data = "";
    send_data["dockpin"] = 1;
    serializeJson(send_data, Serial);
    Serial.println();
    send_data.clear();
  }
  if (esp_data == dockmode_off)
  {
    esp_data = "";
    send_data["dockmode_off"] = true;
    serializeJson(send_data, Serial);
    Serial.println();
    send_data.clear();
  }
  if (esp_data == dockingon)
  {
    esp_data = "";
    send_data["docking"] = dockingon;
    serializeJson(send_data, Serial);
    Serial.println();
    send_data.clear();
  }
  else if (esp_data == relayon)
  {
    esp_data = "";
    send_data["docking"] = relayon;
    serializeJson(send_data, Serial);
    Serial.println();
    send_data.clear();
  }
  else if (esp_data == docking)
  {
    send_data["docking"] = docking;
    serializeJson(send_data, Serial);
    Serial.println();
    esp_data = "";
    send_data.clear();
  }
  else if (esp_data == detch)
  {
    send_data["undocking"] = undocksuc;
    serializeJson(send_data, Serial);
    Serial.println();
    esp_data = "";
    send_data.clear();
  }
  else if (esp_data == fail)
  {
    send_data["docking"] = fail;
    send_data["reason"] = docker;
    serializeJson(send_data, Serial);
    Serial.println();
    esp_data = "";
    send_data.clear();
  }
  else if (esp_data == robot)
  {
    send_data["docking"] = fail;
    send_data["reason"] = robot;
    serializeJson(send_data, Serial);
    Serial.println();
    esp_data = "";
    send_data.clear();
  }
}
