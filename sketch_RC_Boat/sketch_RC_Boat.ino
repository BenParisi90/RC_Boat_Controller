#include <Arduino.h>
#include <SoftwareSerial.h>

//Bluetooth
const byte rxPin = 7;
const byte txPin = 8;
SoftwareSerial BTSerial(rxPin, txPin);
/*const char LEFT = 'a';
const char RIGHT = 'd';
const char FORWARD = 'w';
const char BACKWARD = 's';
const char RELEASE_LEFT = 'j';
const char RELEASE_RIGHT = 'l';
const char RELEASE_FORWARD = 'i';
const char RELEASE_BACKWARD = 'k';
bool left = false;
bool right = false;
bool forward = false;
bool backward = false;*/
const char LEFT_FORWARD = 'q';
const char LEFT_NEUTRAL = 'a';
const char LEFT_BACKWARD = 'z';
const char RIGHT_FORWARD = 'w';
const char RIGHT_NEUTRAL = 's';
const char RIGHT_BACKWARD = 'x';

//Delta Time
long previousMillis = 0;  // Variable to store the previous millis() value
long currentMillis = 0;   // Get the current millis() value

//Motor A
//int enA = 3;
int in1 = 13;
int in2 = 12;
//Motor B
//int enB = 9;
int in3 = 11;
int in4 = 10;

int motorSwitchTime = 1000;
bool motorHigh = false;

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  BTSerial.begin(9600);

  // put your setup code here, to run once:
  //pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //analogWrite(enA, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //analogWrite(enB, 120);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.begin(115200);
}

void loop() {

  currentMillis = millis();

  // Calculate the time elapsed since the last output
  unsigned long deltaTime = currentMillis - previousMillis;

  // Update the previousMillis with the currentMillis for the next iteration
  previousMillis = currentMillis;

  //Turn battery on an off every 3 seconds
  /*motorSwitchTime -= deltaTime;
  //Serial.println(motorSwitchTime);
  if(motorSwitchTime <= 0)
  {
    motorSwitchTime = 3000 + motorSwitchTime;
    if(motorHigh)
    {
      Serial.println("on");
      toggleMotor(1, 1);
      motorHigh = false;
    }
    else
    {
      Serial.println("off");
      toggleMotor(0, 0);
      motorHigh = true;
    }
  }*/

  // put your main code here, to run repeatedly:
  while(BTSerial.available() > 0)
  {
    char data = (char) BTSerial.read();

    //Motor toggle controls
    switch(data)
    {
      case LEFT_FORWARD:
        toggleMotor(1, -2); //-2 makes value be ignored
        break;
      case LEFT_NEUTRAL:
        toggleMotor(0, -2);
        break;
      case LEFT_BACKWARD:
        toggleMotor(-1, -2); //-2 makes value be ignored
        break;
      case RIGHT_FORWARD:
        toggleMotor(-2, 1); //-2 makes value be ignored
        break;
      case RIGHT_NEUTRAL:
        toggleMotor(-2, 0);
        break;
      case RIGHT_BACKWARD:
        toggleMotor(-2, -1); //-2 makes value be ignored
        break;
    }

    /*Direct drive
    int intValue = data;
    intValue = intValue - 48;
    int power = map(intValue, 0, 9, 0, 255);
    Serial.println(power);
    digitalWrite(enA, power);*/
    

    //WASD (plus i to stop)
    /*if(data == FORWARD)
    {
      toggleMotor(1, 1);
    }
    if(data == BACKWARD)
    {
      toggleMotor(-1, -1);
    }
    if(data == LEFT)
    {
      toggleMotor(-1, 1);
    }
    if(data == RIGHT)
    {
      toggleMotor(1, -1);
    }
    if(data == RELEASE_FORWARD)
    {
      toggleMotor(0, 0);
    }*/
  }
}

void toggleMotor(int motorA, int motorB)
{
  Serial.print("Toggle motor");
  if(motorA == 1)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if(motorA == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  else if(motorA == -1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  if(motorB == 1)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(motorB == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else if(motorB == -1)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  motorHigh = !motorHigh;
}
