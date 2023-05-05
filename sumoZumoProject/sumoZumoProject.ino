
#include <Wire.h>
#include <Zumo32U4.h>
#include <LiquidCrystal.h>
#include "ZumoLCD.h"
#include "customchars.h"

// pin assignments for LCD
uint8_t rs = 0, e = 1, db4 = 14, db5 = 17, db6 = 13, db7 = IO_D5;
uint8_t lcdPins[] = {rs, e, db4, db5, db6, db7};

// custom zumo LCD display class that allows for passing different pins
// for use with LiquidCrystal LCD 
ZumoLCD display(lcdPins);

//Zumo32U4LCD display;
Zumo32U4Encoders encoders;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonC buttonA;

Zumo32U4IMU imu;

// stores lineSensorValues when read
unsigned int lineSensorValues[3];

// threshold to determined if line has been sensed
const uint16_t lineSensorThreshold = 1000;

// threshold to determined if prox sensor can see an object
const uint8_t sensorThreshold = 12;

const uint16_t turnSpeedMax = 300;
const uint16_t turnSpeedMin = 100;
const uint16_t forwardSpeed = 150;
const uint16_t forwardSpeedMax = 300;
const uint16_t deceleration = 10;
const uint16_t acceleration = 10;

#define LEFT 0
#define RIGHT 1

// saves last direction prox indication object was seen
bool senseDir = RIGHT;

bool turningLeft = false;
bool turningRight = false;

// Zumo turning speeds
uint16_t turnSpeed = turnSpeedMax;
uint16_t leftSpeed = forwardSpeed;
uint16_t rightSpeed = forwardSpeed;

const uint16_t veerSpeed = 10;

// The time, in milliseconds, when an object was last seen.
uint16_t lastTimeObjectSeen = 0;

uint8_t leftValue;
uint8_t rightValue;
uint8_t lLValue;
uint8_t rRValue;

uint16_t myBrightnessLevels[] = {1, 2, 4, 9, 15, 23, 32, 42, 55, 70, 85, 100, 120, 135, 150, 170};

bool lineLeft = false;
bool lineRight = false;

// hold encoder value to line
int16_t toLine;

// records score
int scoreWin;


int accX;
int accY;

bool collidedLeft = false;
bool collidedRight = false;

int lastBlink;

int stime;

void setup()
{
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
  proxSensors.setBrightnessLevels(myBrightnessLevels, 16);

  imu.enableDefault();

  encoderReset();

  display.begin(16,2);

  // creating a new characters
  display.createChar(1, eye1);
  display.createChar(2, eye2);
  display.createChar(3, eye3);
  display.createChar(4, eye4);

  //Serial.begin(9600);

  display.clear();

  delay(500);

  // Waits for the user to press C before driving the motors.
  display.clear();
  display.setCursor(0, 0);
  display.blink();
  display.print(F("Press C"));
  buttonA.waitForButton();
  display.clear();

  // set eyes to look forward
  eyesForward();

  Serial1.begin(9600);

  //counter for blink
  stime = millis();
}

