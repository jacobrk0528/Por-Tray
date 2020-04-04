/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jacob Krebs                                               */
/*    Created:      Mon Mar 16 2020                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
//-------------------------------------MOTOR SETUP-------------------------------------------------
  vex::motor RightBackMotor(vex::PORT1, ratio18_1, true);
  vex::motor LeftBackMotor(vex::PORT2, ratio18_1, false);
  vex::motor RightFrontMotor(vex::PORT3, ratio18_1, true);
  vex::motor LeftFrontMotor(vex::PORT4, ratio18_1, false);
  vex::inertial Inertial(vex::PORT10);

  vex::controller controller1 = controller();

  vex::directionType forward_ = vex::directionType::fwd;
  vex::directionType reverse_ = vex::directionType::rev;

  vex::velocityUnits velocity_dps = vex::velocityUnits::dps;
  vex::velocityUnits velocity_pct = vex::velocityUnits::pct;
  vex::velocityUnits velocity_rpm = vex::velocityUnits::rpm;

  vex::rotationUnits rotation_deg = vex::rotationUnits::deg;
  vex::rotationUnits rotation_rev = vex::rotationUnits::rev;

  vex::brakeType coast_ = vex::brakeType::coast;
  vex::brakeType brake_ = vex::brakeType::brake;
  vex::brakeType hold_ = vex::brakeType::hold;

  competition Competition;

  int AS_Setting = 1;
  int Auto_Selector = 0;

//-------------------------------------PRE AUTO----------------------------------------------------
  void pre_auton(void) {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();  

    Inertial.startCalibration();
    RightBackMotor.resetRotation();
    LeftBackMotor.resetRotation();

    while(Inertial.isCalibrating()){
      vex::task::sleep(20);
    }
  }
//-------------------------------------FUNCTIONS---------------------------------------------------
  // Draw Functions
    void draw(){
      Brain.Screen.drawRectangle(0, 0, 100, 100, vex::color::red);
      Brain.Screen.printAt(20, 50, "Left");

      Brain.Screen.drawRectangle(0, 125, 100, 100, vex::color::blue);
      Brain.Screen.printAt(20, 175, "Left");

      Brain.Screen.drawRectangle(125, 0, 100, 100, vex::color::red);
      Brain.Screen.printAt(145, 50, "Right");

      Brain.Screen.drawRectangle(125, 125, 100, 100, vex::color::blue);
      Brain.Screen.printAt(145, 175, "Right");

      Brain.Screen.drawRectangle(270, 40, 150, 150, vex::color::yellow);
      Brain.Screen.printAt(315, 120, "Skills");
    }
  // Drive Functions
    void Anti_Push(){
      if(controller1.ButtonUp.pressing()){
        RightBackMotor.stop(hold_);
        LeftBackMotor.stop(hold_); 
        RightFrontMotor.stop(hold_);
        LeftFrontMotor.stop(hold_); 
      }
      else{
        RightBackMotor.setBrake(coast_);
        LeftBackMotor.setBrake(coast_);
        RightFrontMotor.setBrake(coast_);
        LeftFrontMotor.setBrake(coast_);
      }
    }
    void Drive(int direction_, float distance_, float speed){
      RightBackMotor.resetRotation();
      LeftBackMotor.resetRotation();
      RightFrontMotor.resetRotation();
      LeftFrontMotor.resetRotation();
      if(direction_ == 1){
        RightBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.rotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
      }
      if (direction_ == 2){
        RightBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.rotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
      }
    }
    void Start_Drive(int direction_, float distance_, float speed){
      RightBackMotor.resetRotation();
      LeftBackMotor.resetRotation();
      RightFrontMotor.resetRotation();
      LeftFrontMotor.resetRotation();
      if(direction_ == 1){
        RightBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
      }
      if (direction_ == 2){
        RightBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
      }
    }
    //-----------------------------------------------------------------------------------------------

      // 1=Right; 2=Left
    void Turn(int turn_, float distance_, float speed){
      RightBackMotor.resetRotation();
      LeftBackMotor.resetRotation();
      RightFrontMotor.resetRotation();
      LeftFrontMotor.resetRotation();
      if(turn_ == 1){
        RightBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.rotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
      }
      if(turn_ == 2){
        RightBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.rotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
      }
    }
        // 1=Right; 2=Left
    void Start_Turn(int turn_, float distance_, float speed){
      RightBackMotor.resetRotation();
      LeftBackMotor.resetRotation();
      RightFrontMotor.resetRotation();
      LeftFrontMotor.resetRotation();
      if(turn_ == 1){
        RightBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
      }
      if(turn_ == 2){
        RightBackMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        RightFrontMotor.startRotateFor(forward_, distance_, rotation_deg, speed, velocity_dps);
        LeftFrontMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
        LeftBackMotor.startRotateFor(reverse_, distance_, rotation_deg, speed, velocity_dps);
      }
    }
        // 1=Right; 2=Left
    void Inertial_Turn(int turn_, float distance_, float speed){
      RightBackMotor.resetRotation();
      LeftBackMotor.resetRotation();
      Inertial.resetRotation();
      if(turn_ == 1){
        while(Inertial.rotation() <= distance_){
          RightBackMotor.spin(reverse_, speed, velocity_dps);
          LeftBackMotor.spin(forward_, speed, velocity_dps);
        }
      }
      if(turn_ == 2){
        while(Inertial.rotation() <= distance_){
          RightBackMotor.spin(forward_, speed, velocity_dps);
          LeftBackMotor.spin(reverse_, speed, velocity_dps);
        }
      }
    }

//-------------------------------------Auto--------------------------------------------------------
  void autonomous(void) {
    while(Inertial.isCalibrating()){
      vex::task::sleep(20);
    }
    Inertial.resetRotation();

    if(Auto_Selector == 1){
      Drive(1, 500, 1000);
    } 
    if(Auto_Selector == 2){
      Drive(2, 500, 1000);
    } 
    if(Auto_Selector == 3){
      Turn(1, 500, 1000);
    } 
    if(Auto_Selector == 4){
      Turn(2, 500, 1000);
    } 
    if(Auto_Selector == 5){
      Drive(1, 500, 500);
      Turn(1, 500, 500);
      Drive(2, 500, 500);
    }
  }
//-------------------------------------Driver------------------------------------------------------
  void usercontrol(void) {
    controller1.Screen.print("      Select Code");
    draw();
    while (1) {
      //Brain.Screen.printAt(200, 200, "%d", variable;
      //---------------------------------Auto Selector---------------------------------------------
      while(AS_Setting == 1){
        if(controller1.Axis2.value() >= 30){
          Brain.Screen.clearScreen();
          AS_Setting = 0;
        }
        if(Brain.Screen.pressing()){
          int x = Brain.Screen.xPosition();
          int y = Brain.Screen.yPosition();

          if(((x >= 0) && (x <= 100)) && ((y >= 0) && (y <= 100))){  // top left
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            Brain.Screen.printAt(150, 110, "Left Red Code Selected");
            controller1.Screen.print("    Left Red Code");
            Auto_Selector = 1;
            AS_Setting = 0;
          }
          if(((x >= 110) && (x <= 210) && (y >= 0) && (y <= 100))){ // Top Right
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            Brain.Screen.printAt(150, 110, "Right Red Code Selected");
            controller1.Screen.print("   Right Red Code");
            Auto_Selector = 2;
            AS_Setting = 0;
          }
          if(((x >= 0) && (x <= 100) && (y >= 110) && (y <= 210))){ // Bottom Left
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            Brain.Screen.printAt(150, 110, "Left Blue Code Selected");
            controller1.Screen.print("   Left Blue Code");
            Auto_Selector = 3;
            AS_Setting = 0;
          }
          if(((x >= 110) && (x <= 210) && (y >= 110) && (y <= 210))){ // Bottom Right
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            Brain.Screen.printAt(150, 110, "Right Blue Code Selected");
            controller1.Screen.print("  Right Blue Code");
            Auto_Selector = 4;
            AS_Setting = 0;
          }
          if(((x >= 270) && (x <= 410)) && ((y >= 40) && (y <= 190))){
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            Brain.Screen.printAt(140, 110, "Skills code Selected");
            controller1.Screen.print("      Skills Code");
            Auto_Selector = 5;
            AS_Setting = 0;
          }
        }
      }
      while(AS_Setting == 0){
        Brain.Screen.drawRectangle(380, 165, 100, 75);
        Brain.Screen.printAt(410, 210, "Back");

        if(Brain.Screen.pressing()){
          int x = Brain.Screen.xPosition();
          int y = Brain.Screen.yPosition();

          if(((x >= 380) && (x <= 480)) && ((y >= 165) && (y <= 240))){
            Brain.Screen.clearScreen();
            controller1.Screen.clearLine(3);
            draw();
            controller1.Screen.print("      Select Code");
            Auto_Selector = 0;
            AS_Setting = 1;
          }
        }
      //---------------------------------DRIVE-----------------------------------------------------
        if((controller1.Axis4.value() <= 15) && (controller1.Axis4.value() >= -15)){
          LeftBackMotor.spin(forward_, (controller1.Axis2.value() + controller1.Axis1.value()), velocity_pct);
          LeftFrontMotor.spin(forward_, (controller1.Axis2.value() + controller1.Axis1.value()), velocity_pct);
          RightFrontMotor.spin(forward_, (controller1.Axis2.value() - controller1.Axis1.value()), velocity_pct);
          RightBackMotor.spin(forward_, (controller1.Axis2.value() - controller1.Axis1.value()), velocity_pct);

          Anti_Push();
        }
        if(((controller1.Axis1.value() <= 15) && (controller1.Axis2.value() <= 15)) && ((controller1.Axis1.value() >= -15) && (controller1.Axis2.value() >= -15))){
          RightFrontMotor.spin(reverse_, (controller1.Axis4.value()), velocity_pct);
          RightBackMotor.spin(forward_, (controller1.Axis4.value()), velocity_pct);
          LeftFrontMotor.spin(forward_, (controller1.Axis4.value()), velocity_pct);
          LeftBackMotor.spin(reverse_, (controller1.Axis4.value()), velocity_pct);

          Anti_Push();
        }
    vex::task::sleep(20);
      }
    }
  }
//-------------------------------------MAIN--------------------------------------------------------
  int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
      wait(100, msec);
    }
  }
