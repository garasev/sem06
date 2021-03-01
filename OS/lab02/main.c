#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FTW_F 1 // файл, не являющийся каталогом
#define FTW_D 2 // каталог
#define FTW_DNR 3 // каталог, который не доступен для чтения
#define FTW_NS 4 // файл, информацию о котором невозможно получить

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static char *fullpath;
static int dopath(const char *filename, int depth, Myfunc *);

int main(int argc, char * argv[])
{
	int ret = -1; 
	if (argc != 2)
	{
		printf("ERROR, wrong arguments.\nUse: ./app <dir>\n");
		return(-1);
	}
	
	ret = dopath(argv[1], 0, myfunc); //выполняет всю работу

	printf("Finish");
	return(ret);
}

static int dopath(const char *filename, int depth, Myfunc *myfunc)
{
	struct stat statbuf;
	struct dirent * dirp;
	DIR *dp;
	int ret = 0;

	if (lstat(filename, &statbuf) < 0) // файл, информацию о котором невозможно получить  
		return(myfunc(filename, &statbuf, FTW_NS));

	for (int i = 0; i < depth; ++i)
		printf("|\t");

	if (S_ISDIR(statbuf.st_mode) == 0) // файл
		return(myfunc(filename, &statbuf, FTW_F));

	if ((ret = myfunc(filename, &statbuf, FTW_D)) != 0) // каталог
		return(ret);

	if ((dp = opendir(filename)) == NULL) // каталог недоступен
		return(myfunc(filename, &statbuf, FTW_DNR));
    
	chdir(filename);
	while ((dirp = readdir(dp)) != NULL && ret == 0)
	{
		if (strcmp(dirp->d_name, ".") != 0 &&
			strcmp(dirp->d_name, "..") != 0 ) // пропуск каталогов . и ..
		{
			ret = dopath(dirp->d_name, depth + 1, myfunc);
		}
	}
    
	chdir("..");

	if (closedir(dp) < 0)
		perror("Невозможно закрыть каталог");

	return(ret);    
}

static int myfunc(const char *pathame, const struct stat *statptr, int type)
{
	switch(type)
	{
		case FTW_F: 
			printf( "-- %s\n", pathame);
			break;
		case FTW_D: 
			printf( "-- %s/\n", pathame);
			break;
		case FTW_DNR:
			perror("К одному из каталогов закрыт доступ."); 
			return(-1);
		case FTW_NS:	
			perror("Ошибка функции stat."); 
			return(-1);
		default: 
			perror("Неизвестый тип файла."); 
			return(-1);
	}
	return(0);
}
