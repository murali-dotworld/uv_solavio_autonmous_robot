#include "esp_master.h"
void setup()
{
  esp_serial.begin(esp_baud_rate);                    //Begin serial
  pinMode(emergency_switch, INPUT);                   //Emergency switch as a INPUT
  pinMode(emergency_relay, OUTPUT);                   //Emergency switch as a OUTPUT
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) return;
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  String full_mac_address = WiFi.macAddress();        //MAC Address of the ESP
  for (int i = 0; i < full_mac_address.length(); i = i + mac_address_count)
  {
    mac_address = mac_address + full_mac_address[i];
    mac_address = mac_address + full_mac_address[i + 1];
  }
  mac_address.toUpperCase();                           //Change all the mac address to the upper case
}


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)
{
  serial_json.clear();
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  deserializeJson(doc, incomingReadings);
  String mastermac = doc["master_mac"];
  if (mastermac == mac_address)
  {
    if (doc.containsKey("set"))
    {
      serial_json["set"] = doc["set"];
      serializeJson(serial_json, esp_serial);
      esp_serial.println();
    }
    else if (doc.containsKey("data"))
    {
      String data = doc["data"];
      if (data == "ultrasonic")                         //Setting a Ultrasonic data and emergency switch to the serial
      {
        for (int i = absolute_zero ; i < ultrasonic_count; i++)
        {
          serial_json["u"][i] = doc["u"][i];
        }
        serial_json["emg"] = emergency_status;
        serial_json["rst"] = 0;
        serial_json["soft_emg"] = soft_emg_status;
        serializeJson(serial_json, esp_serial);
        esp_serial.println();
        doc.clear();
        serial_json.clear();
      }
    }
    //soft_emg_status = false;
  }
}


void loop()
{
  if ((digitalRead(emergency_switch) == HIGH))        //If the emergency switch press.
  {
    emergency_status = switch_on;
  }
  else                                                //If the emergency switch releases.
  {
    emergency_status = switch_off;
  }
  if (esp_serial.available() > absolute_zero)
  {
    send_data.clear();
    String data = esp_serial.readStringUntil('\n');
    deserializeJson(send_data , data);
    if (send_data.containsKey("emg"))                 //Serial JSON Data to turn off and on emergency relay
    {
      int emg_rly = send_data["emg"];
      if (emg_rly == true)
      {
        digitalWrite(emergency_relay, HIGH);
        soft_emg_status = true;
        root.clear();
      }
      else if (emg_rly == false)
      {
        digitalWrite(emergency_relay, LOW);
        soft_emg_status = false;
        root.clear();
      }
    }
  }
  send_data.clear();
}
