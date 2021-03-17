#include <linux/module.h> // module_init, ...
#include <linux/kernel.h> // printk
#include <linux/init.h> //__init, __exit
#include <linux/sched.h>
#include <linux/init_task.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dmitry Kulikov");
MODULE_DESCRIPTION("Lab3");


/* Init-функция, вызываемая при загрузке модуля */
static int __init my_module_init(void) {
	printk(KERN_INFO "LAB3: Module is loaded. Hello world!\n");
	struct task_struct *task = &init_task;

	do {
		printk(KERN_INFO "LAB3: ---%s-%d, parent %s-%d", task->comm, task->pid, task->parent->comm, task->parent->pid);
	} while ((task = next_task(task)) != &init_task);

	printk(KERN_INFO "LAB3: ---%s-%d, parent %s-%d", current->comm, current->pid, current->parent->comm, current->parent->pid);


	return 0;
}

/* функция, вызываемая при выгрузке модуля */
static void __exit my_module_exit(void) {
	printk(KERN_INFO "LAB3: Module is unloaded. Good bye.\n");
}


/* Ядру сообщаются названия функций, вызываемых при загрузке и выгрузке модуля */
module_init(my_module_init);
module_exit(my_module_exit);