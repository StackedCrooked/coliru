#include <memory>
#include <vector>
#include <initializer_list>
#include <iostream>

template <typename T, template <typename ELEM, typename ALLOC=std::allocator<ELEM> > class Cont=std::vector>
class VehiclesContainer {
  public:
    VehiclesContainer(std::initializer_list<T> l):container(l){};
    virtual ~VehiclesContainer(){};
    template
    <typename U, template <typename ELEM2, typename ALLOC=std::allocator<ELEM2> > class Cont2>
    friend std::ostream& operator<<(std::ostream& out, const VehiclesContainer<U,Cont2>& obj){
    for(typename Cont<T>::const_iterator it=obj.container.begin(); it!=obj.container.end(); ++it)
        out << *it << " ";
    return out;
}
  private:
    Cont<T> container;
};

int main()
{
    VehiclesContainer<int> v{1,2,3,4};
    std::cout << v;
}