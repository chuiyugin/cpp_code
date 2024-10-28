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
    int num_1, num_2;
    scanf("%d\n", &n);
    string str;
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        q.push(num);
    }
    while (q.size() > 1)
    {
        num_1 = q.front();
        q.pop();
        num_2 = q.front();
        q.pop();
        q.push(num_1 + num_2);
    }
    printf("%d\n", q.front());
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
}