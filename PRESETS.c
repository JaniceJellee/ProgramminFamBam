#pragma config(Motor,  port2,           rLift1,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           rLift2,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           lLift1,        tmotorVex393, openLoop)
#pragma config(Motor,  port5,           lLift2,        tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int GROUND = 0; //5D
const int SKYRISE_DISPENSER = 0; //8L
const int LOW_GOAL = 0; //8D
const int MID_GOAL = 0; //8R
const int HIGH_GOAL = 0; //8U
const int MAX_HEIGHT = 0; //5U

int button5D = vexRT[Btn5DXmtr2];
int button8L = vexRT[Btn8LXmtr2];
int button8D = vexRT[Btn8DXmtr2];
int button8R = vexRT[Btn8RXmtr2];
int button8U = vexRT[Btn8UXmtr2];
int button5U = vexRT[Btn5UXmtr2];


//function for right lift
void rightLift(int a)
{
	motor[rLift1] = a;
	motor[rLift2] = a;
}
//function for left lift
void leftLift (int a)
{
	motor[lLift1] = a;
	motor[lLift2] = a;
}

//function for lift
void lift(int a)
{
	rightLift(a);
	leftLift(a);
}


//move lift until desired value is reached
void moveLift(int a)
{
	if(nMotorEncoder[rlift1] < a)
	{
		lift(127);
	}
	else if(nMotorEncoder[rlift1] > a)
	{
		lift(-127);
	}
	else
	{
		lift(0);
	}
}


void presets(bool * const preset)
{
	nMotorEncoder[rlift1] = 0;

	if((vexRT[Btn8UXmtr2]== 1) || (vexRT[Btn8DXmtr2]== 1) || (vexRT[Btn8LXmtr2] == 1)|| (vexRT[Btn8RXmtr2]== 1)
		|| (vexRT[Btn5UXmtr2] == 1) || (vexRT[Btn5DXmtr2] == 1)&& (vexRT[Btn6UXmtr2] == 0) && (vexRT[Btn6DXmtr2]== 0))
	{
		*preset = true; //enabling the auto control
	}
	else if((vexRT[Btn8UXmtr2]== 0) && (vexRT[Btn8DXmtr2]== 0) && (vexRT[Btn8LXmtr2]== 0)&& (vexRT[Btn8RXmtr2] == 0)
		&& (vexRT[Btn5UXmtr2] == 0) && (vexRT[Btn5DXmtr2]== 0) || (vexRT[Btn6UXmtr2]== 1) || (vexRT[Btn6DXmtr2]== 1))
	{
		*preset = false;	//enabling manual control
	}

	if(preset == true)
	{
		int target = 0;

		if((button8U == 0) && (button8D == 1) && (button8R == 0) && (button8L == 0)
			&& (button5U == 0) && (button5D == 0))
		{
			target = LOW_GOAL;
		}
		else if((button8U == 0) && (button8D == 0) && (button8R == 1) && (button8L == 0)
			&& (button5U == 0) && (button5D == 0))
		{
			target = MID_GOAL;
		}
		else if((button8U == 0) && (button8D == 1) && (button8R == 0) && (button8L == 0)
			&& (button5U == 0) && (button5D == 0))
		{
			target = HIGH_GOAL;
		}
		else if((button8U == 0) && (button8D == 0) && (button8R == 0) && (button8L == 0)
			&& (button5U == 0) && (button5D == 1))
		{
			target = GROUND;
		}
		else if((button8U == 0) && (button8D == 0) && (button8R == 0) && (button8L == 0)
			&& (button5U == 1) && (button5D == 0))
		{
			target = MAX_HEIGHT;
		}
		else if((button8U == 0) && (button8D == 0) && (button8R == 0) && (button8L == 1)
			&& (button5U == 0) && (button5D == 0))
		{
			target = SKYRISE_DISPENSER;
		}
		moveLift(target);
	}

	//manual control for lift
	else if(preset == false)
	{
		if((vexRT[Btn6UXmtr2] == 1) && (vexRT[Btn6DXmtr2] == 0))
		{
			lift(127);
		}
		else if((vexRT[Btn6DXmtr2] == 1) && (vexRT[Btn6UXmtr2] == 0))
		{
			lift(-127);
		}
		else
		{
			lift(0);
		}
	}
}


task usercontrol()
{

	bool preset = false; //initially preset is false 7to allow for manual control

	while(true)
	{
		presets(&preset);
	}
}
