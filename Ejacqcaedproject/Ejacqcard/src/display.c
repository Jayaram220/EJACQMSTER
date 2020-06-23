#include <stdio.h>
#include "main.h"
#include "display.h"
#include <string.h>
//pc4 - pc7 -- D0 -

// PB5 -- RS
//PB6 --- R/W
//PB7 --- EN

#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"

#define RS 0x20 // 0010 0000 -- PB5
#define RW 0x40 // 0100 0000 --- PB6
#define EN 0x80 // 1000 0000 --- PB7

char Max_borderline_str[8]= "200";
char Max_bodyline_str[8]= "500";

#define MAXBORDERLINE 200
#define MAXBODYLINE 500


void delayMs(int delay)
{
	int i;
	for(i = 0; i < delay*1000; i++)
	{

	}

}

/*
void LCDGpio_Init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable GPIOB clock
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // enable GPIOC clock
	GPIOB->MODER |= 0x5400; // 0101 0100 0000 0000
	GPIOB->BSRR = 0x00C; // set EN and RW low ie, 22,23  -- 0000 0000 1100 0000 0000 0000 0000 0000
	//set PC0 - PC7 as output

	GPIOC->MODER |= 0x00005555; // 0000 0000 0000 0000 0101 0101 0101 0101

}

*/

void LCDGpio_Init(void)
{
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable GPIOB clock
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // enable GPIOC clock
		GPIOB->MODER |= 0x0004400;  //                0100 0100 0000 0000   -- o/p as pb5 , pb7
		GPIOB->BSRR = 0x00800000; // CLEAR EN 23 opposite of 7
		//set PC0 - PC7 as output

		GPIOC->MODER |= 0x00005500; // 0000 0000 0000 00|00 01|01 01|01 00|00 00|00
}


void LCD_nibble_Write(char data,unsigned char control)
{
	GPIOC->BSRR = 0x00F00000; // Clear data bits
	GPIOC->BSRR = 0x00F00000; // Clear data bits
	GPIOC->BSRR = data & 0xF0;
	if(control & RS)
	{
		GPIOB->BSRR = RS; // RS = 1

	}
	else
	{
		GPIOB->BSRR = RS <<16;
	}
	// PULSE en
	GPIOB->BSRR = EN;
	delayMs(10);
	GPIOB->BSRR = EN<<16;

}



/*
void LCD_command(unsigned char command)
{
	GPIOB->BSRR = (RS|RW)<<16; // RS = 0, RW=0
	GPIOC->ODR = command; // data is supplied to the data.
	GPIOB->BSRR = EN; // EN: E is known as the enable pin. It Is used by the LCD to secure information.
	// When data is supplied to the data pins a High-Low pulse must be applied
	delayMs(30);
	GPIOB->BSRR = EN <<16; // Clear EN pin
}

*/

void LCD_command(unsigned char command)
{
	LCD_nibble_Write(command & 0XF0,0); // UPPER 4 BITS
		LCD_nibble_Write(command << 4, 0); // LoweR 4 BITS

		if(command <4)
		{
			delayMs(10);
		}
		else
		{
			delayMs(10);
		}

}



/*
void LCD_data(char data)
{
	GPIOB->BSRR = RS; // RS = 1
	GPIOB->BSRR = RW <<16;  // R/W = 0
	GPIOC->ODR = data;
	GPIOB->BSRR = EN;
	delayMs(30);
	GPIOB->BSRR = EN <<16; // Clear EN pin

}
*/

void LCD_data(char data)
{
	LCD_nibble_Write(data & 0XF0,RS);
	LCD_nibble_Write(data <<4,RS);
	delayMs(10);
}


/*
static void LCD_Init(void)
{
	LCDGpio_Init(); //Init Gpio sequence
	delayMs(40);
	LCD_command(0x30); //  means we are setting 8-bit mode lcd having 1 line and we are initializing it to be 5×7 character display
	delayMs(20);
	LCD_command(0x30);
	delayMs(10);
	LCD_command(0x30);

	LCD_command(0x38); // set 8-bit data mode, 2 line, 5*7 font
	LCD_command(0x06); // move cursor right or Auto Increment cursor

	LCD_command(0x01); // clear screen, move cursor home
	LCD_command(0x0F); // turn display, blink cursor


}
*/

static void LCD_Init(void)
{
		LCDGpio_Init();
		delayMs(10);
		LCD_nibble_Write(0X30,0);
		delayMs(10);
		LCD_nibble_Write(0X30,0);
		delayMs(10);
		LCD_nibble_Write(0X30,0);
		delayMs(10);

		LCD_nibble_Write(0X20,0); // SET 4 BIT DATA MODE
		delayMs(10);
		LCD_command(0x28); // 4-bit mode, 2- line, 5*7 font
		delayMs(10);
		LCD_command(0x06); // move curser right
		delayMs(10);
		LCD_command(0x01); // clear screen, move cursor home
		LCD_command(0x0F); // turn on display and blink cursor


}




/* Name: Display_lines
 * 
 *
 *
 */


int display_init(void)
{
	int ret = 0;
	/* Initilize the 12 x 2 segment : Display1: */
	/* initilize the display2: */
	printf ("\n Display - 1 Initialized\n");
	LCD_Init();
	printf ("\n Display - 2 Initialized\n");
	return ret;
}

