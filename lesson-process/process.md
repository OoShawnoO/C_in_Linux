# 进程

```C
创建子进程;父子进程交替运行;
pid_t fork(void);
headers:
	#include <unistd.h>
	#include <sys/types.h>
return:
	返回子进程的pid是在父进程被返回;
	如果返回值0则是在子进程返回的;

父子进程间使用的是虚拟地址的写时拷贝，就是在不改变一个内容时两个进程指向的物理地址空间是相同的，当需要修改时，才会分别指向对应的内容 ;

gdb 多进程调试：
    默认追踪父进程，子进程会自己运行完成
    使用 set follow-fork-mode [parent | child] 来选择追踪的进程
    使用 set detach-on-fork [on | off] on表示其他进程继续运行，off表示其他进程被GDB挂起
    使用 info inferiors 查看调试的进程
    使用 inferior id 切换调试的进程
    使用 detach inferiors id 使进程脱离GDB调试 ;

exec 函数族: 会直接将虚拟空间中的用户区替换为exec执行的程序的新用户区
int execl(const char* path,const char *arg,...);//不会在环境变量中查找
int execlp(const char* path,const char *arg,...); //会到环境变量中区查找可执行文件
	path 推荐使用绝对路径	;
	arg 第一个参数一般写执行的程序名称 第二个参数往后为参数列表 参数最后需要NULL结束（哨兵）;
return:
	调用失败返回 -1 errno ;

进程结束:
#include <stdlib.h>
void exit(int status);
#include <unistd.h>
void _exit(int status);

孤儿进程:
父进程运行完了 子进程还没有，子进程的父进程变为init \(进程号为1的进程),由init等待子进程运行完毕，为起处理后续释放回收工作 ;
僵尸进程:
进程终止时，父进程暂未回收，子进程残留资源PCB存放在内核中，变成僵尸进程;

进程回收:
pid_t wait(int *wstatus); //等待任意一个子进程结束，如果子进程结束本函数会回收子进程的资源
headers:
	#include <sys/types.h>
	#include <sys/wait.h>
params:
	wstatus : 传出的退出状态信息 ;
return:
	success : 子进程的pid 	;
	failed : -1	;
调用wait()函数的进程会挂起(阻塞),直到他的一个子进程退出或收到一个不能被忽略的信号时才被唤醒。如果没有子进程了会立刻返回-1,如果子进程都结束了，也会立即返回-1，并回收子进程的资源 ;

pid_t waitpid(pid_t pid,int *wstatus,int options);
headers:
	#include <sys/types.h>
	#include <sys/wait.h>
params:
	pid : 子进程的id	;	//pid > 0 指定pid pid = 0 当前进程组所有 pid = -1 所有子进程 pid<-1 某个进程组id的绝对值，指定回收某个进程组的子进程
	wstatus : 传出的退出状态信息 ;
	options : 设置是否阻塞	; // 0 阻塞 WNOHANG 非阻塞
return:
	>0 : 返回子进程id	;
	=0 ：options = WNOHANG,表示还有子进程	;
	-1 : 错误或没有子进程	;
```

