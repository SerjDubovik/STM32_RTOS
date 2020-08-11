
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



#define F_CPU 8000000UL


//код обработки ошибок при создании задач
#define	ERROR_ACTION(CODE,POS)		do{}while(0)




// Задача моргалка. Просто так. Мигает диодиком
void vBlinker (void *pvParameters)
{

	RCC->APB2ENR 	|= RCC_APB2ENR_IOPCEN;

	//Конфигурирование GPIOC.13	красный светик на плате
	GPIOC->CRH &= ~GPIO_CRH_MODE13;   			// очистить разряды MODE
	GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// очистить разряды CNF
	GPIOC->CRH |=  GPIO_CRH_MODE13;   			// выход, 50MHz
	GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// общего назначения, симметричный


	while(1)
	{


		GPIOC->BSRR = GPIO_BSRR_BR13;
		vTaskDelay(400);
		GPIOC->BSRR = GPIO_BSRR_BS13;
		vTaskDelay(200);

	} // безконечный цикл задачи vBlinker
}




// Задача обеспечивает связь по протоколу модбас через уарт
void vModBus_slave (void *pvParameters)
{



	while(1)
	{
		vTaskDelay(1);
	}	// бесконечный цикл задачи vModBus_slave

} // закрывает задачу vModBus_slave






int main(void)
{

	SystemInit();


	if(pdTRUE != xTaskCreate(vBlinker,"Blinker", 	configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL))
		{
			ERROR_ACTION(TASK_NOT_CREATE,0);
		}


	if(pdTRUE != xTaskCreate(vModBus_slave,"ModBus Slave", 	configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 10, NULL))
		{
			ERROR_ACTION(TASK_NOT_CREATE,0);
		}



	vTaskStartScheduler();						// Запускаем диспетчер и понеслась.


}	// скобочка мейна



