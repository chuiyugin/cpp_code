#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int getSum(int num)
    {
        int sum = 0;
        while(num!=0)
        {
            sum += ( (num%10) * (num%10) );
            num /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> temp;
        temp.insert(n);
        while(n!=1)
        {
            n = getSum(n);
            if(temp.find(n) != temp.end())
                break;
            temp.insert(n);
        }
        if(n == 1)
            return true;
        else
            return false;
    }
};

int main()
{
    Solution s;
    cout << s.isHappy(19) << endl;

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}