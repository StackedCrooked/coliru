template <typename T>
class test
{
  public:
    //........
    //generic getter
    template <typename F>
    auto getter_elem_member(F fun)->decltype(fun());
  private:
    T elem;                             
};

template <typename T>
template <typename F>
auto test<T>::getter_elem_member(F fun) ->decltype(fun())
{ return elem.fun(); }
int main(){}