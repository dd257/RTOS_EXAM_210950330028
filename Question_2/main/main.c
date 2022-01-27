#include<stdio.h>
#include<stdlib.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

BaseType_t result;
TaskHandle_t taskh1,taskh2,taskh3;
TimerHandle_t timer;

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

void timer_callback(TimerHandle_t timer)
{
	printf("Call back function\n");
	xTimerStop(timer,0);
}

void task3(void *pv)
{
	while(1)
	{
		printf("Task3\n");
	
		if(timer==NULL)
		{
			timer=xTimerCreate("Timer Task",pdMS_TO_TICKS(10000),pdFALSE,NULL,timer_callback);
			if(timer==NULL)
			{
				printf("Task Timer 3 Creation Failed\n");
				exit(0);
			}
			xTimerStart(timer,0);
		}

		vTaskDelay(5000/portTICK_PERIOD_MS);
	}
}

int app_main()
{
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

	result=xTaskCreate(task3,"Task2",2048,NULL,7,&taskh3);
	if(result!=pdPASS)
	{
		printf("Task3 Creation Failed\n");
		return 0;
	}

	return 0;
}
