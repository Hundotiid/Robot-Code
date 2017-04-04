#pragma config(Motor,  port3,           UpperGearBoxTL, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           UpperGearBoxBL, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LowerGearBox,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           UpperGearBoxTR, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           UpperGearBoxBR, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

void launchU(int speed)//launch at 40% speed of lower gear box
{
	motor[UpperGearBoxBL] = speed;
	motor[UpperGearBoxBR] = speed;
	motor[UpperGearBoxTL] = speed;
	motor[UpperGearBoxTR] = speed;
}

void pre_auton()
{

}

task autonomous()
{

}

task usercontrol()
{
	int threshold = 15;
	int driveval = 0;
	while (1)
	{
		if (abs(vexRT[Ch3]) > threshold) launchU((vexRT[Ch3] * 0.4));
		else launchU(0);

		if (abs(vexRT[Ch3]) > threshold) motor[LowerGearBox] = vexRT[Ch3];
		else motor[LowerGearBox] = 0;
	}
}
