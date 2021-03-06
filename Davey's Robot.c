#pragma config(Motor,  port1,           Claw,          tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           Launcher,      tmotorVex393_MC29, 	 openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, 	 openLoop, driveLeft)
#pragma config(Motor,  port4,           Launcher2,     tmotorVex393_MC29, 	 openLoop)
#pragma config(Motor,  port5,           backRightY,    tmotorVex393_MC29, 	 openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           backLeftY,     tmotorVex393_MC29, 	 openLoop, driveLeft)
#pragma config(Motor,  port7,           Launcher3,     tmotorVex393_MC29, 	 openLoop, reversed)
#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, 	 openLoop, driveRight)
#pragma config(Motor,  port9,           Launcher4,     tmotorVex393_MC29, 	 openLoop, reversed)
#pragma config(Motor,  port10,          Claw2,         tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

void move(int speed)
{
	motor[frontLeft] = speed;
	motor[backLeftY] = speed;
	motor[frontRight] = speed;
	motor[backRightY] = speed;
}

void turnL(int speed)
{
	motor[frontLeft] = -speed;
	motor[backLeftY] = -speed;
	motor[frontRight] = speed;
	motor[backRightY] = speed;
}

void turnR(int speed)
{
	motor[frontLeft] = speed;
	motor[backLeftY] = speed;
	motor[frontRight] = -speed;
	motor[backRightY] = -speed;
}

void launch(int speed)
{
	motor[Launcher] = speed;
	motor[Launcher2] = speed;
	motor[Launcher3] = speed;
	motor[Launcher4] = speed;
}

void clawOC(int speed)
{
	motor[Claw] = speed;
	motor[Claw2] = speed;
}

void pre_auton()
{

}

task autonomous()
{
	clawOC(-127);
	wait1Msec(100);
	clawOC(0);
	move(127);
	wait1Msec(750);
	move(0);
	clawOC(127);
	wait1Msec(100);
	clawOC(50);
	wait1Msec(200);
	move(-127);
	wait1Msec(750);
	move(0);
	wait1Msec(200);
	turnL(127);
	wait1Msec(500);//The robot will turn and the claw will hit the back wall.
	move(0);
	wait1Msec(200);
	move(-127);
	wait1Msec(500);
	move(0);
}

task usercontrol()
{
  int drive = 0, turn = 0, threshold = 15;
  while (1)
  {
    if (abs(vexRT[Ch3]) > threshold) drive = vexRT[Ch3];
    else drive = 0;
    if (abs(vexRT[Ch1]) > threshold) turn = vexRT[Ch1];
    else turn = 0;

    motor[frontLeft] = drive + turn;
    motor[backLeftY] = drive + turn;
    motor[frontRight] = drive - turn;
    motor[backRightY] = drive - turn;

    if (abs(vexRT[Ch3Xmtr2]) > threshold) launch(vexRT[Ch3Xmtr2]);
    else launch(0);

    if (abs(vexRT[Ch2Xmtr2]) > threshold) clawOC(vexRT[Ch2Xmtr2]);
    else clawOC(0);
  }
}
