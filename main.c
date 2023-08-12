/*
 * main.c
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */
# include "STD_TYPES.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "KPD_interface.h"
# include "KPD_config.h"

# include <util/delay.h>




int main ()
{
	/*----------------------------------------------------------LCD--------------------------------------------------------------------------------*/
		DIO_VidSetPortDirection(Port_D,0b11100000); // LCD CMD Pins  : Port_D {7,6,5--->OutPut} RS,RW,E respectively only
		DIO_VidSetPortDirection(Port_C,0b11111111); // LCD DATA Pins : Port_C {7,6,5,4,3,2,1,0--->OutPut}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	/*----------------------------------------------------------KPD--------------------------------------------------------------------------------*/
		DIO_VidSetPortDirection(Port_A,0b00001111); // KPD Pins      : Port_A {7,6,5,4-->Input} R4,R3,R2,R1 | {3,2,1,0-->Output} C1,C2,C3,C4 (Gnd)
		DIO_VidSetPortValue(Port_A,0b11110000);     // Pullup Reseistors activation for KPD Input pins : R4,R3,R2,R1
	//---------------------------------------------------------------------------------------------------------------------------------------------
	/*---------------------------------------------------DC Motor,LEDs,Buzzer----------------------------------------------------------------------*/
													// DC Motor Pins : Port_B {3,2,1,0-->Output} AntiClockwise<-Pin1,Pin2   ,  Clockwise<-Pin1,Pin0
		DIO_VidSetPortDirection(Port_B,0b11111111); // LEDs Pins     : Port_B {6(Green),5(Yellow),4(Red)-->Output}
		                                            // Buzzer Pins   : Port_B {7-->Output}
	//---------------------------------------------------------------------------------------------------------------------------------------------

		u8 x=0,y,start,button,HOURS,Hours,MINUTES,Minutes,SECONDS,Seconds;
		u8 Watch_Arr[8]={'0','0',':','0','0',':','0','0'};
		u8 YPos_Arr[6]={0,1,3,4,6,7};
		s8 i,j,k,l,m,n;

		LCD_VidDisplayClear();
		LCD_VidInit();

		LCD_VidSendString("   WELCOME To");
		LCD_VidGotoXY(1,1);
		LCD_VidSendString("   StopWatch");
		_delay_ms(1000);

		while (1)
		{
			LCD_VidDisplayClear();
			y=0;
			LCD_VidSendString("00:00:00");
			LCD_VidGotoXY(1,0);
			LCD_VidSendData('^');

			while (1)
			{
				button=KPD_u8GetPressedKey();
				if (button!=101)
				{
					if (button=='R')
					{
						_delay_ms(100);
						if (y<5)
						{
							LCD_VidGotoXY(1,YPos_Arr[y]);
							LCD_VidSendData(' ');

							y++;
							LCD_VidGotoXY(1,YPos_Arr[y]);
							LCD_VidSendData('^');
						}


					}
					else if (button=='L')
					{
						_delay_ms(100);
						if (y>0)
						{
							LCD_VidGotoXY(1,YPos_Arr[y]);
							LCD_VidSendData(' ');

							y--;
							LCD_VidGotoXY(1,YPos_Arr[y]);
							LCD_VidSendData('^');
						}

					}
					else if (button=='S')
					{
						LCD_VidGotoXY(1,YPos_Arr[y]);
						LCD_VidSendData(' ');

						break;
					}
					else
					{
						LCD_VidGotoXY(0,YPos_Arr[y]);
						Watch_Arr[YPos_Arr[y]]=button;
						LCD_VidSendData(Watch_Arr[YPos_Arr[y]]);
						LCD_VidGotoXY(1,YPos_Arr[y]);
						LCD_VidSendData('^');

					}

				}//if

			}//While

			u8 I=(Watch_Arr[0]-48),J=(Watch_Arr[1]-48),K=(Watch_Arr[3]-48),L=(Watch_Arr[4]-48),M=(Watch_Arr[6]-48),N=(Watch_Arr[7]-48);

			for (i=I;i>=0;i--)
			{
				LCD_VidGotoXY(0,0);
				LCD_VidSendNumber(i);
				for (j=J;j>=0;j--)
				{
					LCD_VidGotoXY(0,1);
					LCD_VidSendNumber(j);
					for (k=K;k>=0;k--)
					{
						LCD_VidGotoXY(0,3);
						LCD_VidSendNumber(k);
						for (l=L;l>=0;l--)
						{
							LCD_VidGotoXY(0,4);
							LCD_VidSendNumber(l);
							for (m=M;m>=0;m--)
							{
								LCD_VidGotoXY(0,6);
								LCD_VidSendNumber(m);
								for (n=N;n>=0;n--)
								{
									LCD_VidGotoXY(0,7);
									LCD_VidSendNumber(n);
									_delay_ms(1000);
								/* N=?------>N=0 */

								}//N=0
								N=9;

							/* M=?-1------>M=0 */

							}//M=0,N=0
							M=5;
							N=9;

						/* L=?-1------>L=0 */

						}//L=0,M=0,N=0
						L=9;
						M=5;
						N=9;

					/* K=?-1------>K=0 */

					}//K=0,L=0,M=0,N=0
					K=5;
					L=9;
					M=5;
					N=9;

				/* J=?-1------>J=0 */

				}//J=0,K=0,L=0,M=0,N=0
				J=9;
				K=5;
				L=9;
				M=5;
				N=9;

			/* I=?-1------>I=0 */


			}//I=0,J=0,K=0,L=0,M=0,N=0

			LCD_VidGotoXY(10,8);
			LCD_VidSendString(" TimeOut");

			LCD_VidGotoXY(1,0);
			LCD_VidSendString("Long Press E>END");


			while (1)
			{
				u8 z=KPD_u8GetPressedKey();

				DIO_VidSetPinValue(Port_B,Pin4,PinHigh);
				DIO_VidSetPinValue(Port_B,Pin7,PinHigh);
				_delay_ms(100);
				DIO_VidSetPinValue(Port_B,Pin4,PinLow);
				DIO_VidSetPinValue(Port_B,Pin7,PinLow);
				_delay_ms(100);

				DIO_VidSetPinValue(Port_B,Pin4,PinHigh);
				DIO_VidSetPinValue(Port_B,Pin7,PinHigh);
				_delay_ms(50);
				DIO_VidSetPinValue(Port_B,Pin4,PinLow);
				DIO_VidSetPinValue(Port_B,Pin7,PinLow);
				_delay_ms(50);
				DIO_VidSetPinValue(Port_B,Pin4,PinHigh);
				DIO_VidSetPinValue(Port_B,Pin7,PinHigh);
				_delay_ms(50);
				DIO_VidSetPinValue(Port_B,Pin4,PinLow);
				DIO_VidSetPinValue(Port_B,Pin7,PinLow);
				_delay_ms(50);

				if (z!=101)
				{
					if (z=='E')
					{
						DIO_VidSetPinValue(Port_B,Pin4,PinLow);
						DIO_VidSetPinValue(Port_B,Pin7,PinLow);
						break;
					}
				}


			}
		}

}//Main
