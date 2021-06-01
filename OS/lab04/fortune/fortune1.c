#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/uaccess.h>

#define PROC_FILE_NAME "Hello"


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fortune Kernel Module");

static char kernel_buffer[256];
static struct proc_dir_entry *proc_file;
static char *out_str;

int proc_init(void);
void proc_exit(void);

// не логируется в struct file_operations, но она указывается в single_open (там логируется)
static int proc_show(struct seq_file *m, void *v)
{
    printk(KERN_INFO "fortune: call proc_hello_show\n");
    int error = 0;
    seq_printf(m, "%s\n", out_str); 
    return error;
}

// В качестве аргументы две структуры для работы с файлами, потому что файлы в ОС линукс/юникс идентифицируется номер inode и описываются struct inode. А открытые файлы( файлы с которыми работает процесс, когда процесс вызывает open) в системе описываются в системе struct file. В системе имеется одна таблица открытых файлов. То есть это не структура которая описывает файлы открытым процессом, это указатель на системную таблицу открытых файлов.
static int proc_open(struct inode *inode, struct file *file)
{
   printk(KERN_INFO "fortune: call proc_open\n");
   return single_open(file, proc_show, NULL);
}


static ssize_t proc_write(struct file *inst, const char  *buffer, size_t max_bytes_to_write, loff_t *offset)
{
   printk(KERN_INFO "fortune: call proc_hello_write\n");
   ssize_t to_copy, not_copied;
   to_copy = min(max_bytes_to_write, sizeof(kernel_buffer)); 
   not_copied = copy_from_user(kernel_buffer, buffer, to_copy);

   // Если мы пишем в загружаемый модуль используя echo передадите "deutsch", получим "Hallo welt"
   if (not_copied == 0)
   {
        printk(KERN_INFO "kernel buffer:\"%s\n", kernel_buffer);
        if (strncmp("deutsch", kernel_buffer,7) == 0)
        {
            out_str =  "Hallo welt";
        }
        if (strncmp("english", kernel_buffer,7) == 0)
        {
            out_str =  "Hello world";
        }
   }
   return to_copy-not_copied;
}

// для логирования своих функции используют struct file_operations
static const struct file_operations proc_hello_fops=
{
   .owner = THIS_MODULE,
   .open = proc_open, // функцию, которую мы сами определили
   .release = single_release, 
   .read = seq_read,
   .write =  proc_write
};


// создаем файл, у которого будет имя которые определили в define
// чтение называется передача данных из ядра в юзер, поскольку мы читаем мы установили права read
int proc_init(void)
{
    printk(KERN_INFO "fortune: call proc_hello_init\n");
    out_str = "Hello";
    proc_file = proc_create_data(PROC_FILE_NAME, S_IRUGO | S_IWUGO, NULL, &proc_hello_fops, NULL); // S_IRUGO - права read для юзера, группы и others
    // NULL - файл будет создан ниже /proc то есть в корневом каталоге proc
    // proc_hello_fops - передаем наши операции определенные  struct file_operations и фактически нами определена только функция proc_hello_open. В ней обращаемся к proc_hello_show в которой используем функцию seqprintf,  а для read seqread по этому мы ее не описываем, а для закрытия определена release а именно single_release мы используем функцию ядра.

    if (!proc_file) 
        return -ENOMEM;
    return 0;
}

void proc_exit(void)
{  
   printk(KERN_INFO "fortune: call proc_hello_exit\n");
   if (proc_file)
      remove_proc_entry(PROC_FILE_NAME, NULL);
}

module_init(proc_init);
module_exit(proc_exit);