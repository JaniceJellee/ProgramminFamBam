#pragma config(Motor,  port1,           DFL,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           DBL,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           DFR,           tmotorVex393, openLoop)
#pragma config(Motor,  port4,           DBR,           tmotorVex393, openLoop)
#pragma config(Motor,  port8,           holo,          tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int tol = 20;
int straight;
int ptturn;
int side;


void driveLeft (int pwr)
{
	motor[DBL] = pwr;
	motor[DFL] = pwr;
}

void driveRight (int pwr)
{
	motor[DFR] = pwr;
	motor[DBR] = pwr;
}

void driveStraight (int pwr)
{
	driveRight(pwr);
	driveLeft(pwr);
}

void turnRight (int pwr)
{
	driveRight(-pwr);
	driveLeft (pwr);
}

void turnLeft (int pwr)
{
	driveRight(pwr);
	driveLeft(-pwr);
}

task main()
{

	while (true)
	{
		if(abs(vexRT[Ch3]) > tol)//set straight
			straight = vexRT[Ch3];
		else
			straight = 0;
		if(abs(vexRT[Ch1]) > tol) //set ptturn
			ptturn = vexRT[Ch1];
		else
			ptturn = 0;
		if(abs(vexRT[Ch4]) > tol) //set side
			side = vexRT[Ch4];
		else
			side = 0;
		if((abs(-ptturn + straight)<=127) && (abs(ptturn + straight)<=127))
		{
			driveRight(-ptturn/2 + straight*2/3);
			driveLeft(ptturn/2 + straight*2/3);
			motor[holo]= side;
		}
		else if(abs(-ptturn + straight) > 127)//(pttrn + straight)
		{
			driveRight(100);
			driveLeft(-100);
			motor[holo]= side;
		}
		else if(abs(-ptturn + straight) > 127)
		{
			driveRight(-100);
			driveLeft(100);
			motor[holo]= side;
		}

		else
		{
			driveLeft(0);
			driveRight(0);
			motor[holo]=0;
		}


	}
}
