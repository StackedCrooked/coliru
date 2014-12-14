#include <vector>
#include <boost/container/vector.hpp>

struct A
{
    // A n'est pas encore complet
    std::vector<A*> vect_ptr; // OK. Il n'y a aucun problème à instancier un pointeur vers un type incomplet
    A* ptr; // OK. Par contre, il ne faut pas appeler de delete dessus avant que le type(A) ne soit complet
    std::vector<A>* get(){ return nullptr;} // pas OK: A est incomplet
    std::vector<A>& a; // pas OK: A est incomplet.
    std::vector<A> b; // pas OK: A est incomplet!
    boost::container::vector<A> c; // OK. Pas de soucis. même si A est toujours incomplet. A doit cependant être complet avant la destruction de c
};

struct B; // forward declaration
std::vector<B> a; // pas OK: B est incomplet.

struct B
{
    void f()
    {
        std::vector<B> a; // OK: B est complet à l'intérieur d'une fonction membre
    }
    //...
/* B n'est toujours pas encore complet */ }; /* là c'est bon! */


std::vector<B> b; // OK: B est désormais complet.

int main()
{
}
