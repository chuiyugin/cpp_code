#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

class Solution {
    public:
        
        int merge(vector<long long>& sum,int L,int M,int R, int lower, int upper)
        {
            int ans = 0;
            int winL = L;
            int winR = L;
            for(int i=M+1;i<=R;i++)
            {
                long long min_ = sum[i] - upper;
                long long max_ = sum[i] - lower;
                while(winR<=M && sum[winR]<=max_)
                    winR++;
                while(winL<=M && sum[winL]<min_)
                    winL++;
                ans += winR - winL;
            }
            //做merge操作
            vector<long long> temp(R-L+1);
            int k=0;
            int i=L;
            int j=M+1;
            while(i<=M && j<=R)
                temp[k++] = sum[i]<sum[j] ? sum[i++] : sum[j++];
            while(i<=M)
                temp[k++] = sum[i++];
            while(j<=R)
                temp[k++] = sum[j++];
            for(int k=0;k<temp.size();k++)
                sum[L+k] = temp[k];
    
            return ans;
        }
    
        int process(vector<long long>& sum,int L,int R ,int lower, int upper)
        {
            int ans = 0;
            int mid = L + (R-L)/2;
            //递归边界条件
            if(L==R)
            {
                if(sum[L]>=lower && sum[L]<=upper)
                    return 1;
                else
                    return 0;
            }
            ans = process(sum,L,mid,lower,upper) 
            + process(sum,mid+1,R,lower,upper) 
            + merge(sum,L,mid,R,lower,upper);
            return ans;
        }
    
        int countRangeSum(vector<int>& nums, int lower, int upper) 
        {
            if(nums.size() == 0)
                return 0;
    
            //求前缀和数组
            vector<long long> sum;
            sum.push_back(nums[0]);
            for(int i=1;i<nums.size();i++)
            {
                sum.push_back(sum[i-1]+nums[i]);
            }
    
            int ans = 0;
            ans = process(sum,0,sum.size()-1,lower,upper);
            return ans;
        }
    };

int main()
{
    Solution mysolution;
    vector<int> test = {2147483647,-2147483648,-1,0};
    int lower = -1,upper = 0;
    int ans;
    ans = mysolution.countRangeSum(test,lower,upper);
    printf("%d\n",ans);

    system("pause");
    return 0;
}