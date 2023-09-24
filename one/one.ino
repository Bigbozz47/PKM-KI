#define pwm1 4
#define pwm2 5
#define pwm3 10
#define pwm4 11
#define pwm5 8
#define pwm6 9
#define pwm7 6
#define pwm8 7

void setup(){
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
   //maju
   analogWrite(pwm1,0);
   analogWrite(pwm2,50);
   analogWrite(pwm3,0);
   analogWrite(pwm4,50);
   analogWrite(pwm5,50);
   analogWrite(pwm6,0);
   analogWrite(pwm7,50);
   analogWrite(pwm8,0);
   delay(2000); //
   
   //stop
   analogWrite(pwm1,0);
   analogWrite(pwm2,0);
   analogWrite(pwm3,0);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,0);
   analogWrite(pwm7,0);
   analogWrite(pwm8,0);
   delay(2000); //

   //kanan
   analogWrite(pwm1,0);
   analogWrite(pwm2,50);
   analogWrite(pwm3,50);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,50);
   analogWrite(pwm7,50);
   analogWrite(pwm8,0);
   delay(2000); //

   //stop
   analogWrite(pwm1,0);
   analogWrite(pwm2,0);
   analogWrite(pwm3,0);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,0);
   analogWrite(pwm7,0);
   analogWrite(pwm8,0);
   delay(2000); //

   //mundur
   analogWrite(pwm1,50);
   analogWrite(pwm2,0);
   analogWrite(pwm3,50);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,50);
   analogWrite(pwm7,0);
   analogWrite(pwm8,50);
   delay(2000); //

   //stop
   analogWrite(pwm1,0);
   analogWrite(pwm2,0);
   analogWrite(pwm3,0);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,0);
   analogWrite(pwm7,0);
   analogWrite(pwm8,0);
   delay(2000); //

   //kiri
   analogWrite(pwm1,50);
   analogWrite(pwm2,0);
   analogWrite(pwm3,0);
   analogWrite(pwm4,50);
   analogWrite(pwm5,50);
   analogWrite(pwm6,0);
   analogWrite(pwm7,0);
   analogWrite(pwm8,50);
   delay(2000); //

   //stop
   analogWrite(pwm1,0);
   analogWrite(pwm2,0);
   analogWrite(pwm3,0);
   analogWrite(pwm4,0);
   analogWrite(pwm5,0);
   analogWrite(pwm6,0);
   analogWrite(pwm7,0);
   analogWrite(pwm8,0);
   delay(2000); //
}
