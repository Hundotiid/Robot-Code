#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  UltronFront,    sensorSONAR_inch)
#pragma config(Sensor, dgtl7,  EncoderFront,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  EncoderBack,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, Armangle,       sensorQuadEncoder)
#pragma config(Motor,  port1,           Claw,          tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port2,           backLeft,      tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           Launcher4,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           frontLeft,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           Launcher2,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           Launcher,      tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           Launcher3,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port9,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          Claw2,         tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

int clawval;
float launchval;
int pot_val;
float ultron_front_val;
int auto_throw = 0;
const int cube = 1;
int encoder_front_val, encoder_back_val, encoder_avg_val;
int encoder_distance;
int auton_num;
const int BtnLeft = 1;
const int BtnCenter = 2;
const int BtnRight = 4;

void resetDriveEncoder()
{
	SensorValue[EncoderBack] = 0;
	SensorValue[EncoderFront] = 0;
	encoder_back_val = 0;
	encoder_front_val = 0;
	encoder_avg_val = 0;
}

void resetArmEncoder()
{
	SensorValue[Armangle] = 0;
	pot_val = SensorValue[Armangle];
}

void move(float speed)
{
	motor[backLeft] = speed;
	motor[backRight] = speed;
	motor[frontLeft] = speed;
	motor[frontRight] = speed;
}

void launch(float speed)
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

void getDriveEncoders()
{
	encoder_front_val = abs(SensorValue[EncoderFront]);
	encoder_back_val = abs(SensorValue[EncoderBack]);
	encoder_avg_val = (encoder_front_val + encoder_back_val) / 2;
}

void gyroTurn(int direction, int turnval)//750 for 90 degree turn
{
	int newGyroVal;
	if (direction == 1) newGyroVal = SensorValue[Gyro] - turnval;
	else if (direction == 2) newGyroVal = SensorValue[Gyro] + turnval;
	if (direction == 1)
	{
		while (SensorValue[Gyro] > newGyroVal)
		{
			motor[backLeft] = -127;
			motor[frontLeft] = -127;
			motor[backRight] = 127;
			motor[frontRight] = 127;
		}
	}
	else if (direction == 2)
	{
		while (SensorValue[Gyro] < newGyroVal)
		{
			motor[backLeft] = 127;
			motor[frontLeft] = 127;
			motor[backRight] = -127;
			motor[frontRight] = -127;
		}
	}
}

void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

void pre_auton()
{
	clearLCDLine(0);
	clearLCDLine(1);
	auton_num = 0;
	SensorValue[Gyro] = 0;
	bLCDBacklight = true;
	displayLCDCenteredString(0, "Stop");
	while (nLCDButtons != BtnCenter)
	{
		waitForPress();
		if (nLCDButtons == BtnLeft)
		{
			waitForRelease();
			auton_num--;
		}
		else if (nLCDButtons == BtnRight)
		{
			waitForRelease();
			auton_num++;
		}

		if (auton_num == -1) auton_num = 11;
		else if (auton_num == 12) auton_num = 0;

		clearLCDLine(0);
		clearLCDLine(1);
		switch(auton_num)
		{
		case 0:
			displayLCDCenteredString(0, "Stop");
			break;

		case 1:
			displayLCDCenteredString(0, "Left Side Stars");
			break;

		case 2:
			displayLCDCenteredString(0, "Right Side Stars");
			break;

		case 3:
			displayLCDCenteredString(0, "Left Side Cube");
			break;

		case 4:
			displayLCDCenteredString(0, "Left Side Cube");
			displayLCDCenteredString(1, "High Fence");
			break;

		case 5:
			displayLCDCenteredString(0, "Right Side Cube");
			break;

		case 6:
			displayLCDCenteredString(0, "Right Side Cube");
			displayLCDCenteredString(1, "High Fence");
			break;

		case 7:
			displayLCDCenteredString(0, "Move Forward");
			break;

		case 8:
			displayLCDCenteredString(0, "Move Forward");
			displayLCDCenteredString(1, "Cube");
			break;

		case 9:
			displayLCDCenteredString(0, "Skills 1");
			break;

		case 10:
			displayLCDCenteredString(0, "Skills 2");
			break;
		case 11:
			displayLCDCenteredString(0, "Gyro Turn Test");
			break;
		}
	}

	clearLCDLine(0);
	clearLCDLine(1);
	wait1Msec(5);
}

