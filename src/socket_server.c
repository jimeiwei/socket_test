#include "socket_server.h"
#include "socket_epoll.h"

WORD32 socket_server_domain_init(void)
{
	struct  sockaddr_un serun, cliun;
    int server_fd = 0;
	int connfd    = 0;
	char buf[100] = {0};
	int on = 1;
	int pkt_read_len = 0;
	socklen_t clilen = 0;
	
	unlink(server_path);
	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket server socket error");
		return COMM_ERR;
	}

	if((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{  
		perror("setsockopt failed");	
		return COMM_ERR;
	}

	memset(&serun, 0, sizeof(struct sockaddr_un));
	serun.sun_family = AF_UNIX;
    strncpy(serun.sun_path, server_path, sizeof(serun.sun_path) - 1);
	
	if (bind(server_fd, (const struct sockaddr *)&serun, sizeof(struct sockaddr_un)) < 0) {
		perror("bind failed");
		return COMM_ERR;
    }
	
	if (listen(server_fd, 20) < 0) 
	{  
		return COMM_ERR;
    }

	while(1)
	{
        connfd = accept(server_fd, (struct sockaddr *)&cliun, &clilen);
		if (connfd == -1)
		{  
			continue;
        }

		pkt_read_len = read(connfd, buf, 100);
		if (pkt_read_len == -1)
		{
			dzlog_error("socket server read error");
			return COMM_ERR;
		}
		printf("read buf:%s\n", buf);

		break;
	}
}



int socket_server_tcp_init(void)
{
	int listen_fd = -1;
	int ret = 0;
	int on  = 1;
	struct sockaddr_in socket_server_buff = {0};
	socket_event_t event = {0};

	listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_fd == -1)
	{
		perror("socket failed");
		return COMM_ERR;
	}

	if((setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{
		perror("setsockopt failed");
		return COMM_ERR;
	}

	socket_server_buff.sin_family = AF_INET;
	socket_server_buff.sin_port   = htons(8800);
	socket_server_buff.sin_addr.s_addr = htonl(INADDR_ANY);               // 任意ip地址。

	if (bind(listen_fd, (const struct sockaddr *)&socket_server_buff, sizeof(struct sockaddr_in)) < 0) {
		perror("bind failed");
		return COMM_ERR;
	}

	if (listen(listen_fd, 20) < 0)
	{
		perror("listen failed");

		return COMM_ERR;
	}

	return listen_fd;
}
