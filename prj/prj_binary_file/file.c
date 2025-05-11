#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 4096

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
    FILE *src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        fprintf(stderr, "Open %s failed\n", argv[1]);
        exit(1);
    }

    FILE *dst = fopen(argv[2], "wb");
    if (src == NULL)
    {
        fprintf(stderr, "Open %s failed\n", argv[2]);
        fclose(src);
        exit(1);
    }

    // 3.复制二进制文件
    char buffer[BUFSIZE];
    int bytes_num;
    while ((bytes_num = fread(buffer, 1, BUFSIZE, src)) > 0)
    {
        fwrite(buffer, 1, BUFSIZE, dst);
    }

    // 4.关闭文件流
    fclose(src);
    fclose(dst);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}