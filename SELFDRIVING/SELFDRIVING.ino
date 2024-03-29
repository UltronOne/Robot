#include <SoftwareSerial.h>

SoftwareSerial serialTest(9, 10);

const int trig = 11;
const int echo = 12;

const int AIN1 = 7;
const int AIN2 = 4;
const int PWMA = 6;
const int BIN1 = 2;
const int BIN2 = 3;
const int PWMB = 5;

//window calculation 
const int height = 240;
const int width = 320;


int offset = 0;
int calcoffset = 0;
int baseSpeed = 150;
int maxSpeed = 240;

boolean links = true;


int speedLinks;
int speedRechts;


void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  Serial.begin(9600);
  serialTest.begin(9600);
  delay(1000);
  links = false;
}


float getDistance() {
  //Measure distance in centimeters
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float echoTime = pulseIn(echo, HIGH);
  float calculateDistance = echoTime / 58.0;

  return calculateDistance;
}

int calculateDirection(int i) {


  return ((width/2) - i);
}


void loop() {

   
    

  

  if (serialTest.available() > 0) {
    offset = serialTest.parseInt();






calcoffset = calculateDirection(offset);



  if (offset == 999) {
    
    Serial.println("--------------------line not found-----------------------------");

//    if (links) {
//      leftMotor(255);
//      rightMotor(120);
//    } else {
//      leftMotor(120);
//      rightMotor(255);
//    }

 leftMotor(0);  
 rightMotor(0);

  } else {

    Serial.println(calcoffset);
    
   

    if (calcoffset <= 0) {
          Serial.println("--------------------left-----------------------------");

      //to the left
      speedLinks = map(abs(calcoffset), 0, (width/2), baseSpeed, maxSpeed);
      
      speedRechts = map(abs(calcoffset), 0, (width/2), baseSpeed,baseSpeed);
      

    } else {
    Serial.println("--------------------right-----------------------------");
      //to the right
      
      speedRechts = map(abs(calcoffset), 0, (width/2), baseSpeed, maxSpeed);
   
      speedLinks = map(abs(calcoffset), 0, (width/2), baseSpeed, baseSpeed);
    
    }

  

    int slowDown = map(abs(calcoffset),0,(width/2),0,150);   
    
    Serial.print("SpeedLinks"); Serial.println(speedLinks);
    Serial.print("SpeedRechts"); Serial.println(speedRechts);


    
    
  
  
    leftMotor(constrain(speedRechts-slowDown, 0, 255));
   rightMotor(constrain(speedLinks-slowDown, 0, 255));














    

  }

  
  }


}


void leftMotor(int motorSpeed) { // this drives the motor
  if (motorSpeed > 0) {          // if the motor is given a positive speed
    digitalWrite(AIN1, HIGH);    //pin 1 is high
    digitalWrite(AIN2, LOW);     // pin 2 is low
  }
  else if (motorSpeed < 0) {     //if the motor should drive backwards (negative speed)
    digitalWrite(AIN1, LOW);     //set pin 1 to low
    digitalWrite(AIN2, HIGH);    //set pin 2 to high
  }
  else {                         //if the motor should stop
    digitalWrite(AIN1, LOW);     //set pin 1 to low
    digitalWrite(AIN2, LOW);     //set pin 2 to low
  }
  motorSpeed = constrain(motorSpeed, -255, 255);
  analogWrite(PWMA, abs(motorSpeed));//now that the motor direction is set, drive it at the entered speed
}

/*------------------ Right Motor ------------------*/

void rightMotor(int motorSpeed) { // this drives the motor
  if (motorSpeed > 0) {           // if the motor is given a positive speed
    digitalWrite(BIN1, HIGH);     //pin 1 is high
    digitalWrite(BIN2, LOW);      // pin 2 is low
  }
  else if (motorSpeed < 0) {      //if the motor should drive backwards (negative speed)
    digitalWrite(BIN1, LOW);      //set pin 1 to low
    digitalWrite(BIN2, HIGH);     //set pin 2 to high
  }
  else {                          //if the motor should stop
    digitalWrite(BIN1, LOW);      //set pin 1 to low
    digitalWrite(BIN2, LOW);      //set pin 2 to low
  }
  motorSpeed = constrain(motorSpeed, -255, 255);
  analogWrite(PWMB, abs(motorSpeed)); //now that the motor direction is set, drive it at the entered speed
}


//motor driving functions here:
void driveMotors(int PWM) {
  leftMotor(PWM);
  rightMotor(PWM);
}


void turnLeft(int PWM) {
  leftMotor(PWM);
  rightMotor(0);
}

void turnRight(int PWM) {
  leftMotor(0);
  rightMotor(PWM);
}
