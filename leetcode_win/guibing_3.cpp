#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    public:
        
        int merge(vector<int>& nums,int L,int M,int R)
        {
            vector<int> temp(R-L+1);
            int i = L,j = M+1,k = 0;
            int ans = 0;
            
            //计算左边数比右边数大2倍的数量
            while(i<=M && j<=R+1)
            {
                if(nums[i]>2*nums[j])
                {
                    if(j<=R)
                        j++;
                    else
                        break;
                }
                else
                {
                    ans += j-(M+1);
                    i++;
                }
            }

            //排序合并
            i = L,j = M+1,k = 0;
            while(i<=M && j<=R)
            {
                temp[k++] = nums[i]<nums[j] ? nums[i++] : nums[j++];
            }
            //要么i越界了,把j剩下的拷贝进去
            while(j<=R)
                temp[k++] = nums[j++];
            //要么j越界了,把i剩下的拷贝进去
            while(i<=M)
                temp[k++] = nums[i++];
            for(int t=0;t<temp.size();t++)
                nums[L+t] = temp[t];//需要注意nums的区间
            return ans;
        }
        
        int process(vector<int>& nums,int L,int R)
        {
            int mid = L + (R - L)/2;
            int ans = 0;
            //递归边界条件
            if(L == R)
                return 0;
            ans = process(nums,L,mid) + process(nums,mid+1,R) + merge(nums,L,mid,R);
            return ans;
        }
    
        int Than2(vector<int>& nums) {
            int ans;
            ans = process(nums,0,nums.size()-1);
            return ans;
        }
    };

int main()
{
    Solution mysolution;
    vector<int> vec = {8,3,5,1,2};
    int ans;
    ans = mysolution.Than2(vec);
    printf("%d\n",ans);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}