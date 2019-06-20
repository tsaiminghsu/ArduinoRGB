//RGB調色盤範例  http://www.appinventor.tw/ble_lesson5_rgb
//0、1腳位可以直接給藍牙就不用額外再定義了，13腳位是預設給arduino板子上的LED燈
#include <SoftwareSerial.h>
#include <Wire.h>  //引用二個函式庫SoftwareSerial及Wire SoftwareSerial 
#define max_char 12 //定義RGB字串  R255G255B255 加上 '\0' 結束字元共13字元

SoftwareSerial BT(10, 11); //定義PIN10及PIN11分別為RX及TX腳位
char message[max_char];    // stores you message
char r_char;               // reads each character
byte index = 0;            // defines the position into your array
int i;

int LED;
//RGB LED Pins
int PIN_RED = 9;
int PIN_GREEN = 6;
int PIN_BLUE = 5;
//RED LED at Pin 13
int RED_LED = 13;/*
String RGB = ""; //store RGB code from BT
String RGB_Previous = "255.255.255)"; //preserve previous RGB color for LED switch on/off, default White
String ON = "ON"; //Check if ON command is received
String OFF = "OFF"; //Check if OFF command is received
boolean RGB_Completed = false;*/
//呼吸燈 http://yehnan.blogspot.com/2012/02/arduino_16.html
int brightness = 0;
int fadeAmount = 5;//0~255每次加上5來回循環
int delayDuration = 100;  //閃爍間隔0.1秒

int flag = 0;
char currentColor;  

String redTempValue;     
String greenTempValue;   
String blueTempValue;     
char ReadChar;
void setup() {
  //馬達輸出
  pinMode(0, OUTPUT);//L298N馬達輸出out1
  pinMode(1, OUTPUT);//L298N馬達輸出out2
  
  pinMode(3, OUTPUT); //LED燈
  pinMode(4, OUTPUT); //馬達
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
  //RGB.reserve(30);
  pinMode(RED_LED, OUTPUT); 
  //Set pin13 as output for LED, 
  // this LED is on Arduino mini pro, not the RGB LED
}
void Light_RGB_LED(){ //RGB調色盤
  /*
  int SP1 = RGB.indexOf('.');
  int SP2 = RGB.indexOf('.', SP1+1);
  int SP3 = RGB.indexOf('.', SP2+1);
  String R = RGB.substring(0, SP1);
  String G = RGB.substring(SP1+1, SP2);
  String B = RGB.substring(SP2+1, SP3);
   //Print out debug info at Serial output window
  Serial.print("R=");
  Serial.println( constrain(R.toInt(),0,255));
  Serial.print("G=");
  Serial.println(constrain(G.toInt(),0,255));
  Serial.print("B=");
  Serial.println( constrain(B.toInt(),0,255));
  //Light up the LED with color code
 //Because these RGB LED are common anode (Common positive)
//So we need to take 255 to minus R,G,B value to get correct RGB color code
*/ if(flag == 0){
    analogWrite(PIN_RED, 0+redTempValue.toInt());
    analogWrite(PIN_GREEN, 0+greenTempValue.toInt());
    analogWrite(PIN_BLUE, 0+blueTempValue.toInt());
    Serial.println(message);
    flag=1;
    for(i=0; i<12; i++){
      message[i] = '\0';
    } 
    //resests the index
    index=0;  
  }
}
void BTcommand(){
  ReadChar = (char)BT.read(); 
  Serial.println(ReadChar);
  //Serial.write(ReadChar);
}
void loop() {
  while (BT.available()>0){
    BTcommand();
    flag = 0;
    //the message can have up to 12 characters 
    if(index < (max_char-1)){         
      r_char = BT.read();      // Reads a character
      message[index] = r_char;     // Stores the character in message array
      if(r_char=='R'){
         currentColor = 'R';
         redTempValue = "";
      }
      else if(r_char=='G'){
         currentColor = 'G';
         greenTempValue = "";
      }
      else if(r_char=='B'){
         currentColor = 'B';
         blueTempValue = "";
      }
      if(currentColor == 'R' && r_char!='R'){
         redTempValue += r_char;
      }
      else if(currentColor == 'G' && r_char!='G'){
         greenTempValue += r_char;
      }
      else if(currentColor == 'B' && r_char!='B'){
         blueTempValue += r_char;
      }
      index++;                     // Increment position
      message[index] = '\0';       // Delete the last position
   }Light_RGB_LED();
      /*
      // Right parentheses ) indicates complet of the string
      if(ReadChar == ')'){
        RGB_Completed = true;
      }else{
        RGB += ReadChar;
      }
      if(RGB_Completed){
     //Print out debug info at Serial output window
        Serial.print("RGB:");
        Serial.print(RGB);
        Serial.print("     PreRGB:");
        Serial.println(RGB_Previous);      
        if(RGB==ON){
            digitalWrite(13,HIGH);
            RGB = RGB_Previous; //We only receive 'ON', so get previous RGB color back to turn LED on
            Light_RGB_LED();          
         }else if(RGB==OFF){
            digitalWrite(13,LOW);
            RGB = "0.0.0)"; //Send OFF string to turn light off
            Light_RGB_LED();
        }else{
            //Turn the color according the color code from Bluetooth Serial Port
            Light_RGB_LED();   
            RGB_Previous = RGB;     
        }
        //Reset RGB String   
        RGB = "";
        RGB_Completed = false;    
      } //end if of check if RGB completed    
    */ if (ReadChar == 'a') {//呼吸燈
        //digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(12, HIGH);
        int value = 1;
        while(value){
          BTcommand();
          if (ReadChar == 'f'){
            value = 0;
          }
          analogWrite(3, brightness);
          brightness = brightness + fadeAmount;
          if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount ;
          }    
          delay(delayDuration);             
        }
      }
      else if (ReadChar == 'b') {//恆亮
        digitalWrite(3, HIGH);
        
        digitalWrite(2, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(12, HIGH);
      }
      else if (ReadChar == 'c') {//閃爍
        int value = 1;
        while(value){
          BTcommand();
          if (ReadChar == 'f'){
            value = 0;
          }
          digitalWrite(3, HIGH);
          delay(delayDuration); 
          digitalWrite(3, LOW);
          delay(delayDuration); 
        }
        digitalWrite(2, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(12, HIGH);  
      }
      else if (ReadChar == 'd') {//馬達旋轉
        digitalWrite(3, HIGH);
        
        digitalWrite(0, HIGH);
        digitalWrite(1, LOW);
        int value = 1;
        while(value){
          BTcommand();
          if (ReadChar == 'f'){
            value = 0;
          }
        }
        /*
        digitalWrite(0, LOW);
        digitalWrite(1, HIGH);
        */
      }
      else if (ReadChar == 'e') {//馬達停止
        digitalWrite(3, LOW);
        
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
      }
  
      else if (ReadChar == 'f') {//停止
        digitalWrite(3, LOW);

        digitalWrite(2, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(12, LOW);

        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
      }
      else{
      }
      //Light_RGB_LED();
    }
}
