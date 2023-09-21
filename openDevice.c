#include "header.h"
#include "default.h"
#include "declaration.h"
//#include "operation.h"


int openDevice(struct inode *inode, struct file *filep)
{
	Dev *ldev;
	#ifdef DEBUG
	printk(KERN_INFO "%s Begin \n",__func__);
	#endif
	ldev = container_of(inode->i_cdev, Dev, c_dev);
	if(!ldev)
	{
		printk(KERN_ERR "%s ERROR: container_of() failure \n",__func__);
		goto OUT;
	}
	filep->private_data = ldev;
	if( (filep->f_flags & O_ACCMODE) == O_WRONLY )
	{
		filep->f_pos = 0;	
	}
	else if( (filep->f_flags & O_ACCMODE) == O_RDONLY )
	{
		printk(KERN_INFO "%s Device Open in readonly \n",__func__);
	}
/*	else if( (filep->f_flags & O_ACCMODE) == O_APPEND )
	{
		printk(KERN_INFO "%s Device Open in append only \n",__func__);
	}
*/
	else
	{
		printk(KERN_INFO "%s Invalid device mode \n",__func__);
		goto OUT;
	}

	#ifdef DEBUG
	printk(KERN_INFO "%s End \n",__func__);
	#endif
	
	return 0;
OUT:
	#ifdef DEBUG
	printk(KERN_ERR "%s ERROR End \n",__func__);
	#endif
	return -1;
}
