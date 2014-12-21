#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>

template < typename COMPONENT > struct component_collection
{
    using POINTER = std::shared_ptr<COMPONENT> ;
    using ID = int ;
    std::unordered_multimap< ID, POINTER > components ;

    void add( ID id, const POINTER& c ) { components.emplace( id, c ); }

    std::vector<POINTER> get( ID id ) const
    {
        std::vector<POINTER> result ;
        auto pair = components.equal_range(id) ;
        for( auto iter = pair.first ; iter != pair.second ; ++iter ) result.push_back(iter->second) ;
        return result ;
    }
};

template < typename... > struct components_have {} ;
template < typename T > struct components_have<T> : protected component_collection<T> {} ;
template < typename FIRST, typename... REST >
struct components_have<FIRST,REST...> : protected component_collection<FIRST>, protected components_have<REST...> {} ;

struct position { /* ... */ };
struct velocity { /* ... */ };
struct orientation { /* ... */ };

struct entity : components_have<position,velocity,orientation>
{
    template < typename COMPONENT >
    void add_component( int id, const std::shared_ptr<COMPONENT>& c )
    { component_collection<COMPONENT>::add(id,c) ; }

    template < typename COMPONENT >
    std::vector< std::shared_ptr<COMPONENT> > get_components( int id ) const
    { return component_collection<COMPONENT>::get(id) ; }
};

int main()
{
   entity e ;

   e.add_component( 99, std::make_shared<position>() ) ;
   e.add_component( 4, std::make_shared<position>() ) ;
   e.add_component( 99, std::make_shared<position>() ) ;
   e.add_component( 7, std::make_shared<position>() ) ;
   e.add_component( 99, std::make_shared<position>() ) ;
   e.add_component( 99, std::make_shared<position>() ) ;

   e.add_component( 22, std::make_shared<velocity>() ) ;
   e.add_component( 38, std::make_shared<velocity>() ) ;
   e.add_component( 22, std::make_shared<velocity>() ) ;

   auto v = e.get_components<position>(99) ;
   std::cout << v.size() << '\n' ; // 4
   std::cout << e.get_components<velocity>(22).size() << '\n' ; // 2
}
