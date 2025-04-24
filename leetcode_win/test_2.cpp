#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;


int test(int *a[])
{
    printf("%d\n", *a[0]);
    return *a[0];
}

int main()
{
    // printf("你好\n");
    // cout<<__cplusplus<<endl;


    int arr[3] = {1, 2, 3};
    int *p = &arr[1];
    int *test_[1] = {p};

    test(test_);
    // printf("%d\n",*(arr+1));

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}