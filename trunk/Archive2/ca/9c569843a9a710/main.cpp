#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
   int maxOf(list<unsigned> l)
{
if (l == NULL) return ERR;
int max = l->content; // valeur en première place
while (l->succ != NULL)
{
l = l->succ; // itération de la liste
if (l->content > max) max = l->contenu;
}
return max;
}
}
