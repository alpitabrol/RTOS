
#include "chip.h"
#include "board.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define BuferSize 12
#define UART_SELECTION 	LPC_UART3
#define IRQ_SELECTION 	UART3_IRQn
#define HANDLER_NAME 	UART3_IRQHandler
//#define configMINIMAL_STACK_SIZE	((unsigned short)128)
//#define tskIDLE_PRIORITY  			((unsigned long) 0U)
//#define configTICK_RATE_HZ			((unsigned long) 1000)
/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring, rxring;

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 32	/* Receive */

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

const char inst1[] = "LPC17xx/40xx UART example using ring buffers\r\n";
const char inst2[] = "Press a key to echo it back or ESC to quit\r\n";
uint8_t key;
	int bytes;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	UART 0 interrupt handler using ring buffers
 * @return	Nothing
 */
void HANDLER_NAME(void)
{
	/* Want to handle any errors? Do it here. */

	/* Use default ring buffer handler. Override this with your own
	   code if you need more capability. */
	Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);
}

/**
 * @brief	Main UART program body
 * @return	Always returns 1
 */
void vSendMessage(char *buff[],int size)
{
	Chip_UART_SendRB(UART_SELECTION, &txring, buff, size-1);
}

void vTaskUART(void *pvParameters)
{
	int bytes;

	/* Setup UART for 115.2K8N1 */
	Chip_UART_Init(UART_SELECTION);
	Chip_UART_SetBaud(UART_SELECTION, 115200);
	Chip_UART_ConfigData(UART_SELECTION, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
	Chip_UART_SetupFIFOS(UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
	Chip_UART_TXEnable(UART_SELECTION);

	/* Before using the ring buffers, initialize them using the ring
	   buffer init function */
	RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	/* Reset and enable FIFOs, FIFO trigger level 3 (14 chars) */
	Chip_UART_SetupFIFOS(UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
							UART_FCR_TX_RS | UART_FCR_TRG_LEV3));

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(UART_SELECTION, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(IRQ_SELECTION, 1);
	NVIC_EnableIRQ(IRQ_SELECTION);

	/* Send initial message */
	char buf[] = "Initialization of the part interface active\r\n";
	Chip_UART_SendRB(UART_SELECTION, &txring, buf, sizeof(buf) - 1);

	//This is not actually used in the video game, I have
	//set this into place just to show that the serial communication
	//is working in both ways.
	while (1)
	{
		bytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &rxbuff, sizeof(rxbuff));
			if (bytes > 0)
			{
				Chip_UART_SendRB(UART_SELECTION, &txring, &rxbuff, sizeof(rxbuff));
				for(int i = 0; i<UART_RRB_SIZE; i++)
				{
					rxbuff[i]=0;
				}
			}

		vTaskDelay(configTICK_RATE_HZ*5);
	}
}

void vTaskCollisions(void * pvParameters)
{

	char commit[] = "Z";
	char devider[] = "\r\n";
	char buffer[BuferSize];

	int test = 33;
	while(1)
	{

		for(uint8_t i = 0;i<BuferSize;i++)
		{
			buffer[i]=' ';
		}
		//Simulate the package construction and then send the message through the interface
		sprintf(buffer,"%d,%d",test,test);
		vSendMessage(&buffer,sizeof(buffer));
		vSendMessage(commit, sizeof(commit));
		vSendMessage(&devider, sizeof(devider));


		//bool cont = true;
		//ptrCht = pHeadMissile;
		//while(cont)

		//This vTaskDelay defines how often the information is sent to the slave
		vTaskDelay(configTICK_RATE_HZ/20);
	}
}



int main(void)
{


	SystemCoreClockUpdate();
	Board_Init();
	Board_UART_Init(UART_SELECTION);
	Board_LED_Set(0, false);

	xTaskCreate(vTaskUART,(signed char *) "UartTask",configMINIMAL_STACK_SIZE, NULL,(tskIDLE_PRIORITY + 1UL),NULL);
	xTaskCreate(vTaskCollisions, (signed char *) "TaskCollisions",configMINIMAL_STACK_SIZE, NULL,(tskIDLE_PRIORITY + 3UL),NULL);

	vTaskStartScheduler();
	return 1;
}

/**
 * @}
 */
