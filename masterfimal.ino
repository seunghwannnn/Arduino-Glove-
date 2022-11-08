#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);       //블루투스의 Rx, Tx핀을 2번 3번핀으로 설정
void setup() {
  // 시리얼 통신의 속도를 9600으로 설정
  Serial.begin(9600);
  while (!Serial)
  {
                                    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  mySerial.begin(9600);               //블루투스와 아두이노의 통신속도를 9600으로 설정
}


void loop() { //코드를 무한반복합니다.

     int Value = analogRead(A1);      // 1번 Flexsensor(엄지) : 속도
     int R = (analogRead(A2));        // 2번 Flexsensor(검지) : 앞 바퀴 각도
     int L = (analogRead(A4));        // 3번 Flexsensor(새끼) : 후진 기어
     int a,b,c;

     a=map(Value,35,125,0,80);     // 1번 Felxsensor 0~80으로 Mapping
     b=map(R,35,135,100,200);      // 2번 Felxsensor 100~200으로 Mapping 
     c=map(L,35,130,210,250);      // 3번 Felxsensor 210~255으로 Mapping
       

     mySerial.write(a);             // Bluetooth를 통해 송신
     mySerial.write(b);
     mySerial.write(c);

     Serial.println(a);             // Serial Monitor
     Serial.println(b);
     Serial.println(c);


     if (mySerial.available())         //블루투스에서 넘어온 데이터가 있다면
       Serial.write(mySerial.read()); //시리얼모니터에 데이터를 출력
     
     if (Serial.available())           //시리얼모니터에 입력된 데이터가 있다면
       mySerial.write(Serial.read());  //블루투스를 통해 입력된 데이터 전달
  
     delay(100);
}
