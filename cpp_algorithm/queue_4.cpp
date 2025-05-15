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
    int n, num;
    int times = 0;
    queue<int> q1, q2;
    scanf("%d", &n);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &num);
            if (i == 0)
            {
                q1.push(num);
            }
            else
            {
                q2.push(num);
            }
        }
    }
    while (!q1.empty())
    {
        if (q1.front() == q2.front())
        {
            q1.pop();
            q2.pop();
        }
        else
        {
            q2.push(q2.front());
            q2.pop();
        }
        times++;
    }
    printf("%d", times);
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
}