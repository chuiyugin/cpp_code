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
class Solution {
    public:
        // ListNode* removeElements(ListNode* head, int val) {
        //     ListNode *now = head;
        //     ListNode *pre = nullptr;//now的前一个
        //     ListNode *temp = nullptr;
        //     while(now != nullptr)
        //     {
        //         //头节点就是要删除的数据
        //         if(head->val == val)
        //         {
        //             head = head->next;
        //             delete now;
        //             now = head;
        //         }
        //         //头节点不是要删除的数据
        //         else if(now->val == val && head->val != val)
        //         {
        //             pre->next = now->next;
        //             temp = now;
        //             now = now->next;
        //             delete temp;
        //             temp = nullptr;
        //         }
        //         //没有要删除的数据
        //         else
        //         {
        //             pre = now;
        //             now = now->next;
        //         }
        //     }
        //     return head;
        // }

        //虚拟头节点解法
        ListNode* removeElements(ListNode* head, int val) {
            ListNode* vitHead = new ListNode(-1);
            vitHead->next = head;
            ListNode* now = vitHead;
            while(now->next != nullptr)
            {
                if(now->next->val == val)
                {
                    ListNode* temp = now->next; 
                    now->next = now->next->next;
                    now = now->next;
                    delete temp;
                }
                else
                {
                    now = now->next;
                }
            }
            return vitHead->next;
        }
    };

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *now = head;
    for(int i=2;i<=8;i++)
    {
        ListNode *temp = new ListNode(i);
        now->next = temp;
        now = now->next;
    }
    now = head;
    
    Solution s;
    now = s.removeElements(head,1);

    while(now->next!=nullptr)
    {
        printf("%d\n",now->val);
        now = now->next;
    }
    
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}