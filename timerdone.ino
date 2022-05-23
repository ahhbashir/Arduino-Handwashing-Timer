#include <TM1637Display.h>
#include "NewPing.h"
#define TRIGGER_PIN 13
#define ECHO_PIN 12

#define CLK 6
#define DIO 7

#define TEST_DELAY   1000

TM1637Display display(CLK, DIO);

int count = 20;
uint8_t data[] = {0, 0, 0, 0};
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

float duration, distance;

const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  distance = sonar.ping_cm();
  Serial.print("Distance = ");
  Serial.println(distance);
  
  if (distance < 10 && distance > 0){
    for(int count = 20; count >= 0; count --){
      display.setBrightness(0x0f);

      data[3] = display.encodeDigit(count/1 % 10);
      data[2] = display.encodeDigit(count/10 % 10);
      data[1] = display.encodeDigit(count/100 % 10);
      data[0] = display.encodeDigit(count/1000 % 10);
      display.setSegments(data);
      delay(TEST_DELAY);
    }
  display.setSegments(done);
  }
}
