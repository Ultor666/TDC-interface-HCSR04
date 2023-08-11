#include <SPI.h>
#include "tdc7200.h"
#include <NewPing.h>


const int INTB_PIN = 2;

void setup() {
  pinMode(INTB_PIN, INPUT_PULLUP); // Set INTB pin as input with pull-up resistor
  Serial.begin(115200);
}

void loop() {
  // Read the state of the INTB pin
  int intbState = digitalRead(INTB_PIN);

  // Print the state of the INTB pin
  Serial.print("INTB pin state: ");
  Serial.println(intbState);

  delay(1000); // Wait for a second before checking again
}

/*// HC-SR04 configuration
#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define MAX_DISTANCE 200

// TDC7200 configuration
const int INTB_PIN = 2;
int startpin = 4;
int stoppin = 7;
const byte CLOCKOUT = 11;
byte config1, config2;
tdc7200 chip1;

NewPing hc_sr04(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Flag to indicate that a measurement should start
volatile bool measurementStarted = false;

void setup() {
  pinMode(INTB_PIN, INPUT); // Set INTB_PIN as input for interrupt
  attachInterrupt(digitalPinToInterrupt(INTB_PIN), interruptHandler, FALLING);\
  
  pinMode(CLOCKOUT, OUTPUT);
  TCCR1A = bit(COM1A0);
  TCCR1B = bit(WGM12) | bit(CS10);
  OCR1A = 7;

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);

  digitalWrite(3, LOW);
  delay(5);
  digitalWrite(3, HIGH);
  delay(5);

  pinMode(INTB_PIN, INPUT_PULLUP); // Set INTB pin as input with pull-up resistor

  Serial.begin(115200);
}

void loop() {
  // Trigger HC-SR04
  long duration = hc_sr04.ping_median();

  chip1.writeReg(CONFIG1, B00000011);
  chip1.writeReg(CONFIG2, B01000100);

  while (digitalRead(TRIGGER_PIN)) {
    break;
  }

  digitalWrite(startpin, HIGH);
  digitalWrite(startpin, LOW);

  delayMicroseconds(100);

  for (int i = 0; i < 4; i++) {
    digitalWrite(stoppin, HIGH);
    digitalWrite(stoppin, LOW);
    delayMicroseconds(100);
  }
  delay(8);
  digitalWrite(stoppin, HIGH);
  digitalWrite(stoppin, LOW);

  chip1.time1 = chip1.readReg24(TIME1);
  chip1.time2 = chip1.readReg24(TIME2);
  chip1.time3 = chip1.readReg24(TIME3);
  chip1.time4 = chip1.readReg24(TIME4);
  chip1.time5 = chip1.readReg24(TIME5);
  chip1.time6 = chip1.readReg24(TIME6);
  chip1.clockcount1 = chip1.readReg24(CLOCK_COUNT1);
  chip1.clockcount2 = chip1.readReg24(CLOCK_COUNT2);
  chip1.clockcount3 = chip1.readReg24(CLOCK_COUNT3);
  chip1.clockcount4 = chip1.readReg24(CLOCK_COUNT4);
  chip1.clockcount5 = chip1.readReg24(CLOCK_COUNT5);
  chip1.cal1 = chip1.readReg24(CALIBRATION1);
  chip1.cal2 = chip1.readReg24(CALIBRATION2);

  chip1.tof1 = chip1.getTOF(chip1.time1, chip1.time2, chip1.clockcount1, chip1.cal1, chip1.cal2);
  chip1.tof2 = chip1.getTOF(chip1.time1, chip1.time3, chip1.clockcount2, chip1.cal1, chip1.cal2);
  chip1.tof3 = chip1.getTOF(chip1.time1, chip1.time4, chip1.clockcount3, chip1.cal1, chip1.cal2);
  chip1.tof4 = chip1.getTOF(chip1.time1, chip1.time5, chip1.clockcount4, chip1.cal1, chip1.cal2);
  chip1.tof5 = chip1.getTOF(chip1.time5, chip1.time6, chip1.clockcount5, chip1.cal1, chip1.cal2);

  Serial.println();
  Serial.print("  ****************");
  Serial.println();
  Serial.print("* TOF1 = ");
  Serial.print(chip1.tof1, 8);
  Serial.println(" *");
  Serial.print("* TOF2 = ");
  Serial.print(chip1.tof2, 8);
  Serial.println(" *");
  Serial.print("* TOF3 = ");
  Serial.print(chip1.tof3, 8);
  Serial.println(" *");
  Serial.print("* TOF4 = ");
  Serial.print(chip1.tof4, 8);
  Serial.println(" *");
  Serial.print("* TOF5 = ");
  Serial.print(chip1.tof5, 8);
  Serial.println(" *");
  Serial.print("  ****************");
  Serial.println();

  if (digitalRead(INTB_PIN)) {
    Serial.println("Interrupt");
  }

  if (duration != 0) {
    Serial.print("Distance: ");
    Serial.print(duration / 29.1); // Convert to cm
    Serial.println(" cm");

    // Use HC-SR04 distance as a trigger to stop TDC7200 measurement
    // You can modify the distance threshold as needed
        if (duration / 29.1 >= 10.0) {
      // Stop the TDC7200 measurement
      digitalWrite(stoppin, HIGH);
      digitalWrite(stoppin, LOW);
      delayMicroseconds(100);
      digitalWrite(stoppin, HIGH);
      digitalWrite(stoppin, LOW);

      // Wait for the measurement to complete
      delay(8);

      // Read and process TDC7200 data as before
      // ...

      // Print the TDC7200 results
      // ...

      // Print the HC-SR04 distance
      Serial.print("HC-SR04 Distance: ");
      Serial.print(duration / 29.1); // Convert to cm
      Serial.println(" cm");
    }
  }
}
// ISR for the external trigger signal
void interruptHandler() {
  // Set the measurementStarted flag to true
  measurementStarted = true;
}*/
