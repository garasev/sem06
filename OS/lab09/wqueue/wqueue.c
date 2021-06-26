#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garasev");

#define IRQ_NUM 1
#define IRQ_NAME "keyboard"
#define WQ_NAME "keyboard_wq"
#define ITER_COUNT 100000000


static struct workqueue_struct *my_wq;

typedef struct
{
  struct work_struct work;
  int work_num; // номер работы
} my_work_t;

// Структуры, описывающие две работы
static my_work_t *work_1;
static my_work_t *work_2;


static int shared_counter = 0;

struct mutex my_mutex;


static int my_proc_show(struct seq_file *m, void *v)
{
  seq_printf(m, "WQUEUE: In user mode: is work_1 pending - %d, is work_1 pending - %d, shared counter - %d\n",
             work_pending(&(work_1->work)), work_pending(&(work_2->work)), shared_counter);

  return 0;
}

static int my_proc_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "WQUEUE: Called my_proc_open\n");
  return single_open(file, my_proc_show, NULL);
}

static struct proc_ops props = {
    .proc_open = my_proc_open,
    .proc_release = single_release,
    .proc_read = seq_read,
};

void my_func_1(struct work_struct *work)
{
  printk(KERN_INFO "WQUEUE: MY_FUNC_1\n");

  mutex_lock(&my_mutex);
  printk(KERN_INFO "WQUEUE: MUTEX LOCKED\n");

  my_work_t *my_work = (my_work_t *)work;

  // первая работа (поток) вошла в крит секцию
  printk(KERN_INFO "WQUEUE: work_1 get monopoly (work_pending=%d)\n", work_pending(&(my_work->work)));

  // вторая работа заблокирована в это время
  printk(KERN_INFO "WQUEUE: work_2 - work_pending returns %d\n", work_pending(&(work_2->work)));
 
  int i, mul = 0;
  for (i = 0; i < ITER_COUNT; i++)
    mul += i;

  shared_counter++;
  printk(KERN_INFO "WQUEUE: SHARED COUNTER INCREASED BY WORK 1 = %d\n",shared_counter);

  mutex_unlock(&my_mutex);
  printk(KERN_INFO "WQUEUE: MUTEX UNLOCKED\n");
}

void my_func_2(struct work_struct *work)
{
  printk(KERN_INFO "WQUEUE: MY_FUNC_2\n");

  mutex_lock(&my_mutex);
  printk(KERN_INFO "WQUEUE: MUTEX LOCKED\n");

  my_work_t *my_work = (my_work_t *)work;

  // вторая работа (поток) вошла в крит секцию
  printk(KERN_INFO "WQUEUE: work_2 get monopoly (work_pending=%d)\n", work_pending(&(my_work->work)));

  // первая работа заблокирована в это время
  printk(KERN_INFO "WQUEUE: work_1 - work_pending returns %d\n", work_pending(&(work_1->work)));

  int i, mul = 0;
  for (i = 0; i < ITER_COUNT; i++)
    mul += i;

  shared_counter++;
  printk(KERN_INFO "WQUEUE: SHARED COUNTER INCREASED BY WORK 2 = %d\n", shared_counter);

  mutex_unlock(&my_mutex);
  printk(KERN_INFO "WQUEUE: MUTEX UNLOCKED\n");
}


irqreturn_t my_irq_handler(int irq_num, void *dev_id)
{
  if (irq_num == IRQ_NUM)
  {
    if (work_1)
      queue_work(my_wq, (struct work_struct *)work_1);
    if (work_2)
      queue_work(my_wq, (struct work_struct *)work_2);

    return IRQ_HANDLED;
  }
  return IRQ_NONE;
}

static int __init my_init(void)
{
  struct proc_dir_entry *entry;
  entry = proc_create("wqueue", S_IRUGO | S_IWUGO, NULL, &props);
  if (!entry)
  {
    printk(KERN_INFO "WQUEUE: Can't create seq file\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "WQUEUE: Seq file created\n");

  if (request_irq(IRQ_NUM, my_irq_handler, IRQF_SHARED, IRQ_NAME, my_irq_handler))
  {
    printk(KERN_ERR "WQUEUE: Failed to register IRQ handler\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "WQUEUE: IRQ handler registered\n");

  work_1 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
  if (work_1)
  {
    INIT_WORK((struct work_struct *)work_1, my_func_1);
    work_1->work_num = 1;
  }
  else
  {
    printk(KERN_ERR "WQUEUE: Failed alloc\n");
    return -ENOMEM;
  }

  work_2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
  if (work_2)
  {
    INIT_WORK((struct work_struct *)work_2, my_func_2);
    work_2->work_num = 2;
  }
  else
  {
    printk(KERN_ERR "WQUEUE: Failed alloc\n");
  }

  my_wq = create_workqueue(WQ_NAME);
  if (!my_wq)
  {
    free_irq(IRQ_NUM, my_irq_handler);
    printk(KERN_ERR "WQUEUE: Failed to create work queue\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "WQUEUE: Workqueue created\n");

  mutex_init(&my_mutex);

  printk(KERN_INFO "WQUEUE: Module loaded!\n");
  return 0;
}

static void __exit my_exit(void)
{
  free_irq(IRQ_NUM, my_irq_handler);

  flush_workqueue(my_wq);
  destroy_workqueue(my_wq);
  mutex_destroy(&my_mutex);

  if (work_1)
    kfree(work_1);

  if (work_2)
    kfree(work_2);

  remove_proc_entry("wqueue", NULL);
  printk(KERN_INFO "WQUEUE: Module unloaded!\n");
}

module_init(my_init);
module_exit(my_exit);