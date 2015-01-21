
template<int index, typename first, typename...ObjectList>
struct type_at_index {
    typedef typename type_at_index<index-1, ObjectList...>::type type;
};
template<typename first, typename...ObjectList>
struct type_at_index<0,first,ObjectList...> {
    typedef first type;
};

template<bool has_child, bool has_parent, int index_, typename... ObjectList>
struct ObjectLinkage {};

template<int index, typename... ObjectList>
struct ObjectLinkage<true,false,index,ObjectList...> {
    typedef ObjectLinkage<false,true,index+1,ObjectList...> child_type;
    child_type* child;
    void setChild(child_type* c);
};

template<int index, typename... ObjectList>
struct ObjectLinkage<false,true,index,ObjectList...> {
    typedef ObjectLinkage<true,false,index-1,ObjectList...> parent_type;
    parent_type* parent;
    void setParent(parent_type* p);
};

template<int index, typename... ObjectList>
struct ObjectLinkage<true,true,index,ObjectList...> 
: ObjectLinkage<true,false,index,ObjectList...>, ObjectLinkage<false,true,index,ObjectList...>
{};

template<int index, typename... ObjectList>
void ObjectLinkage<true,false,index,ObjectList...>::setChild(ObjectLinkage<false,true,index+1,ObjectList...>* c) {child=c; if (c) c->parent = this;}

template<int index, typename... ObjectList>
void ObjectLinkage<false,true,index,ObjectList...>::setParent(ObjectLinkage<true,false,index-1,ObjectList...>* p) {parent=p; if (p) p->child = this;}

template <int index_, typename... ObjectList>
struct Object : ObjectLinkage<(index_+1<sizeof...(ObjectList)),(index_>0),index_,ObjectList...> {
    enum {index=index_};
    typedef typename type_at_index<index,ObjectList...>::type T;    
    T item;    
    Object(const T& t) : item(t) {}
};


int main() {
    Object<0, int, char, double> object(2);
    Object<1, int, char, double> child('r');
    object.setChild(&child);
    Object<2, int, char, double> grandChild(3.5);
    child.setChild(&grandChild);  // Want this line to work.
}