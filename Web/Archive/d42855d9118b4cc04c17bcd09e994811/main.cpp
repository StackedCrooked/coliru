#include <memory>
#include <iostream>

template < typename T, typename TDx = std::default_delete< T > >
class SexyHacks : private std::unique_ptr<T, TDx> {
public:
    
    struct SexyHacksReference {
        SexyHacks* toogood;
        typename std::unique_ptr<T, TDx>::pointer ptr;
           
        SexyHacksReference ( SexyHacks* hax )
        : toogood( hax ), ptr( toogood->get() ) {
               std::cout << "Yeah hack into me baby~ " << *ptr << std::endl; 
        }
        
        operator typename std::unique_ptr<T, TDx>::pointer* () {
            return &ptr;
        }
           
        ~SexyHacksReference () {
            std::cout << "Yeah you destruct me baby~ " << *ptr << std::endl;
            if ( toogood->get() != ptr ) {
                std::cout << "Mmmm just like that! " << *ptr << std::endl;
                toogood->reset( ptr );
            }
        }
    };
    
    SexyHacks ( typename std::unique_ptr<T, TDx>::pointer ohbby )
    : std::unique_ptr<T, TDx>( ohbby ) {
        
    }
    
    typename std::unique_ptr<T, TDx>::pointer get () {
        return std::unique_ptr<T, TDx>::get();   
    }
    
    void reset ( typename std::unique_ptr<T, TDx>::pointer ptr ) {
        std::unique_ptr<T, TDx>::reset( ptr ); 
    }
    
    SexyHacksReference operator& () {
        return SexyHacksReference( this );
    }
    
    T& operator* () {
        return std::unique_ptr<T, TDx>::operator*();
    }
    
    typename std::unique_ptr<T, TDx>::pointer operator-> () {
        return std::unique_ptr<T, TDx>::operator->();
    }
    
};


void FuckingCOM ( int** cominitializegogo ) {
    *cominitializegogo = new int(48);
}

int main ( int argc, char* argv[] ) {
    
    SexyHacks<int> meow( new int(24) );
    
    FuckingCOM ( &meow );
    
    std::cout << *meow << std::endl;
}