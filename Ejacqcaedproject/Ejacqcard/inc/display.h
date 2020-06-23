
#ifndef DISPLAY_H
#define DISPLAY_H

extern int PalluCounter;
extern int BoraderCounter;

void LCD_nibble_Write(char data,unsigned char control);
/*initialize deay*/
void delayMs(int delay);

/*Initialize GPIO of LCD*/
void LCDGpio_Init(void);

/* for sending command  */
void LCD_command(unsigned char command);
/*for sending data*/
void LCD_data(char data);
/* initialize LCD  */
static void LCD_Init(void);

/* Initilize the 12 x 2 segment : Display1: */
/* Initilize the display2: */
int display_init(void);

/* Clear the Display1 or clear the lines 12 x 2 segment display*/
int display1_clear(void) ;

/* Clear the Display-2/ Clear the images */
int display2_clear(void) ;

/* Display Lines in the 12 x 2 segment display */
int display_lines(int line1,int line2);

/* Display the new file content in the Display -2 */
int display_file(char filename[][15]);

void displayFilenames(char *file1,char* file2);

/* Display the flash light on the given line number */
void display_flashlight(UINT32_T lineno);

/* Display the image on the display-2 and Highlight/flashlight on the given line/markno */
int display_image_with_highlight(UINT8_T *buf, UINT32_T len, UINT32_T markno);
 
#endif
