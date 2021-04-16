const int waterSens = A0; //define water sensor and set to pin A0
const int led = 9; //define led and set to pin 9
const int gasSens = A1;
int sensorVal;//create a sensor value variable

#include <Wire.h>
#include <AM2320.h>
#include <TM1637Display.h>
AM2320 th;

#define CLK 10
#define DIO 11

const uint8_t HOOG[] = {
  SEG_F | SEG_B | SEG_G | SEG_E | SEG_C,           // d
  SEG_A | SEG_B | SEG_F | SEG_C | SEG_D | SEG_E,   // O
  SEG_A | SEG_B | SEG_F | SEG_C | SEG_D | SEG_E,                        // n
  SEG_A | SEG_F | SEG_B | SEG_G | SEG_C | SEG_D          // E
  };

const uint8_t GOED[] = {
  SEG_A | SEG_F | SEG_B | SEG_G | SEG_C | SEG_D,           // d
  SEG_A | SEG_B | SEG_F | SEG_C | SEG_D | SEG_E,   // O
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,                           // n
  SEG_D | SEG_E | SEG_C | SEG_G | SEG_B           // E
  };


TM1637Display display(CLK, DIO);

void setup() {
 Serial.begin(9600);//begin the serial monitor
 pinMode(led, OUTPUT);
}

void loop() {
  int sensorVal = analogRead(waterSens); 
  int gasVal = analogRead(gasSens); 
  display.setBrightness(0x0f);
  Serial.print("W=");
  if (sensorVal > 0) {
    Serial.println("1");
    display.setSegments(HOOG);
    delay(3000);
    } else {
      Serial.println("0");
      display.setSegments(GOED);
      }
  // Serial.println(sensorVal);

  switch(th.Read()) {
    case 2:
      Serial.println("CRC failed");
      break;
    case 1:
      Serial.println("Sensor offline");
      break;
    case 0:
      Serial.print("V=");
      Serial.println(th.h); 
      Serial.print("T=");
      Serial.println(th.t);
      break;
  }
  Serial.print("G=");
  if (gasVal > 500) {
    Serial.println("1");
    display.setSegments(HOOG);
    delay(3000);
    } else {
      Serial.println("0");
      display.setSegments(GOED);
      }
  // Serial.println(gasVal);

  delay(2400);
}
