#include <Adafruit_NeoPixel.h>
#define dirPin 2
#define stepPin 3
#define LED_PIN 6
#define LED_COUNT 30
#define stepsPerRevolution 400
int breathSpeed = 2000;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW);

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  int breathControl = 0;
  int breathOfset = 2;
  int ledBrightness = 0;
//  int breathSpeed = 2000;
  digitalWrite(dirPin, HIGH);

  int number = rand() % 100;
  if (number > 50) {
    breathSpeed += 100;
  } else {
    breathSpeed -= 100;
  };
  if (breathSpeed > 3000) {
    breathSpeed == 2000;
  };

  //rotation forward
  for(int i = 0; i < stepsPerRevolution; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(breathSpeed + breathControl);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(breathSpeed + breathControl);
      breathControl += breathOfset;
      if (ledBrightness < 255) {
        uint32_t rgbcolor = strip.ColorHSV(22000, 255, ledBrightness);
        ledBrightness += 1;
        strip.fill(rgbcolor);
        strip.show();
      };
      Serial.println(ledBrightness);
    }
  delay(2000);
  breathControl = 0;
  digitalWrite(dirPin, LOW);

  ledBrightness = 255;
  //rotation back
  for(int i = 0; i < stepsPerRevolution; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(breathSpeed + breathControl);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(breathSpeed + breathControl);
      breathControl += breathOfset;
      if (ledBrightness > 0) {
        uint32_t rgbcolor = strip.ColorHSV(22000, 255, ledBrightness);
        ledBrightness -= 1;
        strip.fill(rgbcolor);
        strip.show();
      };
    }
    delay(2000);
}
