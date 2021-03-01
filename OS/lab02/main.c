#include <dirent.h>
#include <limits.h>

nt main(int argc, char *argv[])
{
	int ret;
	if (argc != 2)
        perror("Использование: ftw <начальный каталог>\n");
	ret = myftw(argv[1], myfunc);
	
	return ret;
}

#define FTW_F 1 // файл, не являющийся каталогом
#define FTW_D 2 // каталог
#define FTW_DNR 3 // каталог, который не доступен для чтения
#define FTW_NS 4 // файл, информацию о котором невозможно получиться


static char *fullpath;

static int myftw(char *pathname, Myfunc *func)
{
	int len;
	
	fullpath = path_alloc(&len);
	
	strncpy(fullpath, pathname, len);
	fullpath[len - 1] = 0;
	
	return(dopath(func));
}

static int dopath(Myfunc *func)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret;
	char *ptr;
	
	if (lstat(fullpath, &statbuf) < 0)
		return(func(fullpath, &statbuf, FTW_NS));
	
	if (S_ISDIR(statbuf.st_mode) == 0)
		return(func(fullpath, &statbuf, FTW_F));
	
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return ret;
	ptr = fullpath + strlen(fullpath);
	
	*ptr++ = '/';
	*ptr = 0;
	
	if ((dp = opendir(fullpath)) == NULL)
		return(func(fullpath, &statbuf, FTW_DNR));
	
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0)
			continue;
		
		strcpy(ptr, dirp->d_name);
		
		if ((ret = dopath(func)) != 0)
			break;		
	} 
	
	ptr[-1] = 0;
	
	if (closedir(dp) < 0)
		perror("Невозможно закрыть каталог!\n");
        return(1);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch (type) {
		case FTW_F:
			printf("%s/file", pathname);
			break;
		case FTW_D:
			printf("%s", pathname);
		default:
			printf("ops");
	}
	return(0);
}