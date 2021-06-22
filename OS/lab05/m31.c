#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>

struct file_s{
  int num;
};

typedef struct file_s file_num;

void* write_to_file(void *arg){
	struct stat statbuf;

	file_num *f_num = (file_num*) arg;

	FILE* fs = fopen("write_result.txt", "w");
	stat ("write_result", &statbuf);
  	stat ("write_result.txt", &statbuf);
	printf("AFTER FOPEN FOR FS%d: inode  = %ld, buffsize = %ld blocksize= %ld\n",f_num->num, (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

  	for (char c = 'a'; c <= 'z'; c++)
 	{
 		if (c % 2 && f_num->num == 1)
 			fprintf(fs, "%c", c);
		if (!(c % 2) && f_num->num == 2)
 			fprintf(fs, "%c", c);
 	}

 	fclose(fs);
	stat ("write_result.txt", &statbuf);
	printf("AFTER FCLOSE FOR FS%d: inode  = %ld, buffsize = %ld blocksize= %ld\n",f_num->num, (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

}

int main()
{

  	pthread_t thread1;
  	pthread_t thread2;

  	file_num f1;
  	file_num f2;

  	f1.num = 1;
  	f2.num = 2;


    int status2 = pthread_create(&thread2, NULL, write_to_file, &f2);
  	if (status2 != 0) {
    	printf("main error: can't create thread, status = %d\n", status2);
    	return -1;
  	}

  	int status1 = pthread_create(&thread1, NULL, write_to_file, &f1);
  	if (status1 != 0) {
    	printf("main error: can't create thread, status = %d\n", status1);
    	return -1;
  	}
  
    

  	pthread_join(thread1, NULL);
  	pthread_join(thread2, NULL);
	
	return 0;
}