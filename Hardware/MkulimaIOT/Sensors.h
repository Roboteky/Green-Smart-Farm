#ifndef _FARM_SENSORS_H_
#define _FARM_SENSORS_H_

#include <OneWire.h>
#include <DS18B20.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "DHTesp.h"


#define NPK_TX_PIN        17
#define NPK_RX_PIN        16
#define NPK_EN_PIN        5

#define RAIN_SENS_PIN     32
#define TANK1_LEVEL_PIN   39
#define TANK2_LEVEL_PIN   34
#define SOIL_MOISURE_PIN  35
#define SOIL_TEMP_PIN     25
#define PH_SENSOR_PIN     26
#define DHT_SENSOR_PIN     4

#define RAIN_THRESH       512//rain sensor threshold

typedef struct
{
  float pvCurrent;
  float pvVoltage;
  bool raining;
  bool pumpOn;
  int tank1Level;
  int tank2Level;
  int soilMoisture;
  float soilTemp;
  float soilPH;
  float airTemp;
  float airHumidity;
  int nitrogen;
  int phosphorus;
  int potassium;
       
}FarmSensors_t;


void SensorsInit(void);
void ReadPvSensor(FarmSensors_t* farm);
void ReadRainfallSensor(FarmSensors_t* farm);
void ReadWaterLevel(FarmSensors_t* farm);
void ReadSoilMoisture(FarmSensors_t* farm);
void ReadSoilTemp(FarmSensors_t* farm);
void ReadSoilPH(FarmSensors_t* farm);
void ReadAmbient(FarmSensors_t* farm);
void ReadNPK(FarmSensors_t* farm);

#endif