task autonomous()
{
	switch(auton_num)
	{
	case 0: break;

	case 1:
		clawOC(-127);
		wait1Msec(100);
		clawOC(0);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(2, 750);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(127);
			getDriveEncoders();
		}
		move(0);

		clawOC(127);
		wait1Msec(950);
		clawOC(40);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);

		resetArmEncoder();
		while (pot_val < 45)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		wait1Msec(250);

		gyroTurn(2, 750);
		move(0);
		wait1Msec(50);

		resetDriveEncoder();
		while (encoder_avg_val < 1250)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(50);

		while (pot_val < 90)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;

	case 2:
		clawOC(-127);
		wait1Msec(100);
		clawOC(0);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(1, 750);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(127);
			getDriveEncoders();
		}
		move(0);

		clawOC(127);
		wait1Msec(950);
		clawOC(40);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);

		resetArmEncoder();
		while (pot_val < 45)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		wait1Msec(250);

		gyroTurn(1, 750);
		move(0);
		wait1Msec(50);

		resetDriveEncoder();
		while (encoder_avg_val < 1250)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(50);

		while (pot_val < 90)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;



	case 4:
		ultron_front_val = SensorValue[UltronFront];
		while (ultron_front_val < 20)
		{
			move(-127);
			ultron_front_val = SensorValue[UltronFront];
		}
		move(0);

		wait1Msec(50);
		clawOC(-127);
		wait1Msec(250);
		clawOC(-30);
		wait1Msec(250);

		gyroTurn(1, 750);
		move(0);
		wait1Msec(50);
		resetDriveEncoder();

		while (encoder_avg_val < 450)
		{
			move(127);
			encoder_front_val = abs(SensorValue[EncoderFront]);
			encoder_back_val = abs(SensorValue[EncoderBack]);
			encoder_avg_val = (encoder_front_val + encoder_back_val) / 2;
		}
		encoder_distance = encoder_avg_val;
		move(0);
		clawOC(127);
		wait1Msec(950);
		clawOC(40);
		if (auton_num == 6) goto cas6;
		resetArmEncoder();
		while (pot_val < 30)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		gyroTurn(2, 750);

		move(-127);
		wait1Msec(1000);
		move(0);
		while (pot_val < 90)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;

	case 5:
	cas5:
		ultron_front_val = SensorValue[UltronFront];
		while (ultron_front_val < 20)
		{
			move(-127);
			ultron_front_val = SensorValue[UltronFront];
		}
		move(0);

		wait1Msec(50);
		clawOC(-127);
		wait1Msec(250);
		clawOC(-30);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(2, 750);
		move(0);
		wait1Msec(50);
		resetDriveEncoder();

		while (encoder_avg_val < 450)
		{
			move(127);
			getDriveEncoders();
		}
		encoder_distance = encoder_avg_val;
		move(0);
		clawOC(127);
		wait1Msec(950);
		clawOC(40);
		if (auton_num == 6) goto cas6;
		resetArmEncoder();
		while (pot_val < 30)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		gyroTurn(1, 750);

		move(-127);
		wait1Msec(1250);
		move(0);
		while (pot_val < 92)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		if (auton_num == 8) goto cas8;
		break;

	case 6:
		goto cas5;
	cas6:

		resetDriveEncoder();

		while (encoder_avg_val < 650)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(50);

		resetArmEncoder();
		while (pot_val < 30)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		wait1Msec(50);

		gyroTurn(1, 750);
		move(-127);
		wait1Msec(950);
		move(0);
		while (pot_val < 90)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;

	case 7:
		move(127);
		wait1Msec(1500);
		move(0);
		break;

	case 8:
		wait1Msec(5000);
		move(127);
		wait1Msec(2500);
		move(0);
		break;

	case 9:
	resetDriveEncoder();
		while (encoder_avg_val < 550)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);

		clawOC(-127);
		wait1Msec(250);
		clawOC(0);

		for (int x = 1; x <= 2; x++)
		{
			resetDriveEncoder();
			getDriveEncoders();
			if (x == 1)
			{
				while (encoder_avg_val < 300)
				{
					move(127/2);
					getDriveEncoders();
				}
			}
			else if (x == 2)
			{
				while (encoder_avg_val < 800)
				{
					move(127/2);
					getDriveEncoders();
				}
			}
			move(0);
			wait1Msec(750);
			clawOC(127);
			wait1Msec(1250);
			clawOC(40);
			move(-127);
			wait1Msec(1500);
			move(0);
			resetArmEncoder();
			while (pot_val < 95)
			{
				launch(-127);
				pot_val = SensorValue[Armangle];
			}
			clawOC(-127);
			wait1Msec(100);
			clawOC(0);
			launch(0);
			wait1Msec(50);
			if (x == 2)
			{
				move(127/2);
				wait1Msec(50);
				move(0);
			}
			while (pot_val > 15)
			{
				launch(127);
				pot_val = SensorValue[Armangle];
			}
			launch(0);
			wait1Msec(200);
		}

		while (encoder_avg_val < 850)
		{
			move(127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(50);
		while (pot_val < 20)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(0);

		goto cas5;
	cas8:
		move(127);
		wait1Msec(750);
		move(0);
		gyroTurn(2, 750);
		move(0);
		wait1Msec(250);
		resetDriveEncoder();
		encoder_avg_val = 0;
		while (encoder_avg_val < encoder_distance)
		{
			getDriveEncoders();
			move(-127);
		}
		move(0);
		clawOC(-127);
		wait1Msec(300);
		clawOC(0);
		gyroTurn(1, 750);
		move(0);
		launch(0);
		break;

	case 10:
		clawOC(-127);
		wait1Msec(100);
		clawOC(0);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(1, 750);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(127);
			getDriveEncoders();
		}
		move(0);

		clawOC(127);
		wait1Msec(950);
		clawOC(40);

		resetDriveEncoder();
		while (encoder_avg_val < 1000)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);

		resetArmEncoder();
		while (pot_val < 45)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		wait1Msec(250);

		gyroTurn(1, 750);
		move(0);
		wait1Msec(50);

		resetDriveEncoder();
		while (encoder_avg_val < 1250)
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(50);

		while (pot_val < 90)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		clawOC(-127);
		wait1Msec(250);
		clawOC(0);
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;

	case 11:
		while(abs(SensorValue[Gyro]) < 750)
		{
			motor[backLeft] = 127;
			motor[frontLeft] = 127;
			motor[backRight] = -127;
			motor[frontRight] = -127;
		}
		move(0);
		break;
	}
}

