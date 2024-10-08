const int btn = 2;
const int ledR = 3;
const int ledG = 4;
const int ledB = 5;

int btnState = 0;
bool btnPressed = false;
int ledColor = 0;

int colors[7][3] = {
  {1, 0, 0},   // 紅
  {1, 1, 0},   // 黃
  {0, 1, 0},   // 綠
  {0, 0, 1},   // 藍
  {0, 1, 1},   // 靛
  {1, 0, 1},   // 紫
  {1, 1, 1}    // 白
};

String colorNames[7] = {"red", "yellow", "green", "blue", "cyan", "purple", "white" };
String currentColorName = colorNames[0];

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  pinMode(btn, INPUT);

  Serial.begin(9600);
}

void loop() {
  btnState = digitalRead(btn);
  
  if (btnState == HIGH && !btnPressed) {
    // 每次按下按鈕，顏色循環
    ledColor = (ledColor + 1) % 7;
    currentColorName = colorNames[ledColor];
    btnPressed = true;
  }
  else if (btnState == LOW && btnPressed) {
    btnPressed = false;
  }
  
  digitalWrite(ledR, colors[ledColor][0] ? LOW : HIGH);
  digitalWrite(ledG, colors[ledColor][1] ? LOW : HIGH);
  digitalWrite(ledB, colors[ledColor][2] ? LOW : HIGH);
  Serial.print("Current Color: ");
  Serial.println(currentColorName);
}