void eyesForward()
{
  // sets up eyes forward custom characters for LCD
  Serial1.end();
  display.begin(16,2);
  display.clear();

  display.createChar(1, eye1);
  display.createChar(2, eye2);
  display.createChar(3, eye3);
  display.createChar(4, eye4);

  display.setCursor(4, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(5, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(4, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(5, 1);
  // draw the eye4
  display.write(4);

  display.setCursor(10, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(11, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(10, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(11, 1);
  // draw the eye4
  display.write(4);

  Serial1.begin(9600);
}

void eyesLeft()
{
  display.setCursor(4, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(5, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(4, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(5, 1);
  // draw the eye4
  display.write(4);

  display.setCursor(10, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(11, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(10, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(11, 1);
  // draw the eye4
  display.write(4);
}

void eyesRight()
{
  display.setCursor(4, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(5, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(4, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(5, 1);
  // draw the eye4
  display.write(4);

  display.setCursor(10, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(11, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(10, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(11, 1);
  // draw the eye4
  display.write(4);

}

void eyesBlink()
{
  Serial1.end();
  display.begin(16,2);
  display.clear();

  display.createChar(1, eyeB1);
  display.createChar(2, eyeB2);
  display.createChar(3, eyeB3);
  display.createChar(4, eyeB4);

  display.setCursor(4, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(5, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(4, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(5, 1);
  // draw the eye4
  display.write(4);

  display.setCursor(10, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(11, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(10, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(11, 1);
  // draw the eye4
  display.write(4);

  Serial1.begin(9600);
}

void eyesWin()
{
  display.setCursor(4, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(5, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(4, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(5, 1);
  // draw the eye4
  display.write(4);

  display.setCursor(10, 0);
  // draw the eye1
  display.write(1);
  display.setCursor(11, 0);
  // draw the eye2
  display.write(2);
  display.setCursor(10, 1);
  // draw the eye3
  display.write(3);
  display.setCursor(11, 1);
  // draw the eye4
  display.write(4);
}

void lineSensorRead()
{
  // determines it theres a line left or right
  lineSensors.read(lineSensorValues);
  if(lineSensorValues[0] >= lineSensorThreshold)
  {
    lineLeft = true;
  }
  else
  {
    lineLeft = false;
  }
  if(lineSensorValues[2] >= lineSensorThreshold)
  {
    lineRight = true;
  }
  else
  {
    lineRight = false;
  }
}

void encoderReset()
{
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();
}

int16_t getEncoderCount()
{
  return (encoders.getCountsLeft() + encoders.getCountsRight())/2;
}

int16_t getEncoderCountLeft()
{
  return encoders.getCountsLeft();
}

int16_t getEncoderCountRight()
{
  return encoders.getCountsRight();
}

void turnRight()
{
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft()
{
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

bool onLine()
{
  // checks if zumo is on a line
  lineSensorRead();
  if(lineLeft || lineRight)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void reverse()
{
  motors.setSpeeds(-forwardSpeedMax, -forwardSpeedMax);  
}

void driveForward()
{
  // if onLine() stop()
  motors.setSpeeds(leftSpeed, rightSpeed);
}

void turnAwayFromLine()
{
  int16_t tillCount = getEncoderCount();

  int16_t turn180 = 1300;
  if(toLine == NULL)
  {
    toLine = tillCount;
  }
  //Serial.println(tillCount);
  encoderReset();
  int16_t leftCount = getEncoderCountLeft();
  
  turnSpeed = forwardSpeedMax;

  while(leftCount > -turn180)
  {
    turnLeft();
    leftCount = getEncoderCountLeft();
    // display.setC(0, 0);
    // display.print(leftCount);
  }

  stop();
  delay(1000);

  encoderReset();
  int16_t count = getEncoderCount();
  turnSpeed = turnSpeedMax;

  while(count < toLine)
  {
    driveForward();
    count = getEncoderCount();
    //Serial.println(count);
  }
  stop();

  delay(100);

  if(senseDir == RIGHT)
  {
    int start = millis();
    int passed = millis() - start;

    while(passed < 250)
    {
      turnRight();
      passed = millis() - start;
    }
    stop();

  }
  else
  {
    int start = millis();
    int passed = millis() - start;

    while(passed < 250)
    {
      turnLeft();
      passed = millis() - start;
    }
    stop();
  }
}

void stop()
{
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void proxRead()
{
  proxSensors.read();
  // saves front and side prox sensor values separately
  leftValue = proxSensors.countsFrontWithLeftLeds();
  rightValue = proxSensors.countsFrontWithRightLeds();

  lLValue = proxSensors.countsLeftWithLeftLeds();
  rRValue = proxSensors.countsRightWithRightLeds();
}

void driveTowards()
{
  //encoderReset();
  proxRead();

  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool objectSeenSides = lLValue >= sensorThreshold || rRValue >= sensorThreshold;

  if(objectSeen)
  {
    if(leftValue > rightValue)
    {
      leftSpeed += veerSpeed;
      rightSpeed = forwardSpeed;
    }
    else if(rightValue > leftValue)
    {
      rightSpeed += veerSpeed;
      leftSpeed = forwardSpeed;
    }
    else
    {
      rightSpeed = forwardSpeed;
      leftSpeed = forwardSpeed;
    }

    leftSpeed = constrain(leftSpeed,forwardSpeed,forwardSpeedMax);
    rightSpeed = constrain(rightSpeed,forwardSpeed,forwardSpeedMax);
    
    if(onLine())
    {
      stop();
      scoreWin += 1;
    }
    else
    {
      driveForward();
    }
  }
  else
  {
    stop();
  }
}

void readAcc()
{
  imu.readAcc();
  accX = imu.a.x;
  accY = imu.a.y;
}

bool collision()
{
  // checks for collision
  bool collided = false;
  if(accX > 500)
  {
    collided = true;
    collidedLeft = true;
  }
  else
  {
    collidedLeft = false;
  }
  if(accY > 500)
  {
    collided = true;
    collidedRight = true;
  }
  else
  {
    collidedRight = false;
  }

  return collided;
}

void turnAndRam()
{
  int16_t turn90 = 650;
  
  if(collidedLeft)
  {
    encoderReset();

    int16_t leftCount = getEncoderCountLeft();

    while(leftCount > -turn90)
    {
      turnLeft();
      leftCount = getEncoderCountLeft();
    }
    stop();

    encoderReset();

    int16_t count = getEncoderCount();

    while(count < 500)
    {
      driveForward();
      count = getEncoderCount();
    }
    stop();

    encoderReset();

    leftCount = getEncoderCountLeft();

    while(leftCount > -turn90)
    {
      turnLeft();
      leftCount = getEncoderCountLeft();
    }
    stop();
  }
  else if(collidedRight)
  {
    encoderReset();

    int16_t rightCount = getEncoderCountRight();

    while(rightCount > -turn90)
    {
      turnRight();
      rightCount = getEncoderCountRight();
    }
    stop();

    encoderReset();

    int16_t count = getEncoderCount();

    while(count < 500)
    {
      driveForward();
      count = getEncoderCount();
    }
    stop();

    encoderReset();

    rightCount = getEncoderCountRight();

    while(rightCount > -turn90)
    {
      turnRight();
      rightCount = getEncoderCountRight();
    }
    stop();
  }
}

void loop()
{

  lastBlink = millis() - stime;

  // checks for last blink
  if(lastBlink > 2000)
  {
    stime = millis();
    eyesBlink();
  }
  else if (lastBlink > 1000)
  {
    eyesForward();
  }

  // sends score to GUI
  if(scoreWin > 0)
  {
    Serial1.print("My Score: ");
    Serial1.println(scoreWin);
  }

  if(collision())
  {
    delay(5000);
    turnAndRam();
  }
  

  if(onLine())
  {
    turnAwayFromLine();
  }
  
  proxRead();
  // Determine if an object is visible or not.
  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;
  bool objectSeenSides = lLValue >= sensorThreshold || rRValue >= sensorThreshold;

  if (objectSeen)
  {
    // An object is visible, so we will start decelerating in
    // order to help the robot find the object without overshooting
    turnSpeed -= deceleration;
  }
  else
  {
    // An object is not visible, so we will accelerate in order
    // to help find the object sooner.
    turnSpeed += acceleration;
  }

  // Constrain the turn speed so it is between turnSpeedMin and
  // turnSpeedMax.
  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen)
  {
    // An object seen.
    ledYellow(1);

    lastTimeObjectSeen = millis();

    if (leftValue < rightValue)
    {
      // The right value is greater, so the object is probably
      // closer to the robot's right LEDs, which means the robot
      // is not facing it directly.  Turn to the right to try to
      // make it more even.
      turnRight();
      senseDir = RIGHT;
    }
    else if (leftValue > rightValue)
    {
      // The left value is greater, so turn to the left.
      turnLeft();
      senseDir = LEFT;
    }
    else
    {
      // The values are equal, so drive towards opponent
      // object in front
      driveTowards();

    }
  }
  else
  {
    // No object is seen, so just keep turning in the direction
    // that we last sensed the object.
    ledYellow(0);

    if (senseDir == RIGHT)
    {
      turnRight();
    }
    else
    {
      turnLeft();
    }
  }


  // used to display prox and line sensor values on LCD when needed
  // display.gotoXY(0, 0);
  // display.print(lLValue);
  // display.print(' ');
  // display.gotoXY(6, 0);
  // display.print(rRValue);
  
  // display.gotoXY(1, 1);
  // display.print(leftValue);
  // display.print(' ');
  // display.print(' ');
  // display.print(rightValue);
  // display.print(turningRight ? 'R' : (turningLeft ? 'L' : ' '));
  // display.print(' ');
  // display.print(turnSpeed);
  // display.print(' ');
  // display.print(' ');
}
