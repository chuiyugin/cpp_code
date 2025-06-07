#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

// offset 应该是页大小的整数倍
#define MMAP_SIZE (4096 * 10)

int main(int argc, char *argv[])
{
    // ./mmap_cp src dst
    if (argc != 3)
    {
        error(1, 0, "Usage: %s src dst", argv[0]);
    }

    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd == -1)
    {
        error(1, errno, "open %s", argv[1]);
    }
    // 需要读写权限
    int dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dstfd == -1)
    {
        close(srcfd);
        error(1, errno, "open %s", argv[2]);
    }
    // 1.需要事先知道文件大小
    // 获取src大小
    struct stat sb;
    fstat(srcfd, &sb);
    off_t fsize = sb.st_size;
    // 将dst文件大小设置为fsize
    ftruncate(dstfd, fsize); // 目标文件大小需要事先固定
    // 设置初始偏移量，表示已经复制的数据
    off_t offset = 0;
    while (offset < fsize)
    {
        // 计算映射区长度
        off_t length;
        if (fsize - offset >= MMAP_SIZE)
            length = MMAP_SIZE;
        else
            length = fsize - offset;
        // 映射
        void *addr1 = mmap(NULL, length, PROT_READ, MAP_SHARED, srcfd, offset);
        if (addr1 == MAP_FAILED)
        {
            error(1, errno, "mmap %s", argv[1]);
        }

        void *addr2 = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, dstfd, offset);
        if (addr2 == MAP_FAILED)
        {
            error(1, errno, "mmap %s", argv[2]);
        }
        // 通过将addr1的内容复制到addr2中实现文件的复制
        memcpy(addr2, addr1, length);
        offset += length;
        // 解除映射
        int err = munmap(addr1, length);
        if (err == -1)
        {
            error(1, errno, "munmap %s", argv[1]);
        }

        err = munmap(addr2, length);
        if (err == -1)
        {
            error(1, errno, "munmap %s", argv[2]);
        }
    } // offset == fsize
    return 0;
}