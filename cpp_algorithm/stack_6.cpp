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

struct node
{
    double num; //操作数
    char op;    //操作符
    bool flag;  // true表达操作数，false表示操作符
};

string str;
stack<node> s; //操作符栈
queue<node> q; //后缀表达式序列
map<char, int> op;

//将中缀表达式转换为后缀表达式
void change()
{
    node temp;
    for (int i = 0; i < str.length();i++)
    {
        if (str[i] >= '0' && str[i] <= '9') //如果是数字
        {
            temp.flag = true;                                          //标记为数字
            temp.num = str[i] - '0';                                 //记录这个操作数的第一个数位
            q.push(temp); //将这个操作数压入后缀表达式队列
        }
        else //如果是操作符
        {
            temp.flag = false;
            temp.op=str[i];
            q.push(temp);
        }
    }
}

//计算后缀表达式
double cal()
{
    double temp1, temp2;
    node cur, temp;
    while (!q.empty()) //后缀表达式队列非空
    {
        cur = q.front(); //记录队列头
        q.pop();
        if (cur.flag == true) //如果是操作数
        {
            s.push(cur); //直接入栈
        }
        else //如果是操作符
        {
            temp1 = s.top().num;
            s.pop();
            temp2 = s.top().num;
            s.pop();
            temp.flag = true; //记录运算后的数据
            if (cur.op == '+')
                temp.num = temp2 + temp1;
            else if (cur.op == '-')
                temp.num = temp2 - temp1;
            else if (cur.op == '*')
                temp.num = temp2 * temp1;
            else
                temp.num = temp2 / temp1;
            s.push(temp); //把计算后的数据压栈
        }
    }
    return s.top().num; //栈顶元素就是后缀表达式运算后的值
}

//主函数
int main()
{
    //设定操作符优先级
    op['+'] = op['-'] = 1;
    op['*'] = op['/'] = 2;
    getline(cin, str);
    for (string::iterator it = str.end(); it != str.begin(); it--)
    {
        if (*it == ' ')
            str.erase(it); //把表达式的空格全部去掉
    }
    while (!s.empty()) //初始化栈
        s.pop();
    change();                //将中缀表达式转换成后缀表达式
    printf("%.2f\n", cal()); //输出计算后缀表达式的结果
    //system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}