#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// 定义伽罗华域 GF(2^10)
/*
poly = 1 + x^3 + x^10
alpha = 2
alpha^10 = b'0000001001 = 0x009
*/
int exp[2048];      // 指数表
int log[1024];      // 对数表
int data[512];      // 产生的数据
int codeWord[1023]; // 对数据编码后的码字
int syndrome[511];  // 症状码（syndrome）多项式
int alpha = 2;      // 本元

// 定义多项式结构体
struct poly
{
    int ci = 0;         // 系数非零的最高次项是多少
    int num[512] = {0}; // 多项式参数数组
};

// 在GF(2^10)有限域内乘2运算的函数, 0<=num<1024
int Mul2(int num)
{
    if (num < 0 || num >= 1024)
    {
        printf("This number %d not in GF(2^10) field Mul2!\n", num);
        return -1;
    }
    else
    {
        int ans;
        if (num & 0x200)
        {
            ans = (((num ^ 0x200) << 1) ^ 0x009);
        }
        else
        {
            ans = num << 1;
        }
        return ans;
    }
}

// 在GF(2^10)有限域内生成指数表和对数表
void GenerateTables(int *my_exp, int *my_log)
{
    int x = 1;
    for (int i = 0; i < 1024; i++)
    {
        my_exp[i] = x;
        my_exp[i + 1023] = x;
        my_log[x] = i;
        x = Mul2(x);
        // printf("%d\n",x);
    }
    // 特殊值处理
    my_exp[2047] = my_exp[1024];
    my_log[0] = NULL;
    my_log[1] = 0;
}

// 在GF(2^10)有限域内加法运算的函数, 0<=a<1024,0<=b<1024
int Add(int a, int b)
{
    if ((a < 0 || a >= 1024) || (b < 0 || b >= 1024))
    {
        printf("This number %d or %d not in GF(2^10) field Add!\n", a, b);
        return -1;
    }
    return a ^ b;
}

// 在GF(2^10)有限域内减法运算的函数, 0<=a<1024,0<=b<1024
int Sub(int a, int b)
{

    return Add(a, b);
}

// 在GF(2^10)有限域内乘法运算的函数, 0<=a<1024,0<=b<1024
int Mul(int a, int b)
{
    if ((a < 0 || a >= 1024) || (b < 0 || b >= 1024))
    {
        printf("This number %d or %d not in GF(2^10) field Mul!\n", a, b);
        return -1;
    }
    else
    {
        if (a == 0 || b == 0)
            return 0;
        else
            return exp[(log[a] + log[b])];
    }
}

// 在GF(2^10)有限域内次方运算的函数, 0<=a<1024
int Pow(int a, int b)
{
    if (a < 0 || a >= 1024)
    {
        printf("This number %d not in GF(2^10) field Pow!\n", a);
        return -1;
    }
    else
    {
        if (a == 0)
            return 0;
        else if (a != 0 && b == 0)
            return 1;
        else
        {
            int ans = 1; // 初始化
            for (int i = 0; i < b; i++)
            {
                ans = Mul(ans, a); // 迭代运算
            }
            return ans;
        }
    }
}

// 在GF(2^10)有限域内相反数运算的函数, 0<=a<1024
int Inv(int a)
{
    if (a < 0 || a >= 1024)
    {
        printf("This number %d not in GF(2^10) field Inv!\n", a);
        return -1;
    }
    else
    {
        return exp[1023 - log[a]];
    }
}

// 在GF(2^10)有限域内除法运算的函数, 0<=a<1024，0<b<1024
int Div(int a, int b)
{
    if ((a < 0 || a >= 1024) || (b <= 0 || b >= 1024))
    {
        printf("This number %d or %d not in GF(2^10) field Div!\n", a, b);
        return -1;
    }
    else
    {
        if (a == 0)
            return 0;
        else
            return exp[(log[a] + 1023 - log[b])];
    }
}

