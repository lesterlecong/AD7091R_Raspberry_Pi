#include "AD7091R.h"

#include <stdint.h>
#include <wiringPi.h>


AD7091R::AD7091R(): 
  m_convstPin(OUT_OF_RANGE_PIN_NUMBER),
  m_csPin(OUT_OF_RANGE_PIN_NUMBER),
  m_clkPin(OUT_OF_RANGE_PIN_NUMBER),
  m_dataPin(OUT_OF_RANGE_PIN_NUMBER) {
}

AD7091R::AD7091R(uint8_t convstPin, uint8_t csPin, uint8_t clkPin, uint8_t dataPin):
  m_convstPin(convstPin),
  m_csPin(csPin),
  m_clkPin(clkPin),
  m_dataPin(dataPin) {
}

AD7091R::~AD7091R() {

}

void AD7091R::convstPin(uint8_t pin) {
  m_convstPin = pin;
}

void AD7091R::csPin(uint8_t pin) {
  m_csPin = pin;
}

void AD7091R::clkPin(uint8_t pin) {
  m_clkPin = pin;
}

void AD7091R::dataPin(uint8_t pin) {
  m_dataPin = pin;
}

uint8_t AD7091R::convstPin() {
  return m_convstPin;
}

uint8_t AD7091R::csPin(){
  return m_csPin;
}

uint8_t AD7091R::clkPin() {
  return m_clkPin;
}

uint8_t AD7091R::dataPin() {
  return m_dataPin;
}

bool AD7091R::begin() {
  if(m_convstPin == OUT_OF_RANGE_PIN_NUMBER ||
     m_csPin == OUT_OF_RANGE_PIN_NUMBER ||
     m_clkPin == OUT_OF_RANGE_PIN_NUMBER ||
     m_dataPin == OUT_OF_RANGE_PIN_NUMBER) {
       return false;
  }

  wiringPiSetup();

  pinMode(m_convstPin, OUTPUT);
  pinMode(m_csPin, OUTPUT);
  pinMode(m_clkPin, OUTPUT);
  pinMode(m_dataPin, INPUT);
	
  digitalWrite(m_csPin, HIGH);
  digitalWrite(m_clkPin, LOW);
  digitalWrite(m_convstPin, HIGH);

  return true;
}

void AD7091R::reset() {
  
  //Start a conversion
  delayMicroseconds(1);
  digitalWrite(m_convstPin, LOW); //Set CONVST Pin to LOW
  delayMicroseconds(1);
  digitalWrite(m_convstPin, HIGH);  //Set CONVST Pin to HIGH

  digitalWrite(m_csPin, LOW);        //Set CS Pin to LOW
  delayMicroseconds(1);

  uint8_t clock_cycle = 0;

  for(clock_cycle = 0; clock_cycle < 4; clock_cycle++) { //4 cycles only to short the cycle; you can choose between 2 to 8
    digitalWrite(m_clkPin, HIGH); //Set CLK Pin to HIGH
    delayMicroseconds(1);
    digitalWrite(m_clkPin, LOW); //Set CLK Pin to LOW
    delayMicroseconds(1);
  }

  digitalWrite(m_csPin, HIGH);

  //Perform Another conversion
  digitalWrite(m_convstPin, LOW); //Set CONVST Pin to LOW
  delayMicroseconds(1);
  digitalWrite(m_convstPin, HIGH);  //Set CONVST Pin to HIGH

  for(clock_cycle = 0; clock_cycle < 12; clock_cycle++) { 
    digitalWrite(m_clkPin, HIGH); //Set CLK Pin to HIGH
    delayMicroseconds(1);
    digitalWrite(m_clkPin, LOW); //Set CLK Pin to LOW
    delayMicroseconds(1);
  }
}

uint16_t AD7091R::data() {
  uint16_t result = 0;
  
  //Start a conversion
  digitalWrite(m_convstPin, LOW); //Set CONVST Pin to LOW
  delayMicroseconds(1);
  digitalWrite(m_convstPin, HIGH);  //Set CONVST Pin to HIGH
  
  digitalWrite(m_csPin, LOW);        //Set CS Pin to LOW
  
  uint8_t clock_cycle = 0;
  for(clock_cycle = 0; clock_cycle < 12; clock_cycle++) { 
    digitalWrite(m_clkPin, HIGH); //Set CLK Pin to HIGH
    delayMicroseconds(1);
    digitalWrite(m_clkPin, LOW); //Set CLK Pin to LOW
    //result = (result << 1) | (digitalRead(m_dataPin) & 0x01);
    digitalRead(m_dataPin);
    delayMicroseconds(1);
  }
  
  delayMicroseconds(1);
  digitalWrite(m_csPin, HIGH);

  return result;
}
