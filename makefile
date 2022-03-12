TARGER 	  = socket_test
CC        = gcc
CURR_PATH = ./
SRC_PATH  = $(addsuffix src, $(CURR_PATH))
OBJ_PATH  = $(addsuffix obj, $(CURR_PATH))
LIB_PATH  = $(addsuffix lib, $(CURR_PATH))

C_FILE_LIST   = $(shell cd src; ls *.c)
OBJ_FILE_LIST = $(foreach n,$(C_FILE_LIST), $(subst .c,.o, $(n) ))
OBJ_PATH_LIST = $(addprefix $(OBJ_PATH)/,$(OBJ_FILE_LIST))
DIR_INC		  = -I./include/openssl -I./include/ 
LIB_INC       = -L./lib -lzlog -lssl -lpthread -lcrypto -ldl 
CFLAG         = ${DIR_INC} -g -w 

client ?= 0
ifeq ($(client), 1)
CFLAG += -D__CLIENT__
TARGER = socket_test_client
endif

server ?= 0
ifeq ($(server), 1)
CFLAG += -D__SERVICE__
TARGER = socket_test_server
endif


#-I./lib/openssl -I./lib/, 头文件搜索路径  -L 指明库文件的所在路径  -l 指向要链接库文件的名称
#生成.o文件，添加头文件需要的搜索路径     -I 
#链接文件时，添加需要的库文件路径和文件名 -L -l

$(TARGER):$(OBJ_PATH_LIST)
	@ echo '--------------------------->'
	@ echo 'Building target [ $@ ]'
	$(CC) $(CFLAG) -o $@ $^ $(LIB_INC)

$(OBJ_PATH_LIST): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) -c $(CFLAG) $< -o $@
	
clean:
	rm -rf ./obj/*.o
	rm -rf $(TARGER)