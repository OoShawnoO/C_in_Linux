# TCP

### 三次握手

- SYN 请求建立连接位
- ACK 确认位
- seq 序号
- ack 确认序号

第一次握手 Client SYN=1 seq=J-----> Server

第二次握手 Server SYN=1 ACK=1 ack=J+1 seq=K ------> Client

第三次握手 Client ACK=1 ack=K+1 -----> Server

确认连接后:

数据传输:

Client seq=1001(100) ack=K+1	 -----> 	 Server

Server ack=1101 		-------> 			Client

Client seq=1101(200) ack=2001 -------> 	  Server

Server ack=1301  	------->				Client



第一次握手: 

1. 客户端将SYN置为1

2. 生成一个随机的32位的序号seq = J，这个序号后边是可以携带数据（数据大小)

第二次握手：

1. 服务器端接收客户端的连接,ACK = 1
2. 服务器会回发一个确认序号：ack=客户端的序号(J) + 数据长度 + SYN/FIN(按一个字节算)
3. 服务器端向客户端发起连接请求： SYN = 1
4. 服务器会生成一个随机序号 seq = K

第三次握手:

1. 客户端应答服务器端的连接请求: ACK = 1
2. 客户端回复收到了服务器端的数据：ack = 服务器端的序号 + 数据长度 + SYN/FIN(按一个字节算)



### 滑动窗口

一种流量控制技术

窗口理解为缓冲区的大小

滑动窗口的大小会随着发送和接收数据而变化

通信的双方都有发送和接收数据的缓冲区

服务器：

 - 发送缓冲区 （发送缓冲区的窗口）
 - 接收缓冲区  (接收缓冲区的窗口)

客户端：

- 发送缓冲区 （发送缓冲区的窗口）
- 接收缓冲区  (接收缓冲区的窗口)

![屏幕截图 2022-08-05 120603](C:\Users\84083\Desktop\屏幕截图 2022-08-05 120603.png)

发送方的缓冲区：

 - 白色格子代表空闲
 - 灰色格子代表数据已经发送但是还未接收
 - 紫色格子代表还没有发送出去的数据

接收方的缓冲区：

- 白色格子代表空闲
- 紫色格子代表已经接收到的数据

![屏幕截图 2022-08-05 121231](C:\Users\84083\Desktop\屏幕截图 2022-08-05 121231.png)

```
mss : Maximum Segment Size 一条数据的最大大小
win : Window 滑动窗口
1.客户端向服务器发起连接，客户端的滑动窗口4096，一次发送的最大数据是1460
2.服务器接收连接情况，告诉客户端服务器端的窗口大小是6144，一次发送的最大数据是1024
3.第三次握手
4.4-9 客户端连接给服务器发送6k的数据，每次发1k
5.第10次，服务器告诉客户端，发送的6k已经接到，存储在缓冲区中，缓冲区已经处理了2k，窗口大小为2k
6.第11次，服务器告诉客户端，发送的6k已经接到，存储在缓冲区中，缓冲区已经处理了4k，窗口大小是4k
7.第12次，客户端给服务器端发送了1k数据
8.第13次，客户端主动请求和服务器断开连接，并且给服务器端发送了1k数据
9.第14次，服务器回复ack=8194，同意断开，告诉客户端已经接收到2k的数据，滑动窗口为2k
10.第15、16次,通知客户端滑动窗口的大小
11.第17次，第三次挥手，服务器端给客户端发送断开请求
12.第18次，客户端同意断开请求
```

### 4次挥手

FIN 表示断开连接

Client FIN =1 -------> Server

Server ACK =1 -------> Client

Server FIN =1 -------> Client

Client ACK =1 --------> Server



### TCP 通信并发

要实现TCP的通信并发，需要使用到多进程或多线程

思路：

1. 一个父进程，多个子进程
2. 父进程只负责等待并接受客户端的链接
3. 子进程：完成通信，接受一个客户端请求，就创建一个子进程用于通信



### TCP 状态转换

2MSL : Maximum Segement Lifetime 两倍最大生存时间.

半关闭 : 当TCP连接中A向B发送FIN请求关闭，另一端B回应ACK(A端进入FIN_WAIT_2 状态),并没有立即发送FIN给A，A方处于半连接状态，此时A可以接收B的数据，但是A不能再向B发送数据.

```c
#include <sys/socket.h>
int shutdown(int sockfd,int how);
params:
	sockfd : 需要关闭的文件描述符;
	how : 允许shutdown操作的方式:
		- SHUT_RD(0):关闭读
        - SHUT_WR(1):关闭写
        - SHUT_RDWR(2):关闭读写
```

### TCP 端口复用

```c
最常用的用途:
1. 防止服务器重启时之前绑定的端口还未释放
2. 程序突然退出而系统没有释放端口
#include <sys/types.h>
#include <sys/socket.h>
int setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen);
params:
	sockfd : 要操作的文件描述符
    level : 级别 - SOL_SOCKET(端口复用的级别)
    optname : 选项的名称 - SO_REUSEADDR 可复用地址 SO_REUSEPORT 可复用端口
    optval : 端口复用的值 1 可以复用 0不可复用
    optlen : optval参数大小
```



网络相关的指令:

netstat

params:

​	-a 所有socket

​	-p 显示正在使用socket的程序名称

​	-n 直接显示IP地址，而不通过域名服务器



### I/O 多路复用

```c
I/O 多路复用（多路转接） 使得程序可以同时监听多个文件描述符，提高程序的性能，Linux下实现I/O多路复用的系统调用主要有select、poll和epoll;
```

#### select 

