#include <Adafruit_NeoPixel.h>
#define LED_PIN 7
#define LED_PIN2 6
#define LED_COUNT 100
#define stepsPerRevolution 255
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_RGBW);

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  int ledColor = 22000; // 22000 = red
  int ledOpacity = 0;
  int ledBrightness = 0;
  int breathSpeed = 4; // 0 = fast; 5 = slow
  int breathPause = 2000; // 1000 = fast; 2000 = slow

  // RNG breath alternator
  int number = rand() % 100;
  if (number > 40) {
    breathSpeed += 1;
  } else {
    breathSpeed -= 1;
  };
  
  // breathSpeed catch
  if (breathSpeed > 10) {
    breathSpeed -= 1;
  };

  // breathSpeed color change
  if (breathSpeed > 4) {
    ledOpacity = 255;
    ledColor = 22000;
  }
  if (breathSpeed < 4) {
     ledOpacity = 0;
     ledColor = 22000;
  }

  //breathe in
  for(int i = 0; i < stepsPerRevolution; i++)
    {
      if (ledBrightness < 255) {
        uint32_t rgbcolor = strip.ColorHSV(ledColor, ledOpacity, ledBrightness);
        uint32_t rgbcolor2 = strip2.ColorHSV(ledColor, ledOpacity, ledBrightness);
        ledBrightness += 1;
        strip.fill(rgbcolor);
        strip2.fill(rgbcolor2);
        strip.show();
        strip2.show();
        delay(breathSpeed);
      };
      Serial.println(ledBrightness);
    }
  delay(breathPause);

  ledBrightness = 255;
  //breathe out
  for(int i = 0; i < stepsPerRevolution; i++)
    {
      if (ledBrightness > 0) {
        uint32_t rgbcolor = strip.ColorHSV(ledColor, ledOpacity, ledBrightness);
        uint32_t rgbcolor2 = strip2.ColorHSV(ledColor, ledOpacity, ledBrightness);
        ledBrightness -= 1;
        strip.fill(rgbcolor);
        strip2.fill(rgbcolor2);
        strip.show();
        strip2.show();
        delay(breathSpeed);
      };
    }
    delay(breathPause);
}
