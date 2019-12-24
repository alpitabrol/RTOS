
#include "chip.h"
#include "board.h"
#include <cr_section_macros.h>
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "game_data_struct.h"
#include <string.h>


/********************************************************************
 * UART Communication Setup
 ********************************************************************/
	#define UART_SELECTION 	LPC_UART3
	#define IRQ_SELECTION 	UART3_IRQn
	#define HANDLER_NAME 	UART3_IRQHandler

	/* Transmit and receive ring buffers */
	STATIC RINGBUFF_T txring, rxring;
	/* Transmit and receive ring buffer sizes */
	#define UART_SRB_SIZE 128	/* Send */
	#define UART_RRB_SIZE 32	/* Receive */
	/* Transmit and receive buffers */
	static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

/********************************************************************
 * Global Variables
 ********************************************************************/
volatile			queue_t		q; 				/* UART queue */
ui_t				user={False, False};
size_t				number_of_enemies=0;



/********************************************************************
 * Private Functions
 ********************************************************************/
/*
 *	function to handle UART Transmissions
 */
static void prvUARTSend(const char tx_text[])
{
	Chip_UART_SendRB(UART_SELECTION, &txring, tx_text, sizeof(tx_text) - 1);
}


static void prvSetupHardware(void)
{
		SystemCoreClockUpdate();
		Board_Init();
		Board_LED_Set(0, true);Board_LED_Set(1, true);Board_LED_Set(2, true);

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

		/* Reset and enable FIFOs, FIFO trigger level 1 (4 bytes --- need zero latency!) */
		Chip_UART_SetupFIFOS(UART_SELECTION, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
								UART_FCR_TX_RS | UART_FCR_TRG_LEV1));

		/* Enable receive data and line status interrupt */
		Chip_UART_IntEnable(UART_SELECTION, (UART_IER_RBRINT | UART_IER_RLSINT));

		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(IRQ_SELECTION, 1);
		NVIC_EnableIRQ(IRQ_SELECTION);

		/* set up GPIO pin interrupts for user interface */

		/* set up DAC for sound effects */
}

/********************************************************************
 * MAIN CODE
 ********************************************************************/
int main(void)
{

	prvSetupHardware();

		xTaskCreate(vRunGameTask, "Game Starting Task", 4*configMINIMAL_STACK_SIZE,
			NULL, RUN_GAME_PRIORITY, NULL);



	vTaskStartScheduler();

	/* return error code if scheduler exits */
    return 1;
}
