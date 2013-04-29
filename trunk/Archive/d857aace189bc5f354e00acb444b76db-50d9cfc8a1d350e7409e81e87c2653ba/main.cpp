#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
    Init,
	RlB,
	RgB
} t_states;

#define FIRE() {iBaseCount++;printf("FIRE(%d)\n",iBaseCount);};

void ZeroCrossSM();
int iBaseCount=0;
float Rp, Bp;
int REFERENCE=60, BASE=40;

int main(int argc, char * argv[])
{
	int i;

	if(argc == 3)
	{
		REFERENCE = atoi(argv[1]); /* reference frequency 50 or 60 Hz*/
		BASE = atoi(argv[2]); /* base frequency, ie frequency to drive pump */
	}
	Rp = ((float)(1.0/REFERENCE));
	Bp = ((float)(1.0/BASE));
	printf("REFERENCE = %d, BASE = %d\n", REFERENCE, BASE);
	for(i = 0; i < 60; i++)
	{
		ZeroCrossSM();
	}
	
	return(0);
}

void ZeroCrossSM()
{
	static float B=0, R=0;
	static int C=0;
	static t_states state=Init;

	switch(state)
	{
		case Init:
			R = Rp;
			B = Bp;
			C = 0;
			iBaseCount = 0;
			FIRE();
			state = RlB;
		break;

		case RlB:
			if(R < B)
			{
				R+=Rp;
			}
			else
			{
				R+=Rp;
				B+=Bp;
				FIRE();
				state = RgB;
			}
			if(C == (REFERENCE-1))
			{
				R = Rp;
				B = Bp;
				C = 0;
				iBaseCount = 0;
				FIRE();
				state = Init;
			}
			C++;
		break;

		case RgB:
			if(R < B)
			{
				R+=Rp;
				state = RlB;
			}
			else
			{
				R+=Rp;
				B+=Bp;
				FIRE();
			}
			if(C == (REFERENCE-1))
			{
				R = Rp;
				B = Bp;
				C = 0;
				iBaseCount = 0;
				FIRE();
				state = Init;
			}
			C++;
		break;

		default:
		break;
	}
	printf("B=%f; R=%f\n", B, R);
}

