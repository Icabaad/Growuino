#include <TFT_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT21   // AM2301 

DHT dht(DHTPIN, DHTTYPE);

TFT_ST7735 tft = TFT_ST7735();       // Invoke custom library

// These are used to get information about static SRAM and flash memory sizes
extern "C" char __data_start[];    // start of SRAM data
extern "C" char _end[];     // end of SRAM data (used to check amount of SRAM this program's variables use)
extern "C" char __data_load_end[];  // end of FLASH (used to check amount of Flash this program's code and data uses)




void setup() {
  Serial.begin(9600);

  Serial.println(F("TFT Initialized!     "));
  tft.init();            // initialize LCD
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  Serial.println("DHT Initialized!");
  dht.begin();

}

void loop() {
  tft.setCursor(0, 0, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(1);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");

    tft.print("H: ");
    tft.print(h,1);
    tft.print(" T: ");
    tft.println(t,1);


    delay(2000);
  }

}
