
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



#define F_CPU 8000000UL


//��� ��������� ������ ��� �������� �����
#define	ERROR_ACTION(CODE,POS)		do{}while(0)




// ������ ��������. ������ ���. ������ ��������
void vBlinker (void *pvParameters)
{

	RCC->APB2ENR 	|= RCC_APB2ENR_IOPCEN;

	//���������������� GPIOC.13	������� ������ �� �����
	GPIOC->CRH &= ~GPIO_CRH_MODE13;   			// �������� ������� MODE
	GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// �������� ������� CNF
	GPIOC->CRH |=  GPIO_CRH_MODE13;   			// �����, 50MHz
	GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// ������ ����������, ������������


	while(1)
	{


		GPIOC->BSRR = GPIO_BSRR_BR13;
		vTaskDelay(400);
		GPIOC->BSRR = GPIO_BSRR_BS13;
		vTaskDelay(200);

	} // ����������� ���� ������ vBlinker
}




// ������ ������������ ����� �� ��������� ������ ����� ����
void vModBus_slave (void *pvParameters)
{



	while(1)
	{
		vTaskDelay(1);
	}	// ����������� ���� ������ vModBus_slave

} // ��������� ������ vModBus_slave






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



	vTaskStartScheduler();						// ��������� ��������� � ���������.


}	// �������� �����



