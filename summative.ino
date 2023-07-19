//*************************************************************
//Title - Main Code w/ Bluetooth
//Description - A program that takes bluetooth input to control a car including forward, backward, turning, brake lights, and turn signals
//Author - Darren Liu
//Date - 06/14/23
//*************************************************************


#include <SoftwareSerial.h>;
SoftwareSerial Bluetooth(10, 11);//RX TX, Digital pins used for bluetooth


int cmd; //int variable used to capture bluetooth input


//the following are all int variables used to store the port ID's of each digital or analog pin


//left wheel output A and B
int LA = 5;
int LB = 4;
//right wheel output A and B
int RA = 3;
int RB = 2;


//Front/Back Left/Right light
int lightBL = 9;
int lightBR = 14;
int lightFL = 6;
int lightFR = 19;


//Right and left brake lights
int brakeR = 13;
int brakeL = 12;


int fast = 255;


void setup() {
  Bluetooth.begin(9600);//Working baud rate for my chip
  Serial.begin(38400);
  Bluetooth.println("Hello darren");


  //set all of our digital/analog pins to output mode except for the bluetooth pins
  pinMode(LA, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RA, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(lightBL, OUTPUT);
  pinMode(lightBR, OUTPUT);
  pinMode(lightFL, OUTPUT);
  pinMode(lightFR, OUTPUT);
  pinMode(brakeR, OUTPUT);
  pinMode(brakeL, OUTPUT);
}


void loop() {


  if (Bluetooth.available()) {//check if bluetooth is available
    cmd = Bluetooth.read();//set int cmd to most recent bluetooth input


    if (cmd == '6') {
      Bluetooth.println("6 --> forward");
      lightsF();
      rightCW();
      leftCCW();//since the motors are mirrored, they should spin in opposite directions relative to the axle in order to spin in the same direction
      brakeLightsOFF();//in case the brake lights were previously on
      delay(500);
      leftStop();
      delay(300);
      leftCCW();
      delay(350);
      rightStop();
      leftStop();
      brakeLightsON();
    }


    if (cmd == '7') {
      Bluetooth.println("7 --> backward");
      lightsB();
      rightCCW();
      leftCW();
      brakeLightsOFF();//in case the brake lights were previously on
      delay(500);
      leftStop();
      delay(300);
      leftCW();
      delay(350);
      rightStop();
      leftStop();
      brakeLightsON();
    }


    if (cmd == '8') {
      Bluetooth.println("8 --> left");
      stopWheels();
      leftCW();
      rightCW();//the motors spinning in the same direction relative to their axles will result in them spinning in opposite directions
      lightsL();
      brakeLightsOFF();//in case the brake lights were previously on
    }


    if (cmd == '9') {
      Bluetooth.println("9 --> right");
      stopWheels();
      rightCCW();
      leftCCW();
      lightsR();
      brakeLightsOFF();//in case the brake lights were previously on


    }


    if (cmd == '5') {//brake command, turns the brake lights on
      Bluetooth.println("5 --> brake");
      stopWheels();
      brakeLightsON();
    }


    if(cmd == '1'){
      brakeLightsOFF();
      lightsF();
      rightCW();
      leftCCW();
    }


    //Next few are for testing the LED's


    // if (cmd == '1') {
    //   digitalWrite(lightBL, HIGH);
    //   digitalWrite(lightBR, HIGH);
    //   Bluetooth.println("1 --> back headlights on");
    // }


    // if (cmd == '2') {
    //   digitalWrite(lightBL, LOW);
    //   digitalWrite(lightBR, LOW);
    //   Bluetooth.println("2 --> back headlights off");
    // }


    // if (cmd == '3') {
    //   digitalWrite(lightFL, HIGH);
    //   digitalWrite(lightFR, HIGH);
    //   Bluetooth.println("3 --> front headlights on");
    // }


    // if (cmd == '4') {
    //   digitalWrite(lightFL, LOW);
    //   digitalWrite(lightFR, LOW);
    //   Bluetooth.println("4 --> front headlights off");
    // }


    // if (cmd == '5') {
    //   lightsON();
    //   Bluetooth.println("5 --> all lights on");
    // }


    if (cmd == '0') {//emergendy stop - turns off all motors and LED's
      Bluetooth.println("0 --> stopping everying");
      stopWheels();
      lightsOFF();
      brakeLightsOFF();
    }
  }
}


//the following methods are to make code more readable and editing as well as coding faster


void rightCCW() {
  digitalWrite(RA, LOW);
  digitalWrite(RB, HIGH);
}


void leftCCW() {
  digitalWrite(LA, LOW);
  digitalWrite(LB, HIGH);
}


void rightCW() {
  digitalWrite(RA, HIGH);
  digitalWrite(RB, LOW);
}


void rightStop(){
  digitalWrite(RA, LOW);
  digitalWrite(RB, LOW);
}


void leftStop(){
  digitalWrite(LA, LOW);
  digitalWrite(LB, LOW);
}


void leftCW() {
  digitalWrite(LA, HIGH);
  digitalWrite(LB, LOW);
}


void rightCWSlow(){
  rightCW();
  delay(500);
  rightStop();
  delay(200);
}


void rightCCWSlow(){
  rightCCW();
  delay(500);
  rightStop();
  delay(200);
}


void lightsF() {//turn back lights off and front lights on
  digitalWrite(lightBL, LOW);
  digitalWrite(lightBR, LOW);
  digitalWrite(lightFL, HIGH);
  digitalWrite(lightFR, HIGH);
}


void lightsB() {//turn back lights on and front lights off
  digitalWrite(lightBL, HIGH);
  digitalWrite(lightBR, HIGH);
  digitalWrite(lightFL, LOW);
  digitalWrite(lightFR, LOW);
}


void lightsR() {//turn on the two right side lights and turn off the left lights
  digitalWrite(lightBL, LOW);
  digitalWrite(lightFL, LOW);
  digitalWrite(lightBR, HIGH);
  digitalWrite(lightFR, HIGH);
  delay(500);
  digitalWrite(lightBR, LOW);
  digitalWrite(lightFR, LOW);
  delay(500);
  digitalWrite(lightBR, HIGH);
  digitalWrite(lightFR, HIGH);
}


void lightsL() {//turn on the two left side lights and turn off the right lights
  digitalWrite(lightBR, LOW);
  digitalWrite(lightFR, LOW);
  digitalWrite(lightBL, HIGH);
  digitalWrite(lightFL, HIGH);
  delay(500);
  digitalWrite(lightBL, LOW);
  digitalWrite(lightFL, LOW);
  delay(500);
  digitalWrite(lightBL, HIGH);
  digitalWrite(lightFL, HIGH);
}


void stopWheels() {//cut power to all motors
  digitalWrite(LA, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RA, LOW);
  digitalWrite(RB, LOW);
}


void brakeLightsON() {//turn all other lights off and turn brake lights on
  digitalWrite(lightFL, LOW);
  digitalWrite(lightFR, LOW);
  digitalWrite(lightBL, LOW);
  digitalWrite(lightBR, LOW);
  digitalWrite(brakeR, HIGH);
  digitalWrite(brakeL, HIGH);
}


void brakeLightsOFF() {//turn off just brake lights
  digitalWrite(brakeR, LOW);
  digitalWrite(brakeL, LOW);
}


void lightsOFF() {//turn off front and back lights
  digitalWrite(lightFL, LOW);
  digitalWrite(lightFR, LOW);
  digitalWrite(lightBL, LOW);
  digitalWrite(lightBR, LOW);
}


void lightsON() {//turn on front and back lights
  digitalWrite(lightFL, HIGH);
  digitalWrite(lightFR, HIGH);
  digitalWrite(lightBL, HIGH);
  digitalWrite(lightBR, HIGH);
}