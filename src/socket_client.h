#ifndef SOCKET_TEST_CLIENT_H
#define SOCKET_TEST_CLIENT_H

#include "comm.h"
#include "socket_server.h"

#define client_path  		"/tmp/client.socket"  

typedef struct  _ntpreqheader_ {
#if 0
    unsigned char rm_vn_mode;       	/* response, more, version, mode */
    unsigned char auth_seq;     		/* key, sequence number */
    unsigned char implementation;       /* implementation number */
    unsigned char request;          	/* request number */
    unsigned short err_nitems;      	/* error code/number of data items */
    unsigned short mbz_itemsize;        /* item size */
    char data[40];              		/* data area [32 prev](176 byte max) */
    unsigned long tstamp;           	/* time stamp, for authentication */
    unsigned int keyid;         		/* encryption key */
    char mac[8];        				/* (optional) 8 byte auth code */
#endif
    unsigned char rm_vn_mode;       	/* response, more, version, mode */
    unsigned char stratum;
    unsigned char poll_Interval;
    unsigned char precision;
    unsigned int  root_delay;
    unsigned int  root_dispersion;
    unsigned int  reference_identifier;
    uint64_t      reference_timestamp;
    uint64_t      originate_timestamp;
    uint64_t      receive_timestamp;
    uint64_t      transmit_timestamp;
}ntpreqheader;


#define  NTP_SERVER_IP   		"120.25.115.20"
#define  NTP_REQ_PKT_LEN 		sizeof(struct  _ntpreqheader_)

#define  JAN_1970               0x83aa7e80      //3600s*24h*(365days*70years+17days)
#define  NTPFRAC(x)             (4294 * (x) + ((1981 * (x)) >> 11))
#define  USEC(x)                (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))
#define  MKSEC(ntpt)            ((ntpt).integer - JAN_1970)
#define  MKUSEC(ntpt)           (USEC((ntpt).fraction))
#define  TTLUSEC(sec,usec)      (( long  long )(sec)*1000000 + (usec))
#define  GETSEC(us)             ((us)/1000000)
#define  GETUSEC(us)            ((us)%1000000)
#define  NTP_SERVER_IP   	    "120.25.115.20"
#define  NTP_REQ_PKT_LEN 	    sizeof(struct  _ntpreqheader_)
#define  LI                     0             //协议头中的元素
#define  VN                     3             //版本
#define  MODE                   3             //模式 : 客户端请求
#define  STRATUM                0
#define  POLL                   4             //连续信息间的最大间隔

typedef struct
{
    unsigned int integer;
    unsigned int fraction;
} NtpTime;


WORD32 socket_client_domain_init(void);







#endif


