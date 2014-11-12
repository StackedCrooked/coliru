#include <thread>
#include <iostream>
#include <mutex>
#include <stack>
#include <stdio.h>

using namespace std; 

class thread_guard{
private:
    thread &t;
public:
    explicit thread_guard(thread &t_)
    :
    t(t_)
    {}
    ~thread_guard(){
        if(t.joinable()){
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

class safe_stack{
    private:
        mutable mutex mx;
        stack<int> st;
    public:
        safe_stack(){}
        ~safe_stack(){}
        bool empty(){
            lock_guard<mutex> lock(mx);
            fprintf(ofp, "Thread number %d: empty()\n",thread_id);
            return st.empty();
        }
        int pop(){
            lock_guard<mutex> lock(mx);
            fprintf(ofp, "Thread number %d: pop() = ",thread_id);
            if (!st.empty()){
                int tmp = st.top();
                fprintf(ofp, "%d\n",tmp);
                st.pop();
                return tmp;
            } else {             
                fprintf(stderr, "ouach!!\n");
                cout << "It is empty" << endl;
                return 0;
            }
        }
        void push(int a){
            lock_guard<mutex> lock(mx);
            fprintf(ofp, "Thread number %d: push()\n",thread_id);
            st.push(a);    
        }
        int size(){
            lock_guard<mutex> lock(mx);
            fprintf(ofp, "Thread number %d: size()\n",thread_id);
            return st.size();    
        }
        int top(){
            lock_guard<mutex> lock(mx);
            fprintf(ofp, "Thread number %d: top()\n",thread_id);
            return st.top();    
        }
};

void seeq1(safe_stack* s){
    s->push(25);
    s->push(17);
    s->push(9);
}

void seeq2(safe_stack* s){
    s->push(1);
    s->push(2);
    s->push(3);
}


FILE *ofp;
int main(){  

    ofp = fopen("log.txt", "w+");

    safe_stack my_stack;
    
    thread_guard t1(*new thread(seeq1, &my_stack));
    thread_guard t2(*new thread(seeq2, &my_stack));
    
    return 0;
}
