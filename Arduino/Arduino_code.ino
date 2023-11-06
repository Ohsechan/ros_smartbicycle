#include <LedControl.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#define LEDZ1 8
#define LEDZ2 9
MPU6050 mpu6050(Wire);
LedControl lc = LedControl(12,11,10,4);

int num;
int button1=5;
int button2=4;
int button3=3;
int button4=2;
int SW1=6;
int SW2=7;
int buttonState1 = 0;
int buttonState2 = 0; 

// LEFT좌회전하시오
byte L[8]={B00010001,B00110011,B01100110,B11001100,B11001100,B01100110,B00110011,B00010001};
// RIGHT우회전하시오
byte R[8]={B10001000,B11001100,B01100110,B00110011,B00110011,B01100110,B11001100,B10001000};
// you're first앞지르시오
byte F[8]={B00110000,B01111000,B11111100,B00110000,B00110000,B00110000,B00111111,B00011111};
// under장애물감지
byte S[8]={B00011000,B00011000,B01111110,B00111100,B00011000,B00000000,B00111100,B01111110};
//ZERO소등
byte Z[8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
//LEFT2좌회전
byte A[8]={B00010001,B00110011,B01110111,B11111111,B11111111,B01110111,B00110011,B00010001};
//RIGHT2우회전
byte B[8]={B10001000,B11001100,B11101110,B11111111,B11111111,B11101110,B11001100,B10001000};
//STOP정지
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
   pinMode(SW1, INPUT_PULLUP);
   pinMode(SW2, INPUT_PULLUP);
}
