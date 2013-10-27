#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <deque>
#include <algorithm>
#include <iterator>
#include <iostream>

struct mesh { void load_obj( const std::string& ) { /* ... */ } ; /* ... */ } ;

struct resource_manager
{
    std::shared_ptr<mesh> load( const std::string& location /* , ... */ )
    {
        if( auto p = get(location) ) return p ; // already loaded

        try
        {
            auto sh_ptr = std::make_shared<mesh>( /* ... */ ) ;
            sh_ptr->load_obj(location) ;
            if( meshes.emplace( location, sh_ptr ).second )
            {
                cache(sh_ptr) ;
                return sh_ptr ;
            }
        }
        catch( const std::exception& ) {}
        return nullptr ; // failed to create/load/emplace
    }

    std::shared_ptr<mesh> get( const std::string& location )
    {
        auto iter = meshes.find(location) ;

        if( iter != meshes.end() )
        {
            // try to get a shared_ptr from the weak_ptr
            if( auto sh_ptr = iter->second.lock() )
            {
                cache(sh_ptr) ;
                return sh_ptr ; // ok, not expired
            }
            else meshes.erase(iter) ; // expired, remove from the map
        }

        return nullptr ; // not found
    }

    private:
         std::map< std::string, std::weak_ptr<mesh> > meshes ;
         static constexpr std::size_t cache_size = 10 ;
         std::deque< std::shared_ptr<mesh> > mru_cache ;

         void cache( std::shared_ptr<mesh>& p )
         {
             auto iter = std::find( std::begin(mru_cache), std::end(mru_cache), p ) ;
             if( iter != std::end(mru_cache) ) std::swap( mru_cache.back(), *iter ) ;
             else
             {
                 mru_cache.push_back(p) ;
                 if( mru_cache.size() > cache_size ) mru_cache.pop_front() ;
             }
         }

     public:
         void debug_dump( std::ostream& stm = std::cout ) const
         {
              stm << "-----------------------------------------\nweak pointers:\n" ;
              for( const auto& pair : meshes )
              {
                  stm << "    " << pair.first << " - " ;

                  if( auto p = pair.second.lock() )
                  {
                      stm << p.get() << "  use count (external): " ;
                      if( std::find( std::begin(mru_cache),
                                      std::end(mru_cache), p ) != std::end(mru_cache) )
                           std::cout << p.use_count() - 2 << " (cached)\n" ;
                      else std::cout << p.use_count() - 1 << '\n' ;
                  }

                  else stm << "expired\n" ;
              }

              stm << "cached:\n" ;
              for( const auto& p : mru_cache ) stm << "    " << p.get() << '\n' ;
         }
};

int main()
{
     resource_manager mgr ;

     constexpr int NKEYS = 25 ;
     std::string keys[NKEYS] ;
     for( int i = 0 ; i < NKEYS ; ++i ) keys[i] = std::string( 3, 'A' + i ) ;
     std::deque< std::shared_ptr<mesh> > seq ;

     {
         for( const auto& str : keys ) seq.push_back( mgr.load(str) ) ;
         mgr.debug_dump() ;
     }

     {
         for( std::size_t i = 0 ; i < seq.size() ; i += 2 ) seq[i] = nullptr ;
         mgr.debug_dump() ;
     }

     {
         std::shared_ptr<mesh> p[5] ;
         for( int i = 0 ; i < 5 ; ++i ) p[i] = mgr.get( keys[ i*2 + 1 ] ) ;
         mgr.debug_dump() ;
     }

     {
         seq.clear() ;
         mgr.debug_dump() ;
     }

     {
         for( const auto& str : keys )
             if( auto p = mgr.get(str) ) seq.push_back(p) ;
         mgr.debug_dump() ;
     }
}
