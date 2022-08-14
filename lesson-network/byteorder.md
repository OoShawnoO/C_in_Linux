# 字节序

```c
union{
    short value;
    char bytes[sizeof(short)];
}test;

test.value = 0x0102;
if(test.bytes[0] == 1 && test.bytes[1] == 2){大端}
else{小端}

#include <arpa/inet.h>
uint16_t htons(uint16_t hostshort); # host byte order - > net byte order
uint16_t ntohs(uint16_t netshort); # net byte order - > host byte order
uint32_t htonl(uint32_t hostlong); # host byte order - > net byte order
uint32_t ntohl(uint32_t netlong); # net byte order - > host byte order
```

