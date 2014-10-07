#include <iostream>
#include <type_traits>
#include <bitset>

#include "boost/mpl/list.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/pop_front.hpp"

enum alarm_enum {
        selfA    , autoA    ,
		selfB  , autoB  ,
		selfC   , autoC, 
    	manA  ,		manB,		manC
    };



template <alarm_enum category, alarm_enum Alarm> struct alarm_struct {
    const static std::bitset<32> value;
};
template <alarm_enum category, alarm_enum alarm>
	const std::bitset<32> alarm_struct<category, alarm>::value = ((1 << category) | (1 << alarm));

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




template<size_t index, typename list, typename outer_element>
struct inner_list
{
    typedef inner_list<index-1, typename boost::mpl::pop_front<list>::type, outer_element > sub_list;
	typedef typename boost::mpl::front<list>::type inner_element;
    
    typedef typename alarm_struct<inner_element::value, outer_element::value>::value element;
};

template<typename list, typename outer_element>
struct inner_list<0, list, outer_element> 
{};


template<size_t index, typename listA, typename listB>
struct outer_list
{
    typedef typename boost::mpl::front<listA>::type element;
    using inner_size = typename boost::mpl::size<listB>::type;
    typedef inner_list<inner_size::value, listB, element> inner;
    typedef outer_list<index-1, typename boost::mpl::pop_front<listA>::type, listB > sub_list;
};

template<typename listA, typename listB>
struct outer_list<0, listA, listB> 
{};



using manu_size = typename boost::mpl::size<manual_reset_alarms>::type;
outer_list <manu_size::value, manual_reset_alarms, self_and_auto_reset_alarms> a;



int main()
{
}
