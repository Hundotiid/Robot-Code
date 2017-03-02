void pre_auton()
{
	clearLCDLine(0);
	clearLCDLine(1);
	auton_num = 0;
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
			displayLCDCenteredString(0, "Left Side Cube");//Doesn't exist yet
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
