#define pwm1 5 
#define pwm2 6

void setup(){
   pinMode(pwm1, OUTPUT);
   pinMode(pwm2, OUTPUT);

   }
void loop(){
   analogWrite(pwm1,100);
   analogWrite(pwm2,0);
}
