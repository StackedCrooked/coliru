#include <iostream>
int calc (int znachenie)
{
return znachenie - 1;
}
int main()
{
 std::cout << "Calc = " << calc(25) << std::endl;
 int d = calc(25);

if (d > 25)
{
      std::cout <<  "Calc bolshe 25 vychtem 1" << std::endl; // если кальк больше 25, то выведет сообщение
      d = d - 1;
}
if (d < 25)
{
     std::cout <<  "Calc menshe 25 pribavym 1" << std::endl;// если кальк меньше 25, то выведет сообщение
     d = d + 1;
}
if (d == 25)
 {
    std::cout <<  "Calc ravno 25" << std::endl; // если кальк равно 25, то выведет сообщение
 }
else
 {
     std::cout <<  "Calc ne ravno 25" << std::endl; // если кальк не равно 25, то выведет сообщение
 }
     return 0;
}
