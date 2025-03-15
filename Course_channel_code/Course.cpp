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
int data[512];//产生的数据
int codeWord[1023];//对数据编码后的码字
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

//在GF(2^10)有限域内次方运算的函数, 0<=a<1024
int Pow(int a,int b)
{
    if(a<0||a>=1024)
    {
        printf("This number not in GF(2^10) field!\n");
        return -1;
    }
    else
    {
        if(a==0)
            return 0;
        else if(a!=0&&b==0)
            return 1;
        else
        {
            int ans = 1;//初始化
            for(int i=0;i<b;i++)
            {
                ans = Mul(ans,a);//迭代运算
            }
            return ans;
        }
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

//编码程序，n=1023，k=512
void rs_encoder(int* codeword,int n,int* message,int k)
{
    for(int i=0;i<n;i++)
    {
        codeword[i] = 0;//清零
        for(int j=0;j<k;j++)
        {
            codeword[i] += Mul(message[j],Pow(exp[i],j));//多项式生成码字
        }
    }
}


int main()
{
    //生成指数表和对数表
    GenerateTables(exp,log);

    //生成消息数据
    for(int i=0;i<512;i++)
    {
        data[i] = i;
        //printf("%d\n",data[i]);
    }

    //执行RS(1023,512)编码函数
    rs_encoder(codeWord,1023,data,512);
    for(int i=0;i<1023;i++)
    {
        printf("%d:%d\n",i,codeWord[i]);
    }

    // int a=exp[1022],b=2;
    // printf("%d\n",Pow(a,b));
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}