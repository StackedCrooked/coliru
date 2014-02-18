#include <iostream>
#include <vector>
#include <memory>
using std::vector;
using std::cout;

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

// here is my custom widget class, which 'show' method is implemented, but 'close' method is not.
struct MyCustomWidget
{
    void show(){ std::cout << "Hey" << std::endl; }
    //void close(){ std::cout << "Bye"  << std::endl; }
};

// here is your custom widget class, which 'show' is not implemented but 'close' is .
struct YourCustomWidget
{
    //void show(){}
    void close(){ std::cout << "Bye" << std::endl;}
};

// common widget class, which may stored within any custom widgets.
struct Widget
{
    Widget() = default;

    template< typename CustomWidget >
    void add(CustomWidget cw)
    {
        auto child = make_unique< proxy<CustomWidget> >( std::move( cw ) );
        childs.push_back( std::move(child ) );
    }
    void show()
    {
        for(auto & e : childs)
            e->show();
    }
    void close()
    {
        for(auto& e : childs)
            e->close();
    }
private:
    struct proxy_base
    {
        virtual void show() = 0;
        virtual void close() = 0;
        virtual ~proxy_base(){}
    };

    template< typename CustomWidget >
    struct proxy : public proxy_base
    {
        explicit proxy(CustomWidget cw_) : cw( std::move(cw_ ) )
        {}
        
         template<typename T>
    auto show_helper(int) -> decltype( std::declval<T>().show(), void())
    {
        cw.show();
    }
    
    template<typename T>
    void show_helper(...) { }

        void show() override final
        {    // -------------->>>>>> (1)
            show_helper<CustomWidget>(0);
        }
        void close() override final
        {     /// ---------------->>>> (2)
            // call cw.close if cw has a 'close' method, otherwise nothing.
        }

        CustomWidget cw;
    };

std::vector< std::unique_ptr< proxy_base > >childs;
};

int main()
{
     Widget w;
     w.add( MyCustomWidget() );
     w.add( YourCustomWidget() );

     w.show();
     //.... a lot of code

     w.close();
}