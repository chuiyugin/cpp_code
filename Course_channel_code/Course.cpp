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
int syndrome[511];//症状码（syndrome）多项式
int alpha = 2;//本元

//定义多项式结构体
struct poly{
    int ci;//系数非零的最高次项是多少
    int num[512]={0};//多项式参数数组
};


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

//编码程序函数，n=1023，k=512
void rs_encoder(int* codeword,int n,int* message,int k)
{
    for(int i=0;i<n;i++)
    {
        codeword[i] = 0;//清零
        for(int j=0;j<k;j++)
        {
            codeword[i] = Add(codeword[i],(Mul(message[j],Pow(exp[i],j))));//多项式生成码字
        }
    }
}

//症状码（syndrome）计算函数，n=1023，k=512
void cal_syn(int* rec,int n,int* syn,int k)
{
    int total = n-k;
    for(int i=0;i<total;i++)
    {
        syn[i] = 0;//清零
        for(int j=0;j<n;j++)
        {
            syn[i] = Add(syn[i],(Mul(rec[j],Pow(exp[i],j))));//接收数据多项式生成症状码
        }
    }
}

//多项式乘法函数
poly poly_Mul(poly a,poly b)
{
    poly temp;
    temp.ci = a.ci + b.ci;
    for(int i=0;i<=a.ci;i++)
    {
        for(int j=0;j<=b.ci;j++)
        {
            if(a.num[i]!=0&&b.num[j]!=0)
                temp.num[i+j] = Mul(a.num[i],b.num[j]);
        }
    }
    return temp;
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
        //printf("%d:%d\n",i,codeWord[i]);
    }

    //计算症状码
    cal_syn(codeWord,1023,syndrome,512);
    for(int i=0;i<511;i++)
    {
        //printf("%d:%d\n",i,syndrome[i]);
    }

    //验算多项式乘法
    poly p1,p2,ans;
    p1.ci = 4;
    p1.num[4] = 1;
    p1.num[0] = 1;
    p2.ci = 2;
    p2.num[2] = 1;
    p2.num[0] = 1;
    ans = poly_Mul(p1,p2);
    for(int i=0;i<=ans.ci;i++)
    {
        printf("%d:%d\n",i,ans.num[i]);
    }

    // int a=exp[1022],b=2;
    //printf("%d\n",Mul(exp[0],exp[0]));
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}