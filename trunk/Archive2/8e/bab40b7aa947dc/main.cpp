#include <iostream>

struct stack
{
    bool full() const { return count == MAX_SIZE ; }
    bool empty() const { return count == 0 ; }

    bool push( int v )
    {
        if( full() )
        {
            std::cerr << "stack is full\n" ;
            return false ;
        }

        array[count] = v ; // place the element at the top
        ++count ; // increment count
        return true ;
    }

    int pop()
    {
        if( empty() )
        {
            std::cerr << "stack is empty\n" ;
            return -1 ;
        }

        --count ; // decrement count
        return array[count] ;
    }

     private:
         enum { MAX_SIZE = 10 };
         int array[MAX_SIZE] ;
         int count = 0 ; //number of items on the stack; initially zero
};

int main()
{
    stack stk ;

    // push values into the stack
    int v = 1 ;
    while( !stk.full() ) { stk.push(v) ; v *= 2 ; }

    // pop and print them out one by one
    while( !stk.empty() ) std::cout << stk.pop() << ' ' ;
    std::cout << '\n' ;
}
