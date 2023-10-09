int ENA = 10;
int ENB = 11;
int IN1 = 9;
int IN2 = 8;
int IN3 = 7;
int IN4 = 6; // RC카 define
 
int front_sensor1 = 2;
int front_sensor2 = 3;
int Side_sensor1 = 4;
int Side_sensor2 = 5; // 초음파 센서 define
 
void setup()
{
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(13,INPUT);
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);
  pinMode(ENA,OUTPUT); // RC카 핀모드
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(A5,INPUT);
  pinMode(12,OUTPUT);
}
 
 
int Front_UltraSensor()
{
   digitalWrite(front_sensor1,HIGH);
  delayMicroseconds(50);
  digitalWrite(front_sensor1,LOW);
  int cul1 = pulseIn(front_sensor2,HIGH);
  float First_val = cul1 / 58.2;
  return First_val;
}
 
int Side_UltraSensor()  
{ 
   digitalWrite(Side_sensor1,HIGH);
  delayMicroseconds(50);
  digitalWrite(Side_sensor1,LOW);
  int cul2 = pulseIn(Side_sensor2,HIGH);
  float Second_val = cul2 / 58.2;
  return Second_val;
}
 
void move_car()
{
  digitalWrite(IN1, LOW); // RC카 직진
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 205); // 양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 200);
  
    if(Front_UltraSensor() < 10) // 앞에 벽 발견, 오른쪽 센서 감지 시작, rc카 2초 정지
  { 
  digitalWrite(IN1, LOW); // 앞에 벽 발견하고 RC카 정지
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 240);  // 양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 240);
  delay(2000);
  
   
    if(Front_UltraSensor()<10 && Side_UltraSensor() < 10)  // 오른쪽 센서가 벽을 인지함
    {
      // 오른쪽에 장애물 발견
      // 왼쪽으로 90도
 
  digitalWrite(IN1, LOW); // 왼쪽으로 회전
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 250); // 양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 250);
  delay(1000);
 
  digitalWrite(IN1, LOW); // 회전 후 멈춤
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 240); // 양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 220);
  delay(2000);
    }
    else if(Front_UltraSensor() < 10 && Side_UltraSensor() > 10) // 오른쪽 센서가 벽을 인지하지못하면 오른쪽으로 회전
    {
      // 오른쪽으로 90도 회전
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 250); // 양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 250);
  delay(1000);
  digitalWrite(IN1, LOW); // 회전 후 멈춤
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 240); //  양쪽 모터의 힘 차이 문제로 좌우 파워 값이 상이 할 수 있음.
  analogWrite(ENB, 240);
  delay(2000);
    }
  }
}
 
 
void headlight_car()
{
  int val = analogRead(A5);
  if(val <= 620)
  {
    digitalWrite(12,HIGH);    
  }
  else if(val > 620)
  {
    digitalWrite(12,LOW);    
  } 
}
 
void loop()
{
    move_car(); 
    headlight_car();
}
