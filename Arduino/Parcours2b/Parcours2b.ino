 /***************************************************************************************
 *
 * Title:       Analog read IR
 * Description: Read an infrared sensor from an analog input port.
 * If the analog value read is < 512, we turn the LED on, else it's turned off.
 * Connect the sensor output to A1.
 * Connect the sensor power rack ENABLE to 4.
 *
 ***************************************************************************************/
#include <prismino.h>
#include <Servo.h>

Servo servo1;
Servo servo2; 
#define IR_EN 4
#define DROITE 0
#define GAUCHE 1
unsigned long MS; 
unsigned long start;
int arret;
int pasballe=1;
int balleapres=0;
int trigPin = 2;    // Trigger
int echoPin = 0;    // Echo
long duration, cm, inches;
unsigned int go=0;
unsigned int pret=0;
long seconde=0;
int depart =1;
int sansligne=0;
long milieu;
int seul =0;
int bite = 1;
// the analog value is between 0 and 1023 so it needs a 16-bit variable
// can use "unsigned int" or "uint16_t" for short

unsigned int ir_value0;
unsigned int ir_value1;
unsigned int ir_value2;
unsigned int ir_value3;
unsigned int ir_value4;
unsigned int ir_value5;

int leftSpeed  = 0;
int rightSpeed = 0;
unsigned int difference;
int direct ;

enum FLAG{IN, INL, INR, OUT};
enum FLAG currState = IN;
  
