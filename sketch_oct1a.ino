const int btn = 2;
const int ledR = 3;
const int ledG = 4;
const int ledB = 5;

int btnState = 0;
int ledColor = 0;

// 定義紅、橙、黃、綠、藍、紫、白的數位值 (1代表HIGH，0代表LOW)
int colors[7][3] = {
  {1, 0, 0},   // 紅
  {1, 1, 0},   // 黃
  {0, 1, 0},   // 綠
  {0, 0, 1},   // 藍
  {0, 1, 1},   // 靛
  {1, 0, 1},   // 紫
  {1, 1, 1}    // 白
};

void setup() {
  // 設定LED腳位為輸出
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  pinMode(btn, INPUT);
}

void loop() {
  // 讀取按鈕狀態
  btnState = digitalRead(btn);
  
  if (btnState == HIGH){
    // 每次按下按鈕，顏色循環
    ledColor = (ledColor + 1) % 7;
    delay(200); // 避免按鈕按下時重複觸發太快
  }
  
  // 設定RGB燈的狀態 (HIGH 或 LOW)
  digitalWrite(ledR, colors[ledColor][0] ? LOW : HIGH);
  digitalWrite(ledG, colors[ledColor][1] ? LOW : HIGH);
  digitalWrite(ledB, colors[ledColor][2] ? LOW : HIGH);
}
