/* 
- Author: Designed by David Park (Park Huck Gu Se)
- No Licesense
- Contact: rjtp5670@gmail.com

This is my personal Arduino Project back in my college life.
All the code may not be perfect for advanced user. But it's easy for rookies as the source is hard-coded. 

The laser module on a tower alarm a person detected within set range. 
The main sensing compononet is P.I.R and sonar sensor. Servo motor will rotate and search the place near than target the object detected.

The formula to get angle is the "Arctan" which converts the tangent reversly. 

Basically the angle can be yiled easily only if you know two variables. 

#1. Length between the object and the application. (Let's say, it's X)
#2. The length to the right angle (90 deg). (Let's say, it's Y)
#3. Tan(theta)= x/y -> X = arctan(x/y) -> Angle you want

For more information, see https://www.spikevm.com/calculators/framing/arctan-angle.php
*/

#include <Servo.h>
#include <math.h>
#define led_R 13 
#define led_L 12
#define servo 9
#define Sensing 8
#define laser 7
#define vert_laser 10
#define hort_laser 11

Servo angle;
Servo Vert_laser;
Servo Hort_laser;

int angle_arr[]={0,5,15}; // When detected, search the near. 

void setup()
{
  Serial.begin(9600); 
  angle.attach(9,0,544);
  Hort_laser.attach(hort_laser,0,544); 
  Vert_laser.attach(vert_laser,0,544);
  pinMode(led_R,OUTPUT); pinMode(led_L,OUTPUT);
}

double Arch_T(double x) // x= distance, 
{
  double radi = atan2(10.0,x); // Height = 10.0 cm. Theta[rad] = tan-1 * y/x. 
  Serial.print("theta angle:");
  Serial.println(radi);
  //Serial.println(radi*180/ 3.1415); //Calculate the angle. 
  return radi*180/ 3.1415; 
}

void Active_Laser(int i,double x)
{
   Hort_laser.write(i); // Trigger Tracing. 
   delay(20);
   
   Vert_laser.write(int(Arch_T(x)));
   delay(20);
   digitalWrite(laser,HIGH); // Trigger the laser module to detect an object. 
}
void Deactive_Laser()
{
  digitalWrite(laser,LOW);
}

void Detect(){ // Alarm 
  Serial.println("Detection");
  digitalWrite(led_R,HIGH);
  delay(200);
  digitalWrite(led_R,LOW);
  digitalWrite(led_L,HIGH);
  delay(200);
  digitalWrite(led_L,LOW);
}

double Distance(){ // Return the distance with a sonar sensor
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW); 
  delayMicroseconds(2); 
  digitalWrite(6,HIGH); 
  delayMicroseconds(5); 
  digitalWrite(6,LOW);
  pinMode(4,INPUT); //ECHO
  double duration = pulseIn(4,HIGH);
  double distance = duration * 340/ 10000/2;
  return distance;
}

bool Sonic_Buster(double *sptr){
  sptr = (double*)malloc(sizeof(double)); // Don't have to use malloc. 
  double cm = Distance();
  sptr = &cm;
  Serial.print("Distance:");
  Serial.println(cm);
  if(cm<=40){
    int sec = 0;
    while(true){
    Serial.println(" Don't move, keep staying !: ");
    pinMode(Sensing,INPUT); // Activate PIR Sensor 
      if(digitalRead(Sensing)== HIGH)
        return true; // If obj moves in 5sec, alarm an invader
    delay(1000); 
    sec+=1;
    Serial.print("Elapsed Time:");
    Serial.println(sec);
    if(sec >=5) break; 
    }
  }
  return false;
}

void loop(){
  int i = 0;
  double* ptr = NULL; 
  bool Detection= NULL;
  for( i = 0; i < 120 ; i++){
     Detection = Sonic_Buster(ptr);
     Serial.print("ptr =");
     Serial.println(*ptr);
    if(Detection == true){   
        Detect(); // Enenmy Detection 
        Active_Laser(i,*ptr); // laser starts a target. Overflow can be seen. 
        }else{ // when it's no enemy, Servo moves
          Deactive_Laser(); // laser down
          angle.write(i);
          delay(50);
          Serial.print("Angle:"); 
          Serial.println(i); // Showing a servo Angle
        }
      }
  delay(20);
  for(i =120; i>=0; i--){ //Angle Down
    Detection = Sonic_Buster(ptr);
    if(Detection == true){ 
      Detect(); // Enenmy Detection 
      Active_Laser(i,*ptr); // laser starts a target.   
      }else{ // when it's no enemy, Servo moves
        Deactive_Laser(); // laser down
        angle.write(i);
        delay(50);
        Serial.print("Angle:");
        Serial.println(i);
     }
  } 
free(ptr); // Free the malloc space. 
}
