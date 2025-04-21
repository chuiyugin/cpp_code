#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Solution {
    public:
        void swap(vector<int>& nums,int a,int b)
        {
            int temp = nums[a];
            nums[a] = nums[b];
            nums[b] = temp;
        }
        
        vector<int> partition(vector<int>& nums,int L,int R)
        {
            vector<int> area(2);
            int pre = L-1; // <区
            int last = R; // >区
            int now = L;
            if(L==R)
            {
                area[0] = L;
                area[1] = R;
                return area;
            }
            else
            {
                while(now<last)
                {
                    if(nums[now]==nums[R])
                        now++;
                    else if(nums[now]<nums[R])
                    {
                        swap(nums,now,pre+1);
                        pre++;
                        now++;
                    }
                    else
                    {
                        swap(nums,now,last-1);
                        last--;
                    }
                }
                swap(nums,last,R);//最后把nums[R]放到=区的末尾
                area[0] = pre+1;
                area[1] = last;
                return area;
            }
        }
    
        void qickSort(vector<int>& nums,int L,int R)
        {
            //递归边界
            if(L>=R)
                return;

            //随机选择一个数和nums[R]进行交换
            srand(time(NULL));
            swap(nums,R,rand()%(R-L+1));

            vector<int> area(2);
            area = partition(nums,L,R);
            qickSort(nums,L,area[0]-1);
            qickSort(nums,area[1]+1,R);
        }
    
        vector<int> sortArray(vector<int>& nums) {
            qickSort(nums,0,nums.size()-1);
            return nums;
        }
    };

int main()
{
    Solution mysolution;
    vector<int> vec;
    vector<int> ans;
    int num,temp;
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        scanf("%d",&temp);
        vec.push_back(temp);
    }
    ans = mysolution.sortArray(vec);
    for(int i=0;i<num;i++)
    {
        printf("%d\n",ans[i]);
    }
    
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}