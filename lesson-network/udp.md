# UDP

```C++
#include <sys/types.h>
#include <sys/socket.h>

ssize_t sendto(int sockfd,const void *buf,size_t len,int flags,const struct sockaddr *dest_addr,socklen_t addrlen);
params:
	sockfd : 要通信的fd;
	buf : 要发送的数据;
	len : 要发送的数据的长度;
	flags : 设置标志;
	dest_addr : 目的地sock地址;
	addrlen : 地址的大小;

ssize_t recvfrom(int sockfd,void* buf,size_t len,int flags,struct sockaddr *src_addr,socklen_t *addrlen);
params:
	sockfd : 通信的fd;
	buf : 接收的数据;
	len : 长度;
	flags : 标志;
	src_addr : 发送方的sock地址;
	addrlen : 长度;


广播:
int setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen);
params:
	sockfd : 文件描述符;
	level : SOL_SOCKET;
	optname : SOL_BROADCAST;
	optval : 为1 允许广播;
	optlen : optval 的大小;

组播:
int setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen);
params:	
	//服务器设置多播的信息，外出接口
	level : IPPROTO_IP;
	optname : IP_MULTICAST_IF;
	optval : struct in_addr;


	//客户端加入多播组
	level : IPPROTO_IP;
	optname : IP_ADD_MEMBERSHIP;
	optval : struct mreqn;
```

