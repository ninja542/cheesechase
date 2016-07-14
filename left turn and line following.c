#pragma config(Sensor, S1,     rightSonicSensor, sensorSONAR)
#pragma config(Sensor, S2,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S3,     leftLightSensor, sensorLightActive)
#pragma config(Sensor, S4,     frontSonicSensor, sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
while(true)
{
	if(SensorValue(frontSonicSensor) < 15) //if both ultrasonic sensors detect walls, turn left
	{
		if(SensorValue(rightSonicSensor) < 10)
		{
			nMotorEncoder[motorC] = 0;
			while(nMotorEncoder[motorC] < 170)
			{
				motor[motorC] = 50;
				motor[motorB] = -50;
			}
		}
		if(SensorValue(rightSonicSensor) > 10) //if right ultrasonic sensor detects nothing, turn right
		{
			nMotorEncoder[motorB] = 0;
			while(nMotorEncoder[motorB] < 170)
			{
				motor[motorC] = -50;
				motor[motorB] = 50;
			}
		}
	}
	else //continue line following
	{
		if(SensorValue(rightLightSensor) < 41) // controls right light sensor for line following
		{
			motor[motorC] = -100;
			motor[motorB] = 0;
		}

		if(SensorValue(rightLightSensor) > 41)
		{
			motor[motorC] = 0;
			motor[motorB] = -100;
		}

		if(SensorValue(leftLightSensor) < 41) // controls left light sensor for line following like above, but in the opposite direction
		{
			motor[motorC] = 0;
			motor[motorB] = -100;
		}

		if(SensorValue(leftLightSensor) > 41)
		{
			motor[motorC] = -100;
			motor[motorB] = 0;
		}
	}
}


}
