#include <iostream>
#include <type_traits>
#include <bitset>

#include "boost/mpl/list.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/insert_range.hpp"

enum alarm_enum {
        selfA,
        autoA,
    	selfB  , 
        autoB  ,
		selfC   , 
        autoC,
    	manA,
        manB,
        manC
    };



template <alarm_enum category, alarm_enum alarm> struct alarm_struct {
    const static uint32_t value = ((1 << category) | (1 << alarm));
};
//template <alarm_enum category, alarm_enum alarm>
//	const uint32_t alarm_struct<category, alarm>::value = ((1 << category) | (1 << alarm));

typedef boost::mpl::list<
    	std::integral_constant<alarm_enum, selfA>    ,
		std::integral_constant<alarm_enum, autoA>    ,
		std::integral_constant<alarm_enum, selfB>  ,
		std::integral_constant<alarm_enum, autoB>  ,
		std::integral_constant<alarm_enum, selfC>   ,
		std::integral_constant<alarm_enum, autoC>
> self_and_auto_reset_alarms;

typedef boost::mpl::list<
    	std::integral_constant<alarm_enum, manA>  ,
		std::integral_constant<alarm_enum, manB>,
		std::integral_constant<alarm_enum, manC>
> manual_reset_alarms;


template<typename T>
using Unpack = typename T::type;

//template<size_t index, typename list, typename outer_element>
//struct inner_list
template<size_t index, typename list, typename outer_element>
struct inner_list
    : boost::mpl::push_front<inner_list<index-1, typename boost::mpl::pop_front<list>::type, outer_element >
	, std::integral_constant<uint32_t, alarm_struct<Unpack<boost::mpl::front<list>>::value, outer_element::value>::value>>::type

{
//    typedef inner_list<index-1, typename boost::mpl::pop_front<list>::type, outer_element > sub_list;
//	typedef typename boost::mpl::front<list>::type inner_element;
//    const static uint32_t element = alarm_struct<inner_element::value, outer_element::value>::value;

//    boost::mpl::push_front<sub_list, std::integral_constant<uint32_t, element>>::type
};

template<typename list, typename outer_element>
struct inner_list<0, list, outer_element>: boost::mpl::list<>
{};


template<size_t index, typename listA, typename listB>
struct outer_list: boost::mpl::insert_range<
    outer_list<index-1, typename boost::mpl::pop_front<listA>::type, listB >,
    typename boost::mpl::begin<outer_list<index-1, typename boost::mpl::pop_front<listA>::type, listB >>::type,
    inner_list<Unpack<boost::mpl::size<listB>>::value, listB, Unpack<boost::mpl::front<listA>>>
    >::type
{
private:
//    typedef typename boost::mpl::front<listA>::type element;
//    using inner_size = typename boost::mpl::size<listB>::type;
//    typedef outer_list<index-1, typename boost::mpl::pop_front<listA>::type, listB > sub_list;
public:
//    typedef inner_list<inner_size::value, listB, element> result;
//    typedef inner_list<Unpack<boost::mpl::size<listB>>::value, listB, Unpack<boost::mpl::front<listA>>> result;

};

template<typename listA, typename listB>
struct outer_list<0, listA, listB>: boost::mpl::list<>
{};



using manu_size = typename boost::mpl::size<manual_reset_alarms>::type;
typedef outer_list <manu_size::value, manual_reset_alarms, self_and_auto_reset_alarms> my_list;

int main()
{
    std::cout << boost::mpl::front<my_list>::type::value << std::endl;
    std::cout << Unpack<boost::mpl::size<my_list>>::value;
}
