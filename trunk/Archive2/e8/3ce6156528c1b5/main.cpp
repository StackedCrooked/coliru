#include <iostream>

using namespace std;

template<typename ContainerOrRange>
void display(ContainerOrRange const& data)
{
    for(auto& row : data)
        for(auto& cel : row)
            cout << cel << endl;
}

int main()
{
    std::string name[] = { "alex", "ben" };
    display(name);
}

