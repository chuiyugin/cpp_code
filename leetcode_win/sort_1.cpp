#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
    public:
        void swap(int& a,int& b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        void print_nums(vector<int>& nums)
        {
            for(int i=0; i<nums.size(); i++)
            {
                printf("%d ",nums[i]);
            }
            printf("\n");
        }

        // 选择排序
        void choose_sort(vector<int>& nums)
        {
            if(nums.size()==0 || nums.size()==1)
                return;
            int minIndex = 0;
            for(int i=0; i<nums.size()-1; i++)
            {
                minIndex = i;
                for(int j=i+1; j<nums.size(); j++)
                {
                    if(nums[j]<nums[minIndex])
                        minIndex = j;
                }
                swap(nums[i],nums[minIndex]);
            }
        }
        
        // 冒泡排序
        void bubble_sort(vector<int>& nums)
        {
            if(nums.size()==0 || nums.size()==1)
                return;
            int last = nums.size()-1;
            int flag = 0;
            for(int i=0; i<nums.size(); i++)
            {
                flag = 0;
                for(int j=0; j<last; j++)
                {
                    if(nums[j]>nums[j+1])
                    {
                        swap(nums[j],nums[j+1]);
                        flag++;
                    }
                }
                if(flag==0)
                    break;
            }
        }

        // 插入排序
        void insert_sort(vector<int>& nums)
        {
            if(nums.size()==0 || nums.size()==1)
                return;
            int value;
            for(int i=1; i<nums.size(); i++) // 要插入元素的索引
            {
                int value = nums[i];
                int j = i - 1;
                while(value < nums[j] && j>=0)
                {
                    nums[j+1] = nums[j];
                    j--;
                }
                nums[j+1] = value;
                print_nums(nums);
            }
        }

};

int main()
{
    Solution s;
    vector<int> v = {3,6,4,2,11,10,5};
    s.insert_sort(v);
    //printf("%d\n",ans);

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}