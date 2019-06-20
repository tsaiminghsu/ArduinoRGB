//0、1腳位可以直接給藍牙就不用額外再定義了，13腳位是預設給arduino板子上的LED燈
#include <SoftwareSerial.h>
#include <Wire.h>  //引用二個函式庫SoftwareSerial及Wire SoftwareSerial 
SoftwareSerial BT(10, 11); //定義PIN10及PIN11分別為RX及TX腳位
int LED;
void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600); //Arduino起始鮑率9600
  BT.begin(9600); //藍牙鮑率57600
  //(注意！此鮑率每個藍牙晶片不一定相同，請先確認完再填寫進去)
  Serial.println("start");
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
}

void loop() {
  if (BT.available() > 0) {
    LED = BT.read();
    Serial.print(LED);
    Serial.println("");
  }

  if (LED == 'a') {//呼吸燈
    digitalWrite(3, HIGH);

    digitalWrite(2, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(12, HIGH);

  }
  if (LED == 'b') {//恆亮
    digitalWrite(3, HIGH);

    digitalWrite(2, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(12, HIGH);;
  }
  if (LED == 'c') {//閃爍
    digitalWrite(3, HIGH);

    digitalWrite(2, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(12, HIGH);
  }

  if (LED == 'd') {
    digitalWrite(4, HIGH);
  }
  if (LED == 'e') {
    digitalWrite(4, LOW);
  }

  if (LED == 'f') {//停止
    digitalWrite(2, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(3,LOW);
  }


}
