#include <LedControl.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#define LEDZ1 8 //좌회전용 ledz1
#define LEDZ2 9 //우회전용 ledz2
MPU6050 mpu6050(Wire); //scl=a5, sda=a4 analogpin
LedControl lc = LedControl(12,11,10,4); //din=12, cs=10, clk=11digitalpin,4module(8x32)dotmatrix

int num;
int button1=5;
int button2=4;
int button3=3;
int button4=2;


// LEFT좌회전하시오
byte L[8]={B00010001,B00110011,B01100110,B11001100,B11001100,B01100110,B00110011,B00010001};

// RIGHT우회전하시오
byte R[8]={B10001000,B11001100,B01100110,B00110011,B00110011,B01100110,B11001100,B10001000};

// you're First앞지르시오
byte F[8]={B00110000,B01111000,B11111100,B00110000,B00110000,B00110000,B00111111,B00011111};

// under장애물감지
byte S[8]={B00011000,B00011000,B01111110,B00111100,B00011000,B00000000,B00111100,B01111110};

//ZERO소등
byte Z[8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

//LEFT2좌회전(자이로센서에 감지되어 자동 자회전 신호)
byte A[8]={B00010001,B00110011,B01110111,B11111111,B11111111,B01110111,B00110011,B00010001};

//RIGHT2우회전(자이로센서에 감지되어 자동 우회전 신호)
byte B[8]={B10001000,B11001100,B11101110,B11111111,B11111111,B11101110,B11001100,B10001000};

//STOP정지하시오(zero velocity : 0)
byte C[8]={B00111100,B01000010,B01000110,B01001010,B01010010,B01100010,B01000010,B00111100};


void setup()
{
for(num=0; num<4; num++) // 매트릭스 0번부터 3번까지 세팅
{
lc.shutdown(num,false); // 0~3번까지 매트릭스 절전모드 해제
lc.setIntensity(num,8); // 매트릭스의 밝기 선언 0~15의 수
lc.clearDisplay(num); // 매트릭스 led를 초기화
}

pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);
pinMode(button4, INPUT_PULLUP);
pinMode(LEDZ1, OUTPUT);
pinMode(LEDZ2, OUTPUT);

for(int i=0; i<5; i++){
digitalWrite(LEDZ1, HIGH);
digitalWrite(LEDZ2, HIGH);
delay(100);
digitalWrite(LEDZ1, LOW);
digitalWrite(LEDZ2, LOW);
delay(100);
}

Serial.begin(9600);
Wire.begin();
mpu6050.begin();
}

void matrix(byte *M)
{
for(int j=0; j<8; j++)
{
lc.setRow(0,j,M[j]);
lc.setRow(1,j,M[j]);
lc.setRow(2,j,M[j]);
lc.setRow(3,j,M[j]);
lc.setRow(4,j,M[j]);
lc.setRow(5,j,M[j]);
lc.setRow(6,j,M[j]);
lc.setRow(7,j,M[j]);
}
}

void loop(){
if(digitalRead(button1) == LOW)
{
matrix(L); //1번 버튼을 누르면 좌회전 수신호 도트매트릭스 동작
}

if (digitalRead(button2) == LOW)
{
matrix(R); //2번 버튼을 누르면 우회전 수신호 도트매트릭스 동작
}

if (digitalRead(button3) == LOW)
{
matrix(F); //3번 버튼을 누르면 앞질러가시오 수신호 도트매트릭스 동작
}

if (digitalRead(button4) == LOW)
{
matrix(S); //4번 버튼을 누르면 밑에 장애물 있음 수신호 도트매트릭스 동작
}

else if ((digitalRead(button1) == HIGH) && (digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(Z); //아무 버튼이 안눌러져 있을 경우 도트매트릭스 소등
}


else if (((digitalRead(button1) == HIGH) && (digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))&&((mpu6050.getAngleX())>1))
{
matrix(A); delay(1000); //아무 버튼이 안눌러졌을 경우와 좌회전이 동시에 일어날 경우 좌회전2신호 표시
}

else if (((digitalRead(button1) == HIGH) && (digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))&&((mpu6050.getAngleX())<-10))
{
matrix(B); delay(1000); //아무 버튼이 안눌러졌을 경우와 우회전이 동시에 일어날 경우 우회전2신호 표시
}

else if ((digitalRead(button1) == LOW) && (digitalRead(button2) == LOW) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(C); delay(1000); // 1번 버튼과 2번 버튼이 동시에 눌릴 경우 급정지 신호 표시
}


mpu6050.update();
Serial.print("angleX: ");
Serial.print(mpu6050.getAngleX());
Serial.print("\tangleY: ");
Serial.print(mpu6050.getAngleY());
Serial.print("\tangleZ: ");
Serial.print(mpu6050.getAngleZ());


//좌회전 시 자동으로 좌회전2 수신호 표시, 하지만 버튼이 우선순위 저장------------------
if ( ((mpu6050.getAngleX())>1)){
digitalWrite(LEDZ1, HIGH);
digitalWrite(LEDZ2, LOW); //좌로 회전하면 좌측 led만 점등, 우측 led 소등

if(digitalRead(button1) == LOW)
{
matrix(L); //1번 버튼이 눌러지면 좌회전 수신호 먼저 표시
}

if (digitalRead(button2) == LOW)
{
matrix(R); //2번 버튼이 눌러지면 우회전 수신호 먼저 표시
}

if (digitalRead(button3) == LOW)
{
matrix(F); //3번 버튼이 눌러지면 앞질러가시오 수신호 먼저 표시
}

if (digitalRead(button4) == LOW)
{
matrix(S); //4번 버튼이 눌러지면 밑에 장애물 존재 수신호 먼저 표시
}

if ((digitalRead(button1) == HIGH) && (digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(A); delay(100); //버튼이 안눌러질 경우 좌회전2 표시
}

if ((digitalRead(button1) == LOW) && (digitalRead(button2) == LOW) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(C); delay(100); //1번과 2번 버튼이 동시에 눌러질 경우 급정지 표시
}
}

//우회전 시 자동으로 우회전2 수신호 표시, 하지만 버튼이 우선순위 저장------------

﻿
﻿
else if ( ((mpu6050.getAngleX())<-10)){
digitalWrite(LEDZ1, LOW);
digitalWrite(LEDZ2, HIGH); //우회전시 좌측led 소등, 우측 led 점등
if(digitalRead(button1) == LOW)
{
matrix(L); //1번 버튼이 눌러지면 좌회전 수신호 먼저 표시
}

if (digitalRead(button2) == LOW)
{
matrix(R); //2번 버튼이 눌러지면 우회전 수신호 먼저 표시
}

if (digitalRead(button3) == LOW)
{
matrix(F); //3번 버튼이 눌러지면 앞질러가시오 수신호 먼저 표시
}

if (digitalRead(button4) == LOW)
{
matrix(S); //4번 버튼이 눌러지면 밑에 장애물존재 수신호 먼저 표시
}

if ((digitalRead(button1) == HIGH) && (digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(B); delay(100); //버튼이 안눌러질 경우 우회전2 표시
}

if ((digitalRead(button1) == LOW) && (digitalRead(button2) == LOW) && (digitalRead(button3) == HIGH) && (digitalRead(button4) == HIGH))
{
matrix(C); delay(100); //1번과 2번 버튼이 동시에 눌러질 경우 급정지 표시
}
}

// 직진구간

else if ( (-10<(mpu6050.getAngleX())<1)){
digitalWrite(LEDZ1, LOW);
digitalWrite(LEDZ2, LOW); // 양쪽 led 모두 소등
}
}
