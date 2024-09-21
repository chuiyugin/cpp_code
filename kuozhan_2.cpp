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
using namespace std;

//求解最大公约数函数(递归算法)
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

//扩展欧几里得算法
int exGcd(int a, int b, int &x, int &y) // x和y使用引用
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int g = exGcd(b, a % b, x, y); //递归计算exGcd(b,a%b,x,y)
    int temp = x;                  //存放x的值
    x = y;                         //更新x=y(old)
    y = temp - a / b * y;          //更新y=x(old)-a/b*y(old)
    return g;                      // g是gcd
}

//逆元求解
int inverse(int a, int m)
{
    int x, y;
    int g = exGcd(a, m, x, y); //求解ax+my=1
    return (x % m + m) % m;    // a模m的逆元为(x%m+m)%m
}

//主函数
int main()
{
    int n, a, m, ans, b;
    scanf("%d %d %d", &n, &a, &m);
    if (gcd(a, m) == 1)
    {
        ans = inverse(a, m);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &b);
            ans = (ans * b) % m;
        }
        printf("%d\n", ans);
    }
    else
        printf("No Solution\n");
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}