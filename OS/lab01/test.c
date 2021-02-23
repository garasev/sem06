#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <time.h>

#include <syslog.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)


void error_quit(const char *error_message, const char *command) {
    syslog(LOG_ERR, "%s %s %s", error_message, command, strerror(errno));
    exit(1);
}


int already_running(void)
{
    int file_descriptor;
    char buffer[16];
    file_descriptor = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);

    if ((file_descriptor) < 0)
    {
        syslog(LOG_ERR, "Can’t open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    flock(file_descriptor, LOCK_EX|LOCK_NB);
	if (errno == EWOULDBLOCK)
    {
        syslog(LOG_ERR, "Can’t lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    ftruncate(file_descriptor, 0);
    sprintf(buffer, "%ld", (long)getpid());
    write(file_descriptor, buffer, strlen(buffer) + 1);

    return(0);
}


void daemonize(const char *command)
{
    int i, file_descriptor_0, file_descriptor_1, file_descriptor_2;
    pid_t pid;
    struct rlimit limit;
    struct sigaction signal_action;

    if (getrlimit(RLIMIT_NOFILE, &limit) < 0)
        error_quit("%s: Can’t get file limit", command);

    // Rule 1: set umask to somewhat restricting value.
    umask(0);

    // Rule 2: Call fork and have the parent exit.
    // Become a session leader to lose controlling TTY
    if ((pid = fork()) < 0)
        error_quit("%s: Can’t fork", command);
    else if (pid != 0) /* parent */
        exit(0);

    // Rule 3: Call setsid to create a new session
    // The process (a) becomes the leader of a new session, (b) becomes the leader of a
    // new process group, and (c) is disassociated from its controlling terminal.
    setsid();
    // Ignore SIGHUP
    signal_action.sa_handler = SIG_IGN;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = 0;

    if (sigaction(SIGHUP, &signal_action, NULL) < 0)
        error_quit("%s: Сan’t ignore SIGHUP", command);

    // Rule 4: Change the current working directory to the root so
    // we won’t prevent file systems from being unmounted.
    if (chdir("/") < 0)
        error_quit("%s: Can’t change directory to /", command);

    // Rule 5: Close all open file descriptors.
    if (limit.rlim_max == RLIM_INFINITY)
        limit.rlim_max = 1024;
    for (i = 0; i < limit.rlim_max; i++)
        close(i);

    // Rule 6: Attach file descriptors 0, 1, and 2 to /dev/null.
    file_descriptor_0 = open("/dev/null", O_RDWR);
    file_descriptor_1 = dup(0);
    file_descriptor_2 = dup(0);
    // Initialize the log file.
    openlog(command, LOG_CONS, LOG_DAEMON);
    if (file_descriptor_0 != 0 || file_descriptor_1 != 1 || file_descriptor_2 != 2)
    {
        syslog(LOG_ERR, "Unexpected file descriptors %d %d %d", file_descriptor_0, file_descriptor_1, file_descriptor_2);
        exit(1);
    }
}


int main (void)
{
    char *command = "I'M  Y O U R  D A E M O N";
    time_t timer = 0;

    // Become a daemom
    daemonize(command);
    //Make sure only one copy of the daemon is running
    if (already_running())
    {
        syslog(LOG_ERR, "Daemon already running");
        exit(1);
    }

    while (1)
    {
        timer = time(NULL);
        syslog(LOG_INFO, "Current time is: %s", ctime(&timer));
	    sleep(3);
    }
=======
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <time.h>

#include <syslog.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)


void error_quit(const char *error_message, const char *command) {
    syslog(LOG_ERR, "%s %s %s", error_message, command, strerror(errno));
    exit(1);
}


int already_running(void)
{
    int file_descriptor;
    char buffer[16];
    file_descriptor = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);

    if ((file_descriptor) < 0)
    {
        syslog(LOG_ERR, "Can’t open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    flock(file_descriptor, LOCK_EX|LOCK_NB);
	if (errno == EWOULDBLOCK)
    {
        syslog(LOG_ERR, "Can’t lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    ftruncate(file_descriptor, 0);
    sprintf(buffer, "%ld", (long)getpid());
    write(file_descriptor, buffer, strlen(buffer) + 1);

    return(0);
}


void daemonize(const char *command)
{
    int i, file_descriptor_0, file_descriptor_1, file_descriptor_2;
    pid_t pid;
    struct rlimit limit;
    struct sigaction signal_action;

    if (getrlimit(RLIMIT_NOFILE, &limit) < 0)
        error_quit("%s: Can’t get file limit", command);

    // Rule 1: set umask to somewhat restricting value.
    umask(0);

    // Rule 2: Call fork and have the parent exit.
    // Become a session leader to lose controlling TTY
    if ((pid = fork()) < 0)
        error_quit("%s: Can’t fork", command);
    else if (pid != 0) /* parent */
        exit(0);

    // Rule 3: Call setsid to create a new session
    // The process (a) becomes the leader of a new session, (b) becomes the leader of a
    // new process group, and (c) is disassociated from its controlling terminal.
    setsid();
    // Ignore SIGHUP
    signal_action.sa_handler = SIG_IGN;
    sigemptyset(&signal_action.sa_mask);
    signal_action.sa_flags = 0;

    if (sigaction(SIGHUP, &signal_action, NULL) < 0)
        error_quit("%s: Сan’t ignore SIGHUP", command);

    // Rule 4: Change the current working directory to the root so
    // we won’t prevent file systems from being unmounted.
    if (chdir("/") < 0)
        error_quit("%s: Can’t change directory to /", command);

    // Rule 5: Close all open file descriptors.
    if (limit.rlim_max == RLIM_INFINITY)
        limit.rlim_max = 1024;
    for (i = 0; i < limit.rlim_max; i++)
        close(i);

    // Rule 6: Attach file descriptors 0, 1, and 2 to /dev/null.
    file_descriptor_0 = open("/dev/null", O_RDWR);
    file_descriptor_1 = dup(0);
    file_descriptor_2 = dup(0);
    // Initialize the log file.
    openlog(command, LOG_CONS, LOG_DAEMON);
    if (file_descriptor_0 != 0 || file_descriptor_1 != 1 || file_descriptor_2 != 2)
    {
        syslog(LOG_ERR, "Unexpected file descriptors %d %d %d", file_descriptor_0, file_descriptor_1, file_descriptor_2);
        exit(1);
    }
}


int main (void)
{
    char *command = "I'M  Y O U R  D A E M O N";
    time_t timer = 0;

    // Become a daemom
    daemonize(command);
    //Make sure only one copy of the daemon is running
    if (already_running())
    {
        syslog(LOG_ERR, "Daemon already running");
        exit(1);
    }

    while (1)
    {
        timer = time(NULL);
        syslog(LOG_INFO, "Current time is: %s", ctime(&timer));
	    sleep(3);
    }
>>>>>>> origin/main
}