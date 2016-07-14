#pragma config(Sensor, S1,     rightSonicSensor, sensorSONAR)
#pragma config(Sensor, S2,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S3,     leftLightSensor, sensorLightActive)
#pragma config(Sensor, S4,     frontSonicSensor, sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

int numCorners;
numCorners = 0;

nVolume = 4; //resets sound volume so woops can play.

while(true)
{
	if(SensorValue(frontSonicSensor) < 14) //if front ultrasonic sensor senses a wall, decide whether to turn left or right
	{
		if(SensorValue(rightSonicSensor) < 11) // if right is less than 10 cm, then turn left
		{
			motor[motorC] = 0;
			motor[motorB] = 0;
			wait1Msec(100); //make sure it's at full stop so it can turn accurately
			numCorners = numCorners + 1; //add 1 to numCorners variable for counting corners
			nMotorEncoder[motorC] = 0;
			while(nMotorEncoder[motorC] < 170)
			{
				motor[motorC] = 50;
				motor[motorB] = -50;
			}
		}
		motor[motorC] = 0;
		motor[motorB] = 0;
		wait1Msec(100); //to make sure it doesn't accidentally sense the walls again and get confused
		if(SensorValue(rightSonicSensor) > 11) //if right ultrasonic sensor detects more than 15 cm, turn right
		{
			numCorners = numCorners + 1; //ad 1 to numCorners variable for counting corners
			nMotorEncoder[motorB] = 0;
			while(nMotorEncoder[motorB] < 150)
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

		if(SensorValue(rightLightSensor) > 60 && SensorValue(leftLightSensor) > 60) //detects the aluminum foil
		{
			motor[motorA] = 100;
			PlaySoundFile("Woops.rso"); //make a sound
			MuteSound(); //so it doesn't keep making sounds
		}

		if(SensorValue(frontSonicSensor) > 30) //makes sure it's not at a corner
		{
			if(SensorValue(rightLightSensor) < 41 && SensorValue(leftLightSensor) < 41) //sees if it has crossed the green line yet
			{
				nMotorEncoder[motorC] = 0;
					while(nMotorEncoder[motorC] > -360) //moves forward one rotation
					{
						motor[motorC] = -100;
						motor[motorB] = -100;
					}
				motor[motorC] = 0;
				motor[motorB] = 0;
				nxtDisplayStringAt(0, 31, "Corners = %d", numCorners); //displays # of corners
				wait1Msec(10000);
			}
		}
	}
}


}
