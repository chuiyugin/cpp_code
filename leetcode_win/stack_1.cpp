#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
    public:
        stack<int> In;
        stack<int> Out;
        MyQueue() {}
    
        void push(int x) { In.push(x); }
    
        int pop() {
            if (!Out.empty()) {
                int temp = Out.top();
                Out.pop();
                return temp;
            } else {
                while (!In.empty()) {
                    Out.push(In.top());
                    In.pop();
                }
                return Out.top();
            }
        }
    
        int peek() {
            if (!Out.empty())
                return Out.top();
            else {
                while (!In.empty()) {
                    Out.push(In.top());
                    In.pop();
                }
                return Out.top();
            }
        }
    
        bool empty() {
            if (In.empty() && Out.empty())
                return true;
            else
                return false;
        }
    };
    
    /**
     * Your MyQueue object will be instantiated and called as such:
     * MyQueue* obj = new MyQueue();
     * obj->push(x);
     * int param_2 = obj->pop();
     * int param_3 = obj->peek();
     * bool param_4 = obj->empty();
     */
    

int main()
{
    MyQueue* myQueue = new MyQueue();
    //myQueue->push(1);
    myQueue->push(2);
    printf("%d\n",myQueue->peek());
    myQueue->pop();
    //myQueue->pop();
    printf("%d\n",myQueue->empty());
    //myQueue->peek();


    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}