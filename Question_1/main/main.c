#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>

BaseType_t result;
QueueHandle_t queue;
TaskHandle_t taskh1,taskh2,taskh3,taskh4,taskh5;

void task1(void *pv)
{
	while(1)
	{
		printf("Task1\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task2(void *pv)
{
	while(1)
	{
		printf("Task2\n");
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
}

void task3(void *pv)
{
	while(1)
	{
		printf("Task3\n");
		vTaskDelay(5000/portTICK_PERIOD_MS);
	}
}

void task4(void *pv)
{
	int task4_data=0;
	while(1)
	{
		task4_data++;
		//printf("Task4\n");
		xQueueSend(queue,&task4_data,portMAX_DELAY);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task5(void *pv)
{
	int task5_data;
	while(1)
	{
		xQueueReceive(queue,&task5_data,portMAX_DELAY);
		printf("Task 5 Received Data: %d\n",task5_data);
		//vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int app_main()
{
	queue=xQueueCreate(1,sizeof(int));

	result=xTaskCreate(task1,"Task1",2048,NULL,5,&taskh1);
	if(result!=pdPASS)
	{
		printf("Task1 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task2,"Task2",2048,NULL,6,&taskh2);
	if(result!=pdPASS)
	{
		printf("Task2 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task3,"Task3",2048,NULL,7,&taskh3);
	if(result!=pdPASS)
	{
		printf("Task3 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task4,"Task4",2048,NULL,8,&taskh4);
	if(result!=pdPASS)
	{
		printf("Task4 Creation Failed\n");
		return 0;
	}

	result=xTaskCreate(task5,"Task5",2048,NULL,9,&taskh5);
	if(result!=pdPASS)
	{
		printf("Task5 Creation Failed\n");
		return 0;
	}

	return 0;
}
