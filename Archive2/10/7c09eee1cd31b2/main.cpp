#include <iostream>
using std::cout;
using std::endl;

template<class T> class Queue //Base class
        {
        private:
            T ArrQueue[20];
        protected:
            T* a;
            T* b;
        public:

        Queue()
        {
             cout<<"QUEUE CONST "<<  endl;
        }
        void push(T x);
        void pop(void);
        };


        template <class T>
        class stack :public Queue<T> // Derived class
        {
        public:
            stack():Queue<T>()
            {
                this->b=this->a;
            }
             void pop()
            {
                this->b--;
            }
        };


int main()
{
    stack<int> S;
    return 0;
}