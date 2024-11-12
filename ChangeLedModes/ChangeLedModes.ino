// Button Output Pin 按鈕的接腳
const int buttonPin = 2;
// RGB LED Output Pin LED燈的接腳
const int RLED = 3;
const int BLED = 6;
const int GLED = 9;

// The color of RGB LED 要顯示泡沫的顏色
int Rcolor = 0;
int Bcolor = 0;
int Gcolor = 0;

// 紀錄按鈕狀態
int buttonState = 0;
int oldButtonState = 0;  // 紀錄前一次按鈕狀態 (避免按鈕反彈延遲五百毫秒)

// 記錄當下時間
bool recordTime = true;
long buttonTimer;       // 紀錄按鈕按下時間

// 紀錄顏色的編號
int colorNum = 0;

int mode = 0;

bool blingOFF = true;
long blingTimer = 0;

bool fadeOn = true;
long fadeTimer = 0;
int Rfade = 255;
int Bfade = 255;
int Gfade = 255;


void setup() {
  pinMode(buttonPin, INPUT);
}

void (*ledModes[4])() = { ModeOff, ModeStay, ModeBling, ModeFading };

void loop() {
  CheckButton();
  if (mode >= 0 && mode < 4)
    ledModes[mode]();
}

void ChangeMode() {
  int modeNum = sizeof(ledModes) / sizeof(ledModes[0]);
  if (oldButtonState == 1 && buttonState == 0)
    mode = (mode == modeNum - 1) ? 0 : mode + 1; // 三元運算式 (condition) ? expression_if_true : expression_if_false;
}

void CheckButton() {
  oldButtonState = buttonState;
  buttonState = digitalRead(buttonPin);
  if (recordTime && buttonState == 1) {
    buttonTimer = millis();
    recordTime = false;
  }
  
  if (oldButtonState == 1 && buttonState == 0) {
    (millis() - buttonTimer > 300) ? ChangeMode() : ChangeColor();
    recordTime = true;
  }
}

void ChangeColor() {
  // 定义颜色数组，每个子数组表示一种颜色的 RGB 值
  int colors[6][3] = {
    {0, 0, 0},      // colorNum == 0
    {0, 255, 255},  // colorNum == 1
    {255, 0, 255},  // colorNum == 2
    {255, 255, 0},  // colorNum == 3
    {0, 0, 255},    // colorNum == 4
    {255, 0, 0}     // colorNum == 5
  };

  // 更新 colorNum，使用三元运算符
  colorNum = (colorNum == 5) ? 0 : colorNum + 1;

  // 从数组中获取对应的 RGB 值
  Rcolor = colors[colorNum][0];
  Bcolor = colors[colorNum][1];
  Gcolor = colors[colorNum][2];
}

void ModeStay() {
  analogWrite(RLED, Rcolor);
  analogWrite(BLED, Bcolor);
  analogWrite(GLED, Gcolor);
}

void ModeOff() {
  analogWrite(RLED, 255);
  analogWrite(GLED, 255);
  analogWrite(BLED, 255);
}

void ModeBling() {
  if (blingOFF && millis() - blingTimer > 200) {
    blingTimer = millis();
    analogWrite(RLED, Rcolor);
    analogWrite(BLED, Bcolor);
    analogWrite(GLED, Gcolor);
    blingOFF = false;
  }
  
  else if (!blingOFF && millis() - blingTimer > 200) {
    blingTimer = millis();
    analogWrite(RLED, 255);
    analogWrite(BLED, 255);
    analogWrite(GLED, 255);
    blingOFF = true;
  }
}

void ModeFading() {
  if (fadeOn && millis() - fadeTimer > 30) {
    analogWrite(RLED, Rfade);
    analogWrite(BLED, Bfade);
    analogWrite(GLED, Gfade);
    
    Rfade -= 5;
    Bfade -= 5;
    Gfade -= 5;

    if (Rfade < Rcolor)
      Rfade = Rcolor;
    if (Bfade < Bcolor)
      Bfade = Bcolor;
    if (Gfade < Gcolor)
      Gfade = Gcolor;

    if (Rfade == Rcolor && Bfade == Bcolor && Gfade == Gcolor)
      fadeOn = false;
    fadeTimer = millis();
  } 
  else if (!fadeOn && millis() - fadeTimer > 30) {
    analogWrite(RLED, Rfade);
    analogWrite(BLED, Bfade);
    analogWrite(GLED, Gfade);

    Rfade += 5;
    Bfade += 5;
    Gfade += 5;

    if (Rfade > 255)
      Rfade = 255;
    if (Bfade > 255)
      Bfade = 255;
    if (Gfade > 255)
      Gfade = 255;
    if (Rfade == 255 && Bfade == 255 && Gfade == 255)
      fadeOn = true;
    fadeTimer = millis();
  }
}

