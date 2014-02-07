#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <iostream>
#include <string>

using namespace boost::multi_index;

namespace traits
{
    template <typename T> struct predefined_indexes;
}

template <typename T> using MultiIndex = multi_index_container<T, traits::predefined_indexes<T> >;

//////
// example from http://www.boost.org/doc/libs/1_55_0/libs/multi_index/example/fun_key.cpp
struct name_record
{
    name_record(std::string given_name_,std::string family_name_): given_name(given_name_),family_name(family_name_) {}
    std::string name() const { return family_name + " " + given_name; }
    std::string given_name, family_name;
};

std::string::size_type name_record_length(const name_record& r)
{
    return r.name().size();
}

namespace traits
{
    template <> struct predefined_indexes<name_record> :
        indexed_by<
            ordered_unique<
                BOOST_MULTI_INDEX_CONST_MEM_FUN(name_record,std::string,name)
            >,
            ordered_non_unique<
                global_fun<const name_record&,std::string::size_type,name_record_length>
            >
        >
    {
    };
}

int main()
{
    using MyTable = MultiIndex<name_record>;
    MyTable myTable;

    myTable.insert(name_record("Joe","Smith"));
    myTable.insert(name_record("Robert","Nightingale"));
    myTable.insert(name_record("Robert","Brown"));
    myTable.insert(name_record("Marc","Tuxedo"));

    /* list the names in myTable in phonebook order */
    std::cout << "Phonenook order\n" << "---------------" << std::endl;
    for(MyTable::iterator it=myTable.begin();it!=myTable.end();++it){
        std::cout << it->name() << std::endl;
    }

    /* list the names in myTable according to their length*/

    std::cout<<"\nLength order\n"
        <<  "------------"<<std::endl;
    for(nth_index<MyTable,1>::type::iterator it1=get<1>(myTable).begin();
            it1!=get<1>(myTable).end();++it1){
        std::cout<<it1->name()<<std::endl;
    }
}
