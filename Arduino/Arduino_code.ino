/*
PIN 8 => Alarm
PIN 2,3 => HM10 Tx,Rx
PIN A4 => SDA
PIN A5 => SCL
*/

#include <SoftwareSerial.h>
#include <SparkFun_ADXL345.h>   
#include "pitches.h" // 알람음 PWM 조절을 위한 헤더, 추가 파일 필요 

#define BT_RXD 2
#define BT_TXD 3
void comp();
int pw[4] = {1,2,3,4}; // 패스워드 설정
int str[4];
int i ,stat = 0; //단순 변수


ADXL345 adxl = ADXL345();
SoftwareSerial HM10(BT_RXD, BT_TXD);

//======================================================= 잠김,열림,알람 음 설정
int melody_lock[] = {
  NOTE_C4, NOTE_E4, NOTE_G4,NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_E6
};
int melody_unlock[] = {
  NOTE_E6, NOTE_C6, NOTE_G5,NOTE_E5, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4
};
int melody_alarm[] = {
  NOTE_C6, NOTE_G6,  NOTE_C6, NOTE_G6,NOTE_C6, NOTE_G6,NOTE_C6, NOTE_G6,
};
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8
};


void setup(){
  
  Serial.begin(9600);
  HM10.begin(9600);
// 가속도계 셋업 시작
  adxl.powerOn(); 
  adxl.setRangeSetting(16);           
  adxl.setSpiBit(0);                
  adxl.setActivityXYZ(1, 0, 0);       
  adxl.setActivityThreshold(75);      
  adxl.setInactivityXYZ(1, 0, 0);     
  adxl.setInactivityThreshold(75);   
  adxl.setTimeInactivity(10);        
  adxl.setTapDetectionOnXYZ(0, 0, 1);  
  adxl.setTapThreshold(50);           
  adxl.setTapDuration(15);            
  adxl.setDoubleTapLatency(80);      
  adxl.setDoubleTapWindow(200);       
  adxl.setFreeFallThreshold(7);       
  adxl.setFreeFallDuration(30);        
  adxl.InactivityINT(1);
  adxl.ActivityINT(1);
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
  adxl.singleTapINT(1);  
  Serial.println("SETUP COMPLETE");   
}

void loop(){
  int x,y,z;   
  adxl.readAccel(&x, &y, &z);  
  while (HM10.available()){ //수신받은 값을 ASCII에서 의미있는 값으로 변환
      int data = HM10.read();       
      //Serial.write(data);  
      str[i] = data-48;
      i++;     
  }
     
  if(i>3){ //입력값 시리얼 모니터 출력 후 비밀번호 비교
   Serial.print(str[0]);
   Serial.print(str[1]);
   Serial.print(str[2]);
   Serial.print(str[3]);
   Serial.println();
   comp();       // 비밀번호 일치 여부 확인
   i=0;
  }      
  if(stat%2) //보안모드시 가속도 모듈 작동, 비밀번호 일치 마다 stat은 홀,짝 반복, 홀수시 보안모드 작동
    ADXL_ISR();
}


void ADXL_ISR() { //동작 감지시 경보 재생, 스마트폰으로 내용 전송
  byte interrupts = adxl.getInterruptSource();
  
  if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
    Serial.println("*** FREE FALL ***");
  }
  
  // Inactivity
  if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
    Serial.println("*** INACTIVITY ***");
  }
  
  // Activity
  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    HM10.println("*** ACTIVITY ***");
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(8, melody_alarm[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
  }
  
  // Double Tap Detection
  if(adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)){ //충격 감지, 알람 재생
    HM10.println("*** DOUBLE TAP ***");
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(8, melody_alarm[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
  }
  
  // Tap Detection
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){ //충격 감지, 알람 재생
    HM10.println("*** TAP ***");   
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(8, melody_alarm[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
}



void comp(){ //비밀번호 대조, 대조 결과 휴대폰 전송
  if((str[0]==pw[0])&&(str[1]==pw[1])&&(str[2]==pw[2])&&(str[3]==pw[3])){
    stat++;  
    HM10.println("correct"); // 비밀번호 일치, 잠금-해제 선택
    if (stat%2){
      HM10.println("Locked");   //잠김      
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 2000 / noteDurations[thisNote];
        tone(8, melody_lock[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8);
      }
    }
    else {
      HM10.println("Unlocked");   //해제
      
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 2000 / noteDurations[thisNote];
        tone(8, melody_unlock[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(8);
      }
    }
  }
  else{
  HM10.println("wrong"); //불일치시 전송
  }
  
}
