#include<iostream>
#include <vector>
using namespace std;

template<class T>
class Stack;

template<class T>
Stack<T>  operator+(const Stack<T> &one,const Stack<T> &other);

template<class T>
class Stack
{
    private:
        vector<T> stack;

    public:
    vector<T> returnStack()
    {
        return stack;
    }

        vector<T> returnStack() const
    {
            return stack;
    }

    void Push(T item)
    {
        stack.insert(stack.begin()+stack.size(),item);
    }

    friend Stack operator+<>(const Stack &one,const Stack &other);
};

template<class T>
Stack<T>  operator+(const Stack<T> &one,const Stack<T> &other)
{
    Stack<T> newStack;
    for (typename vector<T>::size_type i = 0; i < one.size(); i++)
    {
        newStack.Push(one[i]);
    }
    for (typename vector<T>::size_type i = 0; i < other.returnStack().size(); i++)
    {
        newStack.Push(other.returnStack()[i]);
    }
    return newStack;
}

int main()
{
    Stack <int > a;
    Stack <int > b;
    a.Push(1);
    a.Push(2);
    b.Push(3);
    b.Push(4);
    Stack <int> c=a+b ;//have a bug
    return 0;
}