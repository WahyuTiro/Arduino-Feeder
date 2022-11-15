#include <Servo.h>

Servo servo1;
// deklasi sudut servo
int sudut = 90;

// deklarasi nomor pin
const int trigPin = 12;
const int echoPin = 11;

void setup() {
  servo1.attach(8);
  servo1.write(sudut);
 
  pinMode(trigPin, OUTPUT); //  pin Trigger sebagai OUTPUT
  pinMode(echoPin, INPUT); //  pin Echo sebagai INPUT
  Serial.begin(9600); // Start komunikasi serial
}

void loop() {

      long waktu, jarakCm;
      digitalWrite(trigPin, LOW); //TRIG_PIN
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH); //TRIG_PIN
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW); //TRIG_PIN
      waktu = pulseIn(echoPin,HIGH); //ECHO_PIN
      jarakCm = (waktu * 347.662 *100)/(1000000*2);
      Serial.println(jarakCm);
      delay(10);

      if(jarakCm <=15){
          servo1.write(0);
          delay(2000);
      }
      
      else if(jarakCm >=20){
          servo1.write(90);
      }
      
      else {
          servo1.write(90);
      }

            
//      if(jarak<10)
//      {
//        servo1.write(0);
//        servo2.write(0);
//        delay(1000);
//        }
//        else
//        {
//          servo1.write(180);
//          servo2.write(180);
//          }
          
}
