	#include<lpc21xx.h>

#include"header.h"

CAN2 M1;

int FLAG_HEADLIGHT;

int FLAG_INDICATOR_RIGHT;

int FLAG_INDICATOR_LEFT;


int main()

{

	int HEADLIGHT_TOGGLE=1;

	int INDICATOR_RIGHT_TOGGLE=1;

	int INDICATOR_LEFT_TOGGLE=1;

	adc_init();

	can2_init();

	ext_init();

	interrupt_confg();
		M1.DLC=4;
		M1.FF = M1.RTR = 0;

	while(1)

	{

		M1.ID=TEMPERATURE_ID;

	

		M1.BYTEA=adc_read(1);

		can2_tx(M1);


		delay_ms(100);		

		M1.ID=SPEED_ID;		

		M1.BYTEA=adc_read(2);	

		can2_tx(M1);

		delay_ms(100);


		if(FLAG_HEADLIGHT)

		{

		 	FLAG_HEADLIGHT=0;

			M1.ID=HEADLIGHT_ID;

			if(HEADLIGHT_TOGGLE)

			{

				M1.BYTEA=HEADLIGHT_ON;

				HEADLIGHT_TOGGLE=0;		

			}

			else

			{

				M1.BYTEA=HEADLIGHT_OFF;

				HEADLIGHT_TOGGLE=1;		

			}	

			can2_tx(M1);

		}

	  // delay_ms(2000);

		if(FLAG_INDICATOR_RIGHT)

		{

			FLAG_INDICATOR_RIGHT=0;

	   		M1.ID=INDICATOR_ID;

			//C2TFI1=4<<16;

	   		if(INDICATOR_RIGHT_TOGGLE)

			{

				M1.BYTEA=INDICATOR_RIGHT_ON;

				INDICATOR_RIGHT_TOGGLE=0;

				INDICATOR_LEFT_TOGGLE=1;		

			}

			else

			{

				M1.BYTEA=INDICATOR_RIGHT_OFF;

				INDICATOR_RIGHT_TOGGLE=1;		

			}	

			//C2CMR=0x21;
			can2_tx(M1);
		}

	   //delay_ms(2000);

	   if(FLAG_INDICATOR_LEFT)

		{

	   		FLAG_INDICATOR_LEFT=0;

	   		M1.ID=INDICATOR_ID;

			//M2.BYTEA=4<<16;

	   		if(INDICATOR_LEFT_TOGGLE)

			{

				M1.BYTEA=INDICATOR_LEFT_ON;

				INDICATOR_LEFT_TOGGLE=0;

				INDICATOR_RIGHT_TOGGLE=1;		

			}

			else

			{

				M1.BYTEA=INDICATOR_LEFT_OFF;

				INDICATOR_LEFT_TOGGLE=1;		

			}	

			//C2CMR=0x21;
			can2_tx(M1);
		}

	}

}
