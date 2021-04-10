/*Library file for declaration*/
#include "ultrasonic_esp.h"
void setup()
{
  Serial.begin(serial_baud_rate);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  wifi_set_macaddr(0, const_cast<uint8*>(newMACAddress));
  //wifi_set_macaddr(0, const_cast<uint8*>(newMACAddress));                         //Setting a custom mac id to the slave.
  //Serial.println(WiFi.macAddress());
  EEPROM.begin(eeprom_begin);                                                     //Begining EEPROM.
  for ( int i = absolute_zero ; i < MaxByteArraySize; i++)                        //Read the Master MAC address.
  {
    byte b = EEPROM.read(i);
    //Serial.println(b);
    if (b == empty_eeprom)
    {
      first_time = ZERO;
      break;
    }
    byteArray[i] = b;
    broadcastAddress[i] = byteArray[i] ;
    first_time = ONE;
    check = String(b, HEX);
    Serial.println(check);
    if (check.length() < mac_address_max_count)
    {
      check = String("0") + check;
    }
    mastermac = mastermac + check;
    first_time = ONE;
  }
  if (esp_now_init() != 0) return;
  if (first_time == ONE)
  {
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);          //Connection with the Master with the mac address
    mastermac.toUpperCase();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
}


void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)               //Data recieve from the master
{
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  deserializeJson(doc, incomingReadings);
  String master_mac = doc["master_mac"];
  if (master_mac == mastermac)
  {
    if (doc.containsKey("set"))
    {
      const char* mac_address = doc["set"];
      send_data.clear();
      send_data["set"] = 1;
      send_data["slave"] = slave_id;
      serializeJson(send_data, outgoingReading);
      esp_now_send(broadcastAddress, (uint8_t*)outgoingReading, sizeof(outgoingReading));
      hexCharacterStringToBytes(byteArray, mac_address);
      mastermac = mac_address;
      for (int i = 0; i < sizeof(byteArray); i++)
      {
        broadcastAddress[i] = byteArray[i];
      }
      esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    }
    else
    {
      String check = doc["ultrasonic"];
      if (check == "Alive?")
      {
        send_data["ultrasonic"] = "Alive";
        send_data["master_mac"] = master_mac;
        serializeJson(send_data , outgoingReading);
        send_data.clear();
      }
    }
  }
}


void loop()
{
  if (first_time == 0)                                                        //Case not MAC address set.
  {
    root.clear();
    root["purpose"] = "GetMacMaster";
    serializeJson(root, Serial);
    Serial.println();
    while (1)
    {
      root.clear();
      root["purpose"] = "GetMacMaster";
      serializeJson(root, Serial);
      Serial.println();
      //ESPserial.println("GetMacMaster");
      if (esp_serial.available() > ZERO)
      {
        String inp = Serial.readString();
        inp.trim();
        deserializeJson(root, inp);
        const char* mac_address = root["mac_address"];
        hexCharacterStringToBytes(byteArray, mac_address);
        first_time = 1;
        for (int i = ZERO; i < MaxByteArraySize; i++)
        {
          //ESPserial.println(byteArray[i], HEX);
          EEPROM.write(i, byteArray[i]);
          broadcastAddress[i] = byteArray[i];
          mastermac = mac_address;
        }
        esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
        for (int i = 0; i < sizeof(byteArray); i++)
        {
          EEPROM.write(i, byteArray[i]);
        }
        EEPROM.commit();
      }
      if (first_time == 1)
      {
        break;
      }
    }
  }
  else
  {
    if (Serial.available() > 0)                                         //Serial data from the STM32
    {
      send_data.clear();
      String data = Serial.readStringUntil('\n');
      deserializeJson(root, data);
      send_data["slave"] = slave_id;                                //Slave number
      send_data["data"] = "ultrasonic";
      send_data["u"] = root["dis"];                                 //Distance for Ultrasonic Sensor
      send_data["master_mac"] = mastermac;                          //MasterMac
      serializeJson(send_data, outgoingReading);
      esp_now_send(broadcastAddress, (uint8_t*)outgoingReading, sizeof(outgoingReading));  //sending a ultrasonic data to the Master.
    }
  }
}
