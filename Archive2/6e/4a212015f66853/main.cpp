#include <vector>
#include <iostream>

#include <boost/intrusive/list.hpp>

using namespace boost::intrusive;

class MyClass : public list_base_hook<link_mode<auto_unlink>> // This is a derivation hook
{
    int anInt;
  public:
    list_member_hook<link_mode<auto_unlink>> member_hook_; // This is a member hook

    MyClass(int i) : anInt(i) {}
};

// Define a list that will store MyClass using the public base hook
typedef list<MyClass, constant_time_size<false>> BaseList;

// Define a list that will store MyClass using the public member hook
typedef list<MyClass, member_hook<MyClass, list_member_hook<link_mode<auto_unlink>>, &MyClass::member_hook_>, constant_time_size<false> > MemberList;

int main() {
    // Create several MyClass objects, each one with a different value
    std::vector<MyClass> values;
    for (int i = 0; i < 100; ++i)
        values.emplace_back(i);

    BaseList   baselist;
    MemberList memberlist;

    // Now insert them in the reverse order in the base hook list
    for (auto& e : values) {
        baselist.push_front(e);
        memberlist.push_back(e);
    }

    // Now test lists
    auto rbit(baselist.rbegin());
    auto mit(memberlist.begin());
    auto it(values.begin()), itend(values.end());

    // Test the objects inserted in the base hook list
    for (; it != itend; ++it, ++rbit)
        if (&*rbit != &*it)
            return 1;

    // Test the objects inserted in the member hook list
    for (it = values.begin(); it != itend; ++it, ++mit)
        if (&*mit != &*it)
            return 1;

    values.clear();

    std::cout << values.size()     << "\\n";
    std::cout << baselist.size()   << "\\n";
    std::cout << memberlist.size() << "\\n";
}
