#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in8,    gyro1,          sensorGyro)
#pragma config(Sensor, dgtl1,  limit1,         sensorTouch)
#pragma config(Sensor, dgtl2,  limit2,         sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           DFR,           tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           DBR,           tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port4,           DFL,           tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port5,           DBL,           tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_4, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int error = 30;	//define the error

void driveLeft(int a)
{
	motor[DBL] = a;
	motor[DFL] = a;
}

void driveRight(int a)
{
	motor[DBR] = a;
	motor[DFR] = a;
}


void drive_straight(float dist, int speed)
{
	while((nMotorEncoder[DBR] < 360 * dist / (4 * PI) + error) || (nMotorEncoder[DBR] < 360 * dist / (4 * PI) - error))
	{
		driveRight(speed);
		driveLeft(speed);
	}
}


void gyroTurn(int degrees10)  //specify the amount of degrees to turn
{
	while((abs(SensorValue[in8]) < degrees10))
	{
		motor[port1] = 63;
		motor[port2] = -63;
	}
}

//task autonomous()
//{

//	wait1Msec(2000);

//	if(SensorValue(limit1) == 0) //hang a cube from the back, move backwards until the limit switch is pressed
//	{
//		motor[port1] = -100;
//		motor[port2] = -100;
//	}
//	else if(SensorValue(limit1) == 1)
//	{
//		wait1Msec(1000); //wait for the cube to release from the robot
//		motor[port1] = 100;
//		motor[port2] = 100;
//	}

//	gyroTurn(45);// turns 45 degrees

//	drive_straight(sqrt(2), 50);//returns to starting position
//	drive_straight(1.5, 50);
//	//do something with intake
//	if(SensorValue(limit1) == 0)
//	{
//		motor[port1] = -100;
//		motor[port2] = -100;

//	}
//}

task main()
{
	SensorType[in8] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in8] = sensorGyro;
	wait1Msec(2000);
	//int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

	gyroTurn(900);
}


//	//Create "deadzone" for Y1/Ch3
//	if(abs(vexRT[Ch3]) > threshold)
//		Y1 = vexRT[Ch3];
//	else
//		Y1 = 0;
//	//Create "deadzone" for X1/Ch4
//	if(abs(vexRT[Ch4]) > threshold)
//		X1 = vexRT[Ch4];
//	else
//		X1 = 0;
//	//Create "deadzone" for X2/Ch1
//	if(abs(vexRT[Ch1]) > threshold)
//		X2 = vexRT[Ch1];
//	else
//		X2 = 0;

//	//Remote Control Commands
//	motor[DFR] = Y1 - X2 - X1;
//	motor[DBR] =  Y1 - X2 + X1;
//	motor[DFL] = Y1 + X2 + X1;
//	motor[DBL] =  Y1 + X2 - X1;
//}


//touch2 refers to a lift limit
//t ouch1 refers to the back of the robot's touch sensor
