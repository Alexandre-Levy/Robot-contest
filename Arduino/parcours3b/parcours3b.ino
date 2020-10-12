#include <prismino.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
#define IR_EN 4
#define GAUCHE 1
#define DROITE 0
bool haltere;
unsigned long MS; 
unsigned long start;
int arret=0;
int trigPin = 2;    // Trigger
int echoPin = 0;    // Echo
long duration, cm, inches;
 
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
int tempsHaltere ;
int pret=0;
int go=0;
int depart =0;
int compteurBouteille;
int tempsBouteille=0;

enum FLAG{IN, INL, INR, OUT};
enum FLAG currState = IN;

bool flagBouteille;
  
void setup()
{
  // set pin output mode (sources current)
  pinMode(LED, OUTPUT);
  pinMode(IR_EN, OUTPUT);
  servo1.attach(S1); // pin 6
  servo2.attach(S2); // pin 5
  servo2.write(50);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(57600);
  
  
  Serial.println("Goodnight moon!");
  arret = 0;
  haltere = false;

  compteurBouteille = 0;
  flagBouteille = false;
}

void loop()
{
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
  

  cm = (duration/2) / 29.1;

//  Serial.print(duration);
//  Serial.print(',');
//  Serial.println(ir_value5);
//  Serial.print("cm");
// Serial.println();

//  Serial.println(seconde);
  // turn on the emitter and read the IR sensor
  digitalWrite(IR_EN, HIGH); 
  ir_value0 = analogRead(A0);
  ir_value1 = analogRead(A1);
  ir_value2 = analogRead(A2);
  ir_value3 = analogRead(A3);
  ir_value4 = analogRead(A4);
   ir_value5 = analogRead(A5);
//  Serial.println("0: ");
//  Serial.println(ir_value0);
//  Serial.println("1: ");
 Serial.println(ir_value4);
  //Serial.print(ir_value0);      //blue curve
  //Serial.print(",");              //
  //Serial.println(ir_value1);  
  //Serial.print(","); 
  //Serial.println(difference); 
  //orange curve
  if(ir_value2<300 && depart == 0){
    pret=1;
    depart=1;
  }
  else if(ir_value2>500 && pret == 1){

      setSpeed(-30, -30);
      delay(400);
     while(analogRead(A0) >400 || analogRead(A0)<200 ||analogRead(A1) >400 || analogRead(A1)<200 ){
      setSpeed(-30, 30);
    delay(10);
    }
     pret=0;
      go=1;
  setSpeed(0, 0);
   start=millis();
  
  }
  else if(go==1 && arret==0){
      
  MS = millis()-start;
  int seconde;
  seconde = (MS / 1000) % 60 ;
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
      
      if(seconde > 22  && ir_value4 > 300 && seconde>tempsBouteille+2){
         setSpeed(-30,-30);
         delay(1000);
         setSpeed(0,0);
        for(uint8_t pos =50 ; pos < 100; pos++)
        {
          servo2.write(pos);
          delay(50);
        }
        setSpeed(30,30);
        delay(700);
        
        while(difference>10){
          setSpeed(10,-10);
          delay(5);
          ir_value0 = analogRead(A0);
          ir_value1 = analogRead(A1);
          if (ir_value1 > ir_value0){
            difference = ir_value1 - ir_value0;
            direct = 1;
          }
          else {
            difference = ir_value0 - ir_value1;
            direct = 0;
          }
        }
                setSpeed(30,30);
        delay(2000);
    //    setSpeed(30,30);
    //    delay(2500);
    //    setSpeed(0,0);
    //    for(uint8_t pos =100 ; pos > 70; pos--)
    //    {
    //      servo2.write(pos);
    //      delay(50);
    //    }
    //    
    //    setSpeed( 0, 0 );
    //    delay(50000);

          haltere=false;
        setSpeed(0,0);
        for(uint8_t pos =100 ; pos > 70; pos--)
        {
          servo2.write(pos);
          delay(50);
        }
        arret=1;
    
          tempsHaltere=seconde;
          haltere=true;
      }
//      else if(haltere == true && seconde > tempsHaltere+2){
//        haltere=false;
//        setSpeed(0,0);
//        for(uint8_t pos =100 ; pos > 70; pos--)
//        {
//          servo2.write(pos);
//          delay(50);
//        }
//        arret=1;
//      }

    
      //if(seconde == 20){
      //  play(300,5);
      //}
    
      if(seconde > 20 && duration < 850 && flagBouteille==false){
        if(compteurBouteille < 20){
          compteurBouteille += 1;
        }
        else{
    //      play(632,30);
          
          for(int i = 0; i<310; i++){
            //if(analogRead(A2)>800 || analogRead(A3)>800){
            //    play(432,60);
            //}
            setSpeed(-18,30);
            delay(5);
          }
          
          setSpeed(30,30);
          delay(900);
          if(analogRead(A2)>800 || analogRead(A3)>800){
                play(432,500);
                setSpeed(0,0);
                delay(200);
                flagBouteille = true;
                tempsBouteille = seconde;
           }
          setSpeed(-30,-30);
          delay(100);
          
          //if(analogRead(A2)>600){
          //    play(432,60);
          //    flagBouteille = true;
         // }
          
          Serial.println(analogRead(A2)); 
          
          setSpeed(-30,-30);
          delay(800);
          
          for(int i = 0; i<310; i++){
            setSpeed(30,-18);
            delay(5);
          }
    
          while(ir_value1<600){
            setSpeed(10,0);
            delay(10);
            ir_value0 = analogRead(A0);
            ir_value1 = analogRead(A1);
            if (ir_value1 > ir_value0){
              difference = ir_value1 - ir_value0;
              direct = 1;
            }
            else {
              difference = ir_value0 - ir_value1;
              direct = 0;
            }
        }
          
          leftSpeed=0;
          rightSpeed=0;
          compteurBouteille = 0;
        }
      }

  }  
  if (arret){
    rightSpeed=0;
    leftSpeed=0;
  }
      
      setSpeed(rightSpeed, leftSpeed);
      delay(10);

//  delay(0);
}
void tourne45(int sens){
  setSpeed(-30+60*sens, 30-60*sens);
  delay(550);
  setSpeed(0,0);
  delay(30);
}
