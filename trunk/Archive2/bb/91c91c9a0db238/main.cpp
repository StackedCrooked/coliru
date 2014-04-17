    #include <vector>
    #include <list>
    #include <boost/fusion/include/vector.hpp>
    #include <boost/fusion/mpl.hpp>
    #include <boost/mpl/transform.hpp>

    namespace container
    {
        template <typename T> struct vector { typedef std::vector<T> type; };
        template <typename T> struct list   { typedef std::list<T> type; };
    }

    template<typename T, template <typename> class Container>
    struct wrap_into_container
    {
        typedef typename Container<T>::type type;
    };

    

    int main()
    {
        namespace fusion = boost::fusion;
        namespace mpl = boost::mpl;
    
        typedef fusion::vector<int, float, int> vec_type;
        typedef mpl::transform< vec_type, wrap_into_container<mpl::_1, container::vector> >::type wrapped_vec_type;
    
        wrapped_vec_type w;
        return w.size();

    }
