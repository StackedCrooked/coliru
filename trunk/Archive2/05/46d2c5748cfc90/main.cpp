#include <iostream>

template <typename ItemType, bool freeObj = false>
class LinkedList
{
    template <typename T> 
    class Item
    {
        T obj;
    public:
        Item(T)
        {
            std::cout << __PRETTY_FUNCTION__ << '\n';
        }
        ~Item()
        {
            std::cout << __PRETTY_FUNCTION__ << '\n';
        }
    };
    template <typename T>
    class Item <T *>
    {
        T *obj;
    public:
        Item(T *)
        {
            std::cout << __PRETTY_FUNCTION__ << '\n';
        }
        ~Item()
        {
            std::cout << __PRETTY_FUNCTION__ << '\n';
            if(freeObj) delete obj;
        }
    };

public:
    void add(ItemType item)
    {
        // add item to list
        Item<ItemType> i(item);
    }
};



int main()
{
    LinkedList<int *> mylist1;
    mylist1.add(new int());
    
    LinkedList<int> mylist2;
    mylist2.add(int());
}
