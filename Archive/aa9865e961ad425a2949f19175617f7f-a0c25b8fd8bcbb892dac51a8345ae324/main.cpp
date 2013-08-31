#include<iostream>
#include <typeinfo>
#include<boost/mpl/map.hpp>
#include<boost/mpl/at.hpp>
#include<boost/mpl/insert.hpp>
#include<boost/mpl/erase_key.hpp>
#include<boost/mpl/pair.hpp>
#include<boost/mpl/int.hpp>
#include<boost/mpl/plus.hpp>
#include<boost/mpl/equal.hpp>
#include<boost/mpl/size.hpp>
#include<boost/mpl/front.hpp>

namespace mpl = boost::mpl;
using mpl::int_;

using std::cout;
using std::endl;
using std::is_same;

int main(int argc, char *argv[])
{

    typedef int key;

    typedef mpl::map<mpl::pair<key, int_<1>>> Map;
    typedef mpl::map<mpl::pair<key, int_<2>>> Map2;

    typedef mpl::insert<
    				mpl::erase_key<Map, key>::type, 
					mpl::pair<key, mpl::plus<
											int_<1>, 
											mpl::at<Map, key>::type
									>::type
					>::type
			>::type Map3;
	
	using mpl::_1;
	using mpl::_2;
	
	typedef mpl::equal<_1,_2,is_same<_1,_2>> predicate;

    cout << "equal? " << mpl::equal<Map2,Map3,predicate>::type::value << endl;
    cout << "size? " << mpl::size<Map3>::value << endl;
    cout << "key type at front? " << typeid(mpl::front<Map3>::type::first).name() << endl;
    cout << "value type at front? " << mpl::front<Map3>::type::second::value << endl;

    cout << "expected size? " << mpl::size<Map2>::value << endl;
    cout << "expected key type at front? " << typeid(mpl::front<Map2>::type::first).name() << endl;
    cout << "expected value type at front? " << mpl::front<Map2>::type::second::value << endl;

    return 0;
}