#include <vector>
#include <iostream>

#include <boost/intrusive/list.hpp>

using namespace boost::intrusive;

class MyClass : public list_base_hook<> // This is a derivation hook
{
    int anInt;
  public:
    list_member_hook<> member_hook_; // This is a member hook

    MyClass(int i) : anInt(i) {}
};

// Define a list that will store MyClass using the public base hook
typedef list<MyClass> BaseList;

// Define a list that will store MyClass using the public member hook
typedef list<MyClass, member_hook<MyClass, list_member_hook<>, &MyClass::member_hook_> > MemberList;

int main() {
    typedef std::vector<MyClass>::iterator VectIt;

    // Create several MyClass objects, each one with a different value
    std::vector<MyClass> values;
    for (int i = 0; i < 100; ++i)
        values.push_back(MyClass(i));

    BaseList baselist;
    MemberList memberlist;

    // Now insert them in the reverse order in the base hook list
    for (VectIt it(values.begin()), itend(values.end()); it != itend; ++it)
        baselist.push_front(*it);

    // Now insert them in the same order as in vector in the member hook list
    for (VectIt it(values.begin()), itend(values.end()); it != itend; ++it)
        memberlist.push_back(*it);

    // Now test lists
    {
        BaseList::reverse_iterator rbit(baselist.rbegin());
        MemberList::iterator mit(memberlist.begin());
        VectIt it(values.begin()), itend(values.end());

        // Test the objects inserted in the base hook list
        for (; it != itend; ++it, ++rbit)
            if (&*rbit != &*it)
                return 1;

        // Test the objects inserted in the member hook list
        for (it = values.begin(); it != itend; ++it, ++mit)
            if (&*mit != &*it)
                return 1;

        baselist.clear();
        memberlist.clear();
        values.clear();

        std::cout << values.size()     << "\n";
        std::cout << baselist.size()   << "\n";
        std::cout << memberlist.size() << "\n";
    }

    return 0;
}
