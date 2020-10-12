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

unsigned long MS; 
unsigned long start;
int arret;

// the analog value is between 0 and 1023 so it needs a 16-bit variable
// can use "unsigned int" or "uint16_t" for short

unsigned int ir_value0;
unsigned int ir_value1;
unsigned int ir_value2;
unsigned int ir_value3;
unsigned int ir_value4;
int epreuve=0;
int leftSpeed  = 0;
int rightSpeed = 0;
unsigned int difference;
unsigned int go=0;
unsigned int pret=0;
long seconde=0;
int depart =1;
  
void setup()
{
  // set pin output mode (sources current)
   pinMode(LED, OUTPUT);
  pinMode(IR_EN, OUTPUT);
  servo1.attach(S1); // pin 6
  servo2.attach(S2); // pin 5
  servo2.write(0);
  Serial.begin(57600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
  Serial.println("Goodnight moon!");
  arret = 0;
}

void loop()
{

  // turn on the emitter and read the IR sensor
  digitalWrite(IR_EN, HIGH); 
  ir_value0 = analogRead(A0);
  ir_value1 = analogRead(A1);
  ir_value2 = analogRead(A2);
  ir_value3 = analogRead(A3);
  ir_value4 = analogRead(A4);
//  Serial.println("0: ");
//  Serial.println(ir_value0);
//  Serial.println("1: ");
  Serial.println(ir_value2);
  //Serial.print(ir_value0);      //blue curve
  //Serial.print(",");              //
  //Serial.println(ir_value1);  
  //Serial.print(","); 
  //Serial.println(difference); 
  //orange curve
  if (depart){
    if(ir_value2 < 300){
      pret=1;
      depart=0;
    }
  }
  
  if(pret){
    if(ir_value2>500){
         start=millis();
      setSpeed(-30, -30);
      delay(600);
      while(analogRead(A0) >400 || analogRead(A0)<200 ||analogRead(A1) >400 || analogRead(A1)<200 ){
        setSpeed(-30, 30);
    delay(10);
    }
    go=1;
 
    pret=0;
      
    }
  }
  
  if(go==1 && arret==0){
            MS = millis()-start;
    seconde = (MS / 1000) % 60 ;
    //Serial.println(seconde);
    int direct;
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
          
          if(ir_value1>800 && ir_value0>800){
           rightSpeed=30;
           leftSpeed=30;
          }
         if (seconde > 5 && seconde < 20 && ir_value4 > 300 && epreuve==0){
            setSpeed(-30, -30);
            delay(200);
            setSpeed(0, 0);
            // sweep from 0 to 180 degrees
            for(uint8_t pos = 90; pos > 27; pos--)
            {
              servo1.write(pos);
              delay(50);
            }
            for(uint8_t pos = 27; pos < 90; pos++)
            {
              servo1.write(pos);
              delay(50);
            }
            setSpeed( 30, 30 );
            delay(500);
            epreuve=1;
          }
          if( seconde > 10 && ir_value4 > 800 && ir_value1>800 && ir_value0>800){
            arret = 1;
          }
          
  }  
  else if (arret){
            rightSpeed=0;
            leftSpeed=0;
          }
  setSpeed(rightSpeed, leftSpeed);
  delay(10);
//  delay(0);
}
