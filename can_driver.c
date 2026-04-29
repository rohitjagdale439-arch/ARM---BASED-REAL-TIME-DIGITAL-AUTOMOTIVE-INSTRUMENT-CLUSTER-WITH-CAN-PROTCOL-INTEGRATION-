#include<lpc21xx.h>

#include"header.h"

//extern u32 RECEIVER_FLAG;

extern CAN2 M1;

void can2_init(void)

{

  	PINSEL1|=0X00014000;

	VPBDIV=1;

	C2MOD=0X1;

	AFMR=0X2;

	C2BTR=0X001C001D;

	C2MOD=0;

}

#define TCS ((C2GSR>>3)&1)
void can2_tx(CAN2 V){
	C2TID1 = V.ID;
	C2TFI1 = (V.DLC<<16);
	if(V.RTR==0){
		C2TDA1=V.BYTEA;
		C2TDB1=V.BYTEB;
	}else
		C2TFI1 |= (1<<30);
	C2CMR = 1|(1<<5);
	while(TCS==0);
}


