#include <type_traits>
using namespace std;



template <typename ItemType, bool freeObj = false>
class LinkedList
{
    template <typename T> 
    class Item
    {
        T obj;
    public:
        Item(T theObj);
        ~Item();
    };
    template <typename T>
    class Item <T *>
    {
        T *obj;
    public:
        Item(T *theObj);
        ~Item() { if(freeObj) delete obj; }
    };

public:
    void add(ItemType) {}
};



int main()
{
    LinkedList<int *> mylist1;
    mylist1.add(new int());
    
    LinkedList<int> mylist2;
    mylist2.add(int());
}
