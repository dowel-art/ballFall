/*
   Dowel
   ボール落下装置 動作テスト用ソースコード
   20.09.03 Thu.
*/

#define PIN_SOL_FALL 2
#define PIN_SOL_LINE 3
#define PIN_SW 7
#define PIN_LED 9
#define PIN_SENSOR A0
#define THRESHOLD 980

void setup() {
  pinMode(PIN_SOL_FALL, OUTPUT);
  pinMode(PIN_SOL_LINE, OUTPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);

  ledFlash(); //LED点滅
  solReset(); //ソレノイドリセット
}

//LED点滅
void ledFlash() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(300);
    digitalWrite(PIN_LED, LOW);
    delay(300);
  }
}

//投擲装置のソレノイド制御
void ballFall(bool state) {
  if (state == true)
    digitalWrite(PIN_SOL_FALL, HIGH);
  else
    digitalWrite(PIN_SOL_FALL, LOW);
}

//送り装置のソレノイド制御
void ballLine(bool state) {
  if (state == true)
    digitalWrite(PIN_SOL_LINE, HIGH);
  else
    digitalWrite(PIN_SOL_LINE, LOW);
}

//ソレノイドリセット
void solReset() {
  digitalWrite(PIN_SOL_LINE, LOW);
  digitalWrite(PIN_SOL_FALL, LOW);
}

//通過センサのチェック
bool ballCheck() {
  if (analogRead(PIN_SENSOR) < THRESHOLD) return true;
  else return false;
}

void loop() {
  //1.ボール落下
  Serial.println("ball fall");
  ballFall(true);
  delay(1000);
  ballFall(false);
  delay(1000);

  //2.ボールロード
  Serial.println("ball load");
  ballLine(true);
  delay(1000);
  ballLine(false);
  delay(1000);
}
