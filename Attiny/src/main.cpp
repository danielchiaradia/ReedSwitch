#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define ESP_POWER_PIN PB4
#define SWITCH_INPUT_PIN PB1

void setup()
{
  pinMode(SWITCH_INPUT_PIN, INPUT);
  digitalWrite(SWITCH_INPUT_PIN, INPUT_PULLUP);
  pinMode(ESP_POWER_PIN, OUTPUT);
  digitalWrite(ESP_POWER_PIN, HIGH);
}

void sleep()
{

  GIMSK |= _BV(PCIE);                  // Enable Pin Change Interrupts
  PCMSK |= _BV(PCINT1);                // Use PB1 as interrupt pin
  ADCSRA &= ~_BV(ADEN);                // ADC off
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  sleep_enable();
  sei();          // Enable interrupts
  sleep_cpu();    // sleep

  cli();                 // Disable interrupts
  PCMSK &= ~_BV(PCINT1); // Turn off PB1 as interrupt pin
  sleep_disable();       // Clear SE bit
  ADCSRA |= _BV(ADEN);   // ADC on

  sei(); // Enable interrupts
} // sleep

ISR(PCINT0_vect)
{
  // This is called when the interrupt occurs, but I don't need to do anything in it
}

void loop()
{
  sleep();
  digitalWrite(ESP_POWER_PIN, LOW);
  delay(500);
  digitalWrite(ESP_POWER_PIN, HIGH);
}