// 编码程序函数，n=1023，k=512
void rs_encoder(int *codeword, int n, int *message, int k)
{
    for (int i = 0; i < n; i++)
    {
        codeword[i] = 0; // 清零
        for (int j = 0; j < k; j++)
        {
            codeword[i] = Add(codeword[i], (Mul(message[j], Pow(exp[i], j)))); // 多项式生成码字
        }
    }
}

// 症状码（syndrome）计算函数，n=1023，k=512
void cal_syn(int *rec, int n, int *syn, int k)
{
    int total = n - k;
    for (int i = 1; i <= total; i++)
    {
        syn[i-1] = 0; // 清零
        for (int j = 0; j < n; j++)
        {
            syn[i-1] = Add(syn[i-1], (Mul(rec[j], Pow(exp[i], j)))); // 接收数据多项式生成症状码
        }
    }
}

// 多项式乘法函数
poly poly_Mul(poly a, poly b)
{
    poly temp;
    int max_index = a.ci + b.ci;
    for (int i = 0; i <= a.ci; i++)
    {
        for (int j = 0; j <= b.ci; j++)
        {
            if (a.num[i] != 0 && b.num[j] != 0)
            {
                // 对相同次数项的系数进行异或操作
                temp.num[i + j] = Add(temp.num[i + j], Mul(a.num[i], b.num[j])); 
            }
        }
    }
    for (int j = 0; j <= max_index; j++)
    {
        if (temp.num[j] != 0)
            temp.ci = j;
    }
    return temp;
}

// 多项式加减法函数（有限域内加法和减法相同）
poly poly_Sub(poly a, poly b)
{
    int max_index = max(a.ci, b.ci);
    poly temp;
    for (int i = 0; i <= max_index; i++)
    {
        temp.num[i] = Add(a.num[i], b.num[i]); // 有限域内加法和减法相同
        // printf("%d: %d %d %d\n",i,temp.num[i],a.num[i],b.num[i]);
    }
    for (int j = 0; j <= max_index; j++)
    {
        if (temp.num[j] != 0)
            temp.ci = j;
    }
    return temp;
}

// 多项式除法函数，a/b，传入的商和余数poly要保证是空的
void poly_Div(poly a, poly b, poly &shang, poly &yu)
{
    shang.ci = 0;
    memset(shang.num, 0, sizeof(shang.num));
    yu.ci = 0;
    memset(yu.num, 0, sizeof(yu.num));
    if (a.ci < b.ci)
        return; // 商为0，余数为a
    // printf("poly_Div....\n");
    while (a.ci >= b.ci)
    {
        poly max_num;
        max_num.ci = a.ci - b.ci;
        // printf("poly_Div:%d,%d\n",a.num[a.ci],b.num[b.ci]);
        max_num.num[max_num.ci] = Div(a.num[a.ci], b.num[b.ci]); // 得到最高次项的数据
        poly temp;
        temp = poly_Mul(max_num, b);
        a = poly_Sub(a, temp);
        shang = poly_Sub(shang, max_num);
        yu = a;
    }
}

// 辗转相除算法函数,a=a(x),s=b(x)=b(x)
//  poly Euclidean_Algorithm(poly a,poly s,poly& r_ans)
//  {
//      //设置初值
//      int t = 255;
//      poly q,yu;
//      poly_Div(a,s,q,yu);//得到p的初值
//      poly g,g1,g2,r,r1,r2;
//      g1.ci=0;
//      g2.ci=0;
//      g1.num[0]=0;
//      g2.num[0]=1;
//      r1 = a;
//      r2 = s;
//      r = poly_Sub(r1,poly_Mul(q,r2));
//      //迭代计算
//      while(r.ci>=t)
//      // int index = 5;
//      // while(index--)
//      {
//          // printf("q.ci:%d\n",q.ci);
//          // for(int i=0;i<=q.ci;i++)
//          // {
//          //     printf("%d:%d\n",i,q.num[i]);
//          // }
//          // printf("r2.ci:%d\n",r2.ci);
//          // for(int i=0;i<=r2.ci;i++)
//          // {
//          //     printf("%d:%d\n",i,r2.num[i]);
//          // }
//          // printf("r1.ci:%d\n",r1.ci);
//          // for(int i=0;i<=r1.ci;i++)
//          // {
//          //     printf("%d:%d\n",i,r1.num[i]);
//          // }
//          // printf("......\n");
//          r = poly_Sub(r1,poly_Mul(q,r2));
//          r_ans = r;
//          // if (r.ci<t)
//          //     break;

