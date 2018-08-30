typedef struct{
	//Stores the current, unfiltered sensor value
	float rawValue;

	//Circular array with previous filtered values
	float prevValues[3];

	//avg of last 3  potentiometer values
	float avg;

}LRE_filter;

static LRE_filter fwVel;

/**

* initialize filter structure, fill prevValues array with starting sensor values
* @param instance of filter structure
*/

void lrefInit(LRE_filter filter, float val)
{
	filter.rawValue = val;
	filter.prevValues[0] = filter.rawValue;
	filter.prevValues[1] = filter.rawValue;
	filter.prevValues[2] = filter.rawValue;

	filter.avg = (filter.prevValues[0] + filter.prevValues[1] + filter.prevValues[2])/3;
}

/**

* update filter structure, uses simple linear recursive exponential filter, also limits mem usage
*
* @param instance of filter structure
*/

float lrefUpdate(LRE_filter filter, float weight, float val)
{
	filter.rawValue = val;
	filter.prevValues[0] = filter.prevValues[1];	//2nd -> 3rd
	filter.prevValues[1] = filter.prevValues[2];	//1st -> 2nd

	float lreFilter = weight * filter.rawValue + (1 - weight) * filter.avg;
	filter.prevValues[2] = lreFilter;							//new -> 1st

	return lreFilter;
}


float Batt = 0;
float vel  = 0;
float vel2 = 0;
float targetRPM = 0;
float targetPow = 0;
float mPow=0, P,I=0;
float acc=0, velP=0;

int   segment=0,  a=0, b=0;
unsigned long segmentEnd=0;

//Visual debugging for flywheel
void LED(int A,int B,int C,int D)
{
	SensorValue[Gr1] = !A;
	SensorValue[Gr2] = !B;
	SensorValue[Rd1] = !C;
	SensorValue[Rd2] = !D;
}

void FlyWheel()
{
	if(vexRT[Btn8L] == 1) {targetPow = 64;	targetRPM = 136; I=0; segment=0; } // base
	if(vexRT[Btn8U] == 1) {targetPow = 53;	targetRPM = 118; I=0; segment=0; } // mid-field
	if(vexRT[Btn8R] == 1) {targetPow = 42;	targetRPM = 100; I=0; segment=0; } // at the bar
	if(vexRT[Btn8D] == 1) {targetPow =  0;	targetRPM =   0; I=0; segment=0; }

	if(vexRT[Btn6U]==1 && a==0) {targetRPM++; targetPow+=0.5; a=1;}	else if(vexRT[Btn6U]==0) a=0;
	if(vexRT[Btn6D]==1 && b==0) {targetRPM--; targetPow-=0.5; b=1;}	else if(vexRT[Btn6D]==0) b=0;

	short RPM = getMotorVelocity(fw1);

	Batt = (Batt * 7 + nImmediateBatteryLevel / 1000.0) / 8;


	if( segment == 2 && nPgmTime > segmentEnd  ) segment = 0;
	P=0;

	LED(0,0,0,0);

	if( RPM > 0 )
	{
		vel  = ( 5*vel  + RPM)/6;  						// smoothed velocity, used to detect accel drop after firing ball
		vel2 = lrefUpdate(fwVel, 0.7, RPM);	//LRE filtered velocity @@tune param 0.7@@

		float err = targetRPM - vel2;
		acc = 10*(vel - velP);
		velP = vel;
		if( abs(err) < 3.5 ) LED(1,1,0,0); // green
		else if( err > 6.5 ) LED(0,0,1,1); // red

		if( segment == 0 ) // aggressive acceleration
		{
			if( err > 0.5 ) P = err*err; // undershoot, kp>3
			else if( err < -3 ) P = err; // overshoot,  kp=2
			else segment=1;
		}

		if( segment == 1 &&  acc<-targetRPM/5 ) // ball is going trough 138->35, 120->30 velocity drops, tune val@@@
		{
			segment = 2;														//this is the shooting condition
			segmentEnd = nPgmTime + 80; // do not increase motor power for the next 80ms, allow ball to launch
		}

		if( segment == 1 ) // maintain constant speed
		{
			P = err * 0.6; // kp=0.5
			I += err * (err>0 ? 0.001 : 0.003); // assymmetric ki, larger when overshooting
		}
	}

	float mp = ((6+7.623)/(6+Batt)) * (targetPow + P + I ); // scaling, it was tuned at 7.623v (why plus 6?)

	if( mp<0 ) mp=0;		//what happens with neagtive numbers
		if( mp>127 ) mp=127;//should this be indented

	if( mp > mPow+7 )  // limit slew rate to 7 power units per 5 ms
		mPow = mPow+7;
	else mPow = mp;

	motor[fw1] = mPow + 0.5;
	motor[fw2] = mPow;

	clearLCDLine(0);
	clearLCDLine(1);

	displayLCDString(0,1,"V=");
	displayLCDNumber(0,3,vel2);
	displayLCDString(0,8,"B=");
	displayLCDNumber(0,10,Batt * 1000);
	displayLCDString(1,1,"M=");
	displayLCDNumber(1,3,mPow * 10);
	displayLCDString(1,8,"I=");
	displayLCDNumber(1,10,I * 1000);

	//Detect false reading from the encoder
	if(RPM == 0 && targetRPM > 0)
	{
		//display error message to debugger
		//rely on internal encoder of the motor
	}
}
