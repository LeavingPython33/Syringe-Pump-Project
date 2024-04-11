//Speed Motor (200 step per rev *with no microstepping*)
//Diameter of syringe
//Lead Screw (2mm or 8mm)
//speed = ((step/sec)/(step per Rev)) * lead screw
//Volumetric flow rate = (pi*speed*(diameter/2)^2)/min * 1cm^3/1000mm^3 * 60sec/1min

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 3, 2);
const int buttonPin = ;
const int potentiometerPin = ;
const int redPin = ;
const int greenPin = ;
const int bluePin = ;

const int diameter = ;
const int leadScrew = ;
const int stepPerSec = ;
const int microStep = ;

int flowRate = ;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
