#include <iostream>
using namespace std;

template <typename T>
class ForwardList 
{
    public:
    typedef T value_type;
    typedef size_t size_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    
    private:
    
        struct Node 
        {
            T data_;
            Node *right_;
            
            Node():data_(value_type()),right_(0){}
            
            explicit Node ( const value_type &data ) :data_(data),right_(0){}
            
            Node ( const Node &rhs ) : data_(rhs.data_),right_(rhs.right_){}
            
            Node& operator=( const Node &rhs ) 
            {
                if ( this != &rhs ) {data_ = rhs.data_;right_ = rhs.right_;}
                return *this;
            }
    } ;
    private:
    Node *head_; Node *previous_;
    public:
    
    struct const_iterator 
    {
        const_iterator ( const Node *p ) : pointing_(p){}
        const_iterator ( const const_iterator &rhs ) :pointing_(rhs.pointing_){}
        
        const_iterator& operator= ( const const_iterator &rhs ) 
        {
            pointing_ = rhs.pointing_;
            return *this;
        }
    
        const_iterator& operator= ( const Node *rhs ) 
        {
            pointing_ = rhs;
            return *this;
        }
        const_reference operator*() const 
        {
            return pointing_->data_;
        }
        const_pointer operator->() const 
        {
            return &pointing_->data_;
        }
        const_iterator& operator++() 
        {
            pointing_ = pointing_->right_;
            return *this;
        }
        
        bool operator!=( const const_iterator &rhs  )  const
        {
            return pointing_ != rhs.pointing_ ;
        }
        
        const Node* pointing() { return pointing_; }
        
        private:
        const Node *pointing_;
    };

    ForwardList( size_type n ):head_(0),previous_(0) 
    {
        if ( n ) 
        {
            head_ = new Node;
            previous_ = new Node;
            previous_->right_ = head_;
            Node *tail(head_);

            while ( --n ) 
            {
                tail->right_ = new Node;
                tail = tail->right_;
            }
        }
    }
    const_iterator cbegin() const { return head_; }
    const_iterator cend() const 
    {
        Node *iter = head_;
        while ( iter )
        iter = iter->right_;
        return iter;
    }
};

template<typename T>
bool operator!=( typename ForwardList<T>::const_iterator first ,
typename ForwardList<T>::const_iterator second ) {
    return first.pointing() != second.pointing();
}

int main() 
{
    ForwardList<int> fillConstruction(10);
    for ( ForwardList<int>::const_iterator citer 
                         = fillConstruction.cbegin() ,
                          citer_end = fillConstruction.cend();
                          citer != citer_end;
                          ++citer )
            cout << *citer << " ";
    cout << endl;
    
}