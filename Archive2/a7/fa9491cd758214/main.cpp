#include <iostream>
#include <iterator>
#include <algorithm>

template<std::size_t N, std::size_t M>
void peak_finder_print(int (&arr)[N][M])
{
   ///using std::begin
   ///using std::end

   for(const auto& frstD : arr)/// begin works here
    {
       for(const auto& secndD : frstD)///error occurs here
         {
            std::cout <<secndD<<' ';
         }
         std::cout <<std::endl;
    }
}

int main ()
{
   int peakArr[5][5]
    {
     {1, 5, 9, 4, 2},{6, 0, 8, 2, 4},
     {12, 58, 0, 1, 8},{67, 8, 2, 5, 0},
     {3, 45, 6, 89, 0}
    };

   peak_finder_print (peakArr);//error

   return 0;
}
