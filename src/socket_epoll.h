#ifndef SOCKET_TEST_EPOLL_H
#define SOCKET_TEST_EPOLL_H

#include "comm.h"

#define MAX_EPOLL_NUM   50

typedef struct socket_info_s
{
	char data[30];
}socket_info_t;

typedef void(* epoll_evevt_handler_ptr)(socket_info_t* handler_ptr);

struct  _socket_event_s
{
    int fd;
    socket_info_t handler_ptr;
	epoll_evevt_handler_ptr handler;
};

typedef struct _socket_event_s socket_event_t;














#endif

