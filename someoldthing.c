#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, I2C_1,  DFR,            sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightbackIEM,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  rightliftIEM,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  leftliftIEM,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  leftbackIEM,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_6,  DFL,            sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftIntake,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_6)
#pragma config(Motor,  port2,           DFL,           tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port3,           DBL,           tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port4,           liftLT,        tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           liftLB,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port6,           liftRB,        tmotorVex393_MC29, PIDControl, encoderPort, I2C_4)
#pragma config(Motor,  port7,           liftRT,        tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_5)
#pragma config(Motor,  port8,           DBR,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           DFR,           tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port10,          rightIntake,   tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//constants
const int MIN_JOYSTICK_ACTIVATION_THRESHOLD = 10;
const int LOWEST_VALUE = 0;
const int STASH_VALUE = 600;
const int RAIL_VALUE = 400;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
const int threshold = 500; //relatively high number for calibration
const int LIFT_SPEED = 100;
const int DESCEND_SPEED = -100;

//drive functions/////////////////////////////////////////////////////

//left drive motors, correction added
void leftSideD(int power, int constant, int diff)
{
	//change sign of constant depending on which side
	motor[DFL] = power - constant * diff;
	motor[DBL] = power - constant * diff;
	diff = abs(nMotorEncoder[DFL] - nMotorEncoder[DFR]);
}

//right drive motors, correction added
void rightSideD(int power, int constant, int diff)
{
	//change sign of constant depending on which side
	motor[DFR] = power - constant * diff;
	motor[DBR] = power - constant * diff;
	diff = abs(nMotorEncoder[DFL] - nMotorEncoder[DFR]);
}

//function for distance
//assume that robot is equal mass on either side
void drive_straight_with_sensor_on_line(float dist, int speed)
{
	//setMotorTarget(DFR, 360 * dist / (4 * PI), speed, 0);
	//setMotorTarget(DBR, 360 * dist / (4 * PI), speed, 0);
	//setMotorTarget(DFL, 360 * dist / (4 * PI), speed, 0);
	//setMotorTarget(DBL, 360 * dist / (4 * PI), speed, 0);

	while(nMotorEncoder[DFR] && nMotorEncoder[DFL] <= 360 * dist / (4 * PI))
	{
		if(SensorValue(lineFollowerRIGHT) > threshold)
		{
			// counter-steer right:
			leftSideD(100, 0, 0);
			rightSideD(0, 0, 0);
		}
		// CENTER sensor sees dark:
		if(SensorValue(lineFollowerCENTER) > threshold)
		{
			// go straight
			leftSideD(100, 0, 0);
			rightSideD(100, 0, 0);
		}
		// LEFT sensor sees dark:
		if(SensorValue(lineFollowerLEFT) > threshold)
		{
			// counter-steer left:
			leftSideD(0, 0, 0);
			rightSideD(100, 0, 0);
		}

	}

}

void resetDriveEncoder()
{
	resetMotorEncoder(DFR);
	resetMotorEncoder(DBR);
	resetMotorEncoder(DFL);
	resetMotorEncoder(DBL);
}


void drive_straight_with_sensor_no_line(float dist, int speed)
{
	resetDriveEncoder();
	setMotorTarget(DFR, 360 * dist / (4 * PI), speed, 0);
	setMotorTarget(DBR, 360 * dist / (4 * PI), speed, 0);
	setMotorTarget(DFL, 360 * dist / (4 * PI), speed, 0);
	setMotorTarget(DBL, 360 * dist / (4 * PI), speed, 0);
}

//////////////////////////////////////////////////////////////////////




//lift functions//////////////////////////////////////////////////////

//function to have power for all lifts, correction added
void moveLift(int power, int constant, int diff)
{
	motor[liftLB] = power - constant * diff;
	motor[liftRB] = power - constant * diff;
	motor[liftLT] = power - constant * diff;
	motor[liftRT] = power - constant * diff;
	diff = abs(nMotorEncoder[DFL] - nMotorEncoder[DFR]);
}

//function for the target values of the preset lift
void targetLiftValueAndHold(int sensorTarget)
{
	setMotorTarget(liftLB, sensorTarget, LIFT_SPEED, 1);
	setMotorTarget(liftRB, sensorTarget, LIFT_SPEED, 1);
}

void targetLiftValueAndCutPower(int sensorTarget)
{
	setMotorTarget(liftLB, sensorTarget, DESCEND_SPEED, 0);
	setMotorTarget(liftRB, sensorTarget, DESCEND_SPEED, 0);
}

