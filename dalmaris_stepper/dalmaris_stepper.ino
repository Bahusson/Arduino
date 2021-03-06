/*  0981 - 28BYJ-48 stepper motor control with the ULN2003 controller breakout
 * 
 * This sketch shows you how to control the common 28BYJ-48 (geared) 
 * stepper motor with the ULN2003 controller breakout. The sketch will
 * make the motor visit specific positions stored in an int array.
 * 
 * The sketch uses the AccelStepper library to accelerate and decelerate the motor as
 * it reaches the individual positions.
 *  
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - ULN2003 motor controller
 *  - 28BYJ-48 geared stepper motor
 *  
 *  Libraries
 *  ---------
 *  - AccelStepper
 *
 * Connections
 * -----------
 *  
 * Arduino   |   ULN2003 breakout
 * ------------------------------
 *      3    |    IN1
 *      4    |    IN2
 *      5    |    IN3
 *      6    |    IN4
 *      GND  |    -
 *           |    - to power supply GND
 *           |    + to power supply 5V
 *     
 *  More information
 *  ----------------
 *  28BYJ-48 datasheet: http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/07/Stepper-Motor-28BJY-48-Datasheet.pdf
 *  ULN2003 breakout datasheet: https://www.itead.cc/wiki/ULN2003_Stepper_Motor_Driver_Board
 *  AccelStepper documentation: http://www.airspayce.com/mikem/arduino/AccelStepper/
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */
 
#include <AccelStepper.h>

// Motor pin definitions
#define motorPin1  7     // IN1 on the ULN2003 driver 1
#define motorPin2  8     // IN2 on the ULN2003 driver 1
#define motorPin3  12     // IN3 on the ULN2003 driver 1
#define motorPin4  13     // IN4 on the ULN2003 driver 1

int current_position = 0; // We'll use this variable to keep track of the current position
int total_positions = 6;  // Total positions in the positions_to_go array.
int positions_to_go[6] = 
  { 1000,
    -1000,
    2000,
    -1500,
    1500,
    500 }; // An arbitrary set of positions for the motor to go to

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{  
   stepper1.setMaxSpeed(200);  // You can work out these values for your stepper motor via
                               // trial and error.
   stepper1.setSpeed(200);     // This speed seems to work well for the 28BYJ-48 stepper
   stepper1.setAcceleration(100.0);  // This value gives quick acceleration to the set speed
   stepper1.setCurrentPosition(0);   // This is the position where the motor happens to find
                                     // itself when the sketch starts.
   stepper1.moveTo(positions_to_go[current_position++]);  // The first position for the motor to move to
   
}
void loop()
{
    if (stepper1.distanceToGo() == 0) {           // If position reached...
    stepper1.moveTo(positions_to_go[current_position++]); // Go back to the opposite position
    
  }
    stepper1.run();                  // Call run() as often as possible

   if (current_position > total_positions)  // If motor has visited all positions, reset
      {  current_position = 0;              // the counter
         delay(1000);                       // Wait for 1sec before restarting.
      }                              
}
