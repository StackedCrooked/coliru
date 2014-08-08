#include <iostream>
#include <mutex>
#include <vector>


template<typename T>
struct Stack : private std::mutex
{    
    struct Lock : private std::lock_guard<Stack<T>>
    {
        using std::lock_guard<Stack<T>>::lock_guard;
    };
    
    using mutex::lock;
    using mutex::unlock;
    
    T pop(Lock&)
    {
        auto result = vec_.back();
        vec_.pop_back();
        return result;
    }
    
    void push(Lock&, T n)
    {
        vec_.push_back(n);
    }
    
private:
    std::vector<T> vec_;
};


int main()
{
    Stack<int> stack;    
    
    {
        Stack<int>::Lock lock(stack);    
        stack.push(lock, 1);
        stack.push(lock, 2);
    } 
    
    {
        Stack<int>::Lock lock(stack);    
        stack.pop(lock);
    }
}
