//Speed Motor (200 step per rev *with no microstepping*)
//Diameter of syringe
//Lead Screw (2mm or 8mm)
//speed = ((step/sec)/(step per Rev)) * lead screw
//Volumetric flow rate = (pi*speed*(diameter/2)^2)/min * 1cm^3/1000mm^3 * 60sec/1min

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 0, 0);

//Electrical Componenent Pins
const int limitSwitchPin = 0;
const int buttonPin = 0;
const int potPin = 0;
const int rgbPin[3] = {0, 0, 0};

const int leftButtonPin = 0;
const int rightButtonPin = 0;

//Physical Item Attribute
const int microStep = 0; //Steps/Rev
const int diameter = 19; //mm 19/14.5
const int leadScrew = 8; //mm

//FlowRate calculator
double flowRate = 0; //Input desired flowRate in ml/s
double speed = (flowRate /(PI * pow((diameter / 2), 2)) * 1000); //mm/s
double stepPerSec = (speed / leadScrew) * microStep; //Steps/s

//Dynamic flowrate
int prevPotVal = 0; //Dynamic flow rate
int dynamic = false; //Dynamic On/Off

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
  //Reading Pins
  int buttonVal = digitalRead(buttonPin); // On/Off
  int limVal = digitalRead(limitSwitchPin); // NonEmpty/Empty
  int potVal = digitalRead(potPin); // 0 - 1023 (0 - 1ml)
  int leftButtonVal = digitalRead(leftButtonPin);
  int rightButtonVal = digitalRead(rightButtonPin);

  //Dynamic FlowRate
  if(potVal != prevPotVal and dynamic){
    prevPotVal = potVal;
    computeSteps((double)prevPotVal/1000);
  }  

  if(limVal == HIGH){
    //Syringe Empty
    int rgb[3] = {255, 0, 0};
    writeLed(rgb);
    stepper.stop();
  }
  else if(leftButtonVal == HIGH){
    //Moving Left
    int rgb[3] = {0, 255, 0};
    stepper.setSpeed(-stepPerSec);
    writeLed(rgb);
  }
  else if(rightButtonVal == HIGH){
    //Moving Right
    int rgb[3] = {0, 255, 0};
    writeLed(rgb);
    stepper.setSpeed(stepPerSec);
    stepper.runSpeed();
  }
  else{
    //Moving Right if button is ON
    stepper.setSpeed(stepPerSec);
    if(buttonVal == HIGH){
      int rgb[3] = {0, 255, 0};
      writeLed(rgb);
      stepper.runSpeed();
      
    }
    else{
      int rgb[3] = {0, 0, 255};
      writeLed(rgb);
      stepper.stop();
    }
  }
}

void computeSteps(double flow){
  flowRate = flow;
  speed = (flowRate /(PI * pow((diameter / 2), 2)) * 1000); //mm/s
  stepPerSec = (speed / leadScrew) * microStep; //Steps/s
}

void writeLed(int rgb[]){
  for (int i = 0; i < 3; i++){
    analogWrite(rgbPin[i], rgb[i]); 
    }
}
