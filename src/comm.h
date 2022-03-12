//
// Created by jimeiwei on 2021/9/26.
//

#ifndef SOCKET_TEST_COMM_H
#define SOCKET_TEST_COMM_H

#include <stdlib.h>  
#include <stdio.h>  
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <string.h>  
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/un.h>
#include <pthread.h>
#include <linux/hdreg.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/un.h>
#include <sys/msg.h>
#include <linux/rtc.h>
#include <sys/xattr.h>
#include <sys/utsname.h>
#include "zlog.h"

#define  COMM_OK 			 		0x0
#define  COMM_ERR			 		0x1
#define  WORD32               		unsigned int
#define	 SKSERVER_ZLOG_FILE			"./conf/zlog_socket_test.conf"

extern zlog_category_t *comm_category;

#define  COMM_DEBUG(format,...) 	printf("[ debug ]"format,##__VA_ARGS__)  

#define COMM_CHECK_RTN(rc, rtn)       \
		if (rc != COMM_OK){	         			\
            dzlog_error("Return error in File: [%s] Func: [%s] Line: [%d], Except %d But Return %d.",__FILE__ ,__func__, __LINE__, rtn, rc); \
			return 	COMM_ERR;\
		}
		
#define COMM_CHECK_POINT(point)\
		if (point == NULL)	{		 \
			dzlog_error("Point error in File: [%s] Func: [%s] Line: [%d].",__FILE__ ,__func__, __LINE__); \
			return COMM_ERR;			\
		}
		
#define COMM_CHECK_INDEX(index, min, max)\
		if (index > max || index < min)	{ \
			dzlog_error("Index error in File: [%s] Func: [%s] Line: [%d], Index=[%d], Range=[%d,%d].",__FILE__ ,__func__, __LINE__, (int)index, (int)min, (int)max); \
			return COMM_ERR;			\
		}


WORD32 comm_init(void);

WORD32 comm_check_file_exist(char* file);

WORD32 comm_create_file(char* file);

WORD32 comm_write_to_file(const char *path, char *buffer, int buflen);

WORD32 comm_get_file_all(char *path, char *buffer, int buflen);

WORD32 comm_zlog_init(void);

#endif //OPENSSL_TEST_COMM_H
