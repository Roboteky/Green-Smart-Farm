#define ENABLE_DEBUG
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define TANK1_PUMP_PIN    14
#define TANK2_PUMP_PIN    27

#define TANK1THRESH     12
#define TANK2THRESH     30

#include "Network.h"
#include "Sensors.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

hw_timer_t* dataTimer = NULL;
hw_timer_t* uploadTimer = NULL;

bool readSensors = false;
bool uploadData = false;

FarmSensors_t sensorData = {0};
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void IRAM_ATTR everySecond()
{
  readSensors = true;
}

void IRAM_ATTR everyFiveSeconds()
{
  uploadData = true;
}

void setup() {

  Serial.begin(115200);
  //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println("Initialising ...");
  delay(1000);

  SensorsInit();

  //  pinMode(TANK1_PUMP_PIN, OUTPUT);
  //  pinMode(TANK2_PUMP_PIN, OUTPUT);

  WiFiInit();
  FirebaseInit();

  dataTimer = timerBegin(0, 80, true);//timer 0, prescaler 80, count up
  timerAttachInterrupt(dataTimer, &everySecond, true);//trigger timer on high level
  timerAlarmWrite(dataTimer, 1000000, true);//period 1000000, auto-reload = true

  uploadTimer = timerBegin(1, 80, true);//timer 0, prescaler 80, count up
  timerAttachInterrupt(uploadTimer, &everyFiveSeconds, true);//trigger timer on high level
  timerAlarmWrite(uploadTimer, 5000000, true);//period 5000000, auto-reload = true

  //  timerAlarmEnable(dataTimer);//start 1s timer
  timerAlarmEnable(uploadTimer);//start 5s timer

  Serial.println("Initialization complete!!");

}

void loop() {

  if (readSensors)
  {
    readSensors = false;
    ReadSensors(&sensorData);
    if ((sensorData.tank1Level) < TANK1THRESH){
      digitalWrite(TANK1_PUMP_PIN, HIGH);
      sensorData.pumpOn = true;
    } else{
      digitalWrite(TANK1_PUMP_PIN, LOW);
      sensorData.pumpOn = false;
    }
//      if ((sensorData->tank2Level) < TANK2THRESH)
//        digitalWrite(TANK2_PUMP_PIN, HIGH);
//      else
//        digitalWrite(TANK2_PUMP_PIN, LOW);
  }

  if (uploadData)
  {
    uploadData = false;
    Serial.println("Uploading data ...");
    ReadSensors(&sensorData);
    if (FirebaseUploadData(sensorData))
      Serial.println("Sensor Data Uploaded Successfully!");
    else
      Serial.println("Sensor Data Upload Failed!");

  }

}


void ReadSensors(FarmSensors_t* sensors)
{
  ReadPvSensor(sensors);
  ReadRainfallSensor(sensors);
  ReadWaterLevel(sensors);
  ReadSoilTemp(sensors);
  ReadSoilMoisture(sensors);
  ReadSoilPH(sensors);
  ReadAmbient(sensors);
  ReadNPK(sensors);
}
