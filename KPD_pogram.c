/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : KPD DRIVER              *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman           *************************************************************************************************************/
/************************************************* Date    : 27Aug20                 *************************************************************************************************************/
/************************************************* Version : v1.0                    *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/
# include "STD_TYPES.h"
# include "DIO_interface.h"
# include "KPD_interface.h"
# include "KPD_config.h"
# include "KPD_private.h"



u8 KPD_u8GetPressedKey (void)
{
	u8 Local_u8KPD_Arr[ROW_NUM][COLUMN_NUM] =KPD_ARR;

	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY  , Local_u8PinState ;

	u8 Local_u8ColumnArr[COLUMN_NUM]={KPD_COLUMN0_PIN , KPD_COLUMN1_PIN , KPD_COLUMN2_PIN , KPD_COLUMN3_PIN};
	u8 Local_u8RowArr[COLUMN_NUM]   ={KPD_ROW0_PIN    , KPD_ROW1_PIN    , KPD_ROW2_PIN    , KPD_ROW3_PIN   };

	for (u8 col=0;col<COLUMN_NUM;col++)
	{
		/* Activate the current Column */

		DIO_VidSetPinValue(KPD_PORT,Local_u8ColumnArr[col],PinLow);

		for (u8 row=0;row<ROW_NUM;row++)
		{
			/* Read the current Row */

			DIO_VidGetPinValue(KPD_PORT,Local_u8RowArr[row],&Local_u8PinState);

			if (Local_u8PinState==0)
			{
				Local_u8PressedKey=Local_u8KPD_Arr[row][col];

				while (Local_u8PinState==0)
				{
					DIO_VidGetPinValue(KPD_PORT,Local_u8RowArr[row],&Local_u8PinState);
				}

				return Local_u8PressedKey;

			}


		}

		/* Deactivate the current Column */

		DIO_VidSetPinValue(KPD_PORT,Local_u8ColumnArr[col],PinHigh);
	}

	return Local_u8PressedKey;

	
}




