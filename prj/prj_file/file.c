#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 128

int main(int argc, char *argv[])
{
    // xxx.exe src dst
    //  1.参数校验
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s src dst\n", argv[0]);
        exit(1);
    }

    // 2.打开文件流
    FILE *src = fopen(argv[1], "r");
    if (src == NULL)
    {
        fprintf(stderr, "Open %s failed\n", argv[1]);
        exit(1);
    }

    FILE *dst = fopen(argv[2], "w");
    if (src == NULL)
    {
        fprintf(stderr, "Open %s failed\n", argv[2]);
        fclose(src);
        exit(1);
    }

    // 3.读写文件
    // a.一个字符一个字符地读写: fgetc, fputc
    // 把大写转换为小写
    // int c;
    // while ((c = fgetc(src)) != EOF)
    // {
    //     fputc(tolower(c), dst);
    // }

    // b.一行一行地读写字符
    char line[MAXLINE];
    char buffer[MAXLINE];
    int line_num = 1;
    while (fgets(buffer, MAXLINE, src) != NULL)
    {
        sprintf(line, "%d. %s", line_num, buffer);
        fputs(line, dst);
        line_num++;
    }

    // 4.关闭文件流
    fclose(src);
    fclose(dst);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}