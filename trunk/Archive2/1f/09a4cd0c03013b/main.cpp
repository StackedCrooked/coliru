template<typename Type, typename Tag = class default_tag>
struct list_mixin
{
    Type * prev;
    Type * next;
};
 
class thread : list_mixin<thread, class all>, list_mixin<thread, class same_state>
{
    // ....
};