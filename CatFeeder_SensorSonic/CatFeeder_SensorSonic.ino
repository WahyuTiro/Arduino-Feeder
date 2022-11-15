#define waktuBukaServo 2000 //milisecond
#define servoBuka 20 //20 derajat posisi Servo terbuka
#define servoTutup 90 //90 derajat posisi Servo terbuka
   
#define waktuMakan1 DateTime(0, 1, 1,  9, 0, 0, 0)//mengirm data 0 1 1 pada jam 9 pagi
#define waktuMakan2 DateTime(0, 1, 1, 18, 0, 0, 0)//mengirm data 0 1 1 pada jam 6 sore
   
#include "Sodaq_DS3231.h" //library RTC (Real Time Clock)
#include <Servo.h> //library Servo

// deklarasi variabel dan tipe data
Servo servoPakan; //deklarasi Servo
const int trigPin = 12;
const int echoPin = 11;
byte detikDelay; 
char buf[17];

/* Program mulai dijalankan */
void setup() {
  Serial.begin(9600);
  Serial.println("Pakan Otomatis"); // display nama alat
     
  servoPakan.attach(8);
  servoPakan.write(servoTutup);
   
  pinMode(trigPin, OUTPUT); //  pin Trigger sebagai OUTPUT
  pinMode(echoPin, INPUT); //  pin Echo sebagai INPUT
  
  rtc.begin();
   
  Serial.println("Memulai Sistem");
  sprintf(buf, "Atur waktu 1 = %02d:%02d (%lu)", waktuMakan1.hour(), waktuMakan1.minute(), waktuMakan1.get());
  Serial.println(buf);
  sprintf(buf, "Atur waktu 2 = %02d:%02d (%lu)", waktuMakan2.hour(), waktuMakan2.minute(), waktuMakan2.get());
  Serial.println(buf);
}

/* Looping program yang berjalan */
void loop() {
   
      //Fungsi jarak ketinggian makan      
      long waktu, jarakCm;
      digitalWrite(trigPin, LOW); //TRIG_PIN
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH); //TRIG_PIN
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW); //TRIG_PIN
      waktu = pulseIn(echoPin,HIGH); //ECHO_PIN
      jarakCm = (waktu * 347.662 *100)/(1000000*2);
      Serial.println(jarakCm);
      delay(detikDelay);

      if(jarakCm <=15){
      servoPakan.write(servoBuka);
      delay(waktuBukaServo);
      }
   
      else {
      servoPakan.write(servoTutup);
      }

      //Fungsi waktu makan
      //waktu tersimpan
      DateTime now = rtc.now();
      if (detikDelay != now.second())
      {
        //tampilkan jam, menit, dan detik
        sprintf(buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
        Serial.print(buf);
       
        detikDelay = now.second();
        
        //unsigned integer dan fungsi jangka waktu memberi makan
        uint32_t jangka = now.get() % 86400;//hanya jam menit detik
       
        if ((jangka == waktuMakan1.get()) ||
            (jangka == waktuMakan2.get()))
        {
          char buf[17];
          sprintf(buf, "Makan = %02d:%02d", now.hour(), now.minute());
          
          Serial.println(buf);
       
          servoPakan.write(servoBuka);
          delay(waktuBukaServo);
          servoPakan.write(servoTutup);
       
        }
      }
}
