#include "socket_epoll.h"

int g_epoll_fd = -1;

void socket_epoll_init(void)
{	
	g_epoll_fd = epoll_create(1);
	if(g_epoll_fd == -1)
	{
		perror("epoll_create fail");
		return COMM_ERR;
	}
}

int socket_epoll_add_event_epoll(socket_event_t* ev, int op)
{
	int ret = 0;
	struct epoll_event event;
	strncpy(ev->handler_ptr.data, "test:ADD", strlen("test:ADD"));

	event.events = op;
	event.data.ptr = ev;

	if (epoll_ctl(g_epoll_fd, EPOLL_CTL_ADD, ev->fd, &event) == -1) {
		perror("epoll_ctl:EPOLL_CTL_ADD");
		return COMM_ERR;
	}

	return COMM_OK;
}

int socket_epoll_del_event_epoll(socket_event_t* ev)
{
	int ret = 0;
	struct epoll_event event;

	strncpy(ev->handler_ptr.data, "test:DEL", strlen("test:DEL"));

	event.data.ptr = ev;

	if (epoll_ctl(g_epoll_fd, EPOLL_CTL_DEL, ev->fd, &event) == -1) {
		perror("epoll_ctl:EPOLL_CTL_DEL");
		return COMM_ERR;
	}

	return COMM_OK;
}


int socket_epoll_process_event(int timer)
{
	int i = 0;
	int epoll_wait_rtn_num = 0;
	struct _socket_event_s* ev = NULL;
	struct epoll_event events[MAX_EPOLL_NUM] = {0};
	int wait_timer = -1;

	if (timer > 0)
	{
		wait_timer = timer;
	}

	epoll_wait_rtn_num = epoll_wait(g_epoll_fd, events, MAX_EPOLL_NUM, wait_timer);
	if (epoll_wait_rtn_num == -1) {
		perror("epoll_wait");
		return COMM_ERR;
	}

	for (i = 0; i < epoll_wait_rtn_num; i++)
	{
		ev = events[i].data.ptr;
		ev->handler(&ev->handler_ptr);
	}

	return COMM_OK;
}