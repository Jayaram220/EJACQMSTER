
#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"


#include <stdio.h>
#include <string.h>
#include "main.h"
#include "comm.h"
#include "process.h"
#include "display.h"

#define COMM_START	'*'
#define COMM_STOP	'&'
#define COMM_NEXT	'?'
#define COMM_PAUSE	'!'

char Readbuff[80] = "0XFCAB5";


int PalluCounter=1;
int BoraderCounter=1;
int RXflag = 0;
char  cmd = ' ';
//static int sgFileDesc = 0;
static char comm_buf[256];/* buffer is limited to 255 characters, just like the maximum string length for canonical input processing.*/ 


/**
  * @brief Configures the serial terminal settings.
  * @note  tcgetattr(fd, &term): save current serial port settings.
  * @note  termios contains flags as structr members are c_lflag,c_iflag,c_cflag,c_oflag.
	   c_iflag -- input modes.
	   c_oflag -- control modes.
	   c_cflag -- control modes.
	   c_lflag -- local modes. 
  * @note  ISIG    :When any of the characters INTR, QUIT, SUSP, or DSUSP are received,
		   generate the corresponding signal.
	   ICANON  : enable canonical input. 
	   ECHO    : Echo input characters(here it disable all echo functionality, and don't send signals to calling program).
	   IEXTEN  : Enable implementation-defined input processing.  This flag, as
              	     well as ICANON must be enabled for the special characters
              	     EOL2, LNEXT, REPRINT, WERASE to be interpreted, and for the
              	     IUCLC flag to be effective.
	   ICRNL   :Translate carriage return to newline on input (unless IGNCR is set).
	   IXON    :Enable XON/XOFF flow control on output.
	   HUPCL   :Lower modem control lines after last process closes the device
             	    (hang up).
	   OPOST   :Enable implementation-defined output processing.

	    
  * @note    
  * @param  No parameter.
  * @retval zeo
  */





int USART1_InitMode()
{

		int ret = 0;
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
		/* Configure USART1 pins: Rx and Tx ----------------------------*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1,ENABLE);
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

		/* Enable USART1 IRQ */
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		return 0;

}


void USART1_IRQHandler(void)
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Received characters modify string
	{
	cmd = USART_ReceiveData(USART1);
	if (cmd)
	{
		RXflag=1;
	}

	}
}

/*static int serial_init(int fd, UINT32_T baudRate)
{
	int ret=0;
	return 0;
}*/

/**
  * @brief  Initialize the communication channel with extended board.
  * @note   Declare the termios structre which provide a general terminal interface that is
       	    provided to control asynchronous communications ports.
  * @note   If the file opens successfully the function will return 0 t0 fd else it will return negative value
	    and throw error.
  * @note   serial_init(fd, EJACQUARD_BAUD_RATE): Configures the serial terminal settings. 
  * @param  No parameter.
  * @retval zeo
  */

/*
int comm_init(void)
{
	int fd;
//	struct termios SPortSettings;

	/* 
          Open usb device for reading and writing and not as controlling tty
          because we don't want to get killed if linenoise sends CTRL-C.

	fd = open(EJACQUARD_SERIAL_UART, O_RDWR);

	if (fd < 0)
	{
		printf("Error opening Serial Port!\n");
		return fd;
	}
	if(serial_init(fd, EJACQUARD_BAUD_RATE))
	{
		return -1;
	}

	sgFileDesc = fd;
	return 0;
}
  */

/* Send the the Data to the Extended board thru Serial port */
/*
int comm_send_data(UINT8_T *buf, UINT32_T size)
{
	UINT32_T len = 0;
	int ret = 1;
	/* Write the  given binary data in to the serial porth */
	/* size --> size of the data that we should write into the serial port
	while ( ret < 0 && len < size ) {
		ret  = write(sgFileDesc, buf, size);
		len++;	
	}
	if ( len < size ) {
		printf(" Communication error \n");
		return -1;
	}
	printf(" The data of size = %d is wrriten in the Serial port\n",size);
	return 0;
}
*/
/* comm serial wait for the commnds to server for the extended board */
void comm_send_data(char *Readbuff)
{
	for(int i=0; i<strlen(Readbuff); i++)
		{
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
			USART_SendData(USART1,Readbuff[i]);

		}

		USART_SendData(USART1, '\r');
		USART_SendData(USART1, '\n');

}

int comm_process_cmd(void)
{
	int ret = 0;
	//char cmd = ' ';
	//cmd ='?';
	/*unsigned int size = 0;*/
	/* Read the cmds from the extended board and change the appropriate state */
	/*ret = read(sgFileDesc , &cmd, 1);*/
	while(1)
	{

		switch (cmd)
		{
			case COMM_START: 
				RXflag=0;
				cmd = ' ';
				//memset(&comm_buf, 0 , 256);
				//sprintf(comm_buf,"START");
				comm_send_data(Readbuff);
				/*//read the data from process and send in comm port
				size = process_read_data(comm_buf);
				if (size > 0 ) 
					ret = comm_send_data(comm_buf, size); */
				
				break;
			case COMM_STOP:
				/*//Change to Idle State
				CHANGE_STATE( EJACQUARD_STATE_IDLE );
				 //Close the close the channel
				  TODO: close(sgFileDesc);
				 //memset the comminucation channel */

				RXflag=0;
				cmd = ' ';
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"STOP");
				comm_send_data(comm_buf);
				break;
			case COMM_NEXT:
				RXflag=0;
				cmd = ' ';
				//memset(&comm_buf, 0 , 256);
				//sprintf(comm_buf,"NEXT");
				comm_send_data(Readbuff);
				USART_SendData(USART1, '\r');
				USART_SendData(USART1, '\n');
				display_lines(PalluCounter,BoraderCounter);
				PalluCounter++;
				BoraderCounter++;
				break;


				/*//Increament the Pallu and Borader Counter */
				//process_increament_lines(1);


				/* read the data from process and send in comm port */
				//size = process_read_data(comm_buf);
				//if (size > 0 )
				//	ret = comm_send_data(comm_buf, size);

			case COMM_PAUSE:	
				/* Increament the Pallu and Borader Counter */
				//process_increament_lines(1);
				/* Change to Idle State */
				//CHANGE_STATE( EJACQUARD_STATE_IDLE );
				/* memset the comminucation channel */
				RXflag=0;
				cmd = ' ';
				memset(&comm_buf, 0 , 256);
				sprintf(comm_buf,"PAUSE");
				comm_send_data(comm_buf);
				break;
			default: 
				break;/* Just ignore */
		}
	}
	return ret; 

}
