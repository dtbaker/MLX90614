#include <ArduinoOTA.h>


// *****************  OTA ************************
void connectOTA()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);
  
  ArduinoOTA.setHostname(DEVICE_NAME);

  // No authentication by default
  ArduinoOTA.setPassword(OTA_PASSWORD);  //(const char *)

  ArduinoOTA.onStart([]() {
    
  });
  ArduinoOTA.onEnd([]() {
    //Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    /* Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed"); */
  });
  
  ArduinoOTA.begin();
}


// *****************  WIFI CONNECTION ************************
void connectWifi()
{
  // Continually attemps to connect to the Wifi
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    unsigned long resetAttempt = 300000; // 5mins
    static unsigned long timeNow = millis();
    while(millis() - timeNow < resetAttempt){
      digitalWrite(LED_BUILTIN, LOW);  // low = led on
    }
    ESP.restart();
  }
  digitalWrite(LED_BUILTIN, HIGH);  // high = led off
}
