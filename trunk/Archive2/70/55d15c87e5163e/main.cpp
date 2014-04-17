    #include <vector>
    #include <list>
    #include <boost/fusion/include/vector.hpp>
    #include <boost/fusion/mpl.hpp>
    #include <boost/mpl/transform.hpp>

    namespace container
    {
        struct vector {
            template<typename T> struct apply {
                typedef std::vector<T> type;
            };
        };
        struct list   {
            template <typename T> struct apply {
                typedef std::list<T> type;
            };
        };
    }

    template<typename ContainerMaker>
    struct wrap_into_container
    {
        template<typename T> struct apply {
            typedef typename ContainerMaker::template apply<T>::type type;
        };
    };

    

    int main()
    {
        namespace fusion = boost::fusion;
        namespace mpl = boost::mpl;
    
        typedef fusion::vector<int, float, int> vec_type;
        typedef mpl::transform< vec_type, wrap_into_container<container::vector> >::type wrapped_vec_type;
    
        wrapped_vec_type w;
        return size(w);

    }
    #include <vector>
    #include <list>
    #include <boost/fusion/include/vector.hpp>
    #include <boost/fusion/mpl.hpp>
    #include <boost/mpl/transform.hpp>

    namespace container
    {
        struct vector {
            template<typename T> struct apply {
                typedef std::vector<T> type;
            };
        };
        struct list   {
            template <typename T> struct apply {
                typedef std::list<T> type;
            };
        };
    }

    template<typename ContainerMaker>
    struct wrap_into_container
    {
        template<typename T> struct apply {
            typedef typename ContainerMaker::template apply<T>::type type;
        };
    };

    

    int main()
    {
        namespace fusion = boost::fusion;
        namespace mpl = boost::mpl;
    
        typedef fusion::vector<int, float, int> vec_type;
        typedef mpl::transform< vec_type, wrap_into_container<container::vector> >::type wrapped_vec_type;
    
        wrapped_vec_type w;
        return size(w);

    }