// MJN ..Convert this function into Macro
int display1_clear(void) 
{
	int ret = 0;
 	/* Clear the Display1 or clear the lines 12 x 2 segment display*/
	LCD_command(0x01); // clear screen, move cursor home
	printf(" Clear the display1\n");
	return ret;
}
	
int display2_clear(void) 
{
	int ret = 0;
 	/* Clear the Display-2/ Clear the images */
	//needs to add
	printf(" Clear the display2\n");
	return ret;
}

/* below function previously was int display_lines(UINT8_T *line1, UINT8_T *line2)*/

int display_lines(int line1,int line2)
{ 
	int ret = 0;
	char line1_str[8] = {0};
	char line2_str[8] = {0};
	char max_line1_str[8] = {0};
	char max_line2_str[8] = {0};
	int i = 0;

	/* Display Lines in the 12 x 2 segment display-1 */
	//printf ("\n %s \n ", (unsigned char *) line1);
	//printf ("\n %s \n ", (unsigned char *) line2);

	display1_clear();
	sprintf(line1_str, "%d",line1);
	sprintf(line2_str, "%d",line2);
    if(line2 <= MAXBODYLINE)
    {
    	if(line1 <= MAXBORDERLINE)
    	{
    		for ( i= 0; i < strlen(line1_str); i++)
    			{
    				LCD_data(line1_str[i]);
    			}
    			LCD_data('/');
    			for ( i= 0; i < strlen(Max_borderline_str); i++)
    			{
    				LCD_data(Max_borderline_str[i]);
    			}

    			// Print Line-2
    		   // LCD_data(' ');
    			LCD_command(0x88);
    			for ( i= 0; i < strlen(line2_str); i++)
    			{
    				LCD_data(line2_str[i]);
    			}
    			LCD_data('/');
    			for ( i= 0; i < strlen(Max_bodyline_str); i++)
    			{
    				LCD_data(Max_bodyline_str[i]);
    			}

    	}
    	else
    	{
    		line1 = 1;
    		PalluCounter = 1;
    		sprintf(line1_str, "%d",line1);
    		for ( i= 0; i < strlen(line1_str); i++)
    		    {
    		    	LCD_data(line1_str[i]);
    		    }
    		    LCD_data('/');
    		    for ( i= 0; i < strlen(Max_borderline_str); i++)
    		    {
    		    	LCD_data(Max_borderline_str[i]);
    		    }

    		    // Print Line-2
    		    //LCD_data(' ');
    		    LCD_command(0x88);
    		    for ( i= 0; i < strlen(line2_str); i++)
    		    {
    		    	LCD_data(line2_str[i]);
    		    }
    		    LCD_data('/');
    		    for ( i= 0; i < strlen(Max_bodyline_str); i++)
    		    {
    		    	LCD_data(Max_bodyline_str[i]);
    		    }

    	}

    }
    if(BoraderCounter == MAXBODYLINE)
    {
    	PalluCounter = 0;
    	BoraderCounter = 0;
    }

	// Print Line-1
	//LCD_command(0xC0);
    /*{
	for ( i= 1; i <= strlen(line1_str); i++)
	{
		LCD_data(line1_str[i]);
	}
	LCD_data('/');
	for ( i= 1; i <= strlen(Max_borderline_str); i++)
	{
		LCD_data(Max_borderline_str[i]);
	}

	// Print Line-2
    LCD_data(' ');
	for ( i= 0; i < strlen(line2_str); i++)
	{
		LCD_data(line2_str[i]);
	}
	LCD_data('/');
	for ( i= 0; i < strlen(Max_bodyline_str); i++)
	{
		LCD_data(Max_bodyline_str[i]);
	}
    }
    else
    {
    	PalluCounter = 1;


    }*/

	return ret;
}

int display_file(char foldername[][15])
{
	int ret = 0;
	int folderindex;
	int folderindextwo;
	//display2_clear();
	display1_clear();
	//while(filename[0] != '\0')

	for ( folderindex= 0; folderindex < strlen(foldername[0]); folderindex++)
	{
	    LCD_data(foldername[0][folderindex]);
	 }

	LCD_command(0XC0);
	for ( folderindextwo= 0; folderindextwo < strlen(foldername[1]); folderindextwo++)
	{
		    LCD_data(foldername[1][folderindextwo]);
	}


	/* Display the new file content in the Display -2 */

	return ret;
}


void displayFilenames(char *file1,char* file2)
{
	display1_clear();
	int fileindex = 0;
	for ( fileindex= 0; fileindex < strlen(file1); fileindex++)
		{
		    LCD_data(file1[fileindex]);
		 }

		LCD_command(0XC0);
		for ( fileindex= 0; fileindex < strlen(file2); fileindex++)
		{
			    LCD_data(file2[fileindex]);
		}

}




void display_flashlight(UINT32_T lineno)
{
	/* Display the flash light on the given line number of the screen */
	printf("Display flash on the line no %d\n", lineno);
}

int display_image_with_highlight(UINT8_T *buf, UINT32_T len, UINT32_T markno)
{
	int ret = 0;
	
	display2_clear();

	/* Display the image data content in the Display -2 and highlight the line*/
	
	/* Call the flashlight on the given markno */
	display_flashlight(markno);	

	return ret;
}
