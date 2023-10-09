void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}
int state = 0;
void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  int a = digitalRead(8);
  if(a==HIGH)
  {
   if(state == 0)
   {
     state = 1; 
   }
   else if(state == 1)
   {
      state = 0;
   }
  }
  if(state == 0)
  {
     digitalWrite(9,LOW);
     digitalWrite(10,LOW);
     digitalWrite(11,LOW);
  }
  else if(state == 1)
  {
   if(val>512)
   {
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    }
   else
   {
    val = map(val, 0, 1023, 0, 255);
    analogWrite(9,val);
    analogWrite(10,val);
    analogWrite(11,val);
   } 
  }
}
