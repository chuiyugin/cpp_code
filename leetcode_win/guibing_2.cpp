#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    public:
        
        int merge(vector<int>& record,int L,int M,int R)
        {
            int ans = 0;
            int i = M;
            int j = R;
            vector<int> temp(R-L+1);
            int k=R-L;
            while(i>=L && j >= M+1)
            {
                if(record[i]>record[j])
                {
                    ans+=j-(M+1)+1;
                    temp[k--] = record[i--];
                }
                else
                {
                    temp[k--] = record[j--];
                }
            }
            while(i>=L)
            {
                temp[k--] = record[i--];
            }
            while(j >= M+1)
            {
                temp[k--] = record[j--];
            }
            for(int t=0;t<temp.size();t++)
                record[L+t] = temp[t];
            return ans;
        }
    
        int process(vector<int>& record,int L,int R)
        {
            
            int mid = L + (R-L)/2;
            int ans = 0;
            //递归边界条件
            if(R==L)
                return 0;
            ans = process(record,L,mid) 
                    + process(record,mid+1,R) 
                    + merge(record,L,mid,R);
            return ans;
        }
    
        int reversePairs(vector<int>& record) {
            int ans = 0;
            if(record.size()==0)
                return 0;
            else
            {
                ans = process(record,0,record.size()-1);
                return ans;
            }
        }
    };

int main()
{
    Solution mysolution;
    vector<int> vec = {9,7,5,4,6};
    int ans;
    ans = mysolution.reversePairs(vec);
    printf("%d\n",ans);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}