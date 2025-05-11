#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *readFILE(const char *path)
{
    // 2.打开文件流
    FILE *src = fopen(path, "rb"); // 以二进制形式
    if (src == NULL)
    {
        fprintf(stderr, "Open %s failed\n", path);
        exit(1);
    }

    // 3.确定文件大小
    fseek(src, 0, SEEK_END);
    long n = ftell(src);
    char *content = malloc(n + 1); // 1 for '\0'

    // 读文件内容，填充content数组
    rewind(src); // 回到文件开头
    int bytes_num = fread(content, 1, n, src);
    content[bytes_num] = '\0';

    // 4.关闭文件流
    fclose(src);

    return content;
}

int main(int argc, char *argv[])
{
    // xxx.exe src
    //  1.参数校验
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    char *content = readFILE(argv[1]);

    // 输出内容
    puts(content);

    free(content);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}