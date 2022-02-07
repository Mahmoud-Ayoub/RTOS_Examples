/*
 * lab2.c
 *
 * Author : Mahmoud Ayoub
 */ 

/*
	Example for : Synchronization using "Counting semaphore"
*/

#include <avr/io.h>
#include "./RTOS/FreeRTOS.h"
#include "./RTOS/task.h"
#include "./RTOS/FreeRTOSConfig.h"
#include "./RTOS/semphr.h"
#include "./HAL/LCD/LCD.h"
#include "./HAL/Push Button/PB.h"


#include <util/delay.h>

/* Define Tasks Priorities */
#define  INIT_TASK_PRIORITY (3)
#define  LCD_TASK_PRIORITY (2)
#define  PB_TASK_PRIORITY (1)


/*tasks codes prototypes */
 void Init_task (void* pvParamter);
 void LCD_task (void* pvParamter) ;
 void PB_task (void* pvParamter) ; 

/* Init Task Handle */
TaskHandle_t init_Handle;
 
/* create semaphore to synchronize LCD with Push Button */
 xSemaphoreHandle PB_SEM ; 


int main(void)
{
	
	PB_SEM = xSemaphoreCreateCounting(1,0) ;

	/* Create tasks */
	xTaskCreate(Init_task,NULL,configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRIORITY,&init_Handle);
	xTaskCreate(LCD_task,NULL,configMINIMAL_STACK_SIZE,NULL,LCD_TASK_PRIORITY,NULL);
	xTaskCreate(PB_task,NULL,configMINIMAL_STACK_SIZE,NULL,PB_TASK_PRIORITY,NULL);

	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
    
}

/*
	Init Task
*/
void Init_task(void* pvParamter) {
	while (1) {
		/* initialize LCD */
		LCD_init();
		
		/* initialize Push Button */
		PB_init (portA , 0) ;
		
		/* Delete Task */ 
		vTaskDelete(init_Handle) ; 
	}
}

/*
	LCD task
*/
 void LCD_task (void* pvParamter) {
	 uint8 ret = 0 ; 
	 while (1) {
		ret = xSemaphoreTake(PB_SEM , 250) ;
		if (ret == 1) {
			LCD_clear() ;
			LCD_send_str("Fire");
			_delay_ms(1000) ;
			LCD_clear() ;
		} 
	 }
 }

/*
	Push button task
*/
void PB_task (void* pvParamter) {
	uint8 pb_status = 0 ; 
	while (1) {
		pb_status = PB_read(portA , 0) ;
		if (pb_status == 1) {
			// give the semaphore 
			xSemaphoreGive(PB_SEM) ; 
		}
	}
}