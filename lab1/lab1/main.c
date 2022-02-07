/*
 * lab1.c
 *
 * Author : Mahmoud Ayoub
 */ 

/*
	Example for : Mutual Exclusion and shared resources
	using "Mutex" to avoid priority inversion problem in case of "Binary Semaphore"
*/

/*
	NOTES on using Mutex : 
	>> must set configUSE_MUTEXES to 1 in FreeRTOS.h
*/


#include <avr/io.h>
#include "./RTOS/FreeRTOS.h"
#include "./RTOS/task.h"
#include "./RTOS/FreeRTOSConfig.h"
#include "./RTOS/semphr.h"
#include "./HAL/LCD/LCD.h"

#include <util/delay.h>

/* Define Tasks Priorities */
#define  TASK1_PRIORITY (1)
#define  TASK2_PRIORITY (1)

/*tasks codes prototypes */
 void task1_code(void* pvParamter);
 void task2_code(void* pvParamter);
 
/* create semaphore for shared resource (LCD) */
// xSemaphoreHandle LCD_SEM ; 
 
/* create Mutex for shared resource (LCD) */
 xSemaphoreHandle LCD_MUTEX ;


int main(void)
{
	/*initialize LCD*/
	LCD_init();	
	
	// vSemaphoreCreateBinary(LCD_SEM) ;
	LCD_MUTEX = xSemaphoreCreateMutex();

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
	int ret1 = 0 ; 

	while(1)
	{
		ret1 = xSemaphoreTake(LCD_MUTEX , portMAX_DELAY) ;
		if (ret1 == 1) {
			LCD_clear() ;
			LCD_send_char('1');
			_delay_ms(2000) ;
			LCD_clear() ;
			
			LCD_send_str("1 will release") ;
			_delay_ms(2000) ;
			LCD_clear() ;
		}
		else {
			LCD_clear() ;
			LCD_send_str("1 after time out");
			_delay_ms(2000) ;
			LCD_clear() ;

		}
		LCD_send_str("1 will block") ;
		_delay_ms(2000) ;
		LCD_clear() ;
		xSemaphoreGive(LCD_MUTEX) ;
		vTaskDelay(10) ; 
	}
		
}

/*Task 2 Code*/
 void task2_code(void* pvParamter)
{
	int ret1 = 0 ; 
	
	while(1)
	{
		ret1 = xSemaphoreTake(LCD_MUTEX , portMAX_DELAY) ;
		if (ret1 == 1) {
			LCD_clear() ;
			LCD_send_char('2');
			_delay_ms(2000) ;
			LCD_clear() ;
			
			LCD_send_str("2 will release") ;
			_delay_ms(2000) ;
			LCD_clear() ;
		}
		else {
			LCD_clear() ;
			LCD_send_str("2 after time out");
			_delay_ms(2000) ;
			LCD_clear() ;
		}
		LCD_send_str("2 will block") ;
		_delay_ms(2000) ;
		LCD_clear() ;
		xSemaphoreGive(LCD_MUTEX) ;
		vTaskDelay(10) ;
	}
}

