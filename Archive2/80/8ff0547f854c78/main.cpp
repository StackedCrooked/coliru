#include <type_traits>
#include <iostream>
#include <vector>
#include <list>

namespace tags {

    struct ordinary_tag{}; 
    struct special_tag {}; 
    struct extra_special_tag {};

    struct ordinary_collection_tag {}; 
    struct special_collection_tag {}; 

    template<typename Type>
    struct tag 
    {
        typedef void type; 
    }; 

}

class concrete_one {}; 
class concrete_two {}; 

namespace implementation {

    template<typename Result, typename Tag>
    struct algorithm {};

    template<typename Result> 
    struct algorithm<Result, tags::ordinary_tag>
    {
        static Result apply(concrete_one const & a1, concrete_two const & a2)
        {
            Result r; 

            std::cout << "ordinary" << std::endl;
            // Modify r using a1, a2. 

            return r; 
        } 

        // Commutative algorithm. 
        static Result apply(concrete_two const & a1, concrete_one const & a2)
        {
            std::cout << "ordinary" << std::endl;
            return apply(a2, a1); 
        }
    };

    template<typename Result> 
    struct algorithm<Result, tags::special_tag>
    {
        static Result apply(concrete_one const & a1, concrete_two const & a2)
        {
            Result r; 

            std::cout << "special" << std::endl;
            // Modify r using a1, a2.

            return r; 
        } 
    };

    template<typename Result>
    struct algorithm<Result, tags::ordinary_collection_tag>
    {
        static Result apply(concrete_one const & a1, concrete_two const & a2)
        {
            Result r; 

            std::cout << "ordinary collection" << std::endl;

            // Modify r using a1, a2.

            return r; 
        } 
    };

    template<typename Result>
    struct algorithm<Result, tags::special_collection_tag>
    {
        static Result apply(concrete_one const & a1, concrete_two const & a2)
        {
            Result r; 

            // Modify r using a1, a2.

            return r; 
        } 
    };

}

struct first_type {}; 

namespace tags {
    // Make first_type behave as ordinary type.
    template<>
    struct tag<first_type>
    {
        typedef ordinary_tag type; 
    };
}

struct second_type {};  

namespace tags {
    // Make second_type behave as a special type.
    template<>
    struct tag<second_type>
    {
        typedef special_tag type; 
    };
}

template<typename Result, typename ... Arguments>
Result algorithm(Arguments ... args)
{
    // Dispatch to the appropriate algorithm based on the result tag
    // and overload within the algorithm structure for the variadic arguments
    return implementation::algorithm<Result, typename tags::tag<Result>::type>::apply(args ...);
}


// Works but doesn't see that OrdinaryType should be tagged with ordinary_tag, 
// std::list<first_type> and std::vector<second_type> are both tagged ordinary_collection_tag. 
//namespace tags 
//{
    //template 
    //<
        //typename OrdinaryType,  
        //template <typename, typename> class Container, 
        //template <typename> class Allocator 
    //>
    //struct tag
    //<
        //Container<OrdinaryType, Allocator<OrdinaryType>>
    //> 
    //{
        //typedef ordinary_collection_tag type; 
    //};
//}; 

namespace tags 
{
    // An attempt to tag all Containers with Allocator of ordinary tagged types using ordinary_collection_tag.
    template 
    <
        typename OrdinaryType,  
        template <typename, typename> class Container, 
        template <typename> class Allocator 
    >
    struct tag
    <
        typename std::enable_if 
        <
            std::is_same<typename tags::tag<OrdinaryType>::type, tags::ordinary_tag>::value, // true if OrdinaryType is tagged with ordinary_tag
            Container<OrdinaryType, Allocator<OrdinaryType>> // Use this as the T argument of enable_if
        >::type // in enable_if specialized for "true" :: typename T type; 
    > 
    {
        typedef ordinary_collection_tag type; 
    };
}

int main()
{
    concrete_one c1; 
    concrete_two c2; 

    first_type f1 = algorithm<first_type>(c1, c2); 

    second_type f2 = algorithm<second_type>(c1, c2); 

    typedef std::list<first_type> first_type_list; 
    typedef std::vector<first_type> first_type_vector; 
    //typedef std::vector<second_type> second_type_vector; 

    first_type_list fl = algorithm<first_type_list>(c1, c2); 
    first_type_vector fv = algorithm<first_type_vector>(c1, c2); 

    // Uncomment when the tag specialization without enable_if is uncommented. 
    //second_type_vector sv = algorithm<second_type_vector>(c1, c2);

    return 0;
}

