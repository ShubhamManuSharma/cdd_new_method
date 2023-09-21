#include "header.h"
#include "declaration.h"

void *exitDev(void *);
void *openDev(void *);
void *releaseDev(void *);
void *mainMenu(void *);
void *readDev(void *);
void *writeDev(void *);
void* (*fptr[NOF])(void *);

int init()
{
	(fptr[0]) = exitDev;	
	(fptr[1]) = openDev;	
	(fptr[2]) = releaseDev;
	(fptr[3]) = mainMenu;	
	(fptr[4]) = readDev;	
	(fptr[5]) = writeDev;	
	return 1;	
}
