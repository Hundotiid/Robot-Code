task autonomous()
{
	switch(auton_num)
	{
	case 0: break;

	case 1:
		clawOC(-127);
		wait1Msec(200);
		clawOC(0);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(2, 900);

		resetDriveEncoder();
		while (encoder_avg_val < 900)
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

		gyroTurn(2, 900);
		move(0);
		wait1Msec(50);

		resetDriveEncoder();
		while (encoder_avg_val < 900)
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

		gyroTurn(1, 900);

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

		gyroTurn(1, 900);
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



	case 3:
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

		gyroTurn(1, 900);
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
		gyroTurn(2, 900);

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

		gyroTurn(2, 900);
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
		gyroTurn(1, 900);

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

		gyroTurn(1, 900);
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
		launch(127);
		wait1Msec(75);
		launch(0);

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
		gyroTurn(2, 900);
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
		gyroTurn(1, 900);
		move(0);
		launch(0);
		break;

	case 10:
		clawOC(-127);
		wait1Msec(400);
		clawOC(0);
		wait1Msec(250);
		launch(127);
		wait1Msec(75);
		launch(0);

		gyroTurn(1, 900);

		resetDriveEncoder();
		while (encoder_avg_val < 1200)//changed value from 1000 so it moves farther,
		{//still needs to be tested if it is correct for the back stars
			move(127);
			getDriveEncoders();
		}
		move(0);

		clawOC(127);
		wait1Msec(950);
		clawOC(40);

		resetDriveEncoder();
		while (encoder_avg_val < 1200)//same as the previous comment
		{
			move(-127);
			getDriveEncoders();
		}
		move(0);
		wait1Msec(250);

		resetArmEncoder();
		while (pot_val < 45)
		{
			launch(-127);
			pot_val = SensorValue[Armangle];
		}
		launch(-30);
		wait1Msec(250);

		gyroTurn(1, 900);
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
		while(pot_val > 15)
		{
			launch(127);
			pot_val = SensorValue[Armangle];
		}
		move(0);
		launch(0);
		break;

	case 11:
		gyroTurn(2, 900);
		move(0);
		break;
	}
}
