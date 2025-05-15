#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void getNext(vector<int>& next,string s)
    {
        //初始化
        int j=0;
        next[j] = 0;
        for(int i=1; i<s.size(); i++)
        {
            //如果不相等，回退
            while(j>0 && s[i]!=s[j])
            {
                j = next[j-1];//回退
            }
            //如果相等，则i和j都增加
            if(s[i]==s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }
    
    bool repeatedSubstringPattern(string s) {
        vector<int> next(s.size());
        getNext(next,s);
        int ans = s.size() % (s.size()-next[s.size()-1]);
        if(ans || next[s.size()-1]==0)
            return false;
        else
            return true;
    }
};

int main()
{
    Solution s;
    // int ans;
    // string haystack = "hello", needle = "ll";
    // ans = s.strStr(haystack, needle);
    // printf("%d\n", ans);

    string test = "abac";
    vector<int> next(test.size());
    s.getNext(next, test);
    for (int i = 0; i < test.size(); i++)
    {
        printf("%d ", next[i]);
    }
    printf("\n");

    printf("%d\n",s.repeatedSubstringPattern(test));

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}