#include <vector>

using namespace std;

template<class T>
class Stack : private vector<T>
{
    vector<T> S;

public:
    Stack<T> push(T str);
    Stack<T> operator += (const Stack<T> &str);
};


template<class T>
Stack<T> Stack<T>::push(T str)
{
    S.push_back(qElem(str));

}

template<class T>
Stack<T> Stack<T>::operator += (const Stack<T> &str)
{
    return this->push(str);

}

int main() {
    Stack<int> s;
    s += 5;
}