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
        using std::cout;
        using std::endl;
        cout << "Proba_t.a : " << pt.a << endl <<
            "Proba_t.b : " << pt.b << endl;
    }
}


int main()
{
    simple::Proba_t ppt = { 5,4.4 };

    // Nota bene :
    // Typical call this functions is similar <simple::function( ppt );>
    function( ppt );

    return EXIT_SUCCESS;
}
