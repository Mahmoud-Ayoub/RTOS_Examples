/*
 * lab1.c
 *
 * Author : Mahmoud Ayoub
 */ 

/*
	Example for : Inter-Task Communication using "Message Queue"
*/



#include <avr/io.h>
#include "./RTOS/FreeRTOS.h"
#include "./RTOS/task.h"
#include "./RTOS/FreeRTOSConfig.h"
#include "./RTOS/semphr.h"
#include "./HAL/LCD/LCD.h"

#include <util/delay.h>

/* Define Tasks Priorities */
#define  TASK1_PRIORITY (2)
#define  TASK2_PRIORITY (1)

/* Queue Parameters */
#define QUEUE_LENGTH	8
#define QUEUE_ITEM_SIZE	(sizeof(char))

/*tasks codes prototypes */
 void task1_code(void* pvParamter);
 void task2_code(void* pvParamter);
 
 /* Create Message Queue Handler */
 QueueHandle_t msg_queue ;

int main(void)
{
	
	
	/* Create the queue, storing the returned handle in the xQueue variable. */
	msg_queue = xQueueCreate( QUEUE_LENGTH, QUEUE_ITEM_SIZE );
	
	/*initialize LCD*/
	LCD_init();	
	

	/* Create tasks */
	xTaskCreate(task1_code,NULL,configMINIMAL_STACK_SIZE,NULL,TASK1_PRIORITY,NULL);
	xTaskCreate(task2_code,NULL,configMINIMAL_STACK_SIZE,NULL,TASK2_PRIORITY,NULL);
	
	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
    
}

/*Task1 Code */
 void task1_code(void* pvParamter)
{
	char* data = "Mahmoud" ; 
	while (1) {
		xQueueSend(msg_queue , &data , 200) ; 
	}	
}

/*Task 2 Code*/
 void task2_code(void* pvParamter)
{
	char* data = 0 ; 
	while (1) {
		xQueueReceive(msg_queue , &data , 200) ; 
		LCD_send_str(data) ; 	
		_delay_ms(2000) ;
		LCD_clear() ; 
	}
}

