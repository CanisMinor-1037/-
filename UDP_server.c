/* C13.1.a: UDP server.c file */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#define BUFLEN 256  // MAX length of buffer
#define PORT 1234   // fixed server port number

char line[BUFLEN];
struct sockaddr_in me, client;
int sock, rlen, clen = sizeof(client);

int main()
{
    printf("1. create a UDP socket\n");
    // 创建一个用于发送和接收UDP数据报的套接字
    // 新创建的套接字没有任何相联地址
    // 它必须与主机地址和端口号绑定，以识别接收主机或发送主机
    sock = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);

    printf("2. fill me with server address and port number\n");
    memset((char *)&me,0,sizeof(me));
    me.sin_family = AF_INET;
    me.sin_port = htons(PORT);
    me.sin_addr.s_addr = htonl(INADDR_ANY); // use localhost

    printf("3. bind socket to server IP and port\n");
    bind(sock,(struct sockaddr *)&me,sizeof(me));

    printf("4. wait for datagram\n");
    while(1)
    {
        memset(line,0,BUFLEN);
        printf("UDP server: waiting for datagram\n");
        // recvfrom() gets client IP, port in sockaddr_in client
        rlen = recvfrom(sock,line,BUFLEN,0,(struct sockaddr*)&client,&clen);
        printf("received a datagram form [host:port] = [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        printf("rlen=%d: line=%s\n",rlen,line);
        printf("send reply\n");
        sendto(sock,line,rlen,0,(struct sockaddr *)&client,clen);
    }
}