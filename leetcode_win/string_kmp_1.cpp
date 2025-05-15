#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    void getNext(vector<int> &next, string s)
    {
        // 初始化
        int j = 0;
        next[j] = 0;
        for (int i = 1; i < s.size(); i++)
        {
            // 不相等的情况
            while (j > 0 && s[i] != s[j])
            {
                // 回退
                j = next[j - 1];
            }
            // 相等的情况
            if (s[i] == s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }

    int strStr(string haystack, string needle)
    {
        vector<int> next(needle.size());
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++)
        {
            // 不相等
            while (j > 0 && haystack[i] != needle[j])
            {
                j = next[j - 1];
            }
            // 相等但不是末尾,i和j都向后移动
            if (haystack[i] == needle[j] && (j != needle.size() - 1))
            {
                j++;
            }
            // 相等而且是末尾
            else if (haystack[i] == needle[j] && (j == needle.size() - 1))
            {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;
    // int ans;
    // string haystack = "hello", needle = "ll";
    // ans = s.strStr(haystack, needle);
    // printf("%d\n", ans);

    string test = "abcabcabcabc";
    vector<int> next(test.size());
    s.getNext(next, test);
    for (int i = 0; i < test.size(); i++)
    {
        printf("%d ", next[i]);
    }
    printf("\n");

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}