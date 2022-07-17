# 目录操作

```C
int mkdir(const char *pathname,mode_t mode);
headers:
	#include <sys/types.h>
params:
	pathname : 路径 ;
	mode : 权限 8进制 ;
return:
	success : 0 ;
	failed : -1 ;
作用：新建文件夹

int rmdir(const char *pathname);
headers:
	#include <sys/types.h>
params:
	pathname : 路径 ;
return:
	success : 0 ;
	failed : -1 ;
作用：删除文件夹


int rename(const char *oldpath,const char *newpath);
headers:
	#include <fcntl.h>
	#include <stdio.h>
params:
	oldpath : 旧路径 ;
	newpath : 新路径 ;
return:
	success : 0 ;
	failed : -1 ;
作用:重命名文件，如果可以修改文件夹就更改


int chdir(const char *path);
headers:
	#include <unistd.h>
params:
	path : 切换到的路径 ;
作用:切换当前工作目录

char *getcwd(char *buf,size_t size);
headers:
	#include <unistd.h>
params:
	buf : 接受返回的字符数组 ;
	size : 字符数组长度 ;
作用: 获取当前工作路径 ;

DIR *opendir(const char *name);
headers:
	#include <sys/types.h>
	#include <dirent.h>
params:
	name ： 目录路径 ;
return:
	返回一个目录流指针


struct dirent *readdir(DIR *dirp);
headers:
	#include <dirent.h>
params:
	dirp : 目录流指针	;
return:
	structure pointer to a dirent representing the next directory entry in the directory stream pointed to by a dirp
作用：读取目录中的数据	;

struct dirent{
    ino_t d_ino;//目录进入节点inode
    off_t d_off;//目录开头至进入点的偏移量
    unsigned short int d_reclen;//d_name的长度
    unsigned char d_type;//文件类型
    char d_name[256];//文件名
}
    
        
int closedir(DIR *dirp);
作用:关闭文件夹指针 ;

int dup(int oldfd);
作用: 复制文件描述符;

int dup2(int oldfd,int newfd);
作用: 重定向文件描述符 将oldfd对应的文件赋给newfd ;


int fcntl(int fd,int cmd,.../* arg */);
作用: 1. 复制文件描述符 2.设置、获取文件的状态标志 	;
headers:
	#include <fcntl.h>
	#include <unistd.h>
params:
	fd ： 需要操作的文件描述符;
	cmd : 需要对文件描述符进行的操作	; /* F_DUPFD 复制fd F_GETFL 获取当前文件描述符的状态flags（open函数中的flags） F_SETFL 设置文件描述符文件状态flag 必选项 O_RDONLY,O_WRONLY,ORDWR 可选项:O_APPEND,O_NONBLOCK（非阻塞）

```