```c
首先构造一个关于文件描述符的列表，将要监听的文件描述符添加到该列表中
调用一个函数监听该列表中的文件描述符，直到这些描述符中的一个或多个进行I/O操作，该函数才会返回
    这个函数是阻塞的
    函数对文件描述符的检测是由内核完成的
在返回时，会告诉进程有多少描述符要进行I/O
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.
#include <unistd.h>
int select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,struct timeval *timeout);
params:
	nfds : 委托内核检测的文件描述符的最大值+1
    readfds : 要检测的文件描述符的读的集合，委托内核检测那些文件描述符的读属性
        	- 检测的是读缓冲区，是一个传入传出参数
    writefds : 要检测的文件描述符的写的集合，委托内核检测那些文件描述符的写属性
        	 - 委托内核检测写缓冲区是否还能写数据（不满可写）
    exceptfds : 检测发生异常的文件描述符的集合
        	  - NULL 永久阻塞
        	  - tv_sec = 0 tv_usec = 0 表示非阻塞
        	  - tv_sec > 0 tv_usec > 0 阻塞对应的时间
    timeout : 
	struct timeval{
		long tv_sec;
        long tv_usec;
    }
return:
	failed : -1
    success : >0(n) 检测到n个文件描述符发生了变化;

将参数文件描述符对应的标志位进行设置
    
void FD_CLR(int fd,fd_set *set);	//清空

int FD_ISSET(int fd,fd_set *set); //判断

void FD_SET(int fd,fd_set *set);	//设置

void FD_ZERO(fd_set *set);	//全部初始化为0
```



### poll

```c
#include <poll.h>
struct pollfd{
    int fd;	/* 委托内核检测的文件描述符 */
    short events; /* 委托内核检测什么事件 */
    short revents; /* 文件描述符实际发生的事件*/
};
int poll(struct pollfd *fds,nfds_t nfds,int timeout);
params:
	fds : 需要检测的文件描述符的集合
    nfds : 这是第一个参数数组中最后一个有效元素的下标+1、
    timeout : 阻塞时长 0:不阻塞 -1:阻塞，当检查到fd有变化解除阻塞 >0:阻塞时长（ms)
```



### epoll

```c
#include <sys/epoll.h>
//创建一个epoll实例。在内核中创建了一个数据，这个数据有两个比较重要的数据，一个是需要检测的文件描述符的信息（红黑树），还有一个是就绪列表，存放检测到的数据发生改变的文件描述符信息（双向链表）
int epoll_create(int size);
params:
	size : 目前已经没有意义了 随便写个数但是必须大于0;
return:
	success :  >0 表示文件描述符用于操作epoll实例
    failed : -1;

typedef union epoll_data{
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
}epoll_data_t;

struct epoll_event{
    uint32_t events;
    epoll_data_t data;
}
//常见的epoll检测时间
	- EPOLLIN
	- EPOLLOUT
    - EPOLLERR
        
//对epoll实例进行管理,添加，删除，修改文件描述符信息、
int epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);
params:
	epfd : epoll实例对应的文件描述符;
	op : 选项，要进行什么样的操作
        - EPOLL_CTL_ADD 添加
        - EPOLL_CTL_MOD 修改
        - EPOLL_CTL_DEL 删除
    fd : 我们要检测的文件描述符的值
    event : 检测文件描述符的什么事情

//检测函数
int epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout);
params:
	epfd : epoll实例对应的文件描述符;
	events : 传出参数，保存了发送了变化的文件描述符的信息
    maxevents : 第二个参数结构体数组的大小
    timeout : 阻塞时间
   			- 0 不阻塞
        	- -1 阻塞，直到检测到fd数据发生变化，解除阻塞
        	- >0 阻塞的时长(毫秒)
return:
	success : 返回发生变化的文件描述符的个数
    failed : -1
```

### epoll的两种工作模式

- LT (level-triggered)(默认) 水平触发模式，是缺省的工作模式，并且同时支持block和non-block socket.在这种做法中,内核会告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的fd进行IO操作，如果你不做任何操，内核还是会继续通知你

  ```c++
  假设委托内核检测读事件->检测fd的缓冲区
      读缓冲区有数据->epoll检测到了会给用户通知
      a.用户不读数据，数据也一直在缓冲区中，epoll会一直通知
      b.用户只读了一部分数据，epoll会通知
      c.缓冲区的数据读完了，不通知
  ```

  

- ET (edge-triggered) 边沿触发模式，是高速工作模式，只支持no-block socket,在这种模式下，从描述符从未就绪变为就绪时，内核通过epoll告诉你，然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的通知，直到你做了某些操作导致那个文件描述符不再为就绪状态了，但是请注意，如果一直不对这个fd做IO操作，内核不会发送更多的通知。

  ```c++
  假设委托内核检测读事件->检测fd的缓冲区
      读缓冲区有数据->epoll检测到了会给用户通知
      用户不读数据，数据一直在缓冲区,epoll下次检测时就不通知了
      用户读了部分数据，epoll不通知
      缓冲区的数据读完了，不通知
      
  struct epoll_event{
      uint32_t events;
      epoll_data_t data;
  }
  //常见的epoll检测时间
  	- EPOLLIN
  	- EPOLLOUT
      - EPOLLERR
      - EPOLLET (ET模式) 在客户端连接生成客户端文件描述符时为监听事件加上ET模式
  
  需要设置客户端文件描述符非阻塞
  int flag = fcntl(clientfd,F_GETFL);
  flag = flag | O_NONBLOCK;
  fcntl(clientfd,F_SETFL,flag);
  ```

  
