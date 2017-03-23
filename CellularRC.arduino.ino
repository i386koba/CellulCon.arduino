
// サーボモータ動作確認用プログラム
/*
  http://tetsuakibaba.jp/index.php?page=workshop/ServoBasis/main
  シリアルモニタからサーボを操作可能
  r: サーボ値読み取り
  800-2200: 0度〜90度設定

  a: attach(9)
  d: detach()

  http://marupeke296.com/EL_Ard_No9_ServoMotor.html
  http://www.vstone.co.jp/vs_wiki/main/wiki.cgi?page=Arduino%A4%C7%BB%CF%A4%E1%A4%EB%A5%ED%A5%DC%A5%C3%A5%C8%C0%A9%B8%E6
  http://wacho.main.jp/Elec/Servo_Driver/Servo_Driver.html
  http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q14109772659
  http://otonaradicon.com/arrc/

  ＤＦＲｄｕｉｎｏ　Ｐｒｏ　Ｍｉｎｉ　Ｖ１．３（１６Ｍ５Ｖ３２８）
  http://akizukidenshi.com/catalog/g/gM-06682/
  ブートローダー：Ａｒｄｕｉｎｏ　Ｐｒｏ／Ｐｒｏ　Ｍｉｎｉ　（５Ｖ，　１６ＭＨｚ）　ｗ／　Ａｔｍｅｇａ３２８
  Ａｒｄｕｉｎｏ Ｐｒｏ Ｍｉｎｉ 接続図
  http://i.stack.imgur.com/oOtkU.png
  PWM　３，５，６，９，１０，１１Pin
*/

#include <Servo.h>
Servo sv2;
Servo sv3;
Servo sv4;
Servo sv5;
Servo sv6;
Servo sv7;
Servo sv8;
Servo sv11;
Servo sv12;
//Servo sv13;
int analog0 = 0;
int analog1 = 0;
int i = 7;
int inPin = 14;   // デジタルピン14にホール素子
int hallVal = 0;     // 読み取った値を保持する変数
int lasthallVal = 0;     // 前回読み取った値を保持する変数
int hallCount = 0; //ホール通過カウント
unsigned long lastTime;
boolean servoAttached = false;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT); //LED表示
  //ホールセンサーＵＳ１８８１ＬＵＡ http://akizukidenshi.com/catalog/g/gI-05274/
  //オープンドレイン出力
  //オープンコレクタ出力の場合はプルアップ回路が必須 http://play-arduino.seesaa.net/article/427884258.html
  //Arduino 新機能 pinMode関数の第2引数にINPUT_PULLUP http://mag.switch-science.com/2013/05/23/input_pullup/
  pinMode(inPin, INPUT_PULLUP);// ホール素子用に入力に設定
  lastTime = millis();
}

void loop()
{
  //TODO attachInterrupt(interrupt, function, mode) http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=3045
  //Arduino Hall Effect Sensor Project http://diyhacking.com/projects/ArduinoHallEffect.ino
  hallVal = digitalRead(inPin);  // 入力ピンを読む
  if ( hallVal != lasthallVal) {
    lasthallVal = hallVal;
    if (hallVal == 1) {
      hallCount++;
    }
  }

  //Bt通信監視
  if (servoAttached && lastTime > millis() + 1100) {
    sv2.writeMicroseconds(1500);
    sv3.writeMicroseconds(1500);
    sv4.writeMicroseconds(1500);
    sv5.writeMicroseconds(1500);
    sv6.writeMicroseconds(1500);
    sv7.writeMicroseconds(1500);
    sv8.writeMicroseconds(1500);
    sv11.writeMicroseconds(1500);
    sv12.writeMicroseconds(1500);
    //sv13.writeMicroseconds(1500);
  }

  int ret;
  if ( Serial.available() > 0 ) {
    lastTime = millis();
    digitalWrite(13, HIGH); //LED点灯
    int d = Serial.read();

    if ( d == 'a' ) {
      sv2.attach(2, 800, 2200);
      sv3.attach(3, 800, 2200);
      sv4.attach(4, 800, 2200);
      sv5.attach(5, 800, 2200);
      sv6.attach(6, 800, 2200);
      sv7.attach(7, 800, 2200);
      sv8.attach(8, 800, 2200);
      sv11.attach(11, 800, 2200);
      sv12.attach(12, 800, 2200);
      //sv13.attach(13, 800, 2200);
      servoAttached = true;
      Serial.println("Servo Attached");
      hallCount = 0;
    }
    else if ( d == 'd' ) {
      sv2.detach();
      sv3.detach();
      sv4.detach();
      sv5.detach();
      sv6.detach();
      sv7.detach();
      sv8.detach();
      sv11.detach();
      sv12.detach();
      //sv13.detach();
      servoAttached = false;
      Serial.println("Servo Detached");
    }
    else if ( d == 'r' ) {
      if (hallCount != 0) {
        Serial.println("RPS:" + String(hallCount, DEC));
        //"Servo: " + String(sv9.read(), DEC) + " : " + String(sv10.read(), DEC));
        hallCount = 0;
      } else { //A3 Batt Volte 
        int batValue = analogRead(A3);
        Serial.println("BAT:" + String(batValue, DEC));
      }
    }
    else if ( '0' <= d && d <= '9' ) {
      d -= '0';
      if (i == 7) {
        analog0 = d * 1000;
      }
      if (i == 6) {
        analog0 += d * 100;
      }
      if (i == 5) {
        analog0 += d * 10;
      }
      if (i == 4) {
        analog0 += d;
      }
      if (i == 3) {
        analog1 = d * 1000;
      }
      if (i == 2) {
        analog1 += d * 100;
      }
      if (i == 1) {
        analog1 += d * 10;
      }
      if (i == 0) {
        analog1 += d;
        Serial.println("analog0  : " + String(analog0, DEC));
        Serial.println("analog1 : " + String(analog1, DEC));
      }
      i--;
    }
    else if ( d == 'm' ) {
      sv11.writeMicroseconds(analog0);
      sv12.writeMicroseconds(analog1);
      analog0 = 0;
      analog1 = 0;
      i = 7;
    } else if ( d == 'x' ) {
      //sv5.writeMicroseconds(analog9);
      //moveShaft(sv5, analog0, 5);
      //Serial.println("camera x  : " + String(analog9, DEC));
      analog0 = 0;
      i = 7;
    } else if ( d == 'y' ) {
      //sv6.writeMicroseconds(analog9);
      //moveShaft(sv6, analog0, 5);
      //Serial.println("camera y  : " + String(analog9, DEC));
      analog0 = 0;
      i = 7;
    }
    digitalWrite(13, LOW);   //LED消灯
  }
}

