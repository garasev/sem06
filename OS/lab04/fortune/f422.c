#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

MODULE_LICENSE(“GPL”);
MODULE_DESCRIPTION(“Fortune Cookie Kernel Module”);

#define COOKIE_BUF_SIZE PAGE_SIZE

ssize_t fortune_read(struct file *file, char *buf, size_t count, loff_t *f_pos);
ssize_t fortune_write(struct file *file, const char *buf, size_t size, loff_t *offset);

int fortune_init(void);
void fortune_exit(void);

static char *cookie_buf;

static struct proc_dir_entry *proc_entry, *proc_dir, *proc_sym;
static unsigned write_index;

ssize_t fortune_read(struct file *file, char *buf, size_t size, loff_t *ppos)
{
    printk(KERN_INFO “fortune_buf
           : Call my_read\n”);
    int len;
    if (write_index == 0 || *ppos > 0)
        return 0;

    len = print(buf, “% s\n”, &cookie_buf[0]); //  print – аналог copy_to_user
    *ppos = len;

    return len;
}




ssize_t fortune_write(struct file *sp_file, const char *buf, size_t size,                              loff_t *offset)
{
    printk(KERN_INFO “fortune_buf: Call my_write\n”);
    int space_available = (COOKIE_BUF_SIZE – write_index) + 1;

    if (size > space_available)
    {
        printk(KERN_INFO “fortune_buf
               : cookie pot is full\n”);
        return –ENOSPC;
    }

    if (copy_from_user(&cookie_buf[write_index], buf, size))
        return –EFAULT;

    write_index += size;
    //cookie_buf[write_index – 1] = 0;
    return size;
}

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO “fortune_buf
           : Call my_open\n”);
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO “fortune_buf
           : Сall my_release\n”);
    return 0;
}

struct proc_ops fops = {
    .proc_open = my_open,
    .proc_release = my_release,
    .proc_read = fortune_read,
    .proc_write = fortune_write,
};

int fortune_init(void)
{
    printk(KERN_INFO “fortune_buf
           : Call my_init\n”);

    cookie_buf = (char *)vmalloc(COOKIE_BUF_SIZE);



    if (!cookie_buf)
    {
        printk(KERN_INFO “fortune_buf: Not enough memory for the cookie pot\n”);
        return –ENOMEM;
    }
    memset(cookie_buf, 0, COOKIE_BUF_SIZE);

    proc_entry = proc_create(“fortune_buf1”, 0666, NULL, &fops);
    if (!proc_entry)
    {
        vfree(cookie_buf);
        printk(KERN_INFO “fortune_buf
               : Couldn’t create proc entry\n”);
        return –ENOMEM;
    }

    proc_dir = proc_mkdir(“fortune_dirq1”, NULL);
    if (!proc_dir)
    {
        vfree(cookie_buf);
        printk(KERN_INFO “fortune_buf
               : Couldn’t create proc dir\n”);
        return –ENOMEM;
    }

    proc_sym = proc_symlink(“fortune_symlinkq1”, NULL, “/ proc / fortune”);
    if (!proc_sym)
    {
        vfree(cookie_buf);
        printk(KERN_INFO “fortune_buf
               : Couldn’t create proc symlink\n”);
        return –ENOMEM;
    }

    write_index = 0;
    printk(KERN_INFO “fortune_buf
           : module loaded.\n”);
    return 0;
}

void fortune_exit(void)
{
    printk(KERN_INFO “fortune_buf
           : Call my_exit\n”);
    if (proc_entry)
        remove_proc_entry(“fortune_buf1”, NULL);

    if (proc_dir)
        remove_proc_entry(“fortune_dirq1”, NULL);


    if (proc_sym)
        remove_proc_entry(“fortune_symlinkq1”, NULL);

    if (cookie_buf)
        vfree(cookie_buf);

    printk(KERN_INFO “fortune_buf
           : module unloaded.\n”);
}

module_init(fortune_init);
module_exit(fortune_exit);
