#include <iostream>
#include <string>
#include <vector>

namespace client
{
    template<
        typename T
    >
    struct sum_traits;
    
    template<>
    struct sum_traits<char>
    {
        typedef 
        int result_type;
        
        static char 
        zero()
        {
            return 0;
        }
    };
    
    template<>
    struct sum_traits<int>
    {
        typedef 
        long result_type;
        
        static int 
        zero()
        {
            return 0;
        }
    };
    
    template<
        typename T,
        typename
        ST = sum_traits<T>
    >
    struct sum_helper
    {
        typedef ST traits_type;
        
        typedef
        typename 
        traits_type::result_type result_type;
        
        static
        result_type sum(
            const T* beg,
            const T* end
        )
        {
            result_type acc =
                traits_type::zero();
            while(beg != end)
            {
                acc += *beg++;
            }
            
            return acc;
        }
    };
    
    template<
        typename T
    >
    typename
    sum_traits<T>::result_type
    sum(
        const T* begin, 
        const T* end
    )
    {
        return sum_helper<T>::sum(
            begin,
            end
        );
    }
    
    template<
        typename T,
        typename TR
    >
    typename
    TR::result_type
    sum(
        const T* begin, 
        const T* end
    )
    {
        std::cout 
            << 2 
            << "\n";
            
        return 
            sum_helper<T, TR>::sum(
                begin,
                end
            );
    }
}

int main()
{
    const char s[] = "abcdefgh";
    std::cout
        << "sum: "
        << client::sum(s, s + sizeof(s))
        << std::endl;
        
    const int int_ar[] = {1,2,3,4,5,6,7,8};
    std::cout
        << "sum ints: "
        << client::sum<
                int, 
                client::sum_traits<int>
            >(
                int_ar, 
                int_ar + 
                sizeof(int_ar)/sizeof(int)
            )
        << std::endl;        
}
