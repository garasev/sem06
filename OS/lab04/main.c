#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "dirent.h"
#define BUF_SIZE 0x200

FILE *fp;

char *outputStat[] = {
    "pid",          // ID процесса
    "filename",     // Имя файла
    "state",        // Состояние процесса
    "ppid",         // ID родительского процесса
    "gid",          // ID группы процесса
    "session",      // ID сессии процесса
    "tty_nr",       // Контролирующий терминал процесса
    "tp_gid",       // ID внешней группы процессов контролирующего терминала
    "flags",        // Флаги ядра процесса
    "minflt",       // Количество минорных ошибок процесса (Минорные ошибки не включают ошибки загрузки страниц памяти с диска)
    "cminflt",      // Количество минорных ошибок дочерних процессов (Минорные ошибки не включают ошибки загрузки страниц памяти с диска)
    "majflt",       // Количество Мажоных ошибок процесса
    "cmajflt",      // Количество Мажоных ошибок дочерних процессов процесса
    "utime",        // Количество времени, в течение которого этот процесс был запланирован в пользовательском режиме
    "stime",        // Количество времени, в течение которого этот процесс был запланирован в режиме ядра
    "cutime",       // Количество времени, в течение которого ожидаемые дети этого процесса были запланированы в пользовательском режиме
    "cstime",       // Количество времени, в течение которого ожидаемые дети этого процесса были запланированы в режиме ядра
    "priority",     // Приоритет процесса
    "nice",         // nice
    "num_threads",  // Количество потоков
    "itrealvalue",  // Время в тиках до следующего SIGALRM отправленного в процесс из-за интервального таймера.
    "start_tiime",  // Время запуска процесса 
    "vsize",        // Объем виртуальной памяти в байтах
    "rss",          // Resident Set Size: Количество страниц процесса в физической памяти.
    "rsslim",       // Текущий лимит в байтах на RSS процесса
    "startcode",    // Адрес, над которым может работать текст программы
    "endcode",      // Адрес, над которым может работать текст программы
    "startstack",   // Адрес начала (т. е. дна) стека
    "kstkesp",      // Текущее значение ESP (Stack pointer), найденное на странице стека ядра для данного процесса.
    "kstkeip",      // Текущее значение EIP (instruction pointer)
    "signal",       // Растровое изображение отложенных сигналов, отображаемое в виде десятичного числа
    "blocked",      // Растровое изображение заблокированных сигналов, отображаемое в виде десятичного числа
    "sigignore",    // Растровое изображение игнорированных сигналов, отображаемое в виде десятичного числа
    "sigcatch",     // Растровое изображение пойманных сигналов, отображаемое в виде десятичного числа.
    "wchan",        // Канал, в котором происходит ожидание процесса.
    "nswap",        // Количество страниц, поменявшихся местами
    "cnswap",       // Накопительный своп для дочерних процессов
    "exit_signal",  // Сигнал, который будет послан родителю, когда процесс будет завершен.
    "processor",    // Номер процессора, на котором было последнее выполнение.
    "rt_priority",  // Приоритет планирования в реальном времени- число в диапазоне от 1 до 99 для процессов, запланированных в соответствии с политикой реального времени
    "policy",       // Политика планирования
    "delayacct_blkio_tics", // Общие блочные задержки ввода/вывода
    "quest_time",   // Гостевое время процесса
    "cquest_time",  // Гостевое время  дочерних процессов
    "start_data",   // Адрес, над которым размещаются инициализированные и неинициализированные данные программы (BSS).
    "end_data",     // Адрес, под которым размещаются инициализированные и неинициализированные данные программы (BSS).
    "start_brk",    // Адрес, выше которого куча программ может быть расширена с помощью brk.
    "arg_start",    // Адрес, над которым размещаются аргументы командной строки программы (argv).
    "arg_end",      // Адрес, под которым размещаются аргументы командной строки программы (argv).
    "env_start",    // Адрес, над которым размещена программная среда
    "env_end",      // Адрес, под которым размещена программная среда
    "exit_code"     // Состояние выхода потока в форме, сообщаемой waitpid.
};

char *outputStatm[] = {
    "size",
    "resident",
    "shared",
    "text",
    "lib",
    "data",
    "dt"
};

