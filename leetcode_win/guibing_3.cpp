#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
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

class Solution2 {
    public:
        
        int merge(vector<int>& nums,int L,int M,int R)
        {
            vector<int> temp(R-L+1);
            int i = L,j = M+1,k = 0;
            int ans = 0;
            
            //计算左边数比右边数大2倍的数量
            int winR = M+1;
            for(int i=L;i<=M;i++)
            {
                while(winR<=R && nums[i]>(nums[winR]*2))
                    winR++;
                ans += winR - (M+1);
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

// 生成随机数组的函数
vector<int> generateRandomArray(int maxSize, int maxValue) {
    int size = rand() % (maxSize + 1);
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % (2 * maxValue + 1)) - maxValue;
    }
    return arr;
}

// 对数器测试函数
void testComparator() {
    srand(time(0));
    int testTime = 500;
    int maxSize = 100;
    int maxValue = 100;

    for (int i = 0; i < testTime; ++i) {
        vector<int> vec = generateRandomArray(maxSize, maxValue);
        vector<int> vec1 = vec;
        vector<int> vec2 = vec;

        Solution sol1;
        Solution2 sol2;
        int ans1 = sol1.Than2(vec1);
        int ans2 = sol2.Than2(vec2);

        if (ans1 != ans2) {
            cout << "测试失败！" << endl;
            cout << "原数组：";
            for (int num : vec) cout << num << " ";
            cout << "\nSolution1结果：" << ans1 << endl;
            cout << "Solution2结果：" << ans2 << endl;
            return;
        }
    }
    cout << "所有测试用例通过！" << endl;
}

int main()
{
    testComparator(); // 运行对数器

    // 原始测试代码
    // Solution mysolution;
    // Solution2 mysolution2;
    // vector<int> vec = {8,3,5,1,2};
    // vector<int> vec1 = vec;
    // vector<int> vec2 = vec;
    // cout << "Solution1结果：" << mysolution.Than2(vec1) << endl;
    // cout << "Solution2结果：" << mysolution2.Than2(vec2) << endl;

    system("pause");
    return 0;
}