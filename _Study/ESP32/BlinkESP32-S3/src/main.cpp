#include <Arduino.h>

// Цветной светодиод платы — адресный (WS2812 или SK6812), а не обычный:
// им управляют посылкой цвета, и digitalWrite(48, HIGH) его не зажжёт.
// Клон N16R8 и DevKitC-1 v1.0 — вывод 48, DevKitC-1 v1.1 — вывод 38.
// На клоне светодиод отзовётся, только если запаяна перемычка RGB.
const int RGB_PIN = 48;


void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  rgbLedWrite(RGB_PIN, 40, 0, 0);   // красный; яркость от 0 до 255, 40 не слепит
  Serial.println("Красный");
  delay(500);

  rgbLedWrite(RGB_PIN, 0, 40, 0);   // зелёный
  Serial.println("Зелёный");
  delay(500);

  rgbLedWrite(RGB_PIN, 0, 0, 40);   // синий
  Serial.println("Синий");
  delay(500);

  rgbLedWrite(RGB_PIN, 0, 0, 0);    // погасить
  delay(500);
}