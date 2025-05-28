#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

//width:缩进的空格数目
void dfs_print(const char* path, int width);

int directories = 0, files = 0;

int main(int argc, char* argv[])
{
    // 用法: ./young_tree dir
    if(argc != 2)
        error(1, 0, "Usage: %s dir", argv[0]);

    //遍历根节点
    puts(argv[1]);

    //递归打印每一个子树
    dfs_print(argv[1], 4);

    printf("\n%d directories, %d files\n", directories, files);

    return 0;
}

void dfs_print(const char* path, int width){
    //打开目录流
    DIR* stream = opendir(path);
    if(!stream){
        error(1, errno, "opendir %s", path);
    }

    //遍历每一个目录项
    errno = 0; // 等于0表示没出错
    struct dirent* pdirent;
    //readdir():读目录流，得到指向下一个目录项的指针。
    while((pdirent = readdir(stream)) != NULL){
        char* filename = pdirent->d_name;
        //忽略 . 和 ..
        if(strcmp(filename,".") == 0 || strcmp(filename,"..") == 0)
            continue;
        //打印这个目录项的名字
        for(int i=0; i<width; i++){
            putchar(' ');
        }
        puts(filename);
        //如果是目录的话递归地处理
        if(pdirent->d_type == DT_DIR){
            directories++;
            //拼接路径
            char subpath[128];
            sprintf(subpath, "%s/%s", path, filename);
            dfs_print(subpath, width+4);
        }
        else
            files++;
    }
    closedir(stream);
    if(errno){
        error(1, errno, "readdir");
    }
}