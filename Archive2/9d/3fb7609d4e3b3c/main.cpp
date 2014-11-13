#include <vector>
#include <cstdio>
#include <string>
#include <iostream>

class PilotClass
{
    public :
    static std::string GetTableName() { return "Pilot"+ GetName(); }
    static std::string GetName() { return ""; }
};

class AI : public PilotClass
{
    public :
    static std::string GetName() { return "AI"; }
};

class NavMesh : public A
{
    public :
    static std::string GetName() { return "NavMesh"; }
};

int main()
{
    std::cout << AI::GetTableName();
    std::cout << NavMesh::GetTableName();
    
    return 0;
};