#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "http.h"

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

static void do_work(struct http_stack *http_stack) {
    while (1) {
        
    }
}


static void cleanup(struct http_stack *http_stack) {
    close(http_stack->sockfd);
}

int main() 
{
    struct http_stack http_stack;
    
    init_sock_fd(&http_stack);

    // eventloop
    do_work(&http_stack);
    cleanup(&http_stack);
    return 0;
}
