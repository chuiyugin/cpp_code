#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

// 定义伽罗华域 GF(2^10)
const int GF_SIZE = 1024;
int exp[2048];    // 指数表
int log[1024];     // 对数表
int data[512];     // 产生的数据
int codeWord[1023];// 对数据编码后的码字
int syndrome[511]; // 症状码（syndrome）多项式
int alpha = 2;     // 本元

// 定义多项式结构体
struct poly {
    int ci = 0;        // 系数非零的最高次项
    int num[512] = {0};// 多项式参数数组
};

// 在GF(2^10)有限域内乘2运算的函数
int Mul2(int num) {
    if (num < 0 || num >= GF_SIZE) {
        printf("This number %d not in GF(2^10) field Mul2!\n", num);
        return -1;
    }
    if (num & 0x200) 
        return ((num ^ 0x200) << 1) ^ 0x009;
    else 
        return num << 1;
}

// 生成伽罗瓦域指数表和对数表
void GenerateTables() {
    int x = 1;
    for (int i = 0; i < GF_SIZE - 1; ++i) {
        exp[i] = x;
        exp[i + GF_SIZE - 1] = x;
        log[x] = i;
        x = Mul2(x);
    }
    log[0] = -1; // 特殊值处理
}

// 有限域内加法
int Add(int a, int b) { return a ^ b; }

// 有限域内乘法
int Mul(int a, int b) {
    if (!a || !b) return 0;
    return exp[(log[a] + log[b]) % (GF_SIZE - 1)];
}

//在GF(2^10)有限域内除法运算的函数, 0<=a<1024，0<b<1024
int Div(int a,int b)
{
    if((a<0||a>=1024)||(b<=0||b>=1024))
    {
        printf("This number %d or %d not in GF(2^10) field Div!\n",a,b);
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

// RS编码函数
void rs_encoder(int* codeword, int n, int* message, int k) {
    memset(codeword, 0, sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            codeword[i] = Add(codeword[i], Mul(message[j], exp[(i * j) % (GF_SIZE - 1)]));
        }
    }
}

// 计算症状码
void cal_syn(int* rec, int n, int* syn, int k) {
    int total = n - k;
    memset(syn, 0, sizeof(int) * total);
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < n; ++j) {
            syn[i] = Add(syn[i], Mul(rec[j], exp[(i + 1) * j % (GF_SIZE - 1)]));
        }
    }
}

// 多项式除法
void poly_Div(poly a, poly b, poly& shang, poly& yu) {
    shang = {0}; yu = a;
    if (a.ci < b.ci) return;
    while (yu.ci >= b.ci) {
        int term = yu.ci - b.ci;
        shang.num[term] = Div(yu.num[yu.ci], b.num[b.ci]);
        for (int i = 0; i <= b.ci; ++i) {
            yu.num[term + i] ^= Mul(shang.num[term], b.num[i]);
        }
        while (yu.ci > 0 && yu.num[yu.ci] == 0) yu.ci--;
    }
}

// 辗转相除算法
poly Euclidean_Algorithm(poly a, poly s, poly& r_ans) {
    const int t = 255;
    poly q = {0}, yu = {0};
    poly g1 = {0}, g2 = {0, {1}}, r1 = a, r2 = s;

    while (r2.ci >= t) {
        poly_Div(r1, r2, q, yu);
        r_ans = yu;
        poly temp_g = {0};
        for (int i = 0; i <= g1.ci; ++i) {
            for (int j = 0; j <= q.ci; ++j) {
                temp_g.num[i + j] ^= Mul(g1.num[i], q.num[j]);
            }
        }
        for (int i = 0; i <= temp_g.ci; ++i) {
            temp_g.num[i] ^= g2.num[i];
        }
        r1 = r2; r2 = yu;
        g1 = g2; g2 = temp_g;
    }
    return g2;
}

// 钱搜索
void CheinSearch(poly g, int* ans) {
    int index = 0;
    for (int i = 0; i < GF_SIZE; ++i) {
        int val = 0;
        for (int j = 0; j <= g.ci; ++j) {
            val = Add(val, Mul(g.num[j], exp[(i * j) % (GF_SIZE - 1)]));
        }
        if (!val) ans[index++] = 1023 - i;
    }
    ans[index] = -1; // 结束标记
}

// Forney算法
void Forney(int* ded_codeword, int* rec_codeword, poly g, poly r_ans, int* chein) {
    int i = 0;
    while (chein[i] != -1) {
        int pos = chein[i];
        int num = 0, den = 0;
        for (int j = 0; j <= r_ans.ci; ++j) {
            num = Add(num, Mul(r_ans.num[j], exp[(GF_SIZE - 1 - pos * j) % (GF_SIZE - 1)]));
        }
        for (int k = 1; k <= g.ci; k += 2) {
            den = Add(den, Mul(g.num[k], exp[(GF_SIZE - 1 - pos * (k - 1)) % (GF_SIZE - 1)]));
        }
        int err_val = Div(num, den);
        ded_codeword[pos] = Add(rec_codeword[pos], err_val);
        i++;
    }
}

int main() {
    //生成指数表和对数表
    GenerateTables();

    //生成消息数据
    for(int i=0;i<512;i++)
    {
        data[i] = i+1;
        //printf("%d\n",data[i]);
    }

    //执行RS(1023,512)编码函数
    rs_encoder(codeWord,1023,data,512);
    for(int i=0;i<1023;i++)
    {
        printf("%d:%d\n",i,codeWord[i]);
    }

    //引入传输错误
    codeWord[5] = 123;//错误地方
    //codeWord[2] = 341;//错误地方
    //codeWord[20] = 123;//错误地方
    for(int i=0;i<1023;i++)
    {
        //printf("%d:%d\n",i,codeWord[i]);
    }

    //计算症状码
    poly test_syn;
    test_syn.ci = 510;
    cal_syn(codeWord,1023,syndrome,512);
    for(int i=0;i<511;i++)
    {
        test_syn.num[i] = syndrome[i];
        //printf("%d:%d\n",i,test_syn.num[i]);
    }

    //执行辗转相除法测试
    poly a,ans,r_ans;
    a.ci = 511;
    a.num[511] = 1;
    ans = Euclidean_Algorithm(a,test_syn,r_ans);//辗转相除法
    printf("ans.ci:%d\n",ans.ci);
    for(int i=0;i<=ans.ci;i++)
    {
        printf("%d:%d\n",i,ans.num[i]);
    }
    printf("r_ans.ci:%d\n",r_ans.ci);
    for(int i=0;i<=r_ans.ci;i++)
    {
        printf("%d:%d\n",i,r_ans.num[i]);
    }

    //钱搜索测试
    int chein[1024] = {0};
    CheinSearch(ans,chein);
    for(int i=0;i<=1023;i++)
    {
        printf("%d:%d\n",i,chein[i]);
    }

    //执行forney算法
    int ded_codeword[1024] = {0};
    for(int i=0;i<1023;i++)
    {
        ded_codeword[i] = codeWord[i];
    }
    Forney(ded_codeword,codeWord,ans,r_ans,chein);
    for(int i=0;i<1023;i++)
    {
        printf("rec:%d:%d\n",i,codeWord[i]);
        printf("ded:%d:%d\n",i,ded_codeword[i]);
    }

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}