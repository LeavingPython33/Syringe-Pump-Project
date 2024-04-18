//Speed Motor (200 step per rev *with no microstepping*)
//Diameter of syringe
//Lead Screw (2mm or 8mm)
//speed = ((step/sec)/(step per Rev)) * lead screw
//Volumetric flow rate = (pi*speed*(diameter/2)^2)/min * 1cm^3/1000mm^3 * 60sec/1min

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 3, 2);

const int endSwitchPin = 0;
const int buttonPin = 0;
const int potPin = 0;
const int rgbPin[3] = {0, 0, 0};

const int microStep = 0; //Steps/Rev
const int diameter = 0; //mm
const int leadScrew = 8; //mm

int flowRate = 0; //Input desired flowRate
int speed = (flowRate /(PI * pow((diameter / 2), 2))); //mm/s
int stepPerSec = (speed / leadScrew) * microStep; //Steps/s


//const int speed = ((stepPerSec/microStep) * leadScrew
//int flowRate = (PI * speed * pow((diameter / 2), 2)); 

void setup() {
  //Initialize Button
  pinMode(buttonPin, INPUT_PULLUP);

  //Initialize LED
  for (int i = 0; i < 3; i++){
    pinMode(rgbPin[i], OUTPUT); 
  }

  //Initialize stepperMotor
  stepper.setSpeed(stepPerSec);
  stepper.setAcceleration(stepPerSec);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonVal = digitalRead(buttonPin);
  int potVal = digitalRead(potPin); // 0 - 1023

  if(buttonVal == HIGH){
    int rgb[3] = {0, 255, 0};
    writeLed(rgb);
    stepper.runSpeed();
    
  }
  else{
    int rgb[3] = {255, 0, 0};
    writeLed(rgb);
    stepper.stop();
  }
}

void writeLed(int rgb[]){
  for (int i = 0; i < 3; i++){
    analogWrite(rgbPin[i], rgb[i]); 
    }
}
