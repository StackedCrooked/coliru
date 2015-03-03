#include <type_traits>
#include <cassert>

template<bool... Bools>
struct any_of : public std::false_type
{
};

template<bool... Bools>
struct any_of<true, Bools...> : public std::true_type
{
};

template<bool... Bools>
struct any_of<false, Bools...> : public any_of<Bools...>
{
};

template<typename, typename = class default_tag>
struct list_mixin;

template<typename Type, typename Tag>
struct list_mixin
{
    Type * prev;
    Type * next;
};

template<typename Type, typename... Tags>
struct list_mixins : list_mixin<Type, Tags>...
{
    template<typename Tag, typename std::enable_if<any_of<std::is_same<Tag, Tags>::value...>::value, int>::type = 0>
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
}
