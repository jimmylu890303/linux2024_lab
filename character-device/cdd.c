#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h> 

#define CLASS_NAME "cdd"
#define DEVICE_NAME "cddchar"

/* LICENSE */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jimmy");
MODULE_DESCRIPTION("A simple Linux char driver");
MODULE_VERSION("0.1");

static int majorNumber;    
static struct class*  cddClass  = NULL; ///< The device-driver class struct pointer
static struct device* cddDevice = NULL; ///< The device-driver device struct pointer
static char   message[256] = {0};
static short  size_of_message;
static int    numberOpens = 0;

static int cdd_open(struct inode *inode, struct file *filp) 
{
    numberOpens++;
    printk(KERN_INFO "CCD: Device has been opened %d time(s)\n",numberOpens);
    return 0;
}

static int cdd_close(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "CCD: cdd_close\n");
    return 0;
}

static ssize_t cdd_read(struct file *filp, char *buffer, size_t length, loff_t* offset)
{
   int error = 0;
   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   error = copy_to_user(buffer, message, size_of_message);

   if (error==0){            // if true then have success
      printk(KERN_INFO "CCD: Sent %d characters to the user\n", size_of_message);
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "CCD: Failed to send %d characters to the user\n", error);
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}

static ssize_t cdd_write(struct file *filp, const char *buffer, size_t len, loff_t* offset)
{
    if (!buffer) {
        printk(KERN_ERR "CCD: Null buffer pointer\n");
        return -EINVAL; 
    }

    // Test Application is run on the user space
    // need to copy the data to kernel space 
    if (copy_from_user(message, buffer, len)) {
        printk(KERN_ERR "CCD: Failed to copy data from user space\n");
        return -EFAULT; 
    }

    size_of_message = strlen(message);
    message[len] = '\0';
    printk(KERN_INFO "CCD: Received: %s from user space\n", message);
    return len;
}

static struct file_operations cdd_fops = {
    .owner = THIS_MODULE,
    .open = cdd_open,
    .release = cdd_close,
    .read = cdd_read,
    .write = cdd_write,
};

static int __init cdd_init(void)
{
    printk(KERN_INFO "Character Device Driver LKM Init\n");
    
    // Try to dynamically allocate a major number for the device
    majorNumber = register_chrdev(0, DEVICE_NAME, &cdd_fops);
    if (majorNumber<0){
      printk(KERN_ALERT "CCD failed to register a major number\n");
      return majorNumber;
    }
    printk(KERN_INFO "CDD: registered correctly with major number %d\n", majorNumber);
    
    // Register the device class
    cddClass = class_create(CLASS_NAME);
    if (IS_ERR(cddClass)){                // Check for error and clean up if there is
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(cddClass);          // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "CDD: device class registered correctly\n");

    // Register the device driver
    cddDevice = device_create(cddClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(cddDevice)){               // Clean up if there is an error
        class_destroy(cddClass);           // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(cddDevice);
    }
    printk(KERN_INFO "CDD: device class created correctly\n"); // Made it! device was initialized
    return 0;
}
static void __exit cdd_exit(void)
{
    device_destroy(cddClass, MKDEV(majorNumber, 0));     // remove the device
    class_unregister(cddClass);                          // unregister the device class
    class_destroy(cddClass);                             // remove the device class
    unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
    printk(KERN_INFO "Character Device Driver Exit\n");
}

module_init(cdd_init); /* probe entry */
module_exit(cdd_exit); /* exit entry */