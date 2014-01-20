#include <iostream>
#include <array>
#include <vector>

 namespace detail
 {
    template<std::size_t depth>
    struct for_each_in_depth_impl
    {      
        template<class ForwardRange, class UnaryFunction>
        static inline 
        void call(ForwardRange& range, UnaryFunction& f)
        { 
            for (auto& i : range)
                for_each_in_depth_impl<depth - 1>::call(i, f);
        } 
    };
    
    template<>
    struct for_each_in_depth_impl<0>
    {      
        template<class ForwardRange, class UnaryFunction>
        static inline 
        void call(ForwardRange& range, UnaryFunction& f)
        { 
            for (auto& i : range)
                f(i);
        } 
    };
}

template
<
    std::size_t depth
  , class ForwardRange
  , class UnaryFunction 
>
inline void 
for_each_in_depth(ForwardRange&& range, UnaryFunction&& f)
{
    detail::for_each_in_depth_impl<depth>::call(range, f);
}

int main(int argc, char** argv) {
    std::array<std::vector<int>, 3> a
    {
        std::vector<int>{1, 2}
      , std::vector<int>{3, 4}
      , std::vector<int>{5, 6, 7}
    };
    for_each_in_depth<1>(a, [](int i){ std::cout << i << ", "; });
    return 0;
}