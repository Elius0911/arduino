int ledPin = 9; // LED connected to digital pin 9
const int inputPin = 2;

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int digitalInput = digitalRead(inputPin);
  if (digitalInput == 1) {
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect:
      delay(30);
    }
  } else {
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect:
      delay(30);
    }
  }
}
