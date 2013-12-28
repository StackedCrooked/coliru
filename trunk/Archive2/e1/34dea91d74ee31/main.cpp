#include <iostream>
#include <functional>
#include <string>
#include <fstream>

struct foo
{
    template < typename CALLABLE, typename... ARGS >
    explicit foo( CALLABLE&& fn, ARGS&&... args ) :
        load_function( std::bind( fn, std::forward<ARGS>(args)... ) ) {}

    void do_load() { load_function() ; }

    private: std::function<void()> load_function ;
};

namespace sf
{
    struct texture
    {
        bool load_from_file( std::string /*path*/, int /*flags*/ )
        { return std::cout << "sf::texture::load_from_file(std::string,int)\n" ; }

        bool load_from_memory( const void* /*pointer*/, std::size_t /*nbytes*/, int /*hint*/ )
        { return std::cout << "sf::texture::load_from_memory(const void*,std::size_t,int)\n" ; }
        // ...
    };

    struct font
    {
        void load_from_file( std::string /*path*/ )
        { std::cout << "sf::font::load_from_file(std::string)\n" ; }

        void load_from_stream( std::istream& /*stm*/ )
        { std::cout << "sf::font::load_from_stream(std::istream&)\n" ; }

        bool load_from_font_cache( std::string /*name*/, int /*point_size*/ )
        { return std::cout << "sf::font::load_from_font_cache(std::string,int)\n" ; }
    };
}

void free_fun( sf::texture* tex, std::string tex_path,
                sf::font& fnt, std::istream& fnt_stm )
{
    std::cout << "free_fun( sf::texture*, std::string, sf::font&, std::istream& )\n\t" ;
    tex->load_from_file( tex_path, 0 ) ;
    std::cout << '\t' ;
    fnt.load_from_stream(fnt_stm) ;
}

int main()
{
    sf::texture t ;
    sf::font f ;
    sf::font* pointer = std::addressof(f) ;

    char buffer[128] {} ;
    std::string face_name = "Times Roman Italic" ;
    std::ifstream file( "myfont.fnt" ) ;


    foo loaders[] =
    {
        // pass object by value (load_from_file is called on copy of t)
        foo( &sf::texture::load_from_file, t, "some_texture.dat", 0 ),

        // pass object by wrapped reference
        foo( &sf::texture::load_from_memory, std::ref(t), buffer, 128, 7 ),

        // pass object by address
        foo( &sf::font::load_from_file, pointer, "myfont.fnt" ),

        // pass parameter by wrapped fererence
        foo( &sf::font::load_from_stream, std::ref(f), std::ref(file) ),

        // pass parameter by wrapped fererence to const
        foo( &sf::font::load_from_font_cache, std::ref(f), std::cref(face_name), 12 ),

        // pass free function
        foo( free_fun, std::addressof(t), "some_texture.dat",
                         std::ref(f), std::ref(file) ),

        // pass closure
        foo( [&] { f.load_from_font_cache( face_name, 20 ) ; } ),

        // pass bind expression
        foo( std::bind( &sf::texture::load_from_file, std::ref(t),
                                     "some_texture.dat", 0 ) ),

        // pass call wrapper
        foo( std::function< void(sf::font&,std::istream&) >(&sf::font::load_from_stream),
                         std::ref(f), std::ref(file) )

    };

    for( auto& rl : loaders ) rl.do_load() ;
}
