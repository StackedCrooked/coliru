#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>

template < typename COMPONENT > struct attribute_collection
{
    using POINTER = std::shared_ptr<COMPONENT> ;
    using ID = int ;
    std::unordered_map< ID, POINTER > attributes ;

    void add( ID id, const POINTER& c ) { attributes.emplace( id, c ); }

    POINTER get( ID id ) const
    {
        const auto iter = attributes.find(id) ;
        return iter != attributes.end() ? iter->second : nullptr ;
    }

    std::vector<POINTER> all() const
    {
        std::vector<POINTER> result ;
        for( const auto pair : attributes ) result.push_back(pair.second) ;
        return result ;
    }
};

template < typename... > struct components_have {} ;
template < typename T > struct components_have<T> : protected attribute_collection<T> {} ;
template < typename FIRST, typename... REST >
struct components_have<FIRST,REST...> : protected attribute_collection<FIRST>, protected components_have<REST...> {} ;

struct position { /* ... */ };
struct velocity { /* ... */ };
struct orientation { /* ... */ };

struct entity : components_have<position,velocity,orientation>
{
    template < typename COMPONENT >
    void add_component( int id, const std::shared_ptr<COMPONENT>& c )
    { attribute_collection<COMPONENT>::add(id,c) ; }

    template < typename COMPONENT > std::shared_ptr<COMPONENT> get( int id ) const
    { return attribute_collection<COMPONENT>::get(id) ; }

    template < typename COMPONENT > std::vector< std::shared_ptr<COMPONENT> > all() const
    { return attribute_collection<COMPONENT>::all() ; }
};

int main()
{
   entity e ;

   e.add_component( 99, std::make_shared<position>() ) ;
   e.add_component( 56, std::make_shared<position>() ) ;
   e.add_component( 234, std::make_shared<position>() ) ;

   e.add_component( 22, std::make_shared<velocity>() ) ;
   e.add_component( 38, std::make_shared<velocity>() ) ;

   auto v = e.all<position>() ;

   std::cout << v.size() << '\n' // 3
             << e.all<velocity>().size() << '\n' // 2
             << std::boolalpha << ( e.get<position>(56) != nullptr ) << '\n' // true
             << ( e.get<velocity>(45) != nullptr ) << '\n' ; // false
}
