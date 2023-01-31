# 第2章 套接字协议及其数据传输特性
```c
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

## 2.1 domain
domain是套接字中使用的协议族(Protocol Family)信息  
|名称|协议族|
|:-:|:-:|
|PF_INET|IPv4互联网协议族|
|PF_INET6|IPv6互联网协议族|
|PF_LOCAL|本地通信的UNIX协议族|
|PF_PACKET|底层套接字的协议族|
|PF_IPX|IPX Novell协议族|

## 2.2 type
type是数据传输方式
## 2.2.1 面向连接的(SOCK_STREAM)
## 2.2.2 无连接的(SOCK_DGRAM)

## 2.3 protocol
protocol是具体的协议，一般domain和type即可确定所用协议，故protocol一般取0  

若存在 “同一协议族中存在多个数据传输方式相同的协议” 情况，则需要通过protocol参数指定协议