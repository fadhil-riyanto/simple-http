#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "http.h"

#define SERVER "127.0.0.1"
#define PORT 8000

static void init_sock_fd(struct http_stack *http_stack) 
{
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket()");
        _exit(-1);
    }

    http_stack->sockfd = fd;
}

static void connect2server(struct http_stack *http_stack) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, SERVER, &addr.sin_addr) != 1) {
        perror("invalid host");
        close(http_stack->sockfd);
    }
    addr.sin_port = htons(PORT);
    printf("connecting");

    if (connect(http_stack->sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");

        close(http_stack->sockfd);
    }
    
}

static void do_work(struct http_stack *http_stack) {
    char payload[] = "GET / HTTP/1.1\r\n\r\n";
    printf("%s", payload);
    send(http_stack->sockfd, &payload, sizeof(payload), 0);
    
}


static void cleanup(struct http_stack *http_stack) {
    close(http_stack->sockfd);
}

int main() 
{
    struct http_stack http_stack;

    memset(&http_stack, 0, sizeof(struct http_stack));
    
    init_sock_fd(&http_stack);
    connect2server(&http_stack);
    do_work(&http_stack);
    cleanup(&http_stack);
    return 0;
}
