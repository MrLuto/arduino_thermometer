#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int runtime = 0;
float temp = 0.0;
int probeAmount = 4;
int oneWireBus = 9;
const int chipSelect = 10;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  runtime = millis() / 1000;
  String dataString = String(runtime);
  dataString += ",";

  for (int analogPin = 0; analogPin < probeAmount; analogPin++) {
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(analogPin);

    dataString += String(temp);
    if (analogPin < probeAmount - 1) {
      dataString += ",";
    }
  }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(3000);
}








