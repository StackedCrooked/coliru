#include <iostream>
#include <vector>
#include <utility>

struct object
{
    virtual ~object() = default ;
    virtual void paint() const = 0 ;
    // ...
    int n = 0 ;
};

struct object_A : object
{
    virtual void paint() const override { std::cout << "object_A::paint (" << this << ")\n" ; }
    // ...
};

struct object_B : object
{
    virtual void paint() const override { std::cout << "object_B::paint (" << this << ")\n" ; }
    // ...
};

struct board
{
    void paint_all_objects() const { for_each_object( []( const object& obj ) { obj.paint() ; } ) ; }
    void update_all_objects() { for_each_object( []( object& obj ) { ++obj.n ; } ) ; }

    std::vector<object_A> some_objects{4};
    std::vector<object_B> more_objects{3};

    template < typename FN > void for_each_object( FN&& fn )
    {
        for( auto& a : some_objects ) std::forward<FN>(fn)(a) ;
        for( auto& b : more_objects ) std::forward<FN>(fn)(b) ;
    }

    template < typename FN > void for_each_object( FN&& fn ) const
    {
        for( const auto& a : some_objects ) std::forward<FN>(fn)(a) ;
        for( const auto& b : more_objects ) std::forward<FN>(fn)(b) ;
    }
};

int main()
{
    board b ;
    b.update_all_objects() ;
    b.paint_all_objects() ;
}
