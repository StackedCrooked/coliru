#include <memory> // <-- For std::shared_ptr
#include <string>
#include <iostream>

class Widget;
typedef std::shared_ptr<Widget> WidgetPtr;

class Widget
{
    const std::string M_name;
    const std::string M_surname;
    const unsigned M_cat_count = 0;

    Widget( std::string name ) :
        M_name( std::move( name ) ) {}
        
    Widget( const Widget& ) = delete;
    Widget( Widget&& ) = default;
    
    // A new way to make Widgets!
    Widget( std::string name, int cat_count ) :
        M_name( std::move( name ) ),
        M_cat_count( cat_count ) {}
    
    // Another new way to make Widgets!
    Widget( std::string name, std::string surname, int cat_count ) :
        M_name( std::move( name ) ),
        M_surname( std::move( surname ) ),
        M_cat_count( cat_count ) {}

public:
    ~Widget() = default;

    // Get the widget's name
    const std::string& name() const { return M_name; }
    // Get the number of cats we have
    unsigned catCount() const { return M_cat_count; }
    // Get the surname
    const std::string& surname() const { return M_surname; }
    
    // (Rest of Widget omitted)...
    
    // Creates a widget with the given arguments and returns a pointer to it
    template <typename... Args>
    static WidgetPtr create( Args&&... args )
    {
        return WidgetPtr( new Widget( std::forward<Args>( args )... ) );
    }
};

int main( int, char** )
{
    std::string name = "John";
    auto ptr = Widget::create( name, "Smith", 99 );
    ptr = Widget::create( std::move( *ptr ) );
    std::cout << "Expected name: " << name << std::endl;
    std::cout << ptr->name() << std::endl;
    std::cout << ptr->surname() << std::endl;
    std::cout << ptr->catCount() << std::endl;
    
    return 0;
}
