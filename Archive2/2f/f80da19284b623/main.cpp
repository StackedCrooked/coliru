#include <iostream>
#include <map>
#include <boost/iterator/transform_iterator.hpp>
#include <type_traits>

struct data_class
{
    struct DataNode { /* ... */ };

    using iterator = std::multimap< /*const*/ std::string, DataNode* >::iterator ;
    using citerator = std::multimap< /*const*/ std::string, DataNode* >::const_iterator ;

    iterator begin() { return children_.begin() ; }
    iterator end() { return children_.end() ; }

    struct add_const
    {
        std::pair< const std::string, const DataNode* > operator()
                ( const std::pair< const std::string, DataNode* >& p ) const { return p ; }
    };
    using const_iterator = boost::transform_iterator< add_const, citerator > ;

    const_iterator begin() const
    { return boost::make_transform_iterator( children_.cbegin(), add_const() ) ; }

    const_iterator end() const
    { return boost::make_transform_iterator( children_.cbegin(), add_const() ) ; }

    private: std::multimap< /*const*/ std::string, DataNode* > children_ ;
};

int main()
{
    data_class dc ;
    static_assert( std::is_same< decltype( dc.begin()->second ), data_class::DataNode* >::value, "****" ) ;

    const data_class& cdc = dc ;
    static_assert( std::is_same< decltype( cdc.begin()->second ), const data_class::DataNode* >::value, "****" ) ;
}
