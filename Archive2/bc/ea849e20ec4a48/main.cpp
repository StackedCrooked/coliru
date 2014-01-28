#include <iostream>
#include <cassert>
struct stack
{
    
    stack() = default ; // default constructor, construct empty stack
    explicit stack( int v ) : stack() { push(v) ; } // construct stack of size one

    ~stack() { while( !empty() ) pop() ; }

    bool empty() const { return head == nullptr ; }
    int top() const { assert( !empty() ) ; return head->data ; }

    void pop() { assert( !empty() ) ; auto t = head ; head = head->next ; delete t ; }
    void push( int v ) { head = new node( v, head ) ; }

    /* Utility function to print a linked list */
	std::ostream& print( std::ostream& stm = std::cout )
	{
	    stm << "[ " ;
	    for( node* n = head ; n ; n = n->next ) stm << n->data << ' ' ;
        return stm << "]\n" ;
	}

    private:

        /* structure of a linked list node */
        struct node
        {
            int data;
            node *next;
            node( int v, node* n ) : data(v), next(n) {}
        };

        node* head = nullptr ;

        // non-copyable
        stack( const stack& ) = delete ;
        stack& operator= ( const stack& ) = delete ;
};

class A
{
	private: static stack stk ;

	public:
		static void test( int v )
		{
		    stk.push(v);
		    stk.print() ;
        }
};

// define static variable (initialize stack with size one)
stack A::stk(11);

int main()
{
	A a1, a2, a3 ;
	a1.test(222);
	a2.test(3333) ;
	a3.test(44444) ;
	A::test(555555) ;
}
