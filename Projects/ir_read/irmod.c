#include <linux/miscdevice.h> 
#include <linux/delay.h> 
#include <asm/irq.h> 
#include <mach/regs-gpio.h> 
#include <mach/hardware.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/mm.h> 
#include <linux/fs.h> 
#include <linux/types.h> 
#include <linux/delay.h> 
#include <linux/moduleparam.h> 
#include <linux/slab.h> 
#include <linux/errno.h> 
#include <linux/ioctl.h> 
#include <linux/cdev.h> 
#include <linux/string.h> 
#include <linux/list.h> 
#include <linux/pci.h> 
#include <asm/uaccess.h> 
#include <asm/atomic.h> 
#include <asm/unistd.h>  
#include <mach/map.h> 
#include <mach/regs-clock.h> 
#include <mach/regs-gpio.h> 
#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-n.h> 
 
#define DEVICE_NAME "irdrv" 
 
static int ir_open(struct inode *inode, struct file *filp) 
{

	// initail 6410 GPN12 as input
    writel(readl(S3C64XX_GPNCON)&~0x3000000,S3C64XX_GPNCON); 
	return 0;
}

static int ir_release(struct inode *inode, struct file *filp)
{

   return 0;
}


 
static unsigned int ir_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) 
{ 
    udelay(cmd);
	if (readl(S3C64XX_GPNDAT)&0x1000)
	    return 1 ;  
	else return 0;
} 
 
static struct file_operations dev_fops = { 
	.owner = THIS_MODULE, 
	.unlocked_ioctl = ir_ioctl, 
	.open = ir_open,
	.release = ir_release,
}; 
 
static struct miscdevice misc = { 
	.minor = MISC_DYNAMIC_MINOR, 
	.name = DEVICE_NAME, 
	.fops = &dev_fops, 
}; 
 
static int dev_init(void) 
{ 
   printk("irdrv driver module installed\n");
   return misc_register(&misc);
} 

 
static void dev_exit(void) 
{ 
 
	misc_deregister(&misc); 
	printk("irdrv driver module removed\n");
}

module_init(dev_init); 
module_exit(dev_exit); 
MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("CHYA"); 

