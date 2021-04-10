#include "body.h"
void setup()
{
  esp_serial.begin(serial_baud_rate);
  WiFi.mode(WIFI_STA);
  EEPROM.begin(512);
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);                         //Setting a custom mac id to the slave.
  Serial.println(WiFi.macAddress());
  for (int i = absolute_zero; i < MaxByteArraySize; i++)                          //Checking the master Mac id in the EEPROM
  {
    byte b = EEPROM.read(i);
    if (b == 255)
    {
      first_time = absolute_zero;
      break;
    }
    broadcastAddress[i] = b;
    check = String(b, HEX);
    Serial.println(check);
    if (check.length() < mac_address_count)
    {
      check = String("0") + check;
    }
    mastermac = mastermac + check;
    first_time = true_case;
  }
  mastermac.toUpperCase();
  if (esp_now_init() != 0) return;
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  if (first_time == 1)
  {
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);           //Setting a broadcastAddress as a MAC address
  }
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  controllers[0] = &FastLED.addLeds<WS2812, DATA_PIN1, GRB>(leds1, NUM_LEDS);
  controllers[1] = &FastLED.addLeds<WS2812, DATA_PIN2, GRB>(leds2, NUM_LEDS);
  controllers[2] = &FastLED.addLeds<WS2812, DATA_PIN3, GRB>(leds3, NUM_LEDS);
  controllers[3] = &FastLED.addLeds<WS2812, DATA_PIN4, GRB>(leds4, NUM_LEDS);
  led_mode1 = 5 ;
  led_count1 = 120;
  led_colour1[0] = 0;
  led_colour1[1] = 255;
  led_colour1[2] = 0;
  led1 = "eye";
}

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len)
{
  doc.clear();
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.println(incomingReadings);
  deserializeJson(doc, incomingReadings);
  //Serial.println("INSIDE CHECK");
  String master_mac = doc["master_mac"];
  if (master_mac == mastermac)
  {
    if (doc.containsKey("set"))
    {
      const char* mac_address = doc["set"];
      send_data["set"] = true;
      send_data["slave"] = slave_id;
      serializeJson(send_data , outgoingReading);
      esp_now_send(broadcastAddress, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
      send_data.clear();
      hexCharacterStringToBytes(byteArray, mac_address);
      mastermac = "";
      for (int i = 0; i < sizeof(byteArray); i++)
      {
        broadcastAddress[i] = byteArray[i];
        check = String(byteArray[i], HEX);
        if (check.length() < mac_address_count)
        {
          check = String("0") + check;
        }
        mastermac = mastermac + check;
        EEPROM.write(i, byteArray[i]);
      }
      mastermac.toUpperCase();
      EEPROM.commit();
      esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    }
    if (doc.containsKey("ota"))
    {
      ota_flg = true;
      Serial.println("inside ota");
      send_data["ota"] = doc["ota"];
      send_data["board_no"] = doc["board_no"];
      ota_timeout = doc["timeout"];
      Serial.print("ota_timeout : ");
      Serial.println(ota_timeout);
      send_data["master_mac"] = master_mac;
      serializeJson(send_data , outgoingReading);
      esp_now_send(broadcastAddress, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
      serializeJson(send_data, Serial);
      Serial.println();
      send_data.clear();
    }
    else if (doc.containsKey("board_no"))
    {
      int mode_no = doc["mode_no"];
      if (mode_no >= 1 && mode_no <= 9)
      {
        send_data["board_no"] = doc["board_no"];
        send_data["master_mac"] = master_mac;
        send_data["mode_no"] = doc["mode_no"];
        send_data["port_no"] = doc["port_no"];
        send_data["colour1"] = doc["colour1"];
        send_data["colour2"] = doc["colour2"];
        send_data["no_of_led"] = doc["no_of_led"];
        send_data["r_speed"] = doc["r_speed"];
        send_data["f_back"] = doc["f_back"];
        send_data["response"] = true;
        serializeJson(send_data , outgoingReading);
        esp_now_send(broadcastAddress, (uint8_t *)&outgoingReading, sizeof(outgoingReading));
        //serializeJson(send_data, Serial);
        send_data.clear();
        int led_number = doc["port_no"];
        if (led_number == light1)
        {
          led_mode1 = doc["mode_no"];
          led_count1 = doc["no_of_led"];
          led_colour1[0] = doc["colour1"][0];
          led_colour1[1] = doc["colour1"][1];
          led_colour1[2] = doc["colour1"][2];
          r_speed1 = doc["r_speed"];
          f_back1 = doc["f_back"];
          led1 = "eye";
        }
        if (led_number == light2)
        {
          led_mode2 = doc["mode_no"];
          led_count2 = doc["no_of_led"];
          led_colour2[0] = doc["colour1"][0];
          led_colour2[1] = doc["colour1"][1];
          led_colour2[2] = doc["colour1"][2];
          r_speed2 = doc["r_speed"];
          f_back2 = doc["f_back"];
          led2 = "eye";
        }
        if (led_number == light3)
        {
          led_mode3 = doc["mode_no"];
          led_count3 = doc["no_of_led"];
          led_colour3[0] = doc["colour1"][0];
          led_colour3[1] = doc["colour1"][1];
          led_colour3[2] = doc["colour1"][2];
          r_speed3 = doc["r_speed"];
          f_back3 = doc["f_back"];
          led3 = "eye";
        }
        if (led_number == light4)
        {
          led_mode4 = doc["mode_no"];
          led_count4 = doc["no_of_led"];
          led_colour4[0] = doc["colour1"][0];
          led_colour4[1] = doc["colour1"][1];
          led_colour4[2] = doc["colour1"][2];
          r_speed4 = doc["r_speed"];
          f_back4 = doc["f_back"];
          led4 = "eye";
        }
      }
      else
      {
        send_data["board_no"] = doc["board_no"];
        send_data["master_mac"] = master_mac;
        send_data["mode_no"] = doc["mode_no"];
        send_data["port_no"] = doc["port_no"];
        send_data["colour1"] = doc["colour1"];
        send_data["colour2"] = doc["colour2"];
        send_data["no_of_led"] = doc["no_of_led"];
        send_data["response"] = false;
      }
    }
  }
}


void loop()
{
  if (first_time == absolute_zero)
  {
    root.clear();
    root["purpose"] = "GetMacMaster";
    serializeJson(root, esp_serial);
    Serial.println();
    while (true_case)
    {
      root.clear();
      root["purpose"] = "GetMacMaster";
      serializeJson(root, esp_serial);
      Serial.println();
      if (esp_serial.available() > absolute_zero)
      {
        String inp = Serial.readStringUntil('\n');
        deserializeJson(root, inp);
        const char* mac_address = root["mac_address"];
        hexCharacterStringToBytes(byteArray, mac_address);
        first_time = true_case;
        for (int i = absolute_zero; i < MaxByteArraySize; i++)
        {
          esp_serial.println(byteArray[i], HEX);
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
      if (first_time == true_case)
      {
        break;
      }
    }
  }
  if (ota_flg == true)
  {
    wifi_conn_millis = millis();
    init_millis = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (wifi_conn_millis - init_millis < 60000)
    {
      Serial.println("Bootinug");
      wifi_conn_millis = millis();
      ota_handler();
      Serial.println("<<<<<INSIDE OTA");
      delay(600);
    }
    ota_flg = false;
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() != 0)
    {
      return;
    }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(OnDataSent);
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_recv_cb(OnDataRecv);
    ESP.restart();
    ota_timeout = 0;
  }
  else
  {
    if (led1 != "")
    {
      //Serial.println(led_mode1);
      if (led_mode1 == blinkOn) blinkOn1(led_colour1, led_count1), r_mode1 = "blinkOn";
      else if (led_mode1 == blinkOff) blinkOff1(led_colour1, led_count1), led1 = "", r_mode1 = "blinkOff";
      else if (led_mode1 == fadein) fadeIn1(led_colour1, led_count1), r_mode1 = "fadeIn";
      else if (led_mode1 == fadeout) fadeOut1(led_colour1, led_count1), r_mode1 = "fadeOut";
      else if (led_mode1 == fade) fade1(led_colour1, led_count1), r_mode1 = "fade";
      else if (led_mode1 == round_led) rond(led_colour1, 1, led_count1, r_speed1, f_back1), r_mode1 = "round";
      else if (led_mode1 == police_led) police(1, led_count1), r_mode1 = "police";
      else if (led_mode1 == split_led) split(led_colour1, 1 , led_count1, r_speed1, f_back1), r_mode1 = "s_on";
      else if (led_mode1 == reverse_on) reverse(led_colour1, 1, led_count1, r_speed1, f_back1), r_mode1 = "reverse";
    }
    if (led2 != "")
    {
      //Serial.println(led_mode2);
      if (led_mode2 == blinkOn) blinkOn2(led_colour2, led_count2), r_mode2 = "blinkOn";
      else if (led_mode2 == blinkOff) blinkOff2(led_colour2, led_count2), led2 = "", r_mode2 = "blinkOff";
      else if (led_mode2 == fadein) fadeIn2(led_colour2, led_count2), r_mode2 = "fadeIn";
      else if (led_mode2 == fadeout) fadeOut2(led_colour2, led_count2), r_mode2 = "fadeOut";
      else if (led_mode2 == fade) fade2(led_colour2, led_count2), r_mode2 = "fade";
      else if (led_mode2 == round_led) rond(led_colour2, 2, led_count2, r_speed2, f_back2), r_mode2 = "round";
      else if (led_mode2 == police_led) police(2, led_count2), r_mode2 = "police";
      else if (led_mode2 == split_led) split(led_colour2, 2, led_count2, r_speed2, f_back2), r_mode2 = "s_on";
      else if (led_mode2 == reverse_on) reverse(led_colour2, 2, led_count2, r_speed2, f_back2), r_mode1 = "reverse";
    }
    if (led3 != "")
    {
      if (led_mode3 == blinkOn) blinkOn3(led_colour3, led_count3), r_mode3 = "blinkOn";
      else if (led_mode3 == blinkOff) blinkOff3(led_colour3, led_count3), led3 = "", r_mode3 = "blinkOff";
      else if (led_mode3 == fadein) fadeIn3(led_colour3, led_count3), r_mode3 = "fadeIn";
      else if (led_mode3 == fadeout) fadeOut3(led_colour3, led_count3), r_mode3 = "fadeOut";
      else if (led_mode3 == fade) fade3(led_colour3, led_count3), r_mode3 = "fade";
      else if (led_mode3 == round_led) rond(led_colour3, 3, led_count3, r_speed3, f_back3), r_mode3 = "round";
      else if (led_mode3 == police_led) police(3, led_count3), r_mode3 = "police";
      else if (led_mode3 == split_led) split(led_colour3, 3, led_count3, r_speed3, f_back3), r_mode3 = "s_on";
      else if (led_mode3 == reverse_on) reverse(led_colour3, 3, led_count3, r_speed3, f_back3), r_mode3 = "reverse";
    }
    if (led4 != "")
    {
      if (led_mode4 == blinkOn) blinkOn4(led_colour4, led_count4), r_mode4 = "blinkOn";
      else if (led_mode4 == blinkOff) blinkOff4(led_colour4, led_count4), led4 = "", r_mode4 = "blinkOff";
      else if (led_mode4 == fadein) fadeIn4(led_colour4, led_count4), r_mode4 = "fadeIn";
      else if (led_mode4 == fadeout) fadeOut4(led_colour4, led_count4), r_mode4 = "fadeOut";
      else if (led_mode4 == fade) fade4(led_colour4, led_count4), r_mode4 = "fade";
      else if (led_mode4 == round_led) rond(led_colour4, 4, led_count4, r_speed4, f_back4), r_mode4 = "round";
      else if (led_mode4 == police_led) police(4, led_count4), r_mode4 = "police";
      else if (led_mode4 == split_led) split(led_colour4, 4, led_count4, r_speed4, f_back4), r_mode4 = "s_on";
      else if (led_mode4 == reverse_on) reverse(led_colour4, 4, led_count4, r_speed4, f_back4), r_mode4 = "reverse";
    }
  }
}

void ota_handler(void)
{

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
  }
  if (WiFi.waitForConnectResult() == WL_CONNECTED)
  {
    Serial.println("Connected");
  }
  ArduinoOTA.setHostname("esp1");
  ArduinoOTA.setPassword("1234");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]()
  {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  ArduinoOTA.handle();
}
