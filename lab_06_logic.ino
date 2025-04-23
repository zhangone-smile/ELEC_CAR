/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):
  Group Member 1 (name & SID):
  Group Member 2 (name & SID):

*/

// assign meaningful names to those pins that will be used

int regular_speed = 200;
const int pinL_Sensor = A5; // pin A5: left sensor
const int pinB_Sensor = A4; // pin A4: bumper sensor
const int pinR_Sensor = A3; // pin A3: right sensor
const int pinOR_Sensor = A1;
const int pinOL_Sensor = A2;
const int pinM_Sensor = A0;
int countmiddleSensor = 0;
int countfor180 = 0;

const int pinL_PWM = 9;  // pin D9: left motor speed
const int pinL_DIR = 10; // pin D10: left motor direction

const int pinR_PWM = 11; // pin D11: right motor speed
const int pinR_DIR = 12; // pin D12: right motor direction
int curr_time = 0;
// define variables to be used in script

int bumperSensor = 1; // not sensing white
int leftSensor = 1;   // not sensing white
int rightSensor = 1;  // not sensing white
int OleftSensor = 1;
int OrightSensor = 1;
int middleSensor = 1;

int countBumper = 0; // bumper sensor not triggered yet

// the setup function runs once when you press reset or power the board

void go_straight(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, HIGH);
}
void gentle_turn_left(int speed)
{
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinR_DIR, HIGH);
}
void turn_left(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, HIGH);
}
void gentle_turn_right(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, 0);
    digitalWrite(pinL_DIR, HIGH);
}
void turn_right(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, LOW);
}
void go_back(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, LOW);
}
void stop_car()
{
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
}
void turn_right_plus(int speed)
{
    analogWrite(pinL_PWM, speed);
    analogWrite(pinR_PWM, speed * 1.5);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, LOW);
}

void improved_correct_track(int speed){
    if (leftSensor && rightSensor && !middleSensor)
    {
        go_straight(speed);
    }
    if(leftSensor && !rightSensor && !middleSensor){
      gentle_turn_right(speed);
    }
    if(!leftSensor && rightSensor && !middleSensor){
      gentle_turn_left(speed);
    }
    if(!leftSensor && rightSensor && middleSensor){
      turn_left(speed);
    }
    if(leftSensor && !rightSensor && middleSensor){
      turn_right(speed);
    }
}

void setup()
{
    // define pins as input and output
    pinMode(pinB_Sensor, INPUT);
    pinMode(pinL_Sensor, INPUT);
    pinMode(pinR_Sensor, INPUT);
    pinMode(pinOR_Sensor, INPUT);
    pinMode(pinOL_Sensor, INPUT);
    pinMode(pinM_Sensor,  INPUT);

    pinMode(pinL_DIR, OUTPUT);
    pinMode(pinR_DIR, OUTPUT);

    pinMode(pinL_PWM, OUTPUT);
    pinMode(pinR_PWM, OUTPUT);

    // initialize output pins
    digitalWrite(pinL_DIR, HIGH); // forward direction
    digitalWrite(pinR_DIR, HIGH); // forward direction
    analogWrite(pinL_PWM, 0);     // stop at the start position
    analogWrite(pinR_PWM, 0);     // stop at the start position
}

// the loop function runs over and over again forever

