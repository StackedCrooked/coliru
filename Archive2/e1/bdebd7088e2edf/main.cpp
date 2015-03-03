#include <type_traits>
#include <cassert>

template<typename Type, typename Tag = class default_tag>
struct list_mixin
{
    Type * prev;
    Type * next;
};

template<typename Type, typename... Tags>
struct list_mixins : list_mixin<Type, Tags>...
{
    template<typename Tag>
    list_mixin<Type, Tag> & get_list()
    {
        return *static_cast<list_mixin<Type, Tag> *>(this);
    }    
};
 
struct thread : list_mixins<thread, class all, class same_state>
{
};

int main()
{
    thread t;
    t.get_list<all>().next = nullptr;
    t.get_list<same_state>().next = &t;
    
    assert(t.get_list<all>().next == nullptr);
    assert(t.get_list<same_state>().next == &t);
    
    t.get_list<class some_type>(); // doesn't compile
}
