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
// class Solution {
//     public:
//         ListNode* swapPairs(ListNode* head) {
//             ListNode* temp = nullptr;
//             ListNode* temp1 = nullptr;
//             ListNode* now = nullptr;
//             int count = 0;
//             if((head==nullptr) || (head->next==nullptr))
//                 return head;
//             else if(head->next->next == nullptr)
//             {
//                 temp = head->next;
//                 head->next = nullptr;
//                 temp->next = head;
//                 return temp;
//             }
//             else
//             {
//                 now = head;
//                 int count = 0;
//                 while(now->next!=nullptr && now->next->next!=nullptr)
//                 {
//                     if(count==0)
//                     {
//                         head = now->next;
//                         now->next = now->next->next;
//                         head->next = now;
//                         count++;
//                     }
//                     else if(count%2==1)
//                     {
//                         temp = now->next;
//                         temp1 = now->next->next->next;
//                         now->next = now->next->next;
//                         now->next->next = temp;
//                         temp->next = temp1;
//                         count++;
//                         now = now->next;
//                     }
//                     else
//                     {
//                         count++;
//                         now = now->next;
//                     }
//                 }
//                 return head;
//             }
//         }
//     };

//虚拟头节点解法
class Solution {
    public:
        ListNode* swapPairs(ListNode* head) {
            ListNode* temp = nullptr;
            ListNode* temp1 = nullptr;
            ListNode* VitHead = new ListNode(-1);
            VitHead->next = head;
            ListNode* now = VitHead;
            while((now->next != nullptr) && (now->next->next != nullptr))
            {
                temp = now->next;
                temp1 = now->next->next->next;
                
                now->next = now->next->next;
                now->next->next = temp;
                temp->next = temp1;

                now = now->next->next;
            }
            return VitHead->next;
        }
    };

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *now = head;
    for(int i=2;i<=7;i++)
    {
        ListNode *temp = new ListNode(i);
        now->next = temp;
        now = now->next;
    }
    now = head;
    
    Solution s;
    now = s.swapPairs(head);

    while(now!=nullptr)
    {
        printf("%d\n",now->val);
        now = now->next;
    }
    
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}