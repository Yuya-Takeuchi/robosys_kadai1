// SPDX-License-Identifier: GPL-3.0-only
// Copyright (C) 2020 Yuya Takeuchi. All rights reserved.

#include <linux/module.h>                                                        
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>                                                         
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Yuya Takeuchi & Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos){
	        char c;
		int s = 0,h = 0,j = 0;
		if(copy_from_user(&c,buf,sizeof(char)))
			return -EFAULT;

		if(c == '1'){
		while(s < 1)          
		 gpio_base[7] = 1 << 25;			
	  	 msleep(200);
	         gpio_base[10] = 1 << 25;
	         ssleep(1);		  		  
		 s++;	  
		}
		else if (c == '2'){
		while(s < 2){	
		 gpio_base[7] = 1 << 25;                 
		 msleep(200);	 
	         gpio_base[10] = 1 << 25;
      	         ssleep(1);
	         s++;
		}
		}   
		else if(c == '3'){
		while(s < 3){ 
		   gpio_base[7] = 1 << 25;
		   msleep(200);             
		   gpio_base[10] = 1 <<25;
		   ssleep(1);            
		   s++;	
		   }
		}      
		else if(c == '4'){
		while(h < 2){
		 while(s < 3){
	           gpio_base[7] = 1 << 25;
	           ssleep(0.5);
	           gpio_base[10] = 1 << 25;
	           ssleep(1);
	           s++;
	           }
	           ssleep(1);
	           s = 0;
	           h++;
	        }
                while(j < 7){
                 gpio_base[7] = 1 << 25;
                 ssleep(0.5);
                 gpio_base[10] = 1 << 25;
                 ssleep(1);
                 j++;
                 }
               }
	        return 1;
}

static struct file_operations led_fops = {
	        .owner = THIS_MODULE,
	        .write = led_write
};



static int __init init_mod(void)
{
       	int retval;
	retval = alloc_chrdev_region(&dev, 0, 1, "myled"):	
        
	if(retval < 0){
           printk(KERN_ERR "alloc_chrdev_region failed.\n");
	   return retval;								        }
           
	   printk(KERN_INFO "%s is loaded.major:%d\n",_FILE_,MAJOR(dev));
           cdev_init(&cdv, &led_fops);
           retval = cdev_add(&cdv, dev, 1);
	   
	   if(retval < 0){
		 printk(KERN_ERR "cdev_add failed. major:%d. minor:%d\n", MAJOR(dev),MINOR(dev));
		 return retval;  
	 }			         
	 
	 cls = class_create(THIS_MODULE, "myled");
	 if(IS_ERR(cls)){
		 printk(KERN_ERR "class_create failed.");
		 return PTR_ERR(cls);	        
	 }      
	 device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
	 gpio_base = ioremap_nocache(0xfe200000, 0xA0);		         
	 const u32 led = 25;
	 const u32 index = led/10;
	 const u32 shift = (led%10)*3;
	 const u32 mask = ~(0x7 << shift); //~は反転の意味
	 gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
         return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);		        
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
	iounmap(gpio_base);
}

module_init(init_mod);
module_exit(cleanup_mod);
