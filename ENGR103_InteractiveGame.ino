#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

volatile bool decFlag;
volatile bool incFlag;
volatile bool switchFlag;

AsyncDelay delay_2s; //How long should I run timer for?

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(4), decISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), incISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(7), gameSwitch, CHANGE);
}

// Challenge functions? make it a bop it?
// Have difficulty settings that can be changed before starting the game?
// Show points upon failure using lights? Make noise on failure? on success?
// light in a circle, press button to stop at right spot? Different speeds and locations?
// Creeping lights from middle, press both buttons together
// March, full lights on left, press left button, then right, then left (left, right, left, with noise?)
// Yell, lights up, moves forward when it detects a loud enough noise
// rand function and AsyncDelay are your friends
// timed switch function where default case is failure? Would have to use multiple switch functions for each challenge functions

void loop() {

}

void decISR() {
  decFlag = 0;
}

void incISR() {
  incFlag = 0;
}

void gameSwitch() {
  swtichFlag = 0;
}