# 内存映射

```c
headers :
	#include <mman.h>

void *mmap(void *addr,size_t length,int prot,int flags,int fd,off_t offset);
映射文件到内存	;
params:
	addr : 起始地址	;
	length : 映射内存的大小 ;
	prot : 对申请的内存映射区的操作权限	[PROT_EXEC 执行 PROT_READ 读 PROT_WRITE 写 PROT_NONE 无] 	;
	flags : MAP_SHARED 映射区的数据会自动和磁盘空间同步，进程间通信需要设置这个选项,MAP_PRIVATE 不同步，内存映射区的数据改变了，原来的文件不会改变，底层会重新创建一个新的文件。		;
	fd : 要映射的文件的文件描述符	open打开的权限与PROT不能有冲突.	;
	offset:偏移量，一般不用	必须指定4K整数倍	;
return:
	success : addr 首地址	;
	failed : MAP_FAILED	;
int munmap(void *addr,size_t length);
释放映射的内存	;
params:
	addr : 要释放的内存的首地址	;
	length : 要释放的内存的大小	;

使用内存映射实现进程间通信:
	1. 有关系的进程:
		- 在还没有子进程的时候就创建内存映射区，父子共享内存映射区	;
	2. 没有关系的进程:
		- 准备一个磁盘大小不为0的文件 :
		- 进程1 \ 2 分别对此文件进行内存映射，然后使用内存映射区通信	;

匿名映射:不会产生对应的文件
mmap(NULL,Len,PROT_READ|PROT WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

```

