#include <iostream>
#include <string>

struct faith_t
{
    std::string denomination() const { return denomination_ ; }
    std::string sabbath() const { return sabbath_ ; }
    // ... other faith related stuff

    faith_t( std::string denomination, std::string sabbath = "" )
        : denomination_(denomination), sabbath_(sabbath) {}

    private:
        std::string denomination_ ;
        std::string sabbath_ ;
        // ...
};

struct person
{
    std::string name() const { return name_ ; }
    int age() const { return age_ ; }
    const person* best_friend() const { return best_friend_ ; }
    void befriend( const person* p ) { best_friend_ = p ; }
    faith_t faith() const { return faith_ ; }
    void faith( faith_t new_faith, std::string new_name = "" )
    { faith_ = new_faith ; if( !new_name.empty() ) name_ = new_name ; }

    person( std::string name, int age, const faith_t& faith, person* best_friend = nullptr )
        : name_(name), age_(age), faith_(faith), best_friend_(best_friend) {}

    private:
        std::string name_ ;
        int age_ ;
        faith_t faith_ ;
        const person* best_friend_ = nullptr ;
};

std::ostream& operator<< ( std::ostream& stm, const person& per )
{
    stm << per.name() << ' ' << per.age() << " years (" << per.faith().denomination() << ')' ;
    const auto f = per.best_friend() ;
    if(f) stm << "  best friend: " << f->name() << " (" << f->faith().denomination() << ')' ;
    return stm ;
}

int main ()
{
    person mary( "Mary", 28, { "wasp", "Sunday" } ) ;
    person deepika( "Deepika", 23, { "hindu" }, &mary ) ;
    mary.befriend(&deepika) ;
    std::cout << mary << '\n' << deepika << "\n-------------\n" ;

    mary.faith( { "agnostic" }, "Orchid" ) ;
    std::cout << mary << '\n' << deepika << "\n-------------\n" ;

    deepika.faith( { "muslim", "Friday" }, "Fatima" ) ;
    std::cout << mary << '\n' << deepika << "\n-------------\n" ;
}
