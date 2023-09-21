#include "header.h"
#include "default.h"
#include "declaration.h"
#include "operation.h"

int majorNo;
int minorNo;
int nod;
dev_t devid, devno;
Dev *dev;
int size_of_device, no_of_quant, no_of_item, size_of_quant, size_of_data;

module_param(nod, int, S_IRUGO);

#ifdef MODULE_PARAM
module_param(size_of_device, int, S_IRUGO);
module_param(no_of_quant, int, S_IRUGO);
module_param(size_of_quant, int, S_IRUGO);
#endif


static int __init myDevInit(void)
{
	int ret,i;
#ifdef DEBUG
	printk(KERN_INFO "%s Begin\n",__func__);
#endif
	majorNo = MAJORNO; 
	minorNo = MINORNO;
	//nod = NOD;
	/*register Driver*/
	if(alloc_chrdev_region(&devid,minorNo,nod,CDD_NAME)<0)	
	{
		printk(KERN_ERR "%s: ERROR: Device Registeration filed, register_chrdev\n",__func__);
		return -1;
	}
	majorNo = MAJOR(devid);
	minorNo = MINOR(devid);
#ifdef DEBUG
	printk(KERN_INFO "%s: Device Registeration Success, register_chrdev Major No : %d, Minor No : %d \n",__func__,majorNo, minorNo);
#endif
#ifndef MODULE_PARAM
	size_of_device = DEVSIZE;
	no_of_quant    = NOOFREG; 
	size_of_quant  = SIZEOFREG;
#endif
	dev = (Dev *) kmalloc(sizeof(Dev)*nod, GFP_KERNEL);
	if(!dev)
	{
		printk(KERN_ERR "%s Device memory allocation failed\n",__func__);
		return -1;
	}
	memset(dev, '\0', sizeof(Dev)*nod);
	
	printk(KERN_INFO "%s size_of_device: %d\n",__func__,size_of_device );
	printk(KERN_INFO "%s no_of_quant   : %d\n",__func__,no_of_quant    );
	printk(KERN_INFO "%s size_of_quant : %d\n",__func__,size_of_quant  );

	for(i=0; i<nod; i++)
	{
		// device initialization
		cdev_init(&dev[i].c_dev,&fops);
		dev[i].c_dev.owner = THIS_MODULE;
		dev[i].size_of_device = size_of_device;
		dev[i].no_of_quant    = no_of_quant;
		dev[i].size_of_quant  = size_of_quant;
		dev[i].c_dev.ops = &fops;
		devno = MKDEV(majorNo,i);
		// add device
		ret = cdev_add(&dev[i].c_dev, devno,1);
		if(ret == -1)
		{
			printk(KERN_ERR "%s cdev_add failed\n",__func__);
			return -1;
		}
//		minorNo = MINOR(devno);
#ifdef DEBUG
		printk(KERN_INFO "%s: Device Registeration Success, Minor No : %d \n",__func__,MINOR(dev[i].c_dev.dev));
#endif
	}
#ifdef DEBUG
	printk(KERN_INFO "%s End\n",__func__);
#endif
	return 0;
}

module_init(myDevInit);
