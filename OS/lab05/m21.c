#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>


struct file_desc{
  int fd;
};

typedef struct file_desc file_desc_t;

void* read_file(void *arg){
  char c;
  file_desc_t* fd = (file_desc_t*) arg;

  while(read(fd->fd, &c, 1) == 1){
    write(1, &c, 1);
  }
}

int main()
{

  pthread_t thread1;
  pthread_t thread2;

  // have kernel open two connection to file alphabet.txt
  file_desc_t fd1;
  fd1.fd = open("alphabet.txt",O_RDONLY);
  file_desc_t fd2;
  fd2.fd = open("alphabet.txt",O_RDONLY);
  

  int status1 = pthread_create(&thread1, NULL, read_file, &fd1);
  if (status1 != 0) {
    printf("main error: can't create thread, status = %d\n", status1);
    return -1;
  }
  
  int status2 = pthread_create(&thread2, NULL, read_file, &fd2);
  if (status2 != 0) {
    printf("main error: can't create thread, status = %d\n", status2);
    return -1;
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}