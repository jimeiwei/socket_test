#include "comm.h"
#include "socket_client.h"
#include "socket_server.h"
#include <linux/fs.h>
#include "socket_epoll.h"

void rtc_read_time(int fd)
{
	int retval;
	struct rtc_time rtc_tm;
	/*read the RTC time/date*/
	retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
	if (retval == -1) {
		perror("RTC_RD_TIME ioctl");
		exit(errno);
	}
	printf("Current RTC date time is %d-%d-%d, %02d:%02d:%02d.\n",
	        rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
	        rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
}

void printf_test(socket_info_t* s_info)
{
	printf("@test:%s\n", s_info->data);
}

int main()
{
	WORD32 ret = 0;
	int listen_fd = -1;
	socket_event_t server_ev = {0};

	ret = comm_zlog_init();
	COMM_CHECK_RTN(ret, COMM_OK);

#ifdef __CLIENT__
	socket_client_tcp_init();
#endif
	
#ifdef __SERVICE__
	socket_epoll_init();
	listen_fd = socket_server_tcp_init();
	if(listen_fd == -1)
	{
		printf("server tcp init fail\n");
		return COMM_ERR;
	}

	server_ev.fd = listen_fd;
	strcpy(server_ev.handler_ptr.data, "server epoll init");
	server_ev.handler = printf_test;    //init_connection

	ret = socket_epoll_add_event_epoll(&server_ev, EPOLLIN);
	COMM_CHECK_RTN(ret, COMM_OK);

	while(1)
	{
		socket_epoll_process_event(-1);
	}

#endif

	zlog_fini();
	return COMM_OK;
}

