#include <iostream>

#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
    #include <boost/mpl/front.hpp>
    #include <boost/mpl/push_back.hpp>
    #include <boost/mpl/size.hpp>
    #include <boost/mpl/find.hpp>
    #include <boost/mpl/insert.hpp>
    #include <boost/mpl/erase_key.hpp>
    #include <boost/mpl/placeholders.hpp>
    #include <tuple>
    #include <boost/mpl/fold.hpp>
    namespace mpl = boost::mpl;


    int main()
    {

            using unique_edge_types =
            typename mpl::fold<
            mpl::vector<int,double,float,float,float>
            , mpl::set0<>
            , mpl::insert<mpl::placeholders::_1, mpl::placeholders::_2> /** _1 = State = set<...>, _2 element of NodeTypes*/
            >::type;

        using iter =  typename boost::mpl::find< unique_edge_types , int>::type;
        std::cout << iter::pos::value << std::endl; 
    }