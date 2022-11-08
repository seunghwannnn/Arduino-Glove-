#include <SoftwareSerial.h>
#include <Servo.h>


SoftwareSerial BTSerial(3, 2);
Servo servo;

int M1 = 8; /*int1*/
int M2 = 9; /*int2*/
int flag=1;

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  servo.attach(11);
  BTSerial.begin(9600);

  Serial.begin(9600);
//  Serial.print("모터가 준비 되었습니다. 숫자 1,2,3,4중 하나를 입력해주세요.");
  servo.write(90);
}

void loop() {
if(BTSerial.available())
{
int n = BTSerial.read();

 
     Serial.println(n);
     
      if(n==83)                  //stop일때 중앙, 정지
    {
      servo.write(90);
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);     
    }

      else if(n==71)           // Go일떄 중앙, 속도 170
    {
         servo.write(90);
         digitalWrite(M1, LOW);
         digitalWrite(M2, HIGH);
         analogWrite(5,150);
      
    }

      else if(n==76)          // Left일때 왼쪽, 전진
    {
      servo.write(60); 
        digitalWrite(M1, LOW);
         digitalWrite(M2, HIGH);
         analogWrite(5,150);
             
    }    

    else if(n==82)          // Right일때 오른쪽, 전진
    {
        servo.write(120);
        digitalWrite(M1, LOW);
         digitalWrite(M2, HIGH);
         analogWrite(5,150);
    }
     else                  // 후진 정렬, 후진
     {
         servo.write(90);
         digitalWrite(M1, HIGH);
         digitalWrite(M2, LOW);
         analogWrite(5,150);
     }
     
  }
  


         
         
    }



       
  
