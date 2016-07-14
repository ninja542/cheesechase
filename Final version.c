#pragma config(Sensor, S1,     rightSonicSensor, sensorSONAR)
#pragma config(Sensor, S2,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S3,     leftLightSensor, sensorLightActive)
#pragma config(Sensor, S4,     frontSonicSensor, sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

int numCorners;
numCorners = 0; //Number of Corners

nVolume = 4; //resets sound volume so woops can play.

while(true)
{
	if(SensorValue(frontSonicSensor) < 13) //if front ultrasonic sensor senses a wall, decide whether to turn left or right
	{
		if(SensorValue(rightSonicSensor) < 11) // if right is less than 10 cm, then turn left
		{
			numCorners = numCorners + 1; //When it senses it needs to turn left, it will add to variable numCorners
			nMotorEncoder[motorC] = 0;
			while(nMotorEncoder[motorC] < 180)
			{
				motor[motorC] = 100;
				motor[motorB] = -100;
			}
		}
		motor[motorC] = 0;
		motor[motorB] = 0;
		wait1Msec(200); //to make sure it doesn't accidentally sense the walls again and get confused
		if(SensorValue(rightSonicSensor) > 11) //if right ultrasonic sensor detects more than 15 cm, turn right
		{
			numCorners = numCorners + 1; //When it senses it needs to turn right, it will add to variable numCorners
			nMotorEncoder[motorB] = 0;
			while(nMotorEncoder[motorB] < 150)
			{
				motor[motorC] = -100;
				motor[motorB] = 100;
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

		if(SensorValue(rightLightSensor) > 60 && SensorValue(leftLightSensor) > 60)
		{
			motor[motorA] = 100;
			PlaySoundFile("Woops.rso"); //make a sound
			MuteSound(); //so it doesn't keep making sounds
		}

		if(SensorValue(frontSonicSensor) > 30) //makes sure it's not at a corner
		{
			if(SensorValue(rightLightSensor) < 41 && SensorValue(leftLightSensor) < 41) //sees if it has crossed the green line yet
			{
				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(100); //this is to make sure robot is relatively straight when stopping in the end zone

				nMotorEncoder[motorC] = 0;
				while(nMotorEncoder[motorC] > -360)
				{
					motor[motorC] = -100;
					motor[motorB] = -100;
				}
			motor[motorC] = 0;
			motor[motorB] = 0;
			nxtDisplayStringAt(0, 31, "Corners = %d", numCorners); //display # of corners
			wait1Msec(10000);
			}
		}
	}
}


}
