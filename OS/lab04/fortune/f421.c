#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/seq_file.h>
#include<linux/slab.h>
#include<linux/vmalloc.h>
 
MODULE_LICENSE("GPL");
 
static char *str = NULL;
 
//индексы куда писать и откуда считывать
unsigned int write_index;
unsigned int read_index;
 
#define COOKIE_POT_SIZE PAGE_SIZE  
 static int my_show(struct seq_file *m, void *v)
{
    printk(KERN_INFO "fortune-seq: my_show\n");
    //seq_printf стандартная функция, выполняет действия, аналогичные copy_to_user или sprintf.
    //int seq_printf(struct seq_file *sfile, const char *fmt, …);
    // Это эквивалент printf для реализаций seq_file; он принимает обычную строку формата и дополнительные аргументы значений. 
    // Однако, вы также должны передать ей структуру seq_file, которая передаётся в функцию show. 
    // Если seq_printf возвращает ненулевое значение, это означает, что буфер заполнен и вывод будет отброшен. Большинство реализаций, однако, игнорирует возвращаемое значение.
 
    seq_printf(m, "Message is %s. Index is %u\n", str + read_index, read_index);
 
    int len = strlen(str + read_index);
    if (len)
        read_index += len + 1;
    return 0;
}
 



static ssize_t my_write(struct file* file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "fortune-seq: my_write\n");
    if (copy_from_user(&str[write_index], buffer, count)) // (куда, откуда, сколько байт)
        return -EFAULT; //ошибка сегментирования (минус так как соглашение)
 
    write_index += count;
    str[write_index-1] = 0;
 
    return count;
}
 
static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "fortune-seq: my_open\n");
    // чтобы создать один файловый экземпляр модуля используется single_open который передаёт адрес функции my_show, а функция my_show передаёт адрес страницы памяти

    return single_open(file, my_show, NULL);  // стандартная функция, может быть одновременно вызвана только одним процессом (чтобы открыть определенный файл) cat
}
 
static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "fortune-seq: my_release\n");
    return single_release(inode, file);  //выгружает seq file
}
 
static struct file_operations fortune_proc_ops={
    .open = my_open,
    .release = my_release,
    .read = seq_read,
    .write = my_write
};
 
static int __init fortune_init(void)
{
    printk(KERN_INFO "fortune-seq: fortune init\n");
    write_index = 0;
    read_index = 0;
    // выделить память для строки 
    str = vmalloc(COOKIE_POT_SIZE);
    if (!str)
    {
        printk(KERN_INFO "Error: can’t malloc cookie buffer\n");
        return -ENOMEM;
    }
    memset(str, 0, COOKIE_POT_SIZE); //заполняем строку нулями
    //Чтобы работать с виртуальной файловой системой proc в ядре, в ядре определена структура 
    struct proc_dir_entry *entry;
    entry = proc_create("fortune", S_IRUGO | S_IWUGO, NULL, &fortune_proc_ops); //создаёт файл в виртуальной системе проц – имя файла, права доступа, указатель на родителя (если Null то создастся в корне), указатель на операции
    if(!entry)
    {
        vfree(str);
        printk(KERN_INFO "Error: can’t create fortune file\n");
        return -ENOMEM;
    }   
    // создать каталог в файловой системе /proc 
    proc_mkdir("cookie_dir", NULL);
    // создать символическую ссылку на «/proc/fortune»
    proc_symlink("cookie_symlink", NULL, "/proc/fortune");  
    printk(KERN_INFO "Fortune module loaded successfully\n");
    return 0;
}
 
static void __exit fortune_exit(void)
{
    printk(KERN_INFO "fortune-seq: exit\n");
 
    remove_proc_entry("fortune", NULL);
    remove_proc_entry("cookie_dir", NULL); //Чтобы работать с виртуальной файловой системой proc в ядре, в ядре определена структура 
    remove_proc_entry("cookie_symlink", NULL);
    if (str)
        vfree(str);
    printk(KERN_INFO "Fortune module unloaded\n"); //dmesq
}
 
module_init(fortune_init);
module_exit(fortune_exit);
// для release и open нужен inode так как там надо работать открывать закрывать файлы, а read и write работают уже с открытыми.
