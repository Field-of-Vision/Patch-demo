
#include "AccelStepper.h" 
#include <MultiStepper.h>




// AccelStepper Setup
AccelStepper stepper2(AccelStepper::DRIVER, 3, 4);
AccelStepper stepper1(AccelStepper::DRIVER, 8, 9);  // 1 = Easy Driver interface
                                  // NANO Pin 2 connected to STEP pin of Easy Driver
                                  // NANO Pin 3 connected to DIR pin of Easy Driver

// Define the Pins used
#define home_switch 14 // Pin 9 connected to Home Switch (MicroSwitch)
#define home_switch2 15
// Stepper Travel Variables
long TravelX;  // Used to store the X value entered in the Serial Monitor
int move_finished=1;  // Used to check if move is completed
long initial_homing=-1;  // Used to Home Stepper at startup

MultiStepper steppers;
void setup() {
  
   Serial.begin(9600);  // Start the Serial monitor with speed of 9600 Bauds
   
   pinMode(home_switch, INPUT_PULLUP);
   pinMode(home_switch2, INPUT_PULLUP);
   
   delay(5);  // Wait for EasyDriver wake up

   //  Set Max Speed and Acceleration of each Steppers at startup for homing
  stepper1.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepper1.setAcceleration(20000.0);  // Set Acceleration of Stepper
 

// Start Homing procedure of Stepper Motor at startup

  Serial.print("Stepper is Homing . . . . . . . . . . . ");

  while (digitalRead(home_switch)) {  // Make the Stepper move CCW until the switch is activated   
    stepper1.moveTo(-10000);  // Set the position to move to
    //initial_homing--;  // Decrease by 1 for next move if needed
    stepper1.run();  // Start moving the stepper
    delay(5);
}

  stepper1.setCurrentPosition(0);  // Set the current position as zero for now
  stepper1.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepper1.setAcceleration(20000.0);  // Set Acceleration of Stepper
  initial_homing=1;

  while (!digitalRead(home_switch)) { // Make the Stepper move CW until the switch is deactivated
    stepper1.moveTo(initial_homing);  
    stepper1.run();
    initial_homing++;
    delay(5);
  }
  
  stepper1.setCurrentPosition(0);
  Serial.println("Homing Completed");
  Serial.println("");
  stepper1.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepper1.setAcceleration(20000.0);  // Set Acceleration of Stepper

// Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");
    stepper1.setMaxSpeed(700);
  stepper2.setMaxSpeed(700);



 while (digitalRead(home_switch2)) {  // Make the Stepper move CCW until the switch is activated   
    stepper2.moveTo(-10000);  // Set the position to move to
    //initial_homing--;  // Decrease by 1 for next move if needed
    stepper2.run();  // Start moving the stepper
    delay(5);
}

  stepper2.setCurrentPosition(0);  // Set the current position as zero for now
  stepper2.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  stepper2.setAcceleration(20000.0);  // Set Acceleration of Stepper
  initial_homing=1;

  while (!digitalRead(home_switch2)) { // Make the Stepper move CW until the switch is deactivated
    stepper2.moveTo(initial_homing);  
    stepper2.run();
    initial_homing++;
    delay(5);
  }
  
  stepper1.setCurrentPosition(0);
  Serial.println("Homing Completed");
  Serial.println("");
  stepper1.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepper1.setAcceleration(20000.0);  // Set Acceleration of Stepper

    stepper2.setCurrentPosition(0);
  stepper2.setMaxSpeed(20000.0);      // Set Max Speed of Stepper (Faster for regular movements)
  stepper2.setAcceleration(20000.0);  // Set Acceleration of Stepper

// Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");
    stepper1.setMaxSpeed(700);
  stepper2.setMaxSpeed(700);


  

//long positions [2];
  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);





  
}

void loop() {
  
  
  int w=1100;
//  long positions[2]; // Array of desired stepper positions
 // stepper1.setMaxSpeed(2000);
 // stepper2.setMaxSpeed(2000);
  

float wCoordinates [35] = {5.5, 5.7, 6, 5.9, 6.1, 6.5, 7, 7.2, 7.3, 6.5, 6.2, 6, 8, 7.7, 7.6, 7.4, 6.8, 5.5, 5.2, 5.3, 5.4, 5.2, 5.3, 5.4, 5.8, 6, 6.1, 6.2, 6.3, 6.4, 4.8, 4.7, 4.7, 5, 5};
float lCoordinates [35] = {4.5, 4, 3.7, 3, 2.5, 2.6, 2.6, 2.6, 2.3, 1.9, 1.7, 1.4, 1.7, 1.8, 1.8, 2.7, 3.7, 4.2, 4.7, 5.2, 5.8, 6.3, 7.5, 8, 9, 9, 6.5, 6, 4.5, 3.5, 2.4, 1.8, 1.7, 0.3, 0,};

 stepper1.setMaxSpeed(7000);
  stepper2.setMaxSpeed(7000);
  
long positions[2];

  positions[0] = 5.0*w;
 positions[1] = 4.5*w*1.7;
  steppers.moveTo(positions);
 steppers.runSpeedToPosition(); // Blocks until all are in position
 

for (int i = 0; i <= 35; i++) {
 
  float widthW = wCoordinates[i];
float lengthL = lCoordinates[i];

  float nextWidthW = wCoordinates[i+1];
float nextlengthL = lCoordinates[i+1];

  float currentPositionX = widthW*w;
float currentPositionY = lengthL*w*1.7;

  float nextPositionX = nextWidthW*w;
float nextPositionY = nextlengthL*w*1.7;
  
  stepper1.setMaxSpeed(abs(nextPositionX - currentPositionX));
stepper2.setMaxSpeed(abs(nextPositionY - currentPositionY));
  

positions[0] = currentPositionX;
positions[1] = currentPositionY;
  
   steppers.moveTo(positions);
   steppers.runSpeedToPosition();
 delay(1000);
}



//for (int i = 0; i <= 35; i++) {
// 
// // float widthW = wCoordinates[i];
//float lengthL = lCoordinates[i];
//
// // float nextWidthW = wCoordinates[i+1];
//float nextlengthL = lCoordinates[i+1];
//
// // float currentPositionX = widthW*w;
//float currentPositionY = lengthL*w*1.7;
//
// // float nextPositionX = nextWidthW*w;
// float nextPositionY = nextlengthL*w*1.7;
//  
// // stepper1.setMaxSpeed(abs(nextPositionX - currentPositionX));
//stepper2.setMaxSpeed(abs(nextPositionY - currentPositionY));
//  
//
////positions[0] = currentPositionX;
//positions[1] = currentPositionY;
//  
//   steppers.moveTo(positions);
//   steppers.runSpeedToPosition();
// 
//}



delay(5000);

}//
