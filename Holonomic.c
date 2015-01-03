#pragma config(Motor,  port1,           DFR,           tmotorVex393, openLoop)
#pragma config(Motor,  port2,           DBR,           tmotorVex393, openLoop)
#pragma config(Motor,  port3,           DFL,           tmotorVex393, openLoop)
#pragma config(Motor,  port4,           DBL,           tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!


//move forward

void autonStraight(int dist, bool reversed)
{
	if(reversed == true)
	{
		motor[DBR] = dist * 28.65; //this numba is bad
		motor[DBL] = dist * 28.65;
	}
	else
	{
		motor[DFR] = dist * 28.65;
		motor[DFL] = dist * 28.65;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		//holonomic drive
		motor[DFR] = vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
		motor[DBR] =  vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4];
		motor[DFL] = vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4];
		motor[DBL] =  vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4];
	}
}
