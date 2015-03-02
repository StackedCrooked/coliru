
template<typename T,
template<typename,typename> class F,
template<typename,typename> class... Rest>
struct warp_base_class_helper
{
  using type = F<T, typename warp_base_class_helper<T, Rest...>::type>;
};

template<typename T,
template<typename,typename> class F>
struct warp_base_class_helper<T, F>
{
  using type = F<T, void>;
};

template<typename T, typename = void>
struct A
{
    
};

template<typename T, typename = void>
struct B
{
    
};

using test = typename warp_base_class_helper<int, A, B>::type;
test x = 1;
int main()
{
}
