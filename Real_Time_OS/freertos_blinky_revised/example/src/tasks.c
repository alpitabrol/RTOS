
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "game_data_struct.h"


void vPlayerTask(void *pvParams)
{
/*it will take input from user and updates the coordinates of the player car
 * also it will first check whether the player is alive or not
 */
}

void vEmemyTask(void *pvParams)
{

	/*it will updates the coordinates of the enemy car till
	 * the time game is running i.e. player is alive
	 *
	 */

}

void vCollisionTask(void *pvParams)
{

while(1)
	{
	/*Check for collisions
	 * if collided delete player task and send the game over text.
	 *
	 * it will update the score variable with the number of enemies leaving the screen
	 * also it will update the coordinates of player and enemy
	 *
	 */
	}
}

void vRunGameTask(void *pvParams)
{

	xTaskCreate(vPlayerTask, "Player_Car_Task",
		configMINIMAL_STACK_SIZE, NULL,GO_TASK_PRIORITY, &player_handler);
	xTaskCreate(vEmemyTask, "Enemy_Car_Task",
			configMINIMAL_STACK_SIZE, NULL,GO_TASK_PRIORITY, &enemy_handler);

	while(1)
	{
		xTaskCreate(vCollisionTask, "Collision_task",
								1024,NULL, IMPACTS_TASK_PRIORITY, &pvImpactsTaskHandle);
	}
}


void vTaskUART(void *pvParams)
{
	int bytes;

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

