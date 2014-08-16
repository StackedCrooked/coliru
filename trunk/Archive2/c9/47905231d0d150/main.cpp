    template <class T> class mylist;
    
    template <class T> class mlist
    {
    protected:
        T item = 0;
        mylist<T>* next = 0;
    };
    
    template <class T> class mylist : mlist<T>
    {
    private:
        T item;
        mylist<T>* next;
    
    // --- some funtions ---
    
    };


int main()
{
 mylist<int> list; 
}
