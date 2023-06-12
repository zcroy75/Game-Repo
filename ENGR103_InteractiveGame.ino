#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

// Volatile Variables
volatile bool leftFlag = 0;
volatile bool rightFlag = 0;

// Variables
bool setState;
int gameRand;
int score;
int lightCheck;
int soundValue;

AsyncDelay delay_2s; // 2 second long timer setup

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  delay_2s.start(2000, AsyncDelay::MILLIS);

  // Interrupts
  attachInterrupt(digitalPinToInterrupt(4), leftISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), rightISR, FALLING);
}

void loop() {
  CircuitPlayground.clearPixels();
  // Start game by pressing left button
  if(leftFlag || setState) {
    leftFlag = 0;
    setState = 0;
    gameRand = random(0, 2); // Randomly choose task
    if(gameRand == 0) {
      creeping();
    }
    if(gameRand == 1) {
      snap();
    }
  }
}

void creeping() { // Creeping lights from middle, press right button to continue
  delay_2s.start(2000, AsyncDelay::MILLIS);
  volatile bool creepState = 1;

  int j = 4;
  for(int i = 0; i < 3; i++) {
    // Lights
    CircuitPlayground.setPixelColor(i, 255, 255, 0);
    CircuitPlayground.setPixelColor(i+5, 255, 255, 0);
    CircuitPlayground.setPixelColor(j, 255, 255, 0);
    CircuitPlayground.setPixelColor(j+5, 255, 255, 0);
    j--;

    if(rightFlag && creepState) { // Success condition
      score++;
      rightFlag = 0;
      creepState = 0;
      setState = 1;
      loop(); // Return to loop for next task
    }

    else if(delay_2s.isExpired()) { // Failure condition
      creepState = 0;
      failure();
    }
    delay(1000);
  }
}

void snap() { // Lights up, make loud enough noise to continue
  delay_2s.start(2000, AsyncDelay::MILLIS);
  volatile bool snapState = 1;

  while(snapState) { // loop task for 2 seconds
    for(int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 255, 255); // Set Lights
    }

    soundValue = CircuitPlayground.mic.soundPressureLevel(10); // Read sound level

    if(soundValue > 95) { // Success conditon
      score++;
      snapState = 0;
      setState = 1;
      loop(); // Return to loop for next task
    }

    else if(delay_2s.isExpired()) { // Failure condition
      snapState = 0;
      failure();
      return;
    }
  }
}

void failure() { // Function for when player fails task
  Serial.println(score); // Print score to player
  score = 0; // Reset score

  // Flash red lights to show player failed
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 255, 0, 0); // Set lights red
    }
    delay(100);

    CircuitPlayground.clearPixels(); // Clear lights to show flash effect
    delay(100);
  }
  loop();
}

void leftISR() { // Left button ISR
  leftFlag = 1;
}

void rightISR() { // Right button ISR
  rightFlag = 1;
}
