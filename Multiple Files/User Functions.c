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

void turnL(int speed)
{
	motor[backLeft] = -speed;
	motor[frontLeft] = -speed;
	motor[backRight] = speed;
	motor[frontRight] = speed;
}

void turnR(int speed)
{
	motor[backLeft] = speed;
	motor[frontLeft] = speed;
	motor[backRight] = -speed;
	motor[frontRight] = -speed;
}

void gyroTurn(int direction, int turnval)//degrees of turn * 10 for turn
{
	if (direction == 1) newGyroVal -= turnval;
	else if (direction == 2) newGyroVal += turnval;

	if (direction == 1)
	{
		while (SensorValue[Gyro] > (newGyroVal + 250)) turnL(127);
		move(0);
		wait1Msec(100);
		while (SensorValue[Gyro] != newGyroVal)
		{
			if (SensorValue[Gyro] > newGyroVal) turnL(50);
			else if (SensorValue[Gyro] < newGyroVal) turnR(50);
		}
	}
	else if (direction == 2)
	{
		while (SensorValue[Gyro] < (newGyroVal - 250)) turnR(127);
		move(0);
		wait1Msec(100);
		while (SensorValue[Gyro] != newGyroVal)
		{
			if (SensorValue[Gyro] > newGyroVal) turnL(50);
			else if (SensorValue[Gyro] < newGyroVal) turnR(50);
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
