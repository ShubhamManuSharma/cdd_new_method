#include "header.h"
#include "default.h"
#include "declaration.h"
//#include "operation.h"


ssize_t readDevice(struct file *filep, char __user  *ubuff, size_t size, loff_t *loff)
{
	Dev *ldev;
	size_t noctr, nocsr, lsize;
	Item *curr = NULL;
	unsigned int no_of_reg;
	int i,l, not=0;
	#ifdef DEBUG
	printk(KERN_INFO "%s Begin Read Device \n",__func__);
        #endif

	ldev = (Dev *)filep->private_data;
	if(!ldev)
	{
        	printk(KERN_ERR "%s: ERROR Device Not Found for Reading \n",__func__);
		goto OUT;	
	}
	if((filep->f_flags & O_ACCMODE) != O_RDONLY )
	{
        	printk(KERN_ERR "%s: ERROR Device Mode is Not Read\n",__func__);
		goto OUT;	
	}
	if (size == 0)
	{
        	printk(KERN_INFO "%s: Nothing for Writing \n",__func__);
		return 0;	
	}

	if(size > size_of_device)
		noctr = lsize = size_of_device;
	else
		noctr = lsize = size;

	if(lsize > ldev->size_of_data)
		lsize = ldev->size_of_data;

	if(ldev->headp != NULL)
	{
		curr = ldev->headp;
	}
	else
	{
        	printk(KERN_INFO "%s Nothing to read, device emplty \n",__func__);
		goto OUT;	
	}
	
	no_of_reg = lsize / ldev->size_of_quant;
	if(lsize % ldev->size_of_quant)
		no_of_reg++;
       
        printk(KERN_INFO "%s No of register [%d], data to be read : [%ld] noctr : {%ld} \n",__func__, no_of_reg, lsize,noctr);
	curr = curr->next;
	nocsr =0;
        for(i=l=0; l < no_of_reg; l++)
	{
		if(noctr >= ldev->size_of_quant)
			noctr = ldev->size_of_quant;

		not = copy_to_user(ubuff+nocsr, curr->data[i], noctr);	
		if(not < 0)
		{
			printk(KERN_ERR "%s ERROR Copy_to_user \n",__func__);
			goto OUT;
		}
		nocsr = nocsr + ldev->size_of_quant - not;
		noctr = lsize - nocsr;
#ifdef SHUB
		printk(KERN_INFO "%s Copy_to_user successfully read, [%ld] bytes : remain : [%ld] \n",__func__,nocsr, noctr);
#endif
		if(i == ldev->no_of_quant -1)
		{
			curr = curr->next;
			i =0;
		}
		else
		{
			i++;
		}
	}	

#ifdef DEBUG
        printk(KERN_INFO "%s End, [%ld] bytes read Successfully\n",__func__,nocsr);
#endif
        return nocsr;
OUT:
        printk(KERN_ERR "%s ERROR End \n",__func__);
	return -1;
}

