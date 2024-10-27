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

//主函数
int main()
{
    int n, num, pointer = 0;
    int array[105];
    bool flag = true;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    for (int j = 0; j < n; j++)
    {
        if (pointer < array[j])
        {
            pointer = array[j];
        }
        else
        {
            num = array[j];
            for (int k = j + 1; k < n; k++)
            {
                if ((array[k - 1] < array[k] || num < array[k]) && pointer > array[k])
                {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag == true)
        printf("Yes");
    else
        printf("No");
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}