#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
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
using namespace std;

// 主函数
int main()
{
    int n, num = 0;
    queue<int> q;
    int k = 1;
    scanf("%d %d", &n, &num);
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }
    while (!q.empty())
    {
        if (k % num != 0)
        {
            q.push(q.front());
            q.pop();
        }
        else
        {
            printf("%d", q.front());
            if (q.size() > 1)
            {
                printf(" ");
            }
            q.pop();
        }
        k++;
    }
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
}