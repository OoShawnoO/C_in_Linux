# Socket

```c
socket网络编程接口中表示socket地址的结构体是sockaddr;

struct sockaddr{
    sa_family_t sa_family; #地址族的类型
    char sa_data[14]; #地址数据
};

typedef unsigned short int sa_family_t;

struct sockaddr_storage{
	sa_family_t sa_family;
    unsigned long int _ss_align;	#内存对齐
    char __ss_padding[128-sizeof(__ss_align)];
}

专用socket 地址
struct sockaddr_in{
    sa_family sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[sizeof(struct sockaddr)-__SOCKADDR_COMMON_SIZE - sizeof(in_port_t) - sizeof(struct in_addr)];
}

struct in_addr{
    in_addr_t s_addr;
}

struct sockaddr_in6{
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfO;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
}

IP地址转换: 将字符串ip转换为整数 主机、网络字节序的转换;
#include <arpa/inet.h>
in_addr_t inet_addr(const char *cp);

int inet_aton(const char *cp,struct in_addr *inp); #将字符串Ip 转换为网络字节序;

char *inet_ntoa(struct in_addr in);#网络字节序 转换为ip 字符串;

以上不推荐使用;

#include <arpa/inet.h>
int inet_pton(int af,const char *src, void *dst); # p表示点分十进制字符串 n表示网络字节序的整数;
params:
	af : 地址族 AF_INET AF_INET6;
	src : 要转换的字符串;
	dst : 转换后的结果保存在其中;

const char *inet_ntop(int af,const void *src,char *dst,socklen_t size);
params:
	af : 地址族 AF_INET AF_INET6;
	src : 要转换的ip的整数地址;
	dst : 转换后保存的地方;
	size : 第三个参数的大小;
return:
	与dst是同一个值;


//TCP 通信流程
//服务器端
1. 创建一个用于监听的套接字
    - 监听 : 监听有客户端的链接
    - 套接字 : 这个套接字其实就是一个文件描述符
2. 将监听的文件描述符和本地的ip和端口绑定（ip和端口就是服务器的地址信息）
    - 客户端连接服务器的时候使用的就是这个IP 和 端口
3. 设置监听，监听的fd开始工作;
4. 阻塞等待，当有客户端发起连接，解除阻塞，接收客户端的链接，会得到一个和客户端通信的套接字;
5. 开始通信
    - 接收数据
    - 发送数据
6. 断开连接
    
//客户端
1. 创建用于通信的套接字
2. 连接的服务器需要指定Ip和端口
3. 连接成功后，客户端可以直接和服务器端通信:
	- 接收数据
    - 发送数据
4.通信结束断开连接
        
        
socket 函数 :
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int socket(int domain,int type,int protocol);
创建套接字
params:
	domain : 协议族 AF_UNIX,AF_LOCAL,AF_INET,AF_INET6;
	type : 通信过程中使用的协议类型
        - SOCK_STREAM 流式协议 字节流
        - SOCK_DGRAM 报式协议 数据报
   	protocol : 具体的协议.一般传0
        - SOCK_STREAM + 0 表示默认TCP
        - SOCK_DGRAM + 0 表示默认UDP
return:
	success : 文件描述符 (操作的内核缓冲区)
    failed : -1 
int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
绑定端口
params:
	sockfd : 通过socket函数获得的文件描述符
    sockaddr : 需要绑定的socket地址，这个地址封装了ip和端口号的信息;	
	addrlen : 第二个参数占用的内存大小
return:
	success : 0	;
	failed : -1	;

int listen(int sockfd,int backlog);
监听socket上的连接
params:
	sockfd : socket函数返回的文件描述符
    backlog : 未连接的和已经连接的和的最大值 一般使用 5

int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
服务器端调用接收客户端的连接 阻塞等待客户端连接
params:
	sockfd : 文件描述符	;
	*addr : 传出参数 记录连接成功后客户端的地址信息 /(ip,端口);
	addrlen : 指定第二个参数的对应内存大小
return :
	success : 返回用于通信的文件描述符(服务器端)
	failed : -1
int connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
客户端连接服务器
params:
	sockfd : socket生成的文件描述符;
	addr : 客户端要连接的服务器的地址信息;
	addrlen : 第二个参数的内存大小;

ssize_t write(int fd,const void *buf,size_t count);

ssize_t read(int fd,void *buf,size_t count);
```