task usercontrol()
{
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15; //Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	while(1)
	{
		if(abs(vexRT[Ch3]) > threshold) Y1 = vexRT[Ch3]; //Create "deadzone" for Y1/Ch3
		else Y1 = 0;
		if(abs(vexRT[Ch4]) > threshold) X1 = vexRT[Ch4]; //Create "deadzone" for X1/Ch4
		else X1 = 0;
		if(abs(vexRT[Ch1]) > threshold) X2 = vexRT[Ch1]; //Create "deadzone" for X2/Ch1
		else X2 = 0;
		motor[frontRight] = Y1 - X2 - X1; //Remote Control/Driving Commands
		motor[backRight] =  Y1 - X2 + X1;
		motor[frontLeft] = Y1 + X2 + X1;
		motor[backLeft] =  Y1 + X2 - X1;

		pot_val = SensorValue[Armangle];
		ultron_front_val = SensorValue[UltronFront];//sets the values of the ultrasonic sensors to their own variables
		getDriveEncoders();

		if (vexRT[Btn7UXmtr2] == 1)pre_auton();

		if (vexRT[Btn6DXmtr2] == 1) resetArmEncoder();
		if (vexRT[Btn8D] == 1) resetDriveEncoder();
		if (vexRT[Btn8DXmtr2] == 1) auto_throw = 0;
		if (vexRT[Btn8LXmtr2] == 1) SensorValue[Gyro] = 0;

		if (vexRT[Btn8RXmtr2] == 1)
		{
			resetArmEncoder();
			auto_throw = cube;
			clawOC(50);
			wait1Msec(5);
		}
		else if (vexRT[Btn8DXmtr2] == 1)
		{
			auto_throw = 0;
			wait1Msec(5);
		}

		if (auto_throw != 0 && pot_val > 83)
		{
			clawOC(-127);
			pot_val = SensorValue[Armangle];
		}

		if (auto_throw != 0 && pot_val < 95)
		{
			launchval = -127;
			pot_val = SensorValue[Armangle];
		}
		else if (auto_throw != 0 && pot_val >= 95)
		{
			launchval = 0;
			clawval = 0;
			auto_throw = 0;
			pot_val = SensorValue[Armangle];
		}
		else if (auto_throw == 0)
		{
			if (abs(vexRT[Ch3Xmtr2]) > threshold)
			{
				launchval = -(vexRT[Ch3Xmtr2]);//sets the speed of the arm from the left joystick on the 2nd controller
			}
			else launchval = 0;
			if (abs(vexRT[Ch2Xmtr2]) > threshold) clawval = vexRT[Ch2Xmtr2];
			else clawval = 0;
			clawOC(clawval);
		}
		launch(launchval);//actually moves the launcher motors to the set speed

		if ((nSysTime % 100) == 0)
		{
			clearLCDLine(0);
			clearLCDLine(1);

			displayLCDNumber(1, 0, ultron_front_val);//prints the value of the front ultrasonic sensor to the LCD Screen
			displayNextLCDString(" inches");
			displayLCDNumber(0, 0, SensorValue[Gyro]);
			displayNextLCDString(" ");
			displayNextLCDNumber(encoder_avg_val);
			displayNextLCDString(" ");
			displayNextLCDNumber(pot_val);//displays the value of the potentiometer/angle of the arm to the LCD Screen
		}
	}
}
