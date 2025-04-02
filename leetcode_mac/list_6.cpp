#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

//链表结构
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    //构造函数
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//解决方案
//虚拟头节点解法
class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            ListNode* now_A = headA;
            ListNode* now_B = headB;
            bool flag = false;
            while(now_A != nullptr)
            {
                while(now_B != nullptr)
                {
                    if(now_B == now_A)
                    {
                        if(flag==false)
                            return now_B;
                        flag = true;
                    }
                    else
                        now_B = now_B->next;
                }
                now_A = now_A->next;
                now_B = headB;
            }
            return nullptr;
        }
    };

int main()
{
    ListNode *head1 = new ListNode(1);
    ListNode *now = head1;
    for(int i=2;i<=3;i++)
    {
        ListNode *temp = new ListNode(i);
        now->next = temp;
        now = now->next;
    }

    ListNode *head2 = new ListNode(2);
    for(int i=3;i<=3;i++)
    {
        ListNode *temp = new ListNode(i);
        now->next = temp;
        now = now->next;
    }
    
    Solution s;
    now = s.getIntersectionNode(head1, head2);

    printf("%d\n",now->val);
    
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}