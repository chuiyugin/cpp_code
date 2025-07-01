#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINE 1024
#define MAXRGS 128

// 解析命令行参数
void parse_parameters(char* message, char* argv[]){
    int i=0;
    argv[i] = strtok(message, " \t\n");
    while(argv[i] != NULL){
        puts(argv[i]);
        i++;
        argv[i] = strtok(NULL, " \t\n");
    } // argv[i] == NULL
}

int main(int argc, char* argv[])
{
    char cmd[MAXLINE];
    char* parameters[MAXRGS];
    for(int i=0; i<argc; i++){
        printf("%s \n",argv[i]);
    }

    // 读取用户命令
    printf("Simple_shell > ");
    fgets(cmd, MAXLINE, stdin);
    parse_parameters(cmd, parameters);

    return 0;
}