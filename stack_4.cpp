#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <cstring>
#include <iostream>
#include <utility>
#include <map>
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
#include <ctime>
#include <cmath>
#include <sstream>
#include <queue>
using namespace std;

//定义变量
const int MAXN = 105;
int n; //输出index-n的全排列
int p[MAXN];
bool HashTable[MAXN] = {false};

//判断是否合法出栈序列函数
bool isValidSeq(int *array)
{
    int num, pointer = 0;
    bool flag = true;
    for (int j = 1; j <= n; j++)
    {
        if (pointer < array[j])
        {
            pointer = array[j];
        }
        else
        {
            num = array[j];
            for (int k = j + 1; k <= n; k++)
            {
                if ((array[k - 1] < array[k] || num < array[k]) && pointer > array[k])
                {
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}

//生成全排列数据并判断是否合法出栈序列函数
void Full_permutation(int index)
{
    //递归边界
    if (index == n + 1)
    {
        if (isValidSeq(p) == true)
        {
            for (int i = 1; i < n; i++)
            {
                printf("%d ", p[i]);
            }
            printf("%d\n", p[n]);
        }
        return;
    }
    //递归式
    for (int k = 1; k <= n; k++)
    {
        if (!HashTable[k]) // HashTable[k]==false->说明该元素还没有被用上
        {
            p[index] = k;        //处理这一种情况
            HashTable[k] = true; //到这里说明假设1到index已经排好
            //递归进入函数再排index+1之后的部分
            Full_permutation(index + 1);
            //递归返回结束后循环还没有结束，继续处理下一循环的问题
            HashTable[k] = false; //已经处理完p[index]=k;这一种情况，还原状态
        }
    }
}

//主函数
int main()
{
    scanf("%d", &n);
    Full_permutation(1);
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}