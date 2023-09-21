#include "header.h"
#include "declaration.h"

#define FILES  "myfile"
#define FILES1  "/dev/mycddfile"

#define BUFSIZE 1000
int fd; 

void *exitDev(void *res)
{
	printf("%s : Begin \n",__func__);
	exit(1);
	printf("%s : End \n",__func__);
}

void *readDev(void *res)
{
	printf("%s : Begin \n",__func__);
	char *buff=NULL;
	int fd = *(int *)res;
	ssize_t size;
	int i, len;
	
	printf("%s fd : %d\n",__func__, fd);
	buff = (char *)malloc(sizeof(char)*BUFSIZE);
	if(!buff)
	{
		printf("malloc error");
		exit(-1);	
	}
	memset(buff, '\0', BUFSIZE);

	printf("%s : Begin : [%d] line \n",__func__,__LINE__);

	size = read(fd, buff, BUFSIZE);
	if(size < 0)
	{
		printf("read error");
		return NULL;
	}
	len = strlen(buff);	
	printf("read data len : %d, size : %d\n",len, size);
	for(i=0; i< len; i++)
	{
		printf("%c",buff[i]);
	}
	printf("\n");

//	close(fd);
	printf("%s : End \n",__func__);
}

void *writeDev(void *res)
{
	printf("%s : Begin \n",__func__);
	char *buff = "Hello Kernel!! I am Shubham Writing my first charecter device Driver";
	//char *buff = "Hello Kernel";
	int len = strlen(buff);
	int ret;
	int fd = *(int *)res;
	ssize_t size;
	size = write(fd, buff, len);
	if(size < 0)
	{
		printf("Write error");
		return NULL;
	}
//	close(fd);
	printf("%s : End \n",__func__);
}

void *openDev(void *res)
{
	printf("%s : Begin \n",__func__);
	char ch;
	pthread_t thid;
	int ret;
	ch = *(char *)res;
	printf("get char mode %c  \n",ch);
	if(ch  == 'w')
	{
		fd = open(FILES1, O_WRONLY);
		if(fd<0)
		{
			perror("file open issue");
		}
		
		ret = pthread_create(&thid, NULL, writeDev,(void *)&fd);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}
	else
	{
		fd = open(FILES1, O_RDONLY);
		if(fd<0)
		{
			perror("file open issue");
		}

		ret = pthread_create(&thid, NULL, readDev,(void *)&fd);
		if(ret == -1)
		{
			perror("pthread_crete_failed");
			(*fptr[0])((void *)"FAILURE");
		}
	}	
	printf(" fd : %d : %s\n",fd,FILES1);
	printf("%s : End \n",__func__);
}

void *releaseDev(void *res)
{
	printf("%s : Begin \n",__func__);
	int ret;
	ret = close(fd);
	printf("Closed file : %d\n",ret);
	printf("%s : End \n",__func__);
}