//         r1 = r2;
//         r2 = r;
//         g = poly_Sub(g1,poly_Mul(q,g2));
//         g1 = g2;
//         g2 = g;

//         printf("r.ci:%d\n",r.ci);
//         for(int i=0;i<=r.ci;i++)
//         {
//             printf("%d:%d\n",i,r.num[i]);
//         }
//         printf("g.ci:%d\n",g.ci);
//         for(int i=0;i<=g.ci;i++)
//         {
//             printf("%d:%d\n",i,g.num[i]);
//         }
//         printf("q.ci:%d\n",q.ci);
//         for(int i=0;i<=q.ci;i++)
//         {
//             printf("%d:%d\n",i,q.num[i]);
//         }

//         if (r.ci<t)
//             break;
//         //对q清零
//         fill(q.num,q.num+q.ci+8,0);
//         fill(yu.num,yu.num+yu.ci+8,0);
//         q.ci=0;
//         yu.ci=0;
//         poly_Div(r1,r2,q,yu);//得到q的初值
//     }
//     return g;
// }

// Euclidean_Algorithm 循环条件
poly Euclidean_Algorithm(poly a, poly s, poly &r_ans)
{
    int t = 256; // 纠错能力t=255
    poly q, yu;
    poly_Div(a, s, q, yu); // 初始除法
    poly g1 = {0, {0}}, g2 = {0, {1}}, r1 = a, r2 = s;

    while (r2.ci >= t)
    {                            // 余数次数≥t时继续
        poly_Div(r1, r2, q, yu); // 计算商q和余数yu
        r_ans = yu;
        poly temp_g = poly_Sub(g1, poly_Mul(q, g2));

        // 更新变量
        r1 = r2;
        r2 = yu;
        g1 = g2;
        g2 = temp_g;
    }
    return g2; // 返回错误位置多项式
}

// 钱搜索函数
void CheinSearch(poly g, int *ans)
{
    int index = 0;
    int temp = 0;
    for (int i = 1; i <= 1023; i++)
    {
        temp = 0;
        for (int j = 0; j <= g.ci; j++)
        {
            temp = Add(temp, (Mul(g.num[j], Pow(exp[i], j))));
        }
        //printf("temp:%d\n",temp);
        if (temp == 0)
            ans[index++] = 1023 - i; // 钱搜索数组
    }
}

// Forney算法实现
void Forney(int *ded_codeword, int *rec_codeword, poly g, poly r_ans, int *chein)
{
    int fenzi, fenmu, err;
    for (int i = 0; i < 1024; i++)
    {
        if (chein[i] == -1)
            break;
        else
        {
            fenzi = 0;
            fenmu = 0;
            for (int j = 0; j <= r_ans.ci; j++)
            {
                fenzi = Add(fenzi, (Mul(r_ans.num[j], Pow(Inv(exp[chein[i]]), j))));
            }
            // printf("fenzi:%d\n",fenzi);
            for (int k = 1; k <= g.ci; k++)
            {
                if (k % 2 != 0)
                    fenmu = Add(fenmu, (Mul(g.num[k], Pow(Inv(exp[chein[i]]), k - 1))));
                // printf("fenmu:%d\n",fenmu);
            }
            err = Div(fenzi, fenmu);
            // printf("err:%d\n",err);
            ded_codeword[chein[i]] = Add(rec_codeword[chein[i]], err);
        }
    }
}

