#include <linux/init.h> 
#include <linux/module.h> 
#include "md.h" 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garasev");

static int __init md_init(void) 
{ 
   printk("LAB3: module md3 start!\n"); 
   printk("LAB3: data string exported from md1 : %s\n", md1_data); 
   //printk("LAB3: try ty use no-exported md1_noexport() is : %s\n", md1_noexport()); 
   //printk("LAB3: try to use local md1_local() is : %d\n", md1_local()); 
   return -1; 
} 	

static void __exit md_exit(void) 
{ 
   printk("LAB3: module md3 unloaded!\n"); 
} 

module_init(md_init); 
module_exit(md_exit);
