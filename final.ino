#include <SoftwareSerial.h>
#include <Servo.h>


SoftwareSerial BTSerial(3, 2);                // Rx핀을 3번 Tx핀을 2번
Servo servo;
int value = 90;                              // 바퀴의 초기 각도를 90(중앙)으로 설정한다.
int M1 = 8;                                  // Motor1
int M2 = 9;                                  // Motor2
int flag=1;                                 // 후진 기어를 위한 flag 설정

void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(11, OUTPUT);
  servo.attach(11);
  BTSerial.begin(9600);                    // 블루투스 통신속도를 9600bps로 설정
  Serial.begin(9600);
  servo.write(value);
}

void loop() {
  if(BTSerial.available())
  {
    int n = BTSerial.read(),R;
    if(n>205 & n<225) flag=1;                // 후진기어 설정값
    if(n>=225 & n<255) flag=0;
 
    if(flag==1)
      {
        Serial.println(n);                 // 블루투스 통신을 받으면 Serial Monitor에 값을 표시한다.
        if(n<20) // 정지
        {
          digitalWrite(M1, HIGH);           // Flex sensor 저항값이 20보다 작으면 M1,M2 를 HIGH로 하여 차가 정지한다.
          digitalWrite(M2, HIGH);
        }

        if(n>=20 & n<80) // 전진
        {
          digitalWrite(M1, LOW);         // Flex sensor 저항값이 20~80 사이면 전진하며, 속도를 저항값*4로 설정하였다.
          digitalWrite(M2, HIGH);        
          analogWrite(5,n*4);      
        }
        if(n>100 & n <200) // 앞바퀴 각도 조절
        {    
          R = map(n,100,200,130,25);    // Flex sensor 저항값이 100~200사이면 Maping을 통해 바뀐 값으로 서보모터에 입력하여 바퀴의 각도를 조절한다.
          servo.write(R);   
        }     
      }
  
    if(flag==0)                            // 저항값이 커져서(후진 기어) flag값이 0으로 설정되면
    {
      Serial.println(n);
      digitalWrite(M1, HIGH);      // M1,M2를 HIGH LOW로 설정하여 후진으로 이동하게 된다.
      digitalWrite(M2, LOW);
      analogWrite(5,170);          // 그때의 후진속도는 170으로 설정한다.
      if(n>100 & n <200)
      {   
        R = map(n,100,200,130,25);   // 후진으로 설정되었을 때 바퀴의 각도를 설정하는것은 위와 동일하다.
        servo.write(R);
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
        analogWrite(5,170);       
      } 
    }
  }
}
