# 管道

```c
int pipe(int pipefd[2]);
创建一个匿名管道进行进程间通信
headers:
	#include <unistd.h>
params:
	pipefd[2] : 用于返回管道的文件描述符 一般的 pipe[0] 表示读端 pipe[1] 表示写端	;
return:
	success : 0	;
	failed : -1	;
匿名管道只能用在具有关系的进程之间。	;

管道的读写操作特点：
    1. 当管道的写端文件描述符都被关闭了，有进程从管道的读端读取数据，如果有剩余数据则读取，读完后再使用read会返回0。
    2. 如果写端文件描述符没有全部被关闭，读完剩余数据后，再read则会阻塞，知道写入新的数据。
    3. 如果读端的文件描述符都关闭了，那么该进程会收到一个信号SIGPIPE,通常会导致进程异常终止
    4. 如果指向管道的读端的文件描述符没有被关闭，而持有管道读端的进程也没有从管道中读数据，这是有进程向管道中写入数据，那么管道被写满时，再次使用write会阻塞，知道管道再次有空位后再写。	;

int mkfifo(const char* pathname,mode_t mode);
创建一个有名管道进行进程间通信	;
严格遵循先进先出原则，对管道的读总是从开始处读取，写则是把数据添加到末尾。
headers:
	#include <sys/types.h>
	#include <sys/stat.h>
params:
	pathname : 名字	;
	mode : 八进制权限	;
return:
	success : 0	;
	failed	: -1 errno	;
有名管道:
	1. 一个为只读而打开的进程会阻塞直到一个为只写而打开的进程产生	;
	2. 一个为只读而打开的进程会阻塞直到一个为只读而打开的进程产生	;


```

