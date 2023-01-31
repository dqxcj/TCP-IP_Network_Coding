# 第1章 理解网络编程和套接字
## 1.1 网络编程和套接字
### 1.1.1 服务端
1. “安装电话机”  socket
```c
#include <sys/socket.h>
// domain: 协议族
// type: 数据传输类型
// protocol: 协议；domain决定protocol的范围
int socket(int domain, int type, int protocol);
```
成功返回文件描述符，失败返回-1


2. “分配电话号码” bind
```c
#include <sys/socket.h>
int bind(int sockfd, struct sockaddr *myaddr, socklen_t adddrlen);
```
成功返回0，失败返回-1


3. “连接电话线” listen
```c
#include <sys/socket.h>
int listen(int socket, int backlog);
```
成功返回0，失败返回-1


4. “拿起话筒” accept
```c
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
成功返回文件描述符，失败返回-1  
执行到accept时若无连接请求，则不会返回，直到有连接请求为止


4返回的文件描述符与1返回的文件描述符不同，4的描述符用于标识当前的连接；1的描述符用于建立连接，可用于多个连接



### 1.1.2 客户端
1. socket
2. “打电话” connect
```c
#include <sys/socket.h>
int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
```
成功返回0，失败返回-1



## 1.2 基于Linux的文件操作
### 1.2.1 打开文件
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// path: 文件名字符串地址
// flag: 打开模式
int open(const char *path, int flag);
```
成功返回文件描述符，失败返回-1

|打开模式|含义|
|:-:|:-:|
|O_CREAT|必要时创建文件|
|O_TRUNC|删除全部现有数据|
|O_APPEND|维持现有数据，保存到其后面|
|O_RDONLY|只读打开|
|O_WRONLY|只写打开|
|O_RDWR|读写打开|


### 1.2.2 关闭文件
```c
#include <unistd.h>
int close(int fd);
```
成功时返回0，失败时返回-1

### 1.2.3 将数据写入文件
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t nbytes);
```
成功返回写入的字节数，失败返回-1  
size_t是用typedef声明的unsigned int 类型  
ssize_t第一个s是signed，即ssize_t是typedef声明的signed int类型

### 1.2.4 读取文件中的数据
```c
#include <unistd.h>
ssize_t read(int fd)
```
成功返回接收的字节数（但遇到文件结尾则返回0），失败返回-1