#include <vector>
#include <array>
#include <cstdio>

int main()
{
     std::vector<std::array<double, 2>> v(2);

    v[0][0] = 1.0;

    v[0][1] = 2.0;

    v[1][0] = 3.0;

    v[1][1] = 4.0;

   for( const auto &arr : v )
   {
     for( const auto &data : arr )
     {
        printf( "%f, ", data ) ;
     }
   }

}