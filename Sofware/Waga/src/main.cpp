#include <Arduino.h>
#include <HX711.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
HX711 scale;

// --- KONFIGURACJA ---
const int doutPin = 2;
const int sckPin = 3;
const uint8_t Tare_pin = 5;
const uint8_t LED_pin = 6;

static float Scale = (181224.0f - 44012.00f) / 590.0f;

// --- ZMIENNE FILTRA ---
float wykladzona_waga = 0;
float alfa = 0.8; 
bool initialized = false;

void wyswietl(float grams)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Waga:");
  display.setCursor(0, 30);

  if (abs(grams) < 1.0)
    grams = 0.0;
  if (grams >= 1000.0){
    display.print(grams/1000.0, 3);
    display.print(" kg");
  }
else{
  display.print(grams, 1);
  display.print(" g");
}
display.display();
}

void tare()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Zerowanie...");
  display.display();

  scale.tare(20);
  wykladzona_waga = 0;
  initialized = true;
  Serial.println("Tare wykonane.");
}

float pobierz_wynik()
{
  if (scale.is_ready())
  {
    float surowy_odczyt = scale.get_units(5);
    wykladzona_waga = (alfa * surowy_odczyt) + ((1.0 - alfa) * wykladzona_waga);
    return wykladzona_waga;
  }
  return wykladzona_waga;
}

void setup()
{
  Serial.begin(9600);
  pinMode(Tare_pin, INPUT_PULLUP);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, HIGH);

  scale.begin(doutPin, sckPin);
  scale.set_scale(Scale);

  if (!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address))
  {
    Serial.println(F("OLED error"));
  }
  else
  {
    display.clearDisplay();
    display.display();
  }

  tare(); 
}

void loop()
{
  if (digitalRead(Tare_pin) == LOW)
  {
    tare();
    delay(200);
  }

  float aktualna_waga = pobierz_wynik();

  Serial.print("Waga: ");
  Serial.print(aktualna_waga);
  Serial.println(" g");

  wyswietl(aktualna_waga);

  delay(15);
}