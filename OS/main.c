#include <syslog.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h> 
#include <signal.h>
#include <string.h> 
#include <errno.h> 
#include <sys/file.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) 

int lockfile(int fd)
{
    struct flock filelock;
    filelock.l_type = F_WRLCK;
    filelock.l_start = 0;
    filelock.l_whence = SEEK_SET;
    filelock.l_len = 0;
    return (fcntl(fd, F_SETLK, &filelock));
}

int already_running(void)
{
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE)

    if (fd < 0)
    {
        syslog(LOG_ERR, "невозможно открыть %s: %s!", LOCKFILE, strerror(errno));
        exit(1);
    }

    if (lockfile(fd) < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            close(fd);
            return(1);
        }
        syslog(LOG_ERR, "невозможно установить блокировку %s: %s!", LOCKFILE, strerror(errno));
        exit(1);
    }

    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);

}

void daemonize(const char *cmd)
{
    int fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // 1) Сбрасывание маски режима создания файла 
    umask(0);

    // 2) Получение максимального возможного номера дискриптора 
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        perror("Невозможно получить максимальный номер дискриптора!\n");
    
    // 3) Стать лидером новой сессии, чтобы утратить управляющий терминал 
    if ((pid = fork()) < 0)
        perror("Ошибка функции fork!\n");
    else if (pid != 0) //родительский процесс
        exit(0);
    
    setsid();

    // 4) Обеспечить возможность обретения управляющего терминала в будущем
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        perror("Невозможно игнорировать сигнал SIGHUP!\n");

    // 5. Назначить корневой каталог текущим рабочим каталогом, 
    // чтобы впоследствии можно было отмонтировать файловую систему 
    if (chdir("/") < 0)
        perror("Невозможно назначить корневой каталог текущим рабочим каталогом!\n");
    
    // 6. Закрыть все файловые дескрипторы 
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (int i = 0; i < rl.rlim_max; i++)
        close(i);

    // 7. Присоединить файловые дескрипторы 0, 1, 2 к /dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0); //копируем файловый дискриптор
    fd2 = dup(0);

    // 8. Инициализировать файл журнала
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        syslog(LOG_ERR, "ошибочные файловые дескрипторы %d %d %d\n", fd0, fd1, fd2);
        exit(1);
    }

    syslog(LOG_WARNING, "Демон запущен!");
}

int main() 
{
    daemonize("hello");
    // 9. Блокировка файла для одной существующей копии демона 
    if (already_running() != 0)
    {
        syslog(LOG_ERR, "Демон уже запущен!\n");
        exit(1);
    }

    syslog(LOG_WARNING, "Проверка пройдена!");

    syslog(LOG_INFO, getlogin())
    syslog(LOG_INFO, getlogin())
    syslog(LOG_INFO, getlogin())
}