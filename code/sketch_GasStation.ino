#include <LiquidCrystal.h>
int trig=7,echo=6; //초음파 입출력 - echo가 입력
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() 
{
  Serial.begin(9600); //시리얼 모니터 사용
  lcd.begin(16, 2); //lcd 초기화
  pinMode(trig,OUTPUT); //초음파
  pinMode(echo,INPUT);
}
 
float centimeter;
int sensor()
{
  int duration;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(2,LOW);
 
  duration=pulseIn(echo,HIGH);
  centimeter=duration/58.2;
  Serial.println(centimeter);
  return centimeter;
}
 
void loop() 
{
  unsigned long time1=0,cost=0; //시간측정을 위한 변수
  // 전광판 기능, 시간측정, 주유량에 따른 요금 계산
  if(sensor() < 15) // 차(장애물) 인지 : 전광판으로 인사 출력
  {
    lcd.setCursor(0,0);            // 0번째 줄 0번째 셀부터 입력하게 합니다.
    lcd.print("Welcome");
    lcd.setCursor(0,1);     
    lcd.print("Charge start");
    delay(3000);
    lcd.clear();
    //time1 = millis() / 1000; 
    //delay(1000);
    while(1)
    {
      time1++;
      delay(1000);
      if(sensor() > 15)
      {
        lcd.setCursor(0,0);  
        cost=time1*100;
        lcd.print("time : ");
        lcd. print(time1);
        lcd.print("seconds");
        lcd.setCursor(0,1);
        lcd.print("cost : ");
        lcd.print(cost);
        lcd.print("won");
        delay(2000);
        lcd.clear();
        lcd.print("Charge Finished! Goodbye");
        delay(2000);
        lcd.clear();
        delay(3000);  
        break;
      }
    }
  }
}


