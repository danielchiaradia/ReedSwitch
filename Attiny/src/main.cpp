#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define ESP_POWER_PIN PB4
#define SWITCH_INPUT_PIN PB1
#define ESP_POWER_IN_PIN PB0

void setup()
{
  pinMode(SWITCH_INPUT_PIN, INPUT);
  digitalWrite(SWITCH_INPUT_PIN, INPUT_PULLUP);
  pinMode(ESP_POWER_PIN, OUTPUT);
  digitalWrite(ESP_POWER_PIN, HIGH);

  pinMode(ESP_POWER_IN_PIN, INPUT_PULLUP);
}

void resetWatchDog ()
{
  MCUSR = 0;
  WDTCR = bit ( WDCE ) | bit ( WDE ) | bit ( WDIF ); // allow changes, disable reset, clear existing interrupt
  WDTCR = bit ( WDIE ) | bit ( WDP2 )| bit ( WDP1 ); // set WDIE ( Interrupt only, no Reset ) and 1 second TimeOut
                                                     
  wdt_reset();                            // reset WDog to parameters
  
} // end of resetWatchDog ()


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
  int maxDelay = 15000;
  while (digitalRead(ESP_POWER_IN_PIN) == LOW && maxDelay > 0) {
    delay(1);
    maxDelay--;
  }
  digitalWrite(ESP_POWER_PIN, HIGH);
}