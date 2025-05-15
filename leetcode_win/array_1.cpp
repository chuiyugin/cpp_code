#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        int len = nums.size();
        if (len == 1)
        {
            nums[0] = nums[0] * nums[0];
            return nums;
        }
        int index = -1;
        for (int i = 0; i < len; i++)
        {
            if (nums[i] < 0)
                index = i;
            else
                break;
        }
        int left = index;
        int right = index + 1;
        vector<int> arr;
        while (left >= 0 && right <= len - 1)
        {
            if (nums[left] * nums[left] <= nums[right] * nums[right])
            {
                arr.push_back(nums[left] * nums[left]);
                left--;
            }
            else
            {
                arr.push_back(nums[right] * nums[right]);
                right++;
            }
        }
        while (left >= 0)
        {
            arr.push_back(nums[left] * nums[left]);
            left--;
        }
        while (right <= len - 1)
        {
            arr.push_back(nums[right] * nums[right]);
            right++;
        }
        return arr;
    }
};

int main()
{
    Solution mysolution;
    vector<int> vec = {0, 2};
    vector<int> ans;
    int num;
    ans = mysolution.sortedSquares(vec);
    num = ans.size();
    for (int i = 0; i < num; i++)
    {
        printf("%d\n", ans[i]);
    }

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}