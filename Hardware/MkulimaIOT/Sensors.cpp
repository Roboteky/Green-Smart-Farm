#include "Sensors.h"

//PV Panel current $ voltage sensor
Adafruit_INA219 pvSensor;

//NPK sensor connected on hardware UART 2
HardwareSerial npkSensor(2);

//Ambient temperature & humidity sensor
DHTesp airSensor;

//Soil temperature sensor
OneWire oneWire(SOIL_TEMP_PIN);
DS18B20 soilTempSensor(&oneWire);

float phCalibration = 0.00; //change this value to calibrate the PH sensor

const byte npkInquiry[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x03, 0x34, 0x0D};

// A variable used to store NPK values
byte npkData[11];

void SensorsInit(void)
{

  // Initialize the INA219.
  if (! pvSensor.begin()) {
    Serial.println("Could not find INA219 chip");
    int i = 5;
    while (--i) {
      delay(10);
    }
  }


  pinMode(NPK_EN_PIN, OUTPUT);
  pinMode(RAIN_SENS_PIN, INPUT);
  pinMode(TANK1_LEVEL_PIN, INPUT);
  pinMode(TANK2_LEVEL_PIN, INPUT);
  pinMode(SOIL_MOISURE_PIN, INPUT);
  pinMode(PH_SENSOR_PIN, INPUT);

  npkSensor.begin(9600, SERIAL_8N1, NPK_RX_PIN, NPK_TX_PIN);
  airSensor.setup(DHT_SENSOR_PIN, DHTesp::DHT22);
  soilTempSensor.begin();


}


void ReadPvSensor(FarmSensors_t* farm)
{
//  float shuntvoltage = 0;
//  float busvoltage = 0;
//  float current_mA = 0;
//  float loadvoltage = 0;
//  float power_mW = 0;
//
//  shuntvoltage = pvSensor.getShuntVoltage_mV();
//  busvoltage = pvSensor.getBusVoltage_V();
//  current_mA = pvSensor.getCurrent_mA();
//  power_mW = pvSensor.getPower_mW();
//  loadvoltage = busvoltage + (shuntvoltage / 1000);
//
//#ifdef ENABLE_DEBUG
//
//  Serial.print("PV\nVshunt:");
//  Serial.print(shuntvoltage);
//  Serial.print(" mV\tVbus:");
//  Serial.print(busvoltage);
//  Serial.print(" V\tIout:");
//  Serial.print(current_mA);
//  Serial.print(" mA\tPout:");
//  Serial.print(power_mW);
//  Serial.print(" mW\tVload:");
//  Serial.println(loadvoltage);
//
//#endif

//  farm->pvVoltage = busvoltage;
//  farm->pvCurrent = current_mA;

  farm->pvVoltage = 20;
  farm->pvCurrent++;

}

void ReadRainfallSensor(FarmSensors_t* farm)
{
  farm->raining = (analogRead(RAIN_SENS_PIN) > RAIN_THRESH);

#ifdef ENABLE_DEBUG

  if (farm->raining)
    Serial.println("It's raining!");
  else
    Serial.println("It's not raining!");

#endif

}

void ReadWaterLevel(FarmSensors_t* farm)
{
  farm->tank1Level = map(analogRead(TANK1_LEVEL_PIN) , 0, 4095, 0, 100);

#ifdef ENABLE_DEBUG

  Serial.print("Tank1 Water Level: ");
  Serial.print(farm->tank1Level);
  Serial.println("%");

#endif

  farm->tank2Level = map(analogRead(TANK2_LEVEL_PIN) , 0, 4095, 0, 100);

#ifdef ENABLE_DEBUG

  Serial.print("Tank2 Water Level: ");
  Serial.print(farm->tank2Level);
  Serial.println("%");

#endif

}

void ReadSoilMoisture(FarmSensors_t* farm)
{
  farm->soilMoisture = map(analogRead(SOIL_MOISURE_PIN), 0, 4095, 100, 0);

#ifdef ENABLE_DEBUG

  Serial.print("Soil Moisture: ");
  Serial.print(farm->soilMoisture);
  Serial.println("%");

#endif
}

void ReadSoilTemp(FarmSensors_t* farm)
{
  soilTempSensor.requestTemperatures();

  while (!soilTempSensor.isConversionComplete());

  farm->soilTemp = soilTempSensor.getTempC();

#ifdef ENABLE_DEBUG

  Serial.print("Soil Temp: ");
  Serial.print(farm->soilTemp);
  Serial.print("C");

#endif
}

void ReadSoilPH(FarmSensors_t* farm)
{

  farm->soilPH = map(analogRead(PH_SENSOR_PIN), 0, 4095, 1, 14);;

#ifdef ENABLE_DEBUG

  Serial.print("Soil PH:");
  Serial.println(farm->soilPH);

#endif
}

void ReadAmbient(FarmSensors_t* farm)
{
  TempAndHumidity newValues = airSensor.getTempAndHumidity();

  farm->airTemp     = newValues.temperature;
  farm->airHumidity = newValues.humidity;

#ifdef ENABLE_DEBUG

  Serial.print("Air Temp: ");
  Serial.print(farm->airTemp);
  Serial.print(" C");
  Serial.print("\tAir Humidity: ");
  Serial.print(farm->airHumidity);
  Serial.println(" %");

#endif
}

void ReadNPK(FarmSensors_t* farm)
{
  digitalWrite(NPK_EN_PIN, HIGH);
  delay(10);
  if (npkSensor.write(npkInquiry, sizeof(npkInquiry)) == 8) {
    digitalWrite(NPK_EN_PIN, LOW);
    for (byte i = 0; i < 12; i++) {
      //Serial.print(npkSensor.read(),HEX);
      npkData[i] = npkSensor.read();

#ifdef ENABLE_DEBUG
      Serial.print(npkData[i], HEX);
#endif
    }
#ifdef ENABLE_DEBUG
    Serial.println();
#endif

  }
//  farm->nitrogen =    (npkData[4] << 8) | npkData[5];
//  farm->phosphorus =  (npkData[6] << 8) | npkData[7];
//  farm->potassium =   (npkData[8] << 8) | npkData[9];

  farm->nitrogen++ ;
  farm->phosphorus++;
  farm->potassium++;
  
#ifdef ENABLE_DEBUG

  Serial.print("Nitrogen: ");
  Serial.print(farm->nitrogen);
  Serial.println(" mg/kg");
  Serial.print("\tPhosphorus: ");
  Serial.print(farm->phosphorus);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(farm->potassium);
  Serial.println(" mg/kg");

#endif
}
