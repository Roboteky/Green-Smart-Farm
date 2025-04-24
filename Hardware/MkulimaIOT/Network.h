#ifndef _FARM_NETWORK_H_
#define _FARM_NETWORK_H_

#include <WiFi.h>
#include <Firebase_ESP_Client.h>
//#include <addons/TokenHelper.h>
#include "Sensors.h"

//Wi-Fi
#define WIFI_SSID     "THE DEVELOPER"
#define WIFI_PASSWORD "MANAGEMENT2"

//Firebase
#define API_KEY       "AIzaSyA1RK3XYy-djgFtUkq198sBhqkeTnQ_oxg"
#define USER_EMAIL    "8483@farm32.org"
#define USER_PASSWORD "USER_PASSWORD"
#define FIREBASE_PROJ "fir-001-44cf2"

void WiFiInit(void);
void FirebaseInit(void);
bool FirebaseUploadData(FarmSensors_t sensorData);

#endif
