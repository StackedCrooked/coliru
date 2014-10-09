    #include <iostream>
    #include <cstdlib>
    #include <cassert>
    using namespace std;

    #define INITCAP 8
    #define TYPE char

    class FullStackException{};
    class EmptyStackException{};

    class stack{
    public:
        // constructor with default capacity value
        stack(int=INITCAP);

        // copy constructor
        stack(const stack&);

        // assignment operator
        stack& operator=(const stack&);

        // destructor
        ~stack();

        // push an element;
        // if fixed sized stack, throw FullStackException when stack is full
        void push(const TYPE x);

        // remove and element; throw EmptyStackException when stack is empty
        void pop();

        // return a reference to the top element without popping; throw EmptyStackException when stack is empty
        TYPE& top();

        // return true if the stack is empty, false otherwise
        bool empty();

        // return the number of elements currently on the stack
        int  size();

        // return the current capacity of the stack
        int  capacity();

    private:
        TYPE * _arr;     // pointer to dynamic integer array
        int _tos;       // index to top of stack
        int _capacity;  // current capacity 
    }; 

    // constructor with default capacity value
    stack::stack( int n ) {
            _capacity = INITCAP;
            _arr = new char[_capacity];
            _tos = -1;
    }

    // copy constructor
    stack::stack( const stack& s ) {
            _capacity = s._capacity;
            _arr = new char[_capacity];

            for ( int i = 0; i < s._tos + 1; i++ ) {
                    _arr[i] = s._arr[i];
            }
            _tos = s._tos;
    }

    // assignment operator
    stack& stack::operator=( const stack& s ) {
            _capacity = s._capacity;

            for ( int i = 0; i < s._tos + 1; i++ ) {
                    _arr[i] = s._arr[i];
            }
            _tos = s._tos;

            return *this;
    }

    // destructor
    stack::~stack() {
            delete[] _arr;
    }

    // push an element;
    // if fixed sized stack, throw FullStackException when stack is full
    void stack::push(const TYPE x) {
            if ( _tos + 1 == _capacity ) {
                    _capacity *= 2;
                    int *temp = new int[_capacity];
                    for ( int i = 0; i < _capacity; i++ ) {
                            temp[i] = _arr[i];
                    }

                    delete[] temp;
            }
            _tos++;
            _arr[_tos] = x;
    }

    // remove and element; throw EmptyStackException when stack is empty
    void stack::pop() {
            if ( _tos == -1 ) {
                    throw EmptyStackException();
            }
            _tos--;
    }

    // return a reference to the top element without popping; throw EmptyStackException when stack is empty
    TYPE& stack::top() {
            if ( _tos == -1 ) {
                    throw EmptyStackException();
            }
            return _arr[_tos];
    }

    // return true if the stack is empty, false otherwise
    bool stack::empty() {
            return ( _tos == -1 );
    }

    // return the number of elements currently on the stack
    int stack::size() {
            return _tos + 1;
    }

    // return the current capacity of the stack
    int stack::capacity() {
            return _capacity;
    }