const int buttonPin = 2;
const int ledR = 9;
const int ledG = 7;

int buttonState = 0;
int ledColorState = 1; // 0 = noColor, 1 = G, 2 = Y, 3 = R

long currentMillis = 0;
long previousMillis = 0; 
int intervalG = 1500;
int intervalY = 700;
int intervalR = 1500;
int currentInterval = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  Serial.println(ledColorState);
  Serial.println(currentInterval);
  Serial.println(previousMillis);
  buttonState = digitalRead(buttonPin);

  currentMillis = millis();
  if (buttonState == 1)
    lightOff();
  else {
    trafficLight();
    if (currentMillis - previousMillis >= currentInterval) {
      previousMillis = currentMillis;
      if (ledColorState >= 3)
        ledColorState = 1;
      else
        ledColorState += 1;
    } 
  }
}

void lightOff() {
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  ledColorState = 0;
}

void trafficLight() {
  if (ledColorState == 1) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    currentInterval = intervalG;
  }
  else if (ledColorState == 2) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    currentInterval = intervalY;
  }
  else {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    currentInterval = intervalR;
  }
}

