#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
int main()
{
	struct stat statbuf;

	FILE *fs1 = fopen("write_result.txt", "w");
	stat ("write_result.txt", &statbuf);
	printf("AFTER FOPEN FOR FS1: inode  = %ld, buffsize = %ld blocksize= %ld\n", (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

	FILE *fs2 = fopen("write_result.txt", "w");
	stat ("write_result.txt", &statbuf);
	printf("AFTER FOPEN FOR FS2: inode  = %ld, buffsize = %ld blocksize= %ld\n", (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

	for (char c = 'a'; c <= 'z'; c++)
 	{
 		if (c % 2)
 			fprintf(fs1, "%c", c);
		else
 			fprintf(fs2, "%c", c);
 	}


    fclose(fs2);
	stat ("write_result.txt", &statbuf);
	printf("AFTER FCLOSE FOR FS2: inode  = %ld, buffsize = %ld blocksize= %ld\n", (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

	fclose(fs1);
	stat ("write_result.txt", &statbuf);
	printf("AFTER FCLOSE FOR FS1: inode  = %ld, buffsize = %ld blocksize= %ld\n", (long int)statbuf.st_ino, (long int)statbuf.st_size,
	 (long int)statbuf.st_blksize);

	return 0;
}