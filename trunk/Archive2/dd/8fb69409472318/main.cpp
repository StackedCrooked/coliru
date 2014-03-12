#include <iostream>
#include <vector>
using namespace std;

class base{};
class a : public base{};

void Funktion(base& variable)
{
    cout << "base" << endl;
}
void Funktion(a& variable)
{
    cout << "a" << endl;
}

int main()
{
    vector<base*> list;
    list.push_back(new a());
    list.push_back(new base());

    for (const auto& e : list)
    {
        Function(*e);
    }
}