#include "comm.h"

zlog_category_t *comm_category;

WORD32 comm_init(void)
{
	WORD32 ret = 0;

	ret = comm_zlog_init();
	COMM_CHECK_RTN(ret, COMM_OK)
	
	printf("comm init success\n");

	return COMM_OK;
}

/*return: SKS_OK 文件存在，SKS_ERROR 文件不存在*/
WORD32 comm_check_file_exist(char* file)
{
	WORD32 rtn = 0;
	struct stat statbuff;

	COMM_CHECK_POINT(file);
	
	if (!stat(file, &statbuff))
    {
		return COMM_OK;
	}
	
	dzlog_error("file [%s] not exist", file);
	
	return COMM_ERR;
}

WORD32 comm_create_file(char* file)
{
	FILE* fp = NULL;
	COMM_CHECK_POINT(file);

	fp = fopen(file, "w+");
	if (!fp)
	{
		return COMM_ERR;
	}
	fclose(fp);
	
	if (comm_check_file_exist(file))
	{
		return COMM_ERR;
	}
	
	return COMM_OK;
}

WORD32 comm_write_to_file(const char *path, char *buffer, int buflen)
{
	FILE *fp = NULL;
	
	COMM_CHECK_POINT(path);
	COMM_CHECK_POINT(buffer);

    fp = fopen(path, "wb+");
    COMM_CHECK_POINT(fp);
	
    if(fp == NULL)
	{
        dzlog_error("fopen file %s failed", path);
        return COMM_ERR;
    }
	
    fwrite(buffer, 1, buflen, fp);
    fclose(fp);
	
    return COMM_OK;
}

WORD32 comm_get_file_all(char *path, char *buffer, int buflen)
{
    size_t ret = 0;
    FILE *fp = NULL;
	
    COMM_CHECK_POINT(path);
    COMM_CHECK_POINT(buffer);
	
    fp = fopen(path, "r");	
    if(fp == NULL)
	{
		dzlog_error("fopen file %s failed", path);
        return COMM_ERR;
    }
	
    ret = fread(buffer, 1, buflen, fp);
    if (ret < 0)
	{
		dzlog_error("fread failed");
	}
	
    fclose(fp);
	
    return COMM_OK;
}

WORD32 comm_zlog_init(void)
{
	if(zlog_init(SKSERVER_ZLOG_FILE))
	{
		printf("zlog_init failed\n");
		return COMM_ERR;
	}	 
	
	comm_category = zlog_get_category("socket_test_cat");	

	if(comm_category == NULL)
	{	
		printf("zlog_get_category failed\n");
		return COMM_ERR;
	}
	
	return COMM_OK;
}


void comm_hex_print(void* hex_info, WORD32 len)
{
	WORD32 i   = 0;

	for (i = 0; i < len; i++)
	{
		printf("0x%x ", *((unsigned char*)hex_info + i));
	}
	printf("\n");
}































