#include <iostream>
#include <iomanip>
long double Skill( const long long& Kills,
               const long long& Deaths,
               const long long& Assists,
               const long long& Revived,
               const long long& Revives,
               const long long& Heals,
               const long long& VKills)
{
    long double Ass = Assists * 0.75;
    long double KDA = Kills+Ass / Deaths;
    return KDA;
}

int main()
{
    std::cout << Skill( 1000, 100, 25, 250, 250, 2500, 75 );
}