#include <cassert>

int main()
{
    assert(("Mon message d'erreur", 0));
    // Ou
    assert(0 && "Mon message d'erreur");
    return 0;
}