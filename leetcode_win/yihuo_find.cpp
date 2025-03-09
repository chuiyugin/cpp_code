#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

//采用异或运算找到数组中出现奇数次的数
int yihuo_find(vector<int>& a)
{
    int eor = 0;
    for(int i=0;i<a.size();i++)
    {
        eor = eor ^ a[i];
    }
    return eor;
}

int main()
{
    vector<int>  vec1= {1, 1, 3, 3, 3}; 
    int ans = yihuo_find(vec1);
    printf("%d",ans);
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}