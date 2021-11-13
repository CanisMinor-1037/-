/* C13.2.a: TCP server.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MAX 256
#define SERVER_HOST "localhost"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234

struct sockaddr_in server_addr, client_addr;
int mysock, csock;  // socket descriptors
int r, len, n;      // help variables

int server_init()
{
    printf("================= server init =================\n");
    // create a TCP socket by socket() syscall

    printf("1: create a TCP STREAM socket\n");
    // 创建一个用于发送和接收数据流的面向连接的TCP套接字
    mysock = socket(AF_INET,SOCK_STREAM,0);

    if(mysock == 0)
    {
        printf("socket call failed\n");
        exit(1);
    }

    printf("2: fill server_addr with host IP and PORT# info\n");
    // initialize the server_addr structure
    server_addr.sin_family = AF_INET;   // for TCP/IP
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // HOST IP
    server_addr.sin_port = htons(SERVER_PORT);  // port number 1234

    printf("3: bind socket to server address\n");
    r = bind(mysock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(r<0)
    {
        printf("bind failed\n");
        exit(3);
    }
    printf("\thostname = %s port = %d\n",SERVER_HOST,SERVER_PORT);

    printf("4: server is listening ....\n");
    listen(mysock, 5);  // queue length = 5
    printf("================ init done =================\n");
}

int main()
{
    char line[MAX];
    server_init();
    while(1)    // Try to accept a client request
    {
        printf("server: accepting new connection ....\n");
        // Try to accept a client connection as descriptor newsock
        len = sizeof(client_addr);
        csock = accept(mysock,(struct sockaddr *)&client_addr,&len);
        if(csock < 0)
        {
            printf("server: accept error\n");
            exit(1);
        }
        printf("server: accepted a client connection from\n");
        printf("-------------------------------------------\n");
        printf("Client: IP=%s\tport=%d\n",
            inet_ntoa(client_addr.sin_addr),
            ntohs(client_addr.sin_port));
        printf("-------------------------------------------\n");
        // Processing loop: client_sock <== data ==> client
        while(1)
        {
            n = read(csock,line,MAX);
            if(n == 0)
            {
                printf("server: client died, server loops\n");
                close(csock);
                break;
            }
            // show the line string
            printf("server: read n=%d bytes; line=%s\n",n,line);
            // echo line to client
            n = write(csock,line,MAX);
            printf("server: wrote n=%d bytes; ECHO=%s\n",n,line);
            printf("server: ready for next request\n");
        }
    }
}