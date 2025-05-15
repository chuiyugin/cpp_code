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
    scanf("%d\n", &n);
    string str;
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        getline(cin, str); // 读入一整行字符串
        if (str.length() > 3)
        {
            for (int j = 5; j < str.length(); j++)
            {
                num += (str[j] - '0') * pow(10, str.length() - 1 - j);
            }
            q.push(num);
            num = 0;
        }
        else
        {
            if (q.empty())
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", q.front());
                q.pop();
            }
        }
    }
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
}