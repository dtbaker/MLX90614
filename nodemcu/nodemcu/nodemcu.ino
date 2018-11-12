#include <Wire.h>
#include "i2c.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();


#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "credentials.h"

#define HOUSEKEEPING_DELAY 10000 // check things every 10 seconds.

// ************ Function Prototypes ***************
void houseKeeping();
void connectOTA();
void connectWifi();

WiFiClient client;


unsigned long houseKeepingNext = 0;
unsigned long heartbeatNext = 0;
String PostData = "";
double Temp = 0;


void setup()
{
  Serial.begin(9600);
  mlx.begin();
  pinMode(LED_BUILTIN, OUTPUT);


  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  connectOTA();


  // Make sure we're connected to wifi etc..
  housekeeping();
}

void loop()
{
  mlx.setAddress(0x2A);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + ",";

  mlx.setAddress(0x2B);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + ",";

  mlx.setAddress(0x2C);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + ",";

  mlx.setAddress(0x2D);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + ",";

  mlx.setAddress(0x2E);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + ",";

  mlx.setAddress(0x2F);
  Temp = mlx.readObjectTempC();
  PostData = PostData + Temp + "\n";

  delay(400);

  ArduinoOTA.handle();
  housekeeping();

}


void housekeeping() {
  if ( houseKeepingNext == 0 || millis() > houseKeepingNext) {
    //If we drop off Wifi, atempt to reconnect
    if (WiFi.status() != WL_CONNECTED) {
      connectWifi();
    }
    transmitData();
    houseKeepingNext = millis() + HOUSEKEEPING_DELAY;
  }
}

void transmitData() {
  if (client.connect("dtbaker.net", 80)) {
    Serial.println("conected to the server");
    client.println("POST /files/temperature/data.php HTTP/1.1");
    client.println("Host:  dtbaker.net");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    Serial.println(PostData);
    client.println(PostData);
    long interval = 2000;
    unsigned long currentMillis = millis(), previousMillis = millis();

    while (!client.available()) {
      if ( (currentMillis - previousMillis) > interval ) {
        client.stop();
        return;
      }
      currentMillis = millis();
    }

    while (client.connected())
    {
      if ( client.available() )
      {
        char str = client.read();
      }
    }

    PostData = "";
  }

}

