#include "socket_client.h"


WORD32 socket_client_domain_init(void)
{
	struct  sockaddr_un serun;
    int client_fd = 0;  
    int len, pkt_read_len = 0;  
	char buf[100] = {0};
	int on = 1;
	
	client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (client_fd < 0)
	{
		dzlog_error("socket client socket error");
		return COMM_ERR;
	}
	
	if((setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{  
		perror("setsockopt failed");	
		dzlog_error("socket client setsockopt error");
		return COMM_ERR; 
	}
	
	memset(&serun, 0, sizeof( struct sockaddr_un));
	serun.sun_family = AF_UNIX;
	strncpy(serun.sun_path, server_path, sizeof(serun.sun_path) - 1);
	
	if (connect(client_fd, (struct sockaddr *)&serun, sizeof(struct sockaddr_un)) < 0)
	{  
		perror("connect");
		dzlog_error("socket client connect error");
		return COMM_ERR;   
	}  

	strcpy(buf, "test");
	
	len = write(client_fd, buf, strlen(buf) + 1);
	if (len == -1)
	{
		perror("write");
		dzlog_error("socket client write error");
		return COMM_ERR;
	}
	return COMM_OK;
}


int socket_client_tcp_init(void)
{
	int client_fd = -1;
	int on  = 1;
	struct sockaddr_in socket_client_buff = {0};

	client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_fd == -1)
	{
		perror("socket failed");
		return COMM_ERR;
	}

	if((setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{
		perror("setsockopt failed");
		return COMM_ERR;
	}

	socket_client_buff.sin_family = AF_INET;
	socket_client_buff.sin_port   = htons(8800);
	socket_client_buff.sin_addr.s_addr = inet_addr("172.16.47.130");    // 指定ip地址。

	if (connect(client_fd, (struct sockaddr *)&socket_client_buff, sizeof(struct sockaddr_in)) < 0)
	{
		perror("connect");
		return COMM_ERR;
	}
}