void statOutput(char *buf)
{
    int i = 0;
    int len = strlen(buf);
    int currentName = 0;
    char *pch = strtok(buf, " ");

    while (pch != NULL && i < 51)
    {
        printf("\n%15s:\t %s", outputStat[i], pch);
        fprintf(fp, "\n%15s", outputStat[i]);
        fprintf(fp, ":\t %s", pch);
        pch = strtok(NULL, " ");
        i++;
    }
}

void statmOutput(char *buf)
{
    int i = 0;
    int len = strlen(buf);
    int currentName = 0;
    char *pch = strtok(buf, " ");

    while (pch != NULL && i < 7)
    {
        printf("\n%15s:\t %s", outputStatm[i], pch);
        fprintf(fp, "\n%15s:\t %s", outputStatm[i], pch);
        pch = strtok(NULL, " ");
        i++;
    }
}

void simpleOutput(char *buf)
{
    printf("%s\n", buf);
    fprintf(fp, "%s\n", buf);
}

void read_file(char* filename, void (*print_func)(char*))
{
    char buf[BUF_SIZE];
    int i, len;
    FILE *f = fopen(filename, "r");
    while ((len = fread(buf, 1, BUF_SIZE, f)) > 0)
    {
        for (i = 0; i < len; i++)
            if( buf[i] == 0)
                buf[i] = 10;
        buf[len - 1] = 0;
        print_func(buf);
    }
    fclose(f);
}

void read_symlink(char *symlink)
{
    char linkbuf[256];
    int len = readlink(symlink, linkbuf, sizeof linkbuf);
    linkbuf[len] = '\0';
    simpleOutput(linkbuf);
}


void read_fd(char *dir)
{
    printf("\nfd:\n");
    struct dirent *dirp;
    DIR *dp;
    char str[BUF_SIZE];
    char path[BUF_SIZE];
    int len;
    dp = opendir(dir);//открыть директорию
    while ((dirp = readdir(dp)) != NULL)//читаем директорию
    {
        if ((strcmp(dirp->d_name, ".") != 0) &&
            (strcmp(dirp->d_name, "..") != 0))
        {
            sprintf(path, "%s%s", "/proc/self/fd/", dirp->d_name);
            len = readlink(path, str, BUF_SIZE);
            str[len] = '\0';
            printf("%s -> %s\n", dirp->d_name, str);
            fprintf(fp, "%s -> %s\n", dirp->d_name, str);

        }
    }
    closedir(dp);
}

int main(int argc, char *argv[])
{
    int pid;

    if (argc == 2) {
        pid = atoi(argv[1]);
    }

    char buf[256];
    fp = fopen("my.txt", "w");

    printf("\n______________________________\n");
    printf("CMDLINE\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "CMDLINE\n\n");
    sprintf(buf, "/proc/%d/cmdline", pid);
    read_file(buf,  simpleOutput);

    printf("\n______________________________\n");
    printf("CWD\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "CWD\n\n");
    sprintf(buf, "/proc/%d/cwd", pid);
    read_symlink(buf);

    printf("\n______________________________\n");
    printf("FD\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "FD\n\n");
    sprintf(buf, "/proc/%d/fd", pid);
    read_fd(buf);


    printf("\n______________________________\n");
    printf("ENVIRON\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "ENVIRON\n\n");
    sprintf(buf, "/proc/%d/environ", pid);
    read_file(buf,  simpleOutput);

    printf("\n______________________________\n");
    printf("EXE\n\n");
    fprintf(fp,"\n______________________________\n");
    fprintf(fp,"EXE\n\n");
    sprintf(buf, "/proc/%d/exe", pid);
    read_symlink(buf);


    printf("\n______________________________\n");
    printf("MAPS\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "MAPS\n\n");
    sprintf(buf, "/proc/%d/maps", pid);
    read_file(buf,  simpleOutput);

    printf("\n______________________________\n");
    printf("ROOT\n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "ROOT\n\n");
    sprintf(buf, "/proc/%d/root", pid);
    read_symlink(buf);

    printf("\n______________________________\n");
    printf("STAT \n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "STAT \n\n");
    sprintf(buf, "/proc/%d/stat", pid);
    read_file(buf, statOutput);

    printf("\n______________________________\n");
    printf("STATM \n\n");
    fprintf(fp, "\n______________________________\n");
    fprintf(fp, "STATM \n\n");
    sprintf(buf, "/proc/%d/statm", pid);
    read_file(buf, statmOutput);

    return 0;
}