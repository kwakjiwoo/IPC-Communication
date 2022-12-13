//202034303 kwakjiwoo
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_BUF	1024

void main(int argc, char *argv[]){
	pid_t pid_son;
	pid_t pid_daughter;
	
	pid_son = fork();
	
	if(pid_son < 0)
		printf("Fork Failed\n");
	
	else if(pid_son == 0){
		printf("process son create\n");
		char *fifo_son = "/tmp/hw3_fifo_son";
		char buffer_son[MAX_BUF];
		int file_desc_son = open(fifo_son, O_RDONLY);
		while(buffer_son[0] != '0'){
			read(file_desc_son, buffer_son, MAX_BUF);
			if(buffer_son[0] == '0')break;
			printf("Son receives: %s\n", buffer_son);
		}
		close(file_desc_son);
	}
	else{
		pid_daughter = fork();
		if(pid_daughter < 0)
			printf("Fork Failed\n");
		
		else if (pid_daughter == 0){
			printf("\nprocess daughter create\n");
			char *fifo_dau = "/tmp/hw3_fifo_dau";
			char buffer_dau[MAX_BUF];
			int file_desc_dau = open(fifo_dau, O_RDONLY);
			while(buffer_dau[0] != '0'){
				read(file_desc_dau, buffer_dau, MAX_BUF);
				if(buffer_dau[0] == '0')break;
				printf("Daughter receives: %s\n", buffer_dau);
			}
			close(file_desc_dau);
		}
		else{
			wait(NULL);
		}
		
	}	 
}
