const int buttonPin = 2;
const int RLED = 3;
const int GLED = 6;
const int BLED = 9;

int oldButtonState = 0;
int buttonState = 0;
bool recordTimeForPressBtn = false;
long recentTimeForPressBtn = 0;
long previousTimeForPressBtn = 0;
int intervalForPressBtn = 500;

bool changeModeForAlOrB = false;
bool modeAlOrB; //true = AlwaysLight, false = Bling Mode

bool recordTimeForChangeColor = true;
long recentTimeForChangeColor = 0;
long previousTimeForChangeColor = 0;
int intervalForChangeColor = 1000;


bool recordTimeForBling = true;
long recentTimeForBling = 0;
long previousTimeForBling = 0;
int intervalForBling = 250;
bool blingModeLightOn = true;

int colorNum = 0;
int Rcolor = 0;
int Bcolor = 255;
int Gcolor = 255;

//ModeFade
bool fadeOn = true;
long fadeTimer = 0;
int Rfade = 255;
int Bfade = 255;
int Gfade = 255;

void setup() {
  Serial.begin(9600);

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    ModeFade();
    TimerForPressBtn();
  } 
  else {
    if (changeModeForAlOrB) {
      modeAlOrB = !modeAlOrB;
      changeModeForAlOrB = false;
      Serial.print("change mode");
    }
    recordTimeForPressBtn = false;
    TimerForChangeColor();
    if (modeAlOrB)
      ModeAlwaysLight();
    else
      ModeBling();
  }
}

void TimerForChangeColor() {
  recentTimeForChangeColor = millis();
  if (recentTimeForChangeColor - previousTimeForChangeColor >= intervalForChangeColor) {
    previousTimeForChangeColor = recentTimeForChangeColor;
    if (buttonState == LOW)
      ChangeColor();
  }
}

void TimerForPressBtn() {
  // 紀錄按下去的時間
  if (!recordTimeForPressBtn) { 
    previousTimeForPressBtn = millis();
    recordTimeForPressBtn = true;
  }

  if (!changeModeForAlOrB) {
    recentTimeForPressBtn = millis();
    if (recentTimeForPressBtn - previousTimeForPressBtn >= intervalForPressBtn) {
      changeModeForAlOrB = true;
    }
  }
}

void TimerForChangeBling() {
  recentTimeForBling = millis();
  if (recentTimeForBling - previousTimeForBling >= intervalForBling) {
    previousTimeForBling = recentTimeForBling;
    blingModeLightOn = !blingModeLightOn;
    Serial.print("bling");
  }
}




void ModeFade() {
    if (fadeOn && millis() - fadeTimer > 30) {
    analogWrite(RLED, Rfade);
    analogWrite(BLED, Bfade);
    analogWrite(GLED, Gfade);
    
    Rfade -= 5;
    Bfade -= 5;
    Gfade -= 5;

    if (Rfade < 0)
      Rfade = 0;
    if (Bfade < 0)
      Bfade = 0;
    if (Gfade < 0)
      Gfade = 0;

    if (Rfade == 0 && Bfade == 0 && Gfade == 0)
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

void ModeAlwaysLight() {
  analogWrite(RLED, Rcolor);
  analogWrite(GLED, Gcolor);
  analogWrite(BLED, Bcolor);
}

void ModeBling() {
  TimerForChangeBling();
  if (blingModeLightOn) {
    analogWrite(RLED, Rcolor);
    analogWrite(GLED, Gcolor);
    analogWrite(BLED, Bcolor);
  }
  else {
    analogWrite(RLED, 255);
    analogWrite(GLED, 255);
    analogWrite(BLED, 255);
  }
}



void ChangeColor() {
  int colors[5][3] = {
    {0, 255, 255},    //R
    {0, 0, 255},    //Y
    {255, 0, 255},  //G
    {255, 255, 0},  //B
    {0, 255, 0},    //P
  };

  // 更新 colorNum，使用三元运算符
  colorNum = (colorNum == 4) ? 0 : colorNum + 1;

  // 从数组中获取对应的 RGB 值
  Rcolor = colors[colorNum][0];
  Gcolor = colors[colorNum][1];
  Bcolor = colors[colorNum][2];
}