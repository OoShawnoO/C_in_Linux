# 信号

通知进程产生某种事件，又成为软件中断，

| 编号 | 信号名称                         | 对应事件                                                     | 默认动作                   |
| ---- | -------------------------------- | ------------------------------------------------------------ | -------------------------- |
| 2    | <font color="red">SIGINT</font>  | 当用户按下了Ctrl+C后，用户终端向正在运行中的由该终端启动的程序发出此信号 | 终止进程                   |
| 3    | <font color="red">SIGQUIT</font> | 用户按下Ctrl+\后，用户终端向正在运行中的由该终端启动的程序发出此信号 | 终止进程                   |
| 9    | <font color="red">SIGKILL</font> | 无条件终止进程，不能被忽略，处理，阻塞                       | 终止进程，可以杀死任何进程 |
| 11   | <font color="red">SIGSEGV</font> | 指示进程进行了无效内存访问（段错误）                         | 终止进程并产生core文件     |
| 13   | <font color="red">SIGPIPE</font> | Broken pipe向一个没有读端的管道写入数据                      | 终止进程                   |
| 17   | <font color="red">SIGCHLD</font> | 子进程结束，父进程会收到此信号                               | 忽略这个信号               |
| 18   | <font color="red">SIGCONT</font> | 如果进程已结束，则使其继续运行                               | 继续/忽略                  |
| 19   | <font color="red">SIGSTOP</font> | 停止进程的执行。信号不能被忽略处理和阻塞                     | 为终止进程                 |

```c
int kill(pid_t pid,int sig);
给某个进程发送某个信号	;
params:
	pid : 进程Id	; >0 指定进程 | =0 当前进程组 | =-1 将信号发送给每一个有权限接受信号的进程 | <-1 这个pid = 某个进程组的ID取反	;
	sig : 信号的编号或宏值	;

int raise(int sig);
给当前进程发送信号	;

void abort(void);
给当前进程发送SIGABRT信号给当前的进程，杀死当前进程	;

unsigned int alarm(unsigned int seconds);
设置定时器，函数调用，开始倒计时 不阻塞，当倒计时为0的时候，函数给进程发送信号SIGALRM	;
params:
	seconds : 秒 ; 0 定时器无效 | >0 定时秒数 ;
return：
    倒计时剩余的事件	;
SIGALRM信号 默认终止当前进程，每一个进程都有唯一的定时器。	;

int setitimer(int which,const struct itimerval *new_val,struct itimerval *old_value);
设置定时器，可以替代alarm函数。精度要高于alarm为us,可以实现周期性定时	;

struct itimerval{
    struct timeval it_interval;	//每个阶段时间间隔
    struct timeval it_value;	//延迟多长时间执行定时器
}

struct timeval{
    time_t tv_sec;	//秒数
    suseconds_t tv_usec;	//微秒数
}

params:
	which : 定时器什么事件计时	; 	ITIMER_REAL 真实时间，时间到达，发送SIGALRM常用 | ITIMER_VIRTUAL 用户时间 |  ITIMER_PROF 用户态和内核态所消耗的时间
    new_val : 设置定时器属性 ;
	old_val : 记录上一次的时间参数	;
return:
	success : 0;
	failed : -1 errno;

struct itimerval new_val;
new_val.it_interval.tv_sec = 2;
new_val.it_interval.tv_usec = 0;
new_val.it_value.tv_sec = 3;
new_val.it_value.usec = 0;
setitimer(ITIMER_REAL,&new_val,NULL);	//延迟3秒后设置一个2秒的定时器


sighandle_t signal(int signum,sighandler_t handler);
设置某个信号的捕捉行为	;
params:
	signum : 要捕捉的信号	;
	handler : 捕捉的信号要如何处理	; SIG_IGN 忽略信号 | SIG_DFL 使用默认行为 | 回调函数 这个函数是系统调用,程序员只负责写;
回调函数:
  - 需要程序员实现，提前准备好的，函数类型根据实际需求，看函数的定义
  - 不是程序员调用，当信号产生，内核调用
  - 函数指针是实现函数回调的方法，函数实现之后，将函数名放到函数指针的位置即可。
return:
	返回上次注册信号处理函数的地址.第一次NULL;
   	failed : SIG_ERR errno	;
使用:
void myalarm(int num){}
signal(SIGALRM,myalarm);

信号集：
    - 未决信号集
    - 阻塞信号集
    在虚拟内存中的内核区PCB中有该两种信号集，用于对传递来的信号进行处理
    使用 64个二进制位 表示信号集对应信号的状态
    未决信号集中 0 表示该信号不是未决状态， 1 表示该信号是未决状态
    阻塞信号集中 0 表示该信号非阻塞 1表示该信号阻塞
    只有当该信号未决且非阻塞时，才会发送给进程进行进一步处理，否则阻塞。
int sigemptyset(sigset_t *set);
功能： 清空信号集中的数据	;
params:
	set : 需要操作的信号集	;
return :
	success : 0	;
	failed : -1 ;

int sigfillset(sigset_t *set);
功能: 将信号集中的数据都置为1	;

int sigaddset(sigset_t *set,int signum);
功能: 设置信号集中某个信号标志位为 1	;

int sigdelset(sigset_t *set,int signum);
功能: 设置信号集中某个信号标志位为 0	;

int sigismember(const sigset_t *set,int signum);
功能:判断信号是否阻塞;
return:
	success : 1 表示被阻塞 0 表示不阻塞;
	failed : -1 调用失败;

int sigprocmask(int how,const sigset_t *set,sigset_t *oldset);
功能: - 将自定义信号集中的数据设置到内核信号集中 可以设置阻塞，解除阻塞，替换;
params:
	how : 如何对信号集进行操作; 
		- SIG_BLOCK 将用户信号集设置的阻塞信号集添加到信号集中，内核的其他数据不变
		- SIG_UNBLOCK 清楚用户在内核中设置的数据,对内核中的数据进行解除阻塞
        - SIG_SETMASK 覆盖内核中原来的值
	set : 已经初始化好的用户自定义的信号集
    oldset : 保存设置之前的内核中阻塞信号集状态，可以是NULL;

int sigpending(sigset_t *set);
功能：获取内核中的未决信号集	;
params:
	set : 保存的内核中的未决信号集的信息;


int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact);
功能: 信号捕捉	;
params:
	signum : 需要捕捉的信号的编号或宏值	;
	act : 捕捉信号之后的处理动作	;
	oldact : 上一次对信号捕捉的设置 一般不使用传递null;

struct sigaction{
    void (*sa_handler)(int);	//捕捉到信号后的处理函数
    void (*sa_sigaction)(int,siginfo_t *,void *);//不常用
    sigset_t sa_mask;//临时阻塞信号集，在信号捕捉函数执行过程中，阻塞某些信号;
    int sa_flags;	//使用哪一个信号处理方式对捕捉到的信号进行处理 0 表示使用sa_handler
    void (*sa_restorer)(void);	//废弃掉了
}

SIGCHLD 信号
    - 子进程结束
    - 子进程暂停
    - 子进程继续执行 

```

