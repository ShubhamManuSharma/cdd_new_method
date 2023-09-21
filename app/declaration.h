#define NOF 6

int init();
extern void *mainMenu(void *);
extern void *exitDev(void *);
extern void *openDev(void *);
extern void *releaseDev(void *);
extern void *readDev(void *);
extern void *writeDev(void *);
extern void* (*fptr[NOF])(void *);

extern int fd;
