#include "header.h"
#include "default.h"
#include "declaration.h"
//#include "operation.h"


int releaseDevice(struct inode *inode, struct file *file)
{
        #ifdef DEBUG
	printk(KERN_INFO "%s Begin \n",__func__);
        #endif

        #ifdef DEBUG
        printk(KERN_INFO "%s End \n",__func__);
        #endif
        return 0;
}

