#include <Arduino.h>
#include <HX711.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define i2cAddress 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
HX711 scale;

// Configuration
const int doutPin = 2;
const int sckPin = 3;
const uint8_t tarePin = 5;
const uint8_t ledPin = 6;
static float scaleFactor = 232.39f;
float filteredWeight = 0;
bool initialized = false;

float calibrationCorrection(float grams)
{
  if (grams <= 500.0f)
    return grams;

  return grams + 0.003965f * (grams - 500.0f);
}

void displayWeight(float grams)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Weight:");
  display.setCursor(0, 30);

  if (abs(grams) < 1.0)
    grams = 0.0;
  if (grams >= 1000.0)
  {
    display.print(grams / 1000.0, 3);
    display.print(" kg");
  }
  else
  {
    display.print(grams, 2);
    display.print(" g");
  }
  display.display();
}

void tareScale()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Zeroing...");
  display.display();

  scale.tare(25);
  filteredWeight = 0;
  initialized = true;
  Serial.println("Tare completed.");
}

float getWeightResult()
{
  if (scale.is_ready())
  {
    float newReading = calibrationCorrection(scale.get_units(2));

    float difference = abs(newReading - filteredWeight);

    float dynamicAlpha = (difference > 1.0f) ? 0.85f : 0.1f;

    filteredWeight =
        dynamicAlpha * newReading +
        (1.0f - dynamicAlpha) * filteredWeight;

    return filteredWeight;
  }

  return filteredWeight;
}

void setup()
{
  Serial.begin(9600);
  pinMode(tarePin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  scale.begin(doutPin, sckPin);
  scale.set_scale(scaleFactor);

  if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddress))
  {
    Serial.println(F("OLED error"));
  }
  else
  {
    display.clearDisplay();
    display.display();
  }

  tareScale();
}

void loop()
{
  if (digitalRead(tarePin) == LOW)
  {
    tareScale();
    delay(200);
  }

  float currentWeight = getWeightResult();

  Serial.print("Weight: ");
  Serial.print(currentWeight);
  Serial.println(" g");

  displayWeight(currentWeight);

  delay(1);
}