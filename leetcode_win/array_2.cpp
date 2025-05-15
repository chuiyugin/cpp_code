#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
    public:
        vector<vector<int>> generateMatrix(int n) {
            //创建二维数组和下标
            vector<vector<int>> mat(n,vector<int>(n));
            int i=0;
            int j=0;
            //模拟部分
            int count = 1;
            int step = n;
            int num = 1;
            while(step>0)
            {
                //向右横着
                for(int k=0;k<step;k++)
                {
                    printf("i=%d j=%d num = %d\n",i,j,num);
                    mat[i][j++] = num++;
                }
                count++;
                if(count%2 == 0)
                    step--;
                i++;
                j--;
                //向下竖着
                for(int k=0;k<step;k++)
                {
                    printf("i=%d j=%d num = %d\n",i,j,num);
                    mat[i++][j] = num++;
                }
                count++;
                if(count%2 == 0)
                    step--;
                j--;
                i--;
                //向左横着
                for(int k=0;k<step;k++)
                {
                    printf("i=%d j=%d num = %d\n",i,j,num);
                    mat[i][j--] = num++;
                }
                count++;
                if(count%2 == 0)
                    step--;
                i--;
                j++;
                //向上竖着
                for(int k=0;k<step;k++)
                {
                    printf("i=%d j=%d num = %d\n",i,j,num);
                    mat[i--][j] = num++;
                }
                count++;
                if(count%2 == 0)
                    step--;
                j++;
                i++;
            }
            return mat;
        }
    };

int main()
{
    Solution mysolution;
    vector<vector<int>> ans;
    int num = 4;
    ans = mysolution.generateMatrix(num);
    for (int i = 0; i < num; i++)
    {
        for(int j = 0;j < num; j++)
        {
            printf("%d\n", ans[i][j]);
        }
    }

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}