//reset the lift encoders
void liftReset()
{
	resetMotorEncoder(liftRB);
	resetMotorEncoder(liftLB);
}
//////////////////////////////////////////////////////////////////////////////


//LCD Screen Functions////////////////////////////////////////////////////////

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(10);
}


//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(10);
}
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//control functions
////////////////////////////////////////////////////////////////////
bool is_lift_complete()
{
	return((getMotorTargetCompleted(leftIntake) == 1) && (getMotorTargetCompleted(rightIntake) == 1));
}

void wait_for_lift_complete()
{
	while(!is_lift_complete())
	{
		//display_lift_encoder();
	}
}

bool is_drive_complete()
{
	return ((getMotorTargetCompleted(DFR) == 1) && (getMotorTargetCompleted(DBR) == 1) && (getMotorTargetCompleted(DFL) == 1) && (getMotorTargetCompleted(DBL) == 1));
}

void wait_for_drive_complete()
{
	while(!is_drive_complete())
	{
		//display_drive_encoder();
	}
}

void display_drive_encoder()
{
	displayLCDNumber(0, 3, nMotorEncoder[DFR], 6);
	displayLCDNumber(1, 3, nMotorEncoder[DFL], 6);
}

void display_lift_encoder()
{
	displayLCDNumber(0, 3, nMotorEncoder[liftLB], 6);
	displayLCDNumber(1, 3, nMotorEncoder[liftRB], 6);
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	liftReset();
	slaveMotor(liftLT, liftLB);
	slaveMotor(liftRT, liftRB);

	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDString(0, 0, "R: ");
	displayLCDString(1, 0, "L: ");
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is u=sed to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task ProgramChallenge()
{
	//write 60 sec auton here
}

task autonomous()
{
	//initial statement displayed on the LCD
	int count = 0;

	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Left Blue");
			displayLCDCenteredString(1, "<	 Enter	 >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 4;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Right Blue");
			displayLCDCenteredString(1, "<	 Enter	 >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Left Red");
			displayLCDCenteredString(1, "<	 Enter	 >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Right Red");
			displayLCDCenteredString(1, "<	 Enter	 >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;

		case 4:
			//display 60 sec auton
			displayLCDCenteredString(0, "60 Sec");
			displayLCDCenteredString(1, "<	 Enter	 >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			break;

		default:
			count = 0;
			break;
		}
	}

	//------------- Beginning of Robot Movement Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	switch(count){
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "Left Blue");
		displayLCDCenteredString(1, "is running!");

		//blue side left
		drive_straight_with_sensor_on_line(6.5, 100);
		drive_straight_with_sensor_on_line(4.5, 100);
		drive_straight_with_sensor_on_line(8, 100);
		//gyroTurn(716);
		drive_straight_with_sensor_on_line(37.9, 100);
		//gyroTurn(184);
		targetLiftValueAndHold(STASH_VALUE);
		drive_straight_with_sensor_on_line(22.0, 100);
		drive_straight_with_sensor_on_line(-10, 100);

		break;

	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "Right Blue");
		displayLCDCenteredString(1, "is running!");
		//right blue
		drive_straight_with_sensor_on_line(20, 100);
		targetLiftValueAndHold(STASH_VALUE);
		drive_straight_with_sensor_on_line(4, 100);
		drive_straight_with_sensor_on_line(-7, 100);
		//	gyroTurn(-500);
		drive_straight_with_sensor_on_line(27.25, 100);
		//gyroTurn(900);
		drive_straight_with_sensor_on_line(12.5, 100);

		break;

	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "Left Red");
		displayLCDCenteredString(1, "is running!");

		//left red
		drive_straight_with_sensor_on_line(6.5, 100);
		drive_straight_with_sensor_on_line(4.5, 100);
		drive_straight_with_sensor_on_line(8, 100);
		//	gyroTurn(-716);
		drive_straight_with_sensor_on_line(37.9, 100);
		//	gyroTurn(-184);
		targetLiftValueAndHold(STASH_VALUE);
		drive_straight_with_sensor_on_line(22.0, 100);
		drive_straight_with_sensor_on_line(-10, 100);

		break;

	case 3:
		//If count = 3, run the code correspoinding with choice 4
		displayLCDCenteredString(0, "Right Red");
		displayLCDCenteredString(1, "is running!");
		//right red
		drive_straight_with_sensor_on_line(20, 100);
		targetLiftValueAndHold(STASH_VALUE);
		drive_straight_with_sensor_on_line(4, 100);
		drive_straight_with_sensor_on_line(-7, 100);
		//	gyroTurn(500);
		drive_straight_with_sensor_on_line(27.25, 100);
		//	gyroTurn(-900);
		drive_straight_with_sensor_on_line(12.5, 100);

		break;

	case 4:
		//If count = 4, run the code corresponding with choice 4
		displayLCDCenteredString(0, "60 Sec Code");
		displayLCDCenteredString(1, "is running!");

		//write code for the 60 sec challenge here:
		startTask(ProgramChallenge);

		break;

	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


task presets()
{
	nMotorEncoder[liftRB] = 0;
	//reset encoder
	nMotorEncoder[liftLB] = 0;
	//int killDiff = abs((nMotorEncoder(liftLB)) - (nMotorEncoder(liftRB)));

	//initially preset is false to allow for manual control
	bool preset = false;

	if((vexRT[Btn8UXmtr2] == 1) || (vexRT[Btn8DXmtr2] == 1) && (vexRT[Btn6DXmtr2] == 0) && (vexRT[Btn6UXmtr2] == 0) && (vexRT[Btn8RXmtr2] == 0) && (vexRT[Btn8L] == 0))
	{
		preset = true; //enabling the auto control

	}
	else if((vexRT[Btn6DXmtr2] == 1) || (vexRT[Btn8RXmtr2] == 1) || (vexRT[Btn8L] == 1) || (vexRT[Btn6UXmtr2] == 1) && (vexRT[Btn8DXmtr2] == 0) && (vexRT[Btn8UXmtr2] == 0))
	{
		preset = false;	//enabling manual control
	}



	//the actual sensor values and lift locations if driver uses preset
	if(preset == true)
	{
		if((vexRT[Btn8UXmtr2] == 1) && (vexRT[Btn8DXmtr2] == 0) && (vexRT[Btn8RXmtr2] == 0) && (vexRT[Btn8L] == 0))
		{
			targetLiftValueAndHold(STASH_VALUE);
		}
		else if((vexRT[Btn8DXmtr2] == 1) && (vexRT[Btn8UXmtr2] == 0) && (vexRT[Btn8RXmtr2] == 0) && (vexRT[Btn8L] == 0))
		{
			targetLiftValueAndCutPower(LOWEST_VALUE);
		}
		else if((vexRT[Btn8RXmtr2] == 1) || (vexRT[Btn8L] == 1) && (vexRT[Btn8UXmtr2] == 0) && (vexRT[Btn8DXmtr2] == 0))
		{
			targetLiftValueAndHold(RAIL_VALUE);
		}
	}

	//manual control for lift
	else if(preset == false)
	{
		if((vexRT[Btn6UXmtr2] == 1) && (vexRT[Btn6DXmtr2] == 0))
		{
			moveLift(100, 0, 0);
		}
		else if((vexRT[Btn6DXmtr2] == 1) && (vexRT[Btn6UXmtr2] == 0))
		{
			moveLift(-100, 0, 0);
		}
		else
		{
			moveLift(0, 0, 0);
		}
	}


	//intake control
	if((vexRT[Btn5UXmtr2] == 1) && (vexRT[Btn5DXmtr2] == 0))
	{
		motor[rightIntake] = 100;
		motor[leftIntake] = 100;
	}
	else if((vexRT[Btn5DXmtr2] == 1) && (vexRT[Btn5UXmtr2] == 0))
	{
		motor[rightIntake] = -100;
		motor[leftIntake] = -100;
	}
	else
	{
		motor[rightIntake] = 0;
		motor[leftIntake] = 0;
	}
}


//drive
task drive()
{

	//tank drive
	if(abs(vexRT[Ch3]) > MIN_JOYSTICK_ACTIVATION_THRESHOLD)
	{
		motor[DFL] = vexRT[Ch3];
		motor[DBL] = vexRT[Ch3];
	}
	else
	{
		motor[DFL] = 0;
		motor[DBL] = 0;
	}

	if(abs(vexRT[Ch2]) > MIN_JOYSTICK_ACTIVATION_THRESHOLD)
	{
		motor[DFR] = vexRT[Ch2];
		motor[DBR] = vexRT[Ch2];
	}
	else
	{
		motor[DFR] = 0;
		motor[DBR] = 0;
	}

}














task usercontrol()
{
	// User control code here, inside the loop
	while(true)
	{
		startTask(presets);
		startTask(drive);
	}
}