void setup()
{
  // set pin output mode (sources current)
  pinMode(LED, OUTPUT);
  pinMode(IR_EN, OUTPUT);
  servo1.attach(S1); // pin 6
  servo2.attach(S2); // pin 5

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(57600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
  Serial.println("Goodnight moon!");
  arret = 0;
  pasballe = 1;
}

void loop()
{
  // Serial.println(seconde);
      // turn on the emitter and read the IR sensor
      digitalWrite(IR_EN, HIGH); 
      ir_value0 = analogRead(A0);
      ir_value1 = analogRead(A1);
      ir_value2 = analogRead(A2);
      ir_value3 = analogRead(A3);
      ir_value4 = analogRead(A4);
      ir_value5 = analogRead(A5);
      Serial.println(ir_value2);
  if (depart){
    if(ir_value2 < 100){
      pret=1;
      depart=0;
    }
  }
  
  if(pret){
    if(ir_value2>100){
      go=1;
      start=millis();
      setSpeed(-30, -30);
      delay(800);
    while(analogRead(A0) >400 || analogRead(A0)<200 ||analogRead(A1) >400 || analogRead(A1)<200 ){
      setSpeed(-30, 30);
      delay(10);
    }
    pret=0;
      
    }
  }
  if(go==1 && arret==0){
      MS = millis()-start;
      int seconde;
      seconde = (MS / 1000) % 60 ;
     
    //  Serial.println("0: ");
      Serial.println(ir_value2);
    //  Serial.println("1: ");
    //  Serial.println(ir_value3);
      //Serial.print(ir_value0);      //blue curve
      //Serial.print(",");              //
      //Serial.println(ir_value1);  
      //Serial.print(","); 
      //Serial.println(difference); 
      //orange curve
    
    if (ir_value1 <100 && ir_value0< 100){
      sansligne=1;
    }
    if(sansligne==0){
          if (ir_value1 > ir_value0){
            difference = ir_value1 - ir_value0;
            direct = 1;
          }
          else {
            difference = ir_value0 - ir_value1;
            direct = 0;
          }
          if (direct){
                if(difference > 30 && difference < 75){
                rightSpeed=30;
                leftSpeed=25;
              }
              else if(difference > 75 && difference < 125){
                rightSpeed=30;
                leftSpeed=20;
              }
              else if(difference > 125 && difference < 150){
                rightSpeed=30;
                leftSpeed=10;
              }
              else if(difference > 150 && difference < 175){
                rightSpeed=30;
                leftSpeed=0;
              }
              else if(difference > 175 && difference < 200){
                rightSpeed=30;
                leftSpeed=-10;
              }
              else if(difference > 200 && difference < 225){
                rightSpeed=30;
                leftSpeed=-20;
              }
              else if(difference > 225){
                rightSpeed=30;
                leftSpeed=-30;
              }
          }
          else{
              if(difference > 30 && difference < 75){
                rightSpeed=25;
                leftSpeed=30;
              }
              else if(difference > 75 && difference < 125){
                rightSpeed=20;
                leftSpeed=30;
              }
              else if(difference > 125 && difference < 150){
                rightSpeed=10;
                leftSpeed=30;
              }
              else if(difference > 150 && difference < 175){
                rightSpeed=0;
                leftSpeed=30;
              }
              else if(difference > 175 && difference < 200){
                rightSpeed=-10;
                leftSpeed=30;
              }
              else if(difference > 200 && difference < 225){
                rightSpeed=-20;
                leftSpeed=30;
              }
              else if(difference > 225){
                rightSpeed=-30;
                leftSpeed=30;
              }
          }
          
          /*if(ir_value1<100 && ir_value0<100){
           rightSpeed=-30;
           leftSpeed=-30;
          }*/
          
          if(ir_value1>800 && ir_value0>800){
           rightSpeed=30;
           leftSpeed=30;
          }
          
         
    
    }
    else if (sansligne==1 && bite == 1){
       digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  bite=0;
   milieu=duration;
   seul=1;
    }
    else if (seul== 1 && pasballe == 1 ){
      digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
   
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
      if(duration>milieu+5){
        rightSpeed = 25;
        leftSpeed = 30;
      }
      else if(duration<milieu-5){
        rightSpeed = 30;
        leftSpeed = 10;
      }
      else{
        rightSpeed = 30;
        leftSpeed = 30;
      }

      if(analogRead(A2)< 500 || analogRead(A3)< 500 || analogRead(A5)< 500){
        bite=0;
        pasballe=0;
      }

      
    }
    else if (pasballe== 0 && balleapres== 0) {
        
       tourne45(DROITE);
          //setSpeed(-30,-30);
        //delay(600);
    //   setSpeed(30,30);
    //    delay(1250);
    //    tourne(GAUCHE);
    //    setSpeed(30,30);
    //    delay(500);
    //    setSpeed(0,0);
          setSpeed(0,0);
        for(uint8_t pos = 80; pos > 5; pos--)
            {
              servo1.write(pos);
              delay(50);
            }
            for(uint8_t pos = 5; pos < 80; pos++)
            {
              servo1.write(pos);
              delay(50);
            }
        tourne45(GAUCHE);
        balleapres=1;
      
    }
    
    if (balleapres){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
   
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
      if(duration>milieu-300){
        rightSpeed = 25;
        leftSpeed = 30;
      }
      else if(duration<milieu-400){
        rightSpeed = 30;
        leftSpeed = 10;
      }
      else{
        rightSpeed = 30;
        leftSpeed = 30;
      }

      

      if(analogRead(A2)<150|| analogRead(A3)< 150 || analogRead(A5)<150){
        setSpeed(-30,-30); 
        delay(200);
        tourne(GAUCHE);
        setSpeed(30,30);
        delay(2000);
        tourne(DROITE);
        setSpeed(25,30);
        delay(900);
      }
      
      ir_value0 = analogRead(A0);
      ir_value1 = analogRead(A1);
      
      if(ir_value0>500 ||ir_value1>500){
        setSpeed(0,0);
         tourne(GAUCHE);
         
         for(uint8_t pos = 80; pos < 140; pos++)
            {
              servo1.write(pos);
              delay(50);
            }
         setSpeed(0,0);
         delay(1000);
         setSpeed(-100,100);
         delay(6000);
          setSpeed(0,0);
         delay(50000);
         
      }
      
    }
  }
    
  setSpeed(rightSpeed, leftSpeed);
  delay(10);
}

void tourne(int sens){
  setSpeed(-30+60*sens, 30-60*sens);
  delay(1130);
  setSpeed(0,0);
}


void tourne45(int sens){
  setSpeed(-30+60*sens, 30-60*sens);
  delay(700);
  setSpeed(0,0);
  delay(30);
}
