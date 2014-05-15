#include <thread>
#include <iostream>
#include <mutex>
#include <stack>

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
            return st.empty();
        }
        int pop(){
            lock_guard<mutex> lock(mx);
            if (!st.empty()){
                int tmp = st.top();
                st.pop();
                return tmp;
            } else {             
                cout << "It is empty" << endl;
                return 0;
            }
        }
        void push(int a){
            lock_guard<mutex> lock(mx);
            st.push(a);    
        }
        int size(){
            lock_guard<mutex> lock(mx);
            return st.size();    
        }
        int top(){
            lock_guard<mutex> lock(mx);
            return st.top();    
        }
};

void seeq1(safe_stack* s){
    s->push(25);
    s->push(17);
    s->push(9);
    cout << "1: The top equels to "<< s->pop() << endl;
    cout << "1: The top equels to "<< s->pop() << endl;
}

void seeq2(safe_stack* s){
    s->push(1);
    s->push(2);
    s->push(3);
    cout << "2: The top equels to "<< s->pop() << endl;
    cout << "2: The top equels to "<< s->pop() << endl;
}

int main(){    
    safe_stack my_stack;
    
    //thread_guard* t1 = new thread_guard(*new thread(&safe_stack::push, &my_stack, 25));
    //thread_guard* t2 = new thread_guard(*new thread(&safe_stack::push, &my_stack, 17));
    thread_guard t1(*new thread(seeq1, &my_stack));
    thread_guard t2(*new thread(seeq2, &my_stack));
    
    cout<<my_stack.pop()<<endl;
    return 0;
}