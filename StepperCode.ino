#include <Stepper.h> //Includes the code for Stepper motor

//Declaration and Initialization for global variables
const int stepsPerRevolution = 825;
int stepCount = 0;

//Declaring the ports used for the stepper
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  //No setup required
}

void loop() {
  //Reading and maping the sensor value
  int sensorReading = analogRead(A0);
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  
  //Set the motor speed
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    //The motor takes a step
    myStepper.step(stepsPerRevolution / 100);
  }
}
