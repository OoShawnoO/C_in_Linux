# 共享内存

```c
int shmget(key_t key,size_t size,int shmflg);
创建一个新的共享内存段，或者获取一个已经存在的共享内存段的标识，新创建的共享内存的数据会被初始化为0;
params:
	key : key_t 类型是一个整形，通过找到或创建一个共享内存，一般使用16进制，非0值;
	szie : 内存大小	;
	shmflg : 属性
        	- 访问权限
        	- 附加属性 创建 IPC_CREAT\判断共享内存是否存在 IPC_CREAT | IPC_EXCL | 0664(权限);
headers :
	#Include <sys/ipc.h>
	#include <sys/shm.h>
return:
	success : 共享内存的id	;
	failed :-1	;

void *shmat(int shmid,const void *shmaddr,int shmflg);
让对应共享内存段id的共享内存与进程进行关联	;
params:
	shmid : 共享内存的标识	;
	shmaddr : 申请的共享内存的首地址 为NULL 由内核指定	;
	shmflg : 对共享内存的操作
        	读 :SHM_RDONLY,必须有读权限	;
			读写: 0	;
return:
	success : 返回首地址	;
	failed : -1;

int shmdt(const void* shmaddr);
解除关联;

int shmctl(int shmid,int cmd,struct shmid_ds *buf);
删除共享内存，共享内存要删除才会消失，创建的共享内存的进程被销毁了对共享内存没有影响;
params:
	shmid : 共享内存的id	;
	cmd : 对共享内存的操作
        - IPC_STAT 获取共享内存当前的状态
        - IPC_SET 设置共享内存的状态
        - IPC_RMID 标记共享内存被销毁
    buf : 要设置的属性:
		- IPC_STAT: buf存储数据
        - IPC_SET: buf 需要初始化数据设置到内核中
        - IPC_RMID: 没有用,NULL

struct shmid_ds{
    struct ipc_perm shm_perm;
    size_t shm_sgsize;
    time_t shm_atime;
    time_t shm_dtime;
    time_t shm_ctime;
    pid_t shm_cpid;
    pid_t shm_lpid;
    shmatt_t shm_nattch;
    ...
}

key_t ftok(const char *pathname,int proj_id);
根据指定的路径名和int值生成一个共享内存的key;
params：
    pathname : 指定一个存在的路径	;
	proj_id : int 类型的值,但这系统调用只会使用其第一个字节
        范围: 0~255 一般只指定一个字符	;

pid_t getpgrp(void);

pid_t getpgid(pid_t pid);

int setpgid(pid_t pid,pid_t pgid);

pid_t getsid(pid_t pid);

pid_t setsid(void);
```

