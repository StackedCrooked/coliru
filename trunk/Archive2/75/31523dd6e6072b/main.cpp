#include <iostream>
#include <string>
#include <vector>
#include <memory> //new smart-pointers

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::cout;


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Thing
{
    public:
        Thing() = delete;
        Thing(int id) : mId(id){std::cout << "Thing with id " << mId << " created!" << std::endl;};
        ~Thing() {std::cout << "Thing with id " << mId << " deleted!" << std::endl;}
    public:
        int getId() {return mId;}
        void link(shared_ptr<Thing> other) { anotherThing = other;}
        void linkWeak(shared_ptr<Thing> other) { anotherWeakThing = other;}
    private:
        shared_ptr<Thing> anotherThing;
        weak_ptr<Thing> anotherWeakThing;
        int mId;
};

std::shared_ptr<Thing> createThing(int id)
{
    return std::shared_ptr<Thing> ( new Thing(id) );
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    shared_ptr<Thing> p0 = nullptr;
    
    cout << "Start local scope1." << std::endl;
    {
        Thing x {1};
        shared_ptr<Thing> p1(&x);          //two memory allocations
        shared_ptr<Thing> p2(make_shared<Thing>(2)); //guaranteed one memory allocation
        cout << p1->getId() <<std::endl;
        shared_ptr<Thing> p3 = p1;
        p0 = p1;
        p2 = nullptr;                                 //object with id 2 is deleted here (no more reference to the object)
        cout << "End of local scope1." << std::endl;
    }

    
    cout << "Start local scope2." << std::endl;
    //problem with shared_ptr in ring situation
    {
        shared_ptr<Thing> a1(make_shared<Thing>(1));
        shared_ptr<Thing> a2(make_shared<Thing>(2));
        shared_ptr<Thing> a3(make_shared<Thing>(3));
        a1->link(a2);
        a2->link(a3);
        a3->link(a1);               //because of these links, objects never deleted.
        cout << "End of local scope2." << std::endl;
    }
    
    cout << "Start local scope3." << std::endl;
    //solution for shared_ptr issue -> weak_ptr for links
    {
        shared_ptr<Thing> a1(make_shared<Thing>(4));
        shared_ptr<Thing> a2(make_shared<Thing>(5));
        shared_ptr<Thing> a3(make_shared<Thing>(6));
        a1->linkWeak(a2);
        a2->linkWeak(a3);
        a3->linkWeak(a1);               //Weak pointers does not count in reference counter.
        weak_ptr<Thing> a4 = a1;
        a3 = a4.lock();
        if(a3)
        {
            cout << "van"<<std::endl;
        }
        cout << "End of local scope3." << std::endl;
    }   
    cout << "End of program." << std::endl;
}
