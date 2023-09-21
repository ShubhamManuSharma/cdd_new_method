#include "header.h"
#include "default.h"
#include "declaration.h"
//#include "operation.h"

ssize_t writeDevice(struct file *filep, const char __user  *ubuff, size_t size, loff_t *loff)
{
	Dev *ldev;
	Item *curr;
	ssize_t wsize, lsize;
	int nret,i,l, no_of_reg;
	ssize_t noctw, nocsw;
	wsize = 0;
	#ifdef DEBUG
	printk(KERN_INFO "%s Begin, size to be write : [%ld] bytes\n",__func__, size);
        #endif
	if (size == 0)
	{
        	printk(KERN_INFO "%s: Nothing for Writing \n",__func__);
		return 0;	
	}
	ldev = (Dev *)filep->private_data;
	if(!ldev)
	{
        	printk(KERN_ERR "%s: ERROR Device Not Found for Writing \n",__func__);
		goto OUT;	
	}

	/*Max size can be written, noctw: no of char to write*/
	if(size > ldev->size_of_device)
	{
		noctw = lsize = ldev->size_of_device;
	}
	else
	{
		noctw = lsize = size;
	}
	curr = create_scull(lsize, ldev);
	if(!curr)
	{
		printk(KERN_ERR "%s Item memory not found\n",__func__);
		goto OUT;
	}
	if(curr == NULL)
	{
		printk(KERN_ERR "%s Item memory not found!! head -> next is null\n",__func__);
		goto OUT;
	}
#ifdef DEBUG
	printk(KERN_INFO "%s current headp found.. moving for write : no of item : %d\n",__func__, no_of_item);
#endif
	no_of_reg = lsize/ldev->size_of_quant;
	if(lsize % ldev->size_of_quant)
	{
		no_of_reg++;
	}


	curr = curr->next;		// data memory is present after head, so curr should point to head next	
	for(nocsw = i = l= 0; l < no_of_reg; l++)
	{
		if(noctw >= ldev->size_of_quant)
		{
			noctw = ldev->size_of_quant;
		}	
		nret = copy_from_user(curr->data[i], ubuff+nocsw, noctw);	
		if(nret < 0)
		{
			printk(KERN_ERR "%s ERROR Copy_from_user \n",__func__);
			goto OUT;
		}
#ifdef SHUBH
		printk(KERN_INFO "%s Copy_from_user success Before calculate : [%d] bytes write, nocsw [%ld], remain [%ld]  \n",__func__, nret,nocsw,noctw);
#endif
		nocsw += noctw;
		noctw = lsize - nocsw;
		if(i == ldev->no_of_quant -1)
		{
			curr = curr->next;
			i=0;
		}
	}
	if(noctw < 0)
		nocsw = (nocsw + noctw);

	ldev->size_of_data = size_of_data = nocsw;
        #ifdef DEBUG
        printk(KERN_INFO "%s End: write [%ld] bytes success \n",__func__, nocsw);
        #endif
#if 0
#endif
        return nocsw;
OUT:
        printk(KERN_ERR "%s ERROR End \n",__func__);
	return -1;
}

