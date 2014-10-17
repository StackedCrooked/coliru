#include <type_traits>
#include <iostream>
#include <vector>

struct foo_out_type {};
struct foo_in_type {};
struct baz_out_type {};
struct bar_in_type {};

foo_out_type foo(foo_in_type input)
{
    std::cout << "foo" << std::endl;
}

baz_out_type bar(bar_in_type input)
{
    std::cout << "bar" << std::endl;
}

template <typename T_IN, typename T_OUT>
using is_supported = std::integral_constant<bool,
                                     (std::is_same<T_IN, foo_in_type>::value && std::is_same<T_OUT, foo_out_type>::value)
                                  || (std::is_same<T_IN, bar_in_type>::value && std::is_same<T_OUT, baz_out_type>::value)>;

template <typename T_IN, typename T_OUT>
using funtion_ptr = T_OUT(*)(T_IN);

template <typename T_IN, typename T_OUT> funtion_ptr<T_IN, T_OUT> getfunc() { return nullptr; }
template <> funtion_ptr<foo_in_type, foo_out_type> getfunc() { return &foo; }
template <> funtion_ptr<bar_in_type, baz_out_type> getfunc() { return &bar; }

template <typename T_IN, typename T_OUT>
auto do_list(const std::vector<T_IN>& input, std::vector<T_OUT>& output)
    -> typename std::enable_if<!is_supported<T_IN, T_OUT>::value>::type
{
    std::cout << "default do_list" << std::endl;     
}

template <typename T_IN, typename T_OUT>
auto do_list(const std::vector<T_IN>& input, std::vector<T_OUT>& output)
    -> typename std::enable_if<is_supported<T_IN, T_OUT>::value>::type
{
    std::cout << "specialized do_list" << std::endl;
    
    T_OUT(*T_FUNC)(T_IN) = getfunc<T_IN, T_OUT>();
    
    for (size_t i=0; i<input.size(); i++)
        output.push_back(T_FUNC(input[i]));
}                                        

int main()
{
    std::vector<int> vi_in, vi_out;
    std::vector<foo_in_type> vf_in; std::vector<foo_out_type> vf_out;
    std::vector<bar_in_type> vb_in; std::vector<baz_out_type> vb_out;
    
    do_list(vi_in, vi_out);
    do_list(vf_in, vf_out);
    do_list(vb_in, vb_out);
}
