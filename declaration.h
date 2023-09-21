extern dev_t devid, devno;
extern int majorNo, minorNo, nod;
extern int size_of_device, no_of_quant, no_of_item, size_of_quant, size_of_data;

typedef struct Item
{
	void **data;
	struct Item *next;
}Item;


// user define data structure, will describe the hardware device architecture
typedef struct Device
{
	struct cdev c_dev;		// Kernel structure
	Item *headp;	
	int size_of_device;		// device size
	int no_of_quant;		//no of register
	int size_of_quant;		//sizeof register
	int size_of_data;	        // data size 
}Dev;

extern Dev *dev;


int openDevice(struct inode *, struct file*);
int releaseDevice(struct inode *, struct file*);
ssize_t writeDevice(struct file*filep, const char  __user *ubuff, size_t size, loff_t *loff);
ssize_t readDevice(struct file*filep, char  __user *ubuff, size_t size, loff_t *loff);
Item *create_scull(ssize_t lsize, Dev *ldev);
