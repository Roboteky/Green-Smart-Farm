#include "Network.h"
#include "Sensors.h"

FirebaseData  fbDo;
FirebaseAuth fbAuth;
FirebaseConfig fbConfig;

void WiFiInit(void)
{
  //*** WI-FI SETUP
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) //wait for Wi-Fi to connect
  {
    Serial.print(".");
    delay(2000);
  }
  Serial.print("\nConnected! Local IP: ");
  Serial.println(WiFi.localIP());
}

void FirebaseInit(void)
{
  //FIREBASE CONNECTION
  fbConfig.api_key = API_KEY;
  fbAuth.user.email = USER_EMAIL;
  fbAuth.user.password = USER_PASSWORD;

  Firebase.begin(&fbConfig, &fbAuth);
  Serial.println("Firebase Initialized");
  //  Firebase.reconnectWiFi(true);

}

void NetworkInit()
{
  WiFiInit();
  FirebaseInit();
}

bool FirebaseUploadData(FarmSensors_t sensorData)
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not Connected!!");
    return false;
  } else if (!Firebase.ready())
  {
    Serial.println("Firebase error!!");
    return false;
  } else
  {
    String path = "farm/farmData";

    FirebaseJson content;

    content.set("fields/pvCurrent/doubleValue", String(sensorData.pvCurrent).c_str());
    content.set("fields/pvVoltage/doubleValue", String(sensorData.pvVoltage).c_str());
    content.set("fields/raining/booleanValue", (sensorData.raining) ? "true" : "false" );
    content.set("fields/pumpOn/booleanValue", (sensorData.pumpOn) ? "true" : "false" );
    content.set("fields/tank1Level/integerValue", String(sensorData.tank1Level).c_str());
    content.set("fields/tank2Level/integerValue", String(sensorData.tank2Level).c_str());
    content.set("fields/soilMoisture/integerValue", String(sensorData.soilMoisture).c_str());
    content.set("fields/soilTemp/doubleValue", String(sensorData.soilTemp).c_str());
    content.set("fields/soilPH/doubleValue", String(sensorData.soilPH).c_str());
    content.set("fields/airTemp/doubleValue", String(sensorData.airTemp).c_str());
    content.set("fields/airHumidity/doubleValue", String(sensorData.airHumidity).c_str());
    content.set("fields/nitrogen/integerValue", String(sensorData.nitrogen).c_str());
    content.set("fields/phosphorus/integerValue", String(sensorData.phosphorus).c_str());
    content.set("fields/potassium/integerValue", String(sensorData.potassium).c_str());

    Serial.print("Sent content:  ");
    Serial.println(content.raw());

    if (Firebase.Firestore.createDocument(&fbDo, FIREBASE_PROJ, "", path.c_str(), content.raw()))
    {

#ifdef ENABLE_DEBUG
      Serial.println("Sent Payload:\n\n%s\n", fbDo.payload().c_str());
#endif

      return true;
    } else
    {
      //      Serial.println(fbDo.errorReason());

      Serial.print("Updating document... ");
      if (Firebase.Firestore.patchDocument(&fbDo, FIREBASE_PROJ, "", path.c_str(), content.raw(), "pvCurrent, pvVoltage, raining, pumpOn, tank1Level, tank2Level, soilMoisture, soilTemp, soilPH, airTemp, airHumidity, nitrogen, phosphorus, potassium" /* updateMask */))
        Serial.printf("ok\n%s\n\n", fbDo.payload().c_str());
      else
        Serial.println(fbDo.errorReason());
    }



  }
  return true;
}
