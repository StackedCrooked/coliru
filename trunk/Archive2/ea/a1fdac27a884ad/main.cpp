
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
struct ListNode
{
    T item;
    ListNode* next;
    ListNode* prev;
};

template <typename T>
struct LinkedList
{
    LinkedList();
    ~LinkedList() {clear();}
    void clear();
    void append(const T&);
    void for_all( void(*)(T&) );
    
    struct iterator
    {
        iterator() = default;
        iterator(const iterator&) = default;
        iterator operator++() { i=i->next; return i; }
        iterator operator--() { i=i->prev; return i; }
        T& operator*() { return i->item; }
        bool operator==(const iterator& i2) { return i == i2.i; }
        bool operator!=(const iterator& i2) { return i != i2.i; }
    private:
        ListNode<T>* i=0;
        iterator(ListNode<T>* lnp) : i(lnp) {}
    friend
        struct LinkedList;
    };
    
    iterator begin() { return sentry.next; }
    iterator end() { return &sentry; }
    size_t size() { return sz; }
    bool empty() { return sz!=0; }
    
    iterator insert( iterator, const T& );
    iterator erase( iterator );
    iterator push_back( const T& t )  { return insert(   end(), t ); }
    iterator push_front( const T& t ) { return insert( begin(), t ); }
    iterator find( const T& );
    
    T& front() { return sentry.next->item; }
    T& back() { return sentry.prev->item; }
    
    void pop_front() { erase(sentry.next); }
    void pop_back() { erase(sentry.prev); }
    
    void sort();
    
    void reverse();
    
private:

    void unlink( ListNode<T>* node );
    void inlink( ListNode<T>* node, ListNode<T>* before );
        
private:
    size_t sz;
    ListNode<T> sentry;
    void sentset() { sentry.next=sentry.prev=&sentry; sz=0; }
};

template <typename T>
void LinkedList<T>::unlink( ListNode<T>* node )
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

template <typename T>
void LinkedList<T>::inlink( ListNode<T>* node, ListNode<T>* before )
{
    node->prev = before->prev;
    node->next = before;
    node->prev->next = node;
    node->next->prev = node;
}

template <typename T>
LinkedList<T>::LinkedList()
{
    sentset();    
}

template <typename T>
void LinkedList<T>::clear()
{
    ListNode<T>* itr = sentry.next;
    while( itr != &sentry )
    {
        ListNode<T>* nxt = itr->next;
        delete itr;
        itr = nxt;
    }
    sentset();
}

template <typename T>
void LinkedList<T>::append(const T& t)
{
    auto p = new ListNode<T>{t};
    inlink(p,&sentry);
    ++sz;
}

template <typename T>
auto LinkedList<T>::insert(iterator i, const T& t) -> iterator
{
    auto p = new ListNode<T>{t};
    inlink(p,i.i);
    ++sz;
    return p;
}

template <typename T>
auto LinkedList<T>::erase(iterator i) -> iterator
{
    if( i.i == &sentry ) return &sentry;
    auto ret = i.i->next;
    unlink(i.i);
    delete i.i;
    --sz;
    return ret;
}

template <typename T>
auto LinkedList<T>::find(const T& t) -> iterator
{
    auto itr = begin();
    while(itr!=end())
    {
        if( t == *itr ) break;
        ++itr;
    }
    return itr;
}

template <typename T>
void LinkedList<T>::for_all( void (*fp)(T&) )
{
    if(!fp) return;
    ListNode<T>* itr = sentry.next;
    while( itr != &sentry )
    {
        fp(itr->item);
        itr = itr->next;
    }
}

template <typename T>
void LinkedList<T>::sort()
{
    auto last = sentry.next;
    auto curr = sentry.next->next;
    while( curr != &sentry )
    {
        auto nxt = curr->next;
        if( curr->item < last->item )
        {
            unlink(curr);
            auto inspos = last->prev;
            while( (inspos!=&sentry) && (curr->item < inspos->item ) )
                inspos = inspos->prev;
            inlink(curr,inspos->next);
        }
        curr = nxt;
    }
}

template <typename T>
void LinkedList<T>::reverse()
{
    auto curr = &sentry;
    
    while(true)
    {
        auto next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        curr = next;
        if(curr==&sentry) break;
    }
}

// --------------------------------------------------------------------------------------

void print_int_node( int& i)
{
    printf(" %d",i);
}

template<typename T>
void p_all( string lead , T& cont )
{
    cout << lead ;
    for( auto&& i : cont )
    {
        cout << " " << i;
    }
    cout << '\n';
}

int main(int argc, char** argv)
{
    LinkedList<float> lli;
    
    lli.append(1.4);
    lli.append(2.5);
    lli.append(3.6);

    lli.insert( lli.end(), 1.1 );
    lli.insert( lli.end(), 2.2 );
    lli.insert( lli.end(), 3.3 );
    
    lli.insert( lli.begin(), 22.f );
    lli.insert( lli.begin(), 23.f );
    lli.insert( lli.begin(), 24.f );
    
    p_all( "original :", lli );

    printf("\n %lu \n" , lli.size() );
        
    printf(" first %0.2f last %0.2f \n", lli.front(), lli.back() );
    
    lli.sort();

    p_all( "sorted :", lli );
    
    lli.reverse();
    
    p_all( "reversed :", lli );

    printf("\ndone\n");
        
}


