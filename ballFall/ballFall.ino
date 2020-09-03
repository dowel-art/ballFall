/*
   Dowel
   ボール落下装置ソースコード
   20.09.03 Thu.
*/

#define PIN_SOL_FALL 2
#define PIN_SOL_LINE 3
#define PIN_SW 7
#define PIN_LED 9
#define PIN_SENSOR A0
#define THRESHOLD 980
#define TIMEOUT 2000

long timeNow = 0;
long timeThen = 0;

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

  //1.トリガー待ち
  Serial.println("trigger waiting...");
  digitalWrite(PIN_LED, HIGH);
  while (1) {
    if (digitalRead(PIN_SW) == LOW) {
      delay(500);
      if (digitalRead(PIN_SW) == LOW)
        break;
    }
    delay(100);
  }
  digitalWrite(PIN_LED, LOW);

  //2.ボール落下
  Serial.println("ball fall");
  ballFall(true);
  delay(500);
  ballFall(false);
  delay(500);

  //3.ボールロード
  Serial.println("ball loading...");
  ballLine(true);
  delay(1000);
  ballLine(false);

  //ボール通過待ち
  Serial.println("Waiting to pass...");
  timeThen = millis();
  while (ballCheck() == false) {
    timeNow = millis();
    if ((timeNow - timeThen) > TIMEOUT)
      break;
  }
  delay(1000);
}
