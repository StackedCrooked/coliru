#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

template < typename T > class id_helper ;
template < typename T > struct id_
{
    operator std::size_t() const { return value ; }
    const std::size_t value ;

    private:
        id_( std::size_t value ) : value(value) {}

    friend id_helper<T> ;
};

template < typename T > struct id_helper
{
    public:
        std::size_t id() const { return unique_id ; }
        static T* look_up( std::size_t id )
        {
            auto iter = object_map.find(id) ;
            return iter == object_map.end() ? nullptr : iter->second ;
        }

    private:
        id_helper() { object_map[unique_id] = static_cast<T*>(this) ; }
        ~id_helper() { object_map.erase(unique_id) ; }

        static std::unordered_map< std::size_t, T* > object_map ;
        static std::size_t next ;
        id_<T> unique_id{ ++next };

    friend T ;

};

template < typename T > std::unordered_map<std::size_t,T*> id_helper<T>::object_map ;
template < typename T > std::size_t id_helper<T>::next = 0 ;

class Vertex ;

struct Connector : id_helper<Connector>
{
    Connector( std::size_t vertex_from, std::size_t vertex_to ) : vertex_pair{vertex_from,vertex_to} {}
    const std::pair<std::size_t,std::size_t> vertex_pair;

    // ...

};

struct Vertex : id_helper<Vertex>
{
    ~Vertex() ;
    void add_connection( std::size_t connector_id ) ;
    void remove_connection( std::size_t connector_id ) ;
    std::size_t valency() const { return connection_set.size() ; }

    // ...

    private:
        std::unordered_set<std::size_t> connection_set;
        Vertex* adjacent( std::size_t connector_id ) const ;
        // ...
};

Vertex* Vertex::adjacent( std::size_t connector_id ) const
{
    const auto pc = Connector::look_up(connector_id) ;
    if(pc)
    {
        Vertex* v1 = look_up( pc->vertex_pair.first ) ;
        Vertex* v2 = look_up( pc->vertex_pair.second ) ;
        if( v1 != this && v2 != this ) throw std::logic_error("bad connector") ;
        return v1 == this ? v2 : v1 ;
    }
    return nullptr ;
}

void Vertex::add_connection( std::size_t connector_id )
{
    Vertex* adjacent_vertex = adjacent(connector_id) ;
    if(adjacent_vertex)
    {
        connection_set.insert(connector_id) ;
        adjacent_vertex->connection_set.insert(connector_id) ;
    }
}

void Vertex::remove_connection( std::size_t connector_id )
{
    connection_set.erase(connector_id) ;
    Vertex* adjacent_vertex = adjacent(connector_id) ;
    if(adjacent_vertex) adjacent_vertex->connection_set.erase(connector_id) ;
}

Vertex::~Vertex()
{
    for( auto connector_id : connection_set )
    {
        auto adjacent_vertex = adjacent(connector_id) ;
        if(adjacent_vertex) adjacent_vertex->connection_set.erase(connector_id) ;
    }
}

int main()
{
    Vertex v1, v2, v3 ;
    std::cout << v1.valency() << ' ' << v2.valency() << ' ' << v3.valency() << '\n' ;

    Connector c1( v1.id(), v2.id() ) ;
    v1.add_connection( c1.id() ) ;
    std::cout << v1.valency() << ' ' << v2.valency() << ' ' << v3.valency() << '\n' ;

    Connector c2( v1.id(), v3.id() ) ;
    Connector c3( v1.id(), v3.id() ) ;
    v3.add_connection( c2.id() ) ;
    v1.add_connection( c3.id() ) ;
    std::cout << v1.valency() << ' ' << v2.valency() << ' ' << v3.valency() << '\n' ;

    v1.remove_connection( c1.id() ) ;
    v3.remove_connection( c2.id() ) ;
    v3.remove_connection( c3.id() ) ;
    std::cout << v1.valency() << ' ' << v2.valency() << ' ' << v3.valency() << '\n' ;
}
