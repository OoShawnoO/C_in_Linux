# Linux 系统 I/O 函数

```c
int open(const char *pathname,int flags);
headers:
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
params:
	pathname : 文件路径 ;
	flags : 对文件操作权限设置还有其他设置 ;
	flags取值: O_RDONLY 、 O_WRONLY 、 O_RDWR

return:
	success : file descipter 文件描述符 ;
	failed : -1 [errno 记录错误号 可以使用C的 perror(char *errorname) 查看 errorname是自己定的]


int open(const char *pathname,int flags,mode_t mode);
	headers:
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
params:
	pathname : 文件路径 ;
	flags : 对文件操作权限设置还有其他设置 ;
	flags取值: O_RDONLY 、 O_WRONLY 、 O_RDWR \ (必选)   |   O_CREAT (可选) 文件不存在创建新文件 ;
	mode : 八进制数 表示创建出的文件的权限 如0775
   	mode的含义 -rwxrwxrwx 这是0777使用八进制表 0111111111 最开头的一位表示文件类型 前三个rwx表示本用户的读、写、执行权限，中间三个为本用户的组的权限，后三个为其他用户的;
调用案例: open("path.c",O_RDWR | O_CREAT,0777);
return:
	success : file descipter 文件描述符 ;
	failed : -1 [errno 记录错误号 可以使用C的 perror(char *errorname) 查看 errorname是自己定的];


int close(int fd);
	关闭对应文件描述符的文件 ;

ssize_t read(int fd,void *buf,size_t count);
headers:
	#include <unistd.h>

params:
	fd : 文件描述符 ;
	*buf : 要读取到的文本的字符数组指针 ;
	count : 要读取的大小 ;

return:
	success : 	>=0 文件大小 | =0 文件已经读完 ;
	failed : -1 [errno]


ssize_t write(int fd,const void *buf,size_t count);
headers:
	#include <unistd.h>

params:
	fd : 文件描述符 ;
	*buf : 要写入的文本的字符数组指针 ;
	count : 要写入的大小 ;

return:
	success : 写入文件的大小 ;
	failed : -1 [errno]


off_t lseek(int fd,off_t offset,int whence);
headers:
	#include <sys/types.h>
	#include <unistd.h>
params:
	fd ：文件描述符 ;
	offset : 偏移量 ;
	whence : SEEK_CUR 设置文件指针偏移量 | SEEK_SET 设置当前位置+offset的值 | SEEK_END 文件大小+第二个参数offset的值 ;
作用：
    lseek(fd,0,SEEK_SET); 指针移到文件开头
    lseek(fd,0,SEEK_CUR); 获得当前位置偏移量
    lseek(fd,0,SEEK_END); 获得文件大小
    lseek(fd,100,SEEK_END); 拓展文件长度
    
return: 返回偏移量
```

