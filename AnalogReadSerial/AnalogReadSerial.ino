int photoR_in = A0;
int ledR_out = 9;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(photoR_in, INPUT);
  pinMode(ledR_out, OUTPUT);
}

void loop() {
  sensorValue = analogRead(photoR_in);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(ledR_out, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(2);
}
