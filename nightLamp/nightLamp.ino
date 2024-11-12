int ledPin = 9; // LED connected to digital pin 9
bool ledOn = false;
int analogInput;
int oldInput;

void setup() {
}

void loop() {
  oldInput = analogInput;
  analogInput = analogRead(A0);
  
  if (analogInput < 300) { // Set the threshold resistance value for the bulb to turn off.
    if (ledOn) {
      ledOn = false;
      turnOff(oldInput);
    }
  } else {
    if (!ledOn) {
      ledOn = true;
      turnOn(analogInput);
    } else {
      int setValue = map(analogInput, 200, 1023, 255, 0);
      analogWrite(ledPin, setValue);
    }
  }
}

void turnOn(int goal) {
  int brightness = map(goal, 300, 1023, 255, 0);
  for (int fadeValue = 0; fadeValue <= brightness; fadeValue++) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(6);
  }
}

void turnOff(int now) {
  int brightness = map(now, 300, 1023, 255, 0);
  for (int fadeValue = 255; fadeValue >= brightness; fadeValue--) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(6);
  }
}