void loop()
{

    // Arduino is reading the sensor measurements
    bumperSensor = digitalRead(pinB_Sensor);
    leftSensor = digitalRead(pinL_Sensor);
    rightSensor = digitalRead(pinR_Sensor);
    OrightSensor = digitalRead(pinOR_Sensor);
    OleftSensor = digitalRead(pinOL_Sensor);
    middleSensor = digitalRead(pinM_Sensor);
    // car stops at the start position when bumper sensor no trigger
    if (bumperSensor && countBumper == 0)
    {
        analogWrite(pinL_PWM, 0); // stop at the start position
        analogWrite(pinR_PWM, 0);
    }

    // bumper sensor is triggered at the start position for the 1st time
    if (!bumperSensor && countBumper == 0)
    {
        go_straight(regular_speed+10);
        countBumper = countBumper + 1;
        delay(300); // to let the car leave the start position with no miscount
    }
    if (bumperSensor && countBumper == 1)
    {
       improved_correct_track(150);
        if (!OleftSensor && !OrightSensor)
        {
            
            countBumper = countBumper + 1;
            }
            
        }
    

    if (bumperSensor && countBumper == 2)
    {
      
         turn_left(100);
         
         
         if(!middleSensor && OleftSensor  && OrightSensor){
         countBumper++;
         }
    }
    if(bumperSensor && countBumper ==3){
      improved_correct_track(200);
      if(!OleftSensor ){
        
        countBumper = countBumper +1;
        
      }
    }
    if(bumperSensor && countBumper ==4){
      turn_left(100);
      delay(450);
      countBumper++;
      }
      
    if(bumperSensor && countBumper ==5){
      turn_left(100);
      if(!middleSensor ){
        countBumper++;
    }
    }
    if(bumperSensor && countBumper ==6){
      improved_correct_track(200);
      if( !leftSensor && !rightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper==7){
      
      turn_left(100);
      if(!middleSensor){
        countmiddleSensor++;
      }
      if(countmiddleSensor ==2){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==8){
      improved_correct_track(200);
    }
    /*if(bumperSensor && countBumper==6){
      turn_left(100);
      if(!middleSensor && OleftSensor && OrightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==7){
      improved_correct_track(200);
      if(!middleSensor && !leftSensor && !rightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper==8){
      turn_left(100);
      if(!middleSensor && OleftSensor && OrightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper==9){
      improved_correct_track(200);
    }
    
      /*if(!middleSensor && OleftSensor && OrightSensor){
         countBumper = countBumper+1;
         /*countmiddleSensor++;
         delay(180);
         if(countmiddleSensor==4){
          countBumper++;
         }*/
         /*}
    }
      if(bumperSensor && countBumper ==6){
        stop_car();
      }*/
      /*if((!middleSensor && !leftSensor &&  !rightSensor)||(!middleSensor && !leftSensor && !OleftSensor) ||(!middleSensor && !rightSensor && !OrightSensor) ){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==6){
      turn_left(100);
        if(!middleSensor){
          countmiddleSensor++;
          delay(180);
        }
        if(countmiddleSensor==6){
          countBumper++;
        }
    }
    if(bumperSensor && countBumper ==7){
      improved_correct_track(200);
      if(!middleSensor && !leftSensor &&  !rightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==8){
      turn_left(100);
        if(!middleSensor){
          countmiddleSensor++;
          delay(180);
        }
        if(countmiddleSensor==8){
          countBumper++;
        }
     
    }
    if(bumperSensor && countBumper ==9){
      improved_correct_track(200);
      if(!OrightSensor && !middleSensor && !rightSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==10){
      turn_right(100);
      if(!middleSensor){
        countmiddleSensor++;
        delay(180);
      }
      if(countmiddleSensor ==10){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==11){
      improved_correct_track(200);
      if(!middleSensor && !leftSensor &&   !OleftSensor ){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==12){
      turn_left(100);
      if(!middleSensor){
        countmiddleSensor++;
        delay(300);
      }
      if(countmiddleSensor ==12){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==13){
      improved_correct_track(200);
      
      if(!middleSensor && !leftSensor &&   !OleftSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper==14){
      turn_left(100);
      if(!middleSensor){
        countmiddleSensor++;
        delay(300);
      }
      if(countmiddleSensor ==14){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==15){
      improved_correct_track(200);
      
      if(!OleftSensor){
        go_straight(200);
        delay(300);
        
        countBumper++;
      }
    }
    if(bumperSensor && countBumper==16){
      improved_correct_track(200);
        if(!OleftSensor && !leftSensor && !middleSensor){
          countBumper++;
        }
      }
    
    if(bumperSensor && countBumper ==17){
      turn_left(100);
      if(!middleSensor ){
        countmiddleSensor++;
        delay(200);
      }
      if(countmiddleSensor==16){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==18){
      improved_correct_track(200); 
      if(!OrightSensor){
        countBumper++;  
      }
    }
    if(bumperSensor && countBumper ==19){
      turn_right(100);
      if(!middleSensor){
        countmiddleSensor++;
        delay(180);
      }
      if(countmiddleSensor ==18){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==20){
      improved_correct_track(200);
      if(!middleSensor && !rightSensor && !OrightSensor && !leftSensor && !OleftSensor){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==21){
      turn_left(100);
      if(!middleSensor){
        countmiddleSensor++;
        delay(180);
      }
      if(countmiddleSensor== 23){
        countBumper++;
      }
    }
    if(bumperSensor && countBumper ==22){
      improved_correct_track(200);
    }
      /*improved_correct_track(200);
      
      if(!OleftSensor && !leftSensor && !middleSensor && rightSensor && OrightSensor){
        
        countBumper = countBumper +1;
        
      }
     
    }
    if(bumperSensor && countBumper==4){
      
      stop_car();
    }
      /*turn_left(100);
         delay(380);
         if(!middleSensor){
         countBumper = countBumper + 1;
         }
    }
    if(bumperSensor && countBumper==5){
      improved_correct_track(200);
    }*/
        /*if (!OleftSensor && OrightSensor)
        {
            //stop_car();
            turn_left(regular_speed);
            countBumper++;
            delay(400);
        }
        correct_track(10);
    }

    if (bumperSensor && countBumper == 3)
    {

        correct_track(10);
        if (!leftSensor && !rightSensor)
        {
            turn_left(regular_speed);
            countBumper++;
            delay(800);
        }
    }
    if (bumperSensor && countBumper == 4)
    {
        /*go_straight(regular_speed);
        delay(700);
        correct_track(10);
        if (!leftSensor && !rightSensor && !OleftSensor && !OrightSensor)
        {

            turn_left(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
        }
    }
    if (bumperSensor && countBumper == 5)
    {
        go_straight(regular_speed);
        delay(700);
        correct_track(10);
        if (!OrightSensor && !rightSensor)
        {
            turn_right(regular_speed);

            delay(500);
            go_straight(regular_speed);
            delay(100);
            curr_time = millis();
            countBumper = countBumper + 1;
        }
    }

    if (bumperSensor && countBumper == 6)
    {

        // correct_track(1000);
        older_correct_track();
        if (!leftSensor && !rightSensor && !OleftSensor && !OrightSensor && millis() > curr_time + 1000)
        {

            go_straight(regular_speed);
            delay(100);
            turn_left(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper = countBumper + 1;
        }
    } // C curve and left_turn after C curve
    if (bumperSensor && countBumper == 7)
    {
        /*go_straight(regular_speed);
        delay(500);
        correct_track(10);
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            go_straight(regular_speed);
            delay(400);
            countBumper++;
        }

        /*older_correct_track();
           countBumper = countBumper + 1;
           delay(360);
    }
    if (bumperSensor && countBumper == 8)
    {

        correct_track(10);
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            delay(360);
            // stop_car();
            go_straight(regular_speed);
            delay(200);
            turn_right(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(300);
            // older_correct_track();
            countBumper = countBumper + 1;
        }
    }
    if (bumperSensor && countBumper == 9)
    {
        older_correct_track();
        if (!rightSensor && !OrightSensor && leftSensor)
        {
            turn_right(regular_speed);
            delay(360);
            go_straight(regular_speed);
            delay(150);
            older_correct_track();
            if (!rightSensor && !OrightSensor && leftSensor)
            {
                turn_right(regular_speed);
                delay(360);
                go_straight(regular_speed);
                delay(150);
                countBumper++;
            }
        }
    }

    if (bumperSensor && countBumper == 10)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper++;
        }
    }
    if (bumperSensor && countBumper == 11)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && rightSensor)
        {
            turn_left(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
            go_straight(regular_speed);
            delay(150);
            countBumper++;
        }
    }
    if (bumperSensor && countBumper == 12)
    {
        older_correct_track();
        if (!leftSensor && !OleftSensor && !rightSensor && !OrightSensor)
        {
            //stop_car();
            turn_left(regular_speed);
            delay(1600);
            go_straight(regular_speed);
            delay(200);
            countBumper++;
        }
    }
    if(bumperSensor && countBumper == 13)
    {
        older_correct_track();
        if(!leftSensor && !rightSensor)
        {
            stop_car();
            go_back(regular_speed);
            delay(300);
            return;
        }
    }
     // second turn left
    /*if (bumperSensor && countBumper == 12)
    {
        if (!leftSensor && rightSensor)
        {
            turn_left(regular_speed);
        }

        if (leftSensor && !rightSensor)
        {
            turn_right(regular_speed);
        }

        if (leftSensor && rightSensor)
        {
            go_straight(regular_speed);
        }
        if (!rightSensor && !OrightSensor)
        {
            turn_right_plus(regular_speed);
            countBumper = countBumper + 1;
            delay(360);
        }
    }
    if (bumperSensor && countBumper == 13)
    {
        if (!leftSensor && rightSensor)
        {
            turn_left(regular_speed);
        }

        if (leftSensor && !rightSensor)
        {
            turn_right(regular_speed);
        }

        if (leftSensor && rightSensor)
        {
            go_straight(regular_speed);
        }
    }
    */
          }    
