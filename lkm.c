/*
 * 		lkm.c - Loadable Kernel Module that prints output to the syslog
 *
 * 		Background: http://tldp.org/HOWTO/Module-HOWTO/x73.html
 */
/*
 * Defining __KERNEL__ and MODULE allows us to access kernel-level code not
 * usually available to userspace programs.
 */
#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

/*
 * Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h
 * is needed for KERN_INFO.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void) {
	printk(KERN_INFO "Hello world!\n");
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL"); /* to avoid tainted flag */
MODULE_AUTHOR("FH BI Minden"); /* Who wrote this module? */
MODULE_DESCRIPTION("Beispieltreiber"); /* What does this module do */




