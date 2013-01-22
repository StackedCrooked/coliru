#include <iostream>

namespace simple
{
    struct Proba_t
    {
        int a;
        double b;
    };

    inline void function( Proba_t pt )
    {
        std::cout << "Proba_t.a : " << pt.a <<
            "Probat_t.b : " << pt.b << std::endl;
    }
}


int main()
{
    simple::Proba_t ppt;
    ppt.a = 5;
    ppt.b = 4.4;

    function( ppt );

    return EXIT_SUCCESS;
}
