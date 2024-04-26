#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static char *name = "world";        ///< An example LKM argument -- default value is "world"
module_param(name, charp, S_IRUGO); ///< Param desc. charp = char ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter description


static int hello_init(void) {
    printk(KERN_INFO "Hello, %s\n", name);
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_INFO "Goodbye, cruel %s\n", name);
}

module_init(hello_init);
module_exit(hello_exit);
