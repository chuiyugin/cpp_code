#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

//定义伽罗华域 GF(2^10)
/*
poly = 1 + x^3 + x^10
alpha = 2
alpha^10 = b'0000001001 = 0x009
*/
int exp[2048];//指数表
int log[1024];//对数表
int alpha = 2;//本元

//在GF(2^10)有限域内乘2运算的函数, 0<=num<1024
int Mul2(int num)
{
    if(num<0||num>=1024)
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    else
    {
        int ans;
        if(num & 0x200)
        {
            ans = (((num^0x200)<<1)^0x009);
        }
        else
        {
            ans = num << 1;
        }
        return ans;
    }
}

//在GF(2^10)有限域内生成指数表和对数表
void GenerateTables(int* my_exp,int* my_log)
{
    int x = 1;
    for(int i=0;i<1024;i++)
    {
        my_exp[i] = x;
        my_exp[i+1023] = x;
        my_log[x] = i;
        x = Mul2(x);
        //printf("%d\n",x);
    }
    //特殊值处理
    my_exp[2047] = my_exp[1024];
    my_log[0] = NULL;
}

//在GF(2^10)有限域内加法运算的函数, 0<=a<1024,0<=b<1024
int Add(int a,int b)
{
    if((a<0||a>=1024)||(b<0||b>=1024))
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    return a^b;
}

//在GF(2^10)有限域内减法运算的函数, 0<=a<1024,0<=b<1024
int Sub(int a,int b)
{
    
    return Add(a,b);
}

//在GF(2^10)有限域内乘法运算的函数, 0<=a<1024,0<=b<1024
int Mul(int a,int b)
{
    if((a<0||a>=1024)||(b<0||b>=1024))
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    else
    {
        if(a==0||b==0)
            return 0;
        else
            return exp[(log[a]+log[b])];
    }
}

//在GF(2^10)有限域内相反数运算的函数, 0<=a<1024
int Inv(int a)
{
    if(a<0||a>=1024)
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    else
    {
        return exp[1023-log[a]];
    }
}

//在GF(2^10)有限域内除法运算的函数, 0<=a<1024，0<b<1024
int Div(int a,int b)
{
    if((a<0||a>=1024)||(b<=0||b>=1024))
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    else
    {
        if(a==0)
            return 0;
        else
            return exp[(log[a]+1023-log[b])];
    }
}


int main()
{
    GenerateTables(exp,log);
    int a=4,b=2;
    printf("%d\n",Div(a,b));
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}