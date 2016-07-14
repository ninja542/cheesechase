
task main()
{
	nMotorEncoder[motorC] = 0;
		while(nMotorEncoder[motorC] < 180)
			{
				motor[motorC] = 50;
				motor[motorB] = -50;
			}

	nMotorEncoder[motorC] = 0;
			while(nMotorEncoder[motorC] > -150)
			{
				motor[motorC] = -50;
				motor[motorB] = 50;
			}
}
