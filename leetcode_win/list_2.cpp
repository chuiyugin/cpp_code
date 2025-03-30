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

 //解决方案
 class MyLinkedList {
    public:

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

        ListNode* _VitHead;
        int _size = -1;
    
        MyLinkedList() {
            _VitHead = new ListNode(-1);
            _size = -1;
        }
        
        int get(int index) {
            if((_size < 0) || (index > _size))
            {
                return -1;
            }
            else
            {
                ListNode* now = _VitHead;
                for(int i=0;i<=index;i++)
                {
                    now = now->next;
                }
                return now->val;
            }
        }
        
        void addAtHead(int val) {
            ListNode* temp = new ListNode(val);
            temp->next = _VitHead->next;
            _VitHead->next = temp;
            _size++;
        }
        
        void addAtTail(int val) {
            ListNode* temp = new ListNode(val);
            ListNode* now = _VitHead;
            while(now->next!=nullptr)
            {
                now = now->next;
            }
            now->next = temp;
            _size++;
        }
        
        void addAtIndex(int index, int val) {
            ListNode* temp = new ListNode(val);
            ListNode* now = _VitHead;
            ListNode* pre = _VitHead;
            if(index > _size+1)
                return;
            for(int i=0;i<=index;i++)
            {
                
                pre = now;
                now = now->next;
            }
            temp->next = pre->next;
            pre->next = temp;
            _size++;
        }
        
        void deleteAtIndex(int index) {
            ListNode* now = _VitHead;
            ListNode* pre = _VitHead;
            if(index > _size)
                return;
            for(int i=0;i<=index;i++)
            {
                pre = now;
                now = now->next;
            }
            pre->next = now->next;
            delete now;
            _size--;
        }
    };
    
/**
    * Your MyLinkedList object will be instantiated and called as such:
    * MyLinkedList* obj = new MyLinkedList();
    * int param_1 = obj->get(index);
    * obj->addAtHead(val);
    * obj->addAtTail(val);
    * obj->addAtIndex(index,val);
    * obj->deleteAtIndex(index);
*/

int main()
{
    MyLinkedList* myLinkedList = new MyLinkedList();
    myLinkedList->addAtHead(7);
    myLinkedList->addAtHead(2);
    myLinkedList->addAtHead(1);
    myLinkedList->addAtIndex(3, 0);
    myLinkedList->deleteAtIndex(2);
    myLinkedList->addAtHead(6);
    myLinkedList->addAtTail(4);
    cout << myLinkedList->get(4) << endl; 
    
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}