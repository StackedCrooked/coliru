#include <iostream>

namespace reaver
{
    template<uint64_t I>
    struct increment
    {
        static constexpr uint64_t advance()
        {
            return I + 1;
        }
    };

    template<uint64_t I, uint64_t J>
    struct different
    {
        static constexpr bool check()
        {
            return I != J;
        }
    };

    template<uint64_t I, uint64_t J>
    struct less
    {
        static constexpr bool check()
        {
            return I < J;
        }
    };

    namespace _detail
    {
        template<uint64_t, uint64_t, template<uint64_t> class, template<uint64_t, uint64_t> class, template<uint64_t> class, bool>
        struct _static_for;
        
        template<uint64_t Begin, uint64_t End, template<uint64_t> class Func, template<uint64_t, uint64_t> class Compare,
            template<uint64_t> class Advance>
        struct _static_for<Begin, End, Func, Compare, Advance, true>
        {
            static constexpr uint64_t next = Advance<Begin>::advance();
            
            static void exec()
            {
                Func<Begin>{}();

                _static_for<next, End, Func, Compare, Advance, Compare<next, End>::check()>::exec();
            }
        };

        template<uint64_t Begin, uint64_t End, template<uint64_t> class Func, template<uint64_t, uint64_t> class Compare,
            template<uint64_t> class Advance>
        struct _static_for<Begin, End, Func, Compare, Advance, false>
        {
            static void exec()
            {
            }
        };
    }
    
    template<uint64_t Begin, uint64_t End, template<uint64_t> class Func, template<uint64_t, uint64_t> class Compare = less,
        template<uint64_t> class Advance = increment>
    struct static_for
    {
        static void exec()
        {
            _detail::_static_for<Begin, End, Func, Compare, Advance, Compare<Begin, End>::check()>::exec();
        }
    };
}

template<uint64_t I>
struct foo
{
    void operator()()
    {
        std::cout << I * 2 << std::endl;
    }
};
 
int main()
{
    reaver::static_for<0, 256, foo>::exec();
}
