//pin sensor
#define trigPin 38
#define echoPin 40
//bts 1
#define pwm1 12
#define pwm2 13
//bts 2
#define pwm3 7
#define pwm4 6
//bts 3
#define pwm5 8
#define pwm6 9
//bts 4
#define pwm7 3
#define pwm8 2


void setup(){
   Serial.begin (9600);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(pwm1, OUTPUT);
   pinMode(pwm2, OUTPUT);
   pinMode(pwm3, OUTPUT);
   pinMode(pwm4, OUTPUT);
   pinMode(pwm5, OUTPUT);
   pinMode(pwm6, OUTPUT);
   pinMode(pwm7, OUTPUT);
   pinMode(pwm8, OUTPUT);
}

void loop(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 5){ 
      mundur();
  }else if(distance > 10){
      maju();
  }else{
      berhenti();
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);

//    kiri();
//    delay(3000);
//    berhenti();
//    delay(1000);
//    kanan();
//    delay(3000);
}

void maju(){
  analogWrite(pwm1, 50);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 50);
  analogWrite(pwm4, 0);
  analogWrite(pwm5, 50);
  analogWrite(pwm6, 0);
  analogWrite(pwm7, 50);
  analogWrite(pwm8, 0);
}

void berhenti(){
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 0);
  analogWrite(pwm4, 0);
  analogWrite(pwm5, 0);
  analogWrite(pwm6, 0);
  analogWrite(pwm7, 0);
  analogWrite(pwm8, 0);
}

void mundur(){
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 50);
  analogWrite(pwm3, 0);
  analogWrite(pwm4, 50);
  analogWrite(pwm5, 0);
  analogWrite(pwm6, 50);
  analogWrite(pwm7, 0);
  analogWrite(pwm8, 50);
}

void kanan(){
  analogWrite(pwm1, 50);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 0);
  analogWrite(pwm4, 50);
  analogWrite(pwm5, 0);
  analogWrite(pwm6, 50);
  analogWrite(pwm7, 50);
  analogWrite(pwm8, 0);
}

void kiri(){
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 50);
  analogWrite(pwm3, 50);
  analogWrite(pwm4, 0);
  analogWrite(pwm5, 50);
  analogWrite(pwm6, 0);
  analogWrite(pwm7, 0);
  analogWrite(pwm8, 50);
}