// 主函数
int main()
{
    // 生成指数表和对数表
    GenerateTables(exp, log);

    // 生成消息数据
    for (int i = 0; i < 512; i++)
    {
        data[i] = i + 1;
        // printf("%d\n",data[i]);
    }

    // 执行RS(1023,512)编码函数
    rs_encoder(codeWord, 1023, data, 512);
    for (int i = 0; i < 1023; i++)
    {
        printf("%d:%d\n", i, codeWord[i]);
    }

    // 引入传输错误
    codeWord[565] = 123;//错误地方
    codeWord[2] = 341;//错误地方
    codeWord[20] = 123; // 错误地方
    for (int i = 0; i < 1023; i++)
    {
        // printf("%d:%d\n",i,codeWord[i]);
    }

    // 计算症状码
    poly test_syn;
    memset(syndrome, 0, sizeof(syndrome));
    bool flag = false;
    cal_syn(codeWord, 1023, syndrome, 512);
    for(int i=(sizeof(syndrome)/4-1);i>=0;i--)
    {
        if((syndrome[i]!=0) && (flag == false))
        {
            test_syn.ci = i;
            flag = true;
        }
    }
    for (int i = 0; i < 511; i++)
    {
        test_syn.num[i] = syndrome[i];
        // printf("%d:%d\n",i,test_syn.num[i]);
    }

    // 执行辗转相除法测试
    poly a, ans, r_ans;
    a.ci = 511;
    a.num[511] = 1;
    ans = Euclidean_Algorithm(a, test_syn, r_ans); // 辗转相除法
    printf("ans.ci:%d\n", ans.ci);
    // for(int i=0;i<=ans.ci;i++)
    // {
    //     printf("%d:%d\n",i,ans.num[i]);
    // }
    // printf("r_ans.ci:%d\n",r_ans.ci);
    // for(int i=0;i<=r_ans.ci;i++)
    // {
    //     printf("%d:%d\n",i,r_ans.num[i]);
    // }

    // 钱搜索测试
    int chein[1024] = {-1};
    memset(chein, -1, sizeof(chein));
    CheinSearch(ans, chein);
    printf("错误的地方:\n");
    for (int i = 0; i <= 1023; i++)
    {
        printf("%d:%d\n", i, chein[i]);
    }

    // 执行forney算法
    int ded_codeword[1024] = {0};
    for (int i = 0; i < 1023; i++)
    {
        ded_codeword[i] = codeWord[i];
    }
    Forney(ded_codeword, codeWord, ans, r_ans, chein);
    for (int i = 0; i < 1023; i++)
    {
        printf("rec:%d:%d\n", i, codeWord[i]);
        printf("ded:%d:%d\n", i, ded_codeword[i]);
    }

    // 验算多项式乘法、加法和除法
    //  poly p1,p2,ans,test_shang,test_yu;
    //  p1.ci = 4;
    //  p1.num[4] = 1;
    //  // p1.num[1] = 1;
    //  // p1.num[0] = 1;
    //  p2.ci = 3;
    //  p2.num[3] = exp[1];
    //  p2.num[2] = exp[2];
    //  p2.num[1] = exp[2];
    //  p2.num[0] = exp[4];
    //  ans = poly_Mul(p1,p2);//多项式乘法通过
    //  ans = poly_Sub(p1,p2);//多项式减法通过
    //  for(int i=0;i<=ans.ci;i++)
    //  {
    //      printf("%d:%d\n",i,ans.num[i]);
    //  }
    //  printf("%d %d\n",test_shang.ci,test_yu.ci);
    //  poly_Div(p1,p2,test_shang,test_yu);//多项式除法通过
    //  for(int i=0;i<=test_yu.ci;i++)
    //  {
    //      printf("%d:%d\n",i,test_yu.num[i]);
    //  }

    // 辗转相除法测试
    // ans = Euclidean_Algorithm(p1,p2);//辗转相除法通过
    //  for(int i=0;i<=ans.ci;i++)
    //  {
    //      printf("%d:%d\n",i,ans.num[i]);
    //  }

    // 钱搜索测试
    //  int chein[1024] = {0};
    //  CheinSearch(ans,chein);
    //  for(int i=0;i<=1023;i++)
    //  {
    //      printf("%d:%d\n",i,chein[i]);
    //  }

    // int a=exp[1022],b=2;
    // printf("%d\n",Mul(exp[0],exp[0]));

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}