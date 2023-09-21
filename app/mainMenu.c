#include "header.h"
#include "declaration.h"

void *mainMenu(void *arg)
{
	int i;
	int ret;
	pthread_t thid;
	char mode;

	printf("0: Exit Application \n");
	printf("1: Open Device \n");
	printf("2: Close Device \n");
	printf("3: Device Menu\n");
	printf("4: Read Device\n");
	printf("5: Write Device\n");
	printf(" Please Enter Your Choice\n");
	scanf("%d",&i);

	if(i == 0)
	{
		ret = pthread_create(&thid, NULL, fptr[i],0);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
	if(i ==1)
	{
		printf("Enter Mode to open device:\n For Read : 'r'\n For Write : 'w'\n");
		getchar();
		scanf("%c",&mode);
		ret = pthread_create(&thid, NULL, fptr[i],(void *)&mode);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
	if(i == 2)
	{
		ret = pthread_create(&thid, NULL, fptr[i],0);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
	if(i == 3)
	{
		mainMenu((void *)&i);
	}
	if(i == 4)
	{
		ret = pthread_create(&thid, NULL, fptr[i],0);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
	if(i == 5)
	{
		ret = pthread_create(&thid, NULL, fptr[i],0);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
}
