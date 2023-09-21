#include "header.h"
#include "default.h"
#include "declaration.h"
//#include "operation.h"

Item *create_scull(ssize_t lsize, Dev *ldev)
{
	Item *itemp=NULL;
	int size_of_item, no_of_reg;
	int itemcount=0, quant=0;
	int i,l;
        printk(KERN_INFO "%s: Begin : locale size: [%ld]\n",__func__, lsize);
	if(!ldev)
	{
        	printk(KERN_ERR "%s: ERROR Device Not Found for Writing \n",__func__);
		goto OUT;	
	}
	
	size_of_item = ldev->no_of_quant * ldev->size_of_quant;			// size of 1 item
	no_of_item = lsize/size_of_item;					// total no of item
	if(lsize % size_of_item)
	{
		no_of_item++;
	}

	for(i=0;i<=no_of_item;i++)
	{
		if(i ==0)
		{
			itemp = ldev->headp = (Item *) kmalloc(sizeof(Item),GFP_KERNEL);
			if(!ldev->headp)
			{
				printk(KERN_ERR "%s Item memory allocation failed\n",__func__);
				goto OUT;
			}
			printk(KERN_INFO "%s Head Item memory allocation\n",__func__);
			memset(ldev->headp, '\0', sizeof(Item));
		}
		else
		{
			itemp->next =  (Item *) kmalloc(sizeof(Item),GFP_KERNEL);
			if(!itemp->next)
			{
				printk(KERN_ERR "%s Item memory allocation failed\n",__func__);
				goto OUT;
			}
			itemp = itemp->next;
		
			itemp->data = (void **)kmalloc(sizeof(char *)*ldev->no_of_quant, GFP_KERNEL); 
			if(!itemp->data)
			{
				printk(KERN_ERR "%s Item memory allocation failed\n",__func__);
				goto OUT;
			}
			memset(itemp->data,'\0', sizeof(char *)*ldev->no_of_quant);
			itemcount++;
		}
	}

	no_of_reg = lsize/ldev->size_of_quant;
	if(lsize % ldev->size_of_quant)
	{
		no_of_reg++;
	}

        itemp = ldev->headp->next;
        for( l = i = 0; l < no_of_reg; l++)
        {
                itemp->data[i] = kmalloc(size_of_quant, GFP_KERNEL);
                if(!itemp->data[i])
                {
                        printk(KERN_ERR "%s: ERROR: kmalloc() failure.\n",__func__);
                        goto OUT;
                }
                if(i == no_of_quant-1)
                {
                        itemp = itemp->next;
                        i = 0;
                }
                else
                        i++;

		quant++;
        }


        printk(KERN_INFO "%s: End : Scull Create Success: Item generated : %d, no_of reg/quant : %d\n",__func__,itemcount,quant);
	return ldev->headp;	
OUT:
	printk(KERN_ERR "%s End : Item memory allocation failed\n",__func__);
	return NULL;
}

