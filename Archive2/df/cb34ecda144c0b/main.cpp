#include <iostream>
using namespace std;

template <typename T, int SIZE>
class Stack
{
        T element;
        T size[SIZE];
        public:
        void  setElement (T elmt)
        {
                element  = elmt;
                cout <<"Inside setElement"<<endl;
        };
        Stack()
        {
                cout <<"Constructor "<<endl;
                cout <<" SIZE is "<<SIZE<<endl;
        }
};

// Int class Specialization.


template<int SIZE>
class Stack<int, SIZE>
{  int element;
        int size[SIZE];
        public:
        void  setElement (int elmt)
        {
                element  = elmt;
                cout <<"Inside setElement"<<endl;
        };

        Stack()
        {
                cout <<"Constructor "<<endl;
                cout <<" SIZE s is "<<SIZE<<endl;
        }
};


int main(int argc, char ** argv)
{
  Stack<float,50> s;
  Stack<int,20> s1;
}