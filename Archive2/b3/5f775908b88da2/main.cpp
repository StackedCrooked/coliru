
int function(int a, int b, int c, int d)
{
    return (a << 24) | (b << 16) | (c << 8) | d;
}

int original(int u)
{
    int t = 0;
    switch (u) {
    case 1:
      t = t + function(0,2,1,0);   // 1
      break;
    case 2:
      t = t + function(0,2,1,0);  // 1
      t = t + function(1,2,2,0);  // 2
      break;
    case 3:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2
      t = t + function(0,3,3,1) ; // 3
      break;
    case 4:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2
      t = t + function(0,3,3,1) ; // 3
      t = t + function(1,3,4,1) ; // 4 
      t = t + function(3,2,4,0) ; // 6
      break;
    case 5:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2 
      t = t + function(0,3,3,1) ; // 3
      t = t + function(1,3,4,1) ; // 4
      t = t + function(2,3,5,1) ; // 5
      t = t + function(3,2,4,0) ; // 6
      t = t + function(4,2,5,0) ; // 7
      break;
    case 6:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2
      t = t + function(0,3,3,1) ; // 3
      t = t + function(1,3,4,1) ; // 4
      t = t + function(2,3,5,1) ; // 5
      t = t + function(3,2,4,0) ; // 6
      t = t + function(4,2,5,0) ; // 7
      t = t + function(3,3,6,1) ; // 8
      break;
    case 7:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2
      t = t + function(0,3,3,1) ; // 3
      t = t + function(1,3,4,1) ; // 4
      t = t + function(2,3,5,1) ; // 5
      t = t + function(3,2,4,0) ; // 6
      t = t + function(4,2,5,0) ; // 7
      t = t + function(3,3,6,1) ; // 8
      t = t + function(4,3,7,1) ; // 9
      t = t + function(6,2,7,0) ; // 11
      break;
    case 8:
      t = t + function(0,2,1,0) ; // 1
      t = t + function(1,2,2,0) ; // 2
      t = t + function(0,3,3,1) ; // 3
      t = t + function(1,3,4,1) ; // 4
      t = t + function(2,3,5,1) ; // 5
      t = t + function(3,2,4,0) ; // 6
      t = t + function(4,2,5,0) ; // 7
      t = t + function(3,3,6,1) ; // 8
      t = t + function(4,3,7,1) ; // 9
      t = t + function(5,3,8,1) ; // 10
      t = t + function(6,2,7,0) ; // 11
      t = t + function(7,2,8,0) ; // 12
      break;
    }
    return t;
}

int improved(int u)
{
    int t = 0;
    if(u >= 1) t = t + function(0,2,1,0) ; // 1
    if(u >= 2) t = t + function(1,2,2,0) ; // 2
    if(u >= 3) t = t + function(0,3,3,1) ; // 3
    if(u >= 4) t = t + function(1,3,4,1) ; // 4
    if(u >= 5) t = t + function(2,3,5,1) ; // 5
    if(u >= 4) t = t + function(3,2,4,0) ; // 6
    if(u >= 5) t = t + function(4,2,5,0) ; // 7
    if(u >= 6) t = t + function(3,3,6,1) ; // 8
    if(u >= 7) t = t + function(4,3,7,1) ; // 9
    if(u >= 8) t = t + function(5,3,8,1) ; // 10
    if(u >= 7) t = t + function(6,2,7,0) ; // 11
    if(u >= 8) t = t + function(7,2,8,0) ; // 12
    return t;
}

#include <iostream>

int main()
{
    std::cout << original(1) << '\n'; // 131328
    std::cout << original(2) << '\n'; // 17040128
    std::cout << original(3) << '\n'; // 17237505
    std::cout << original(4) << '\n'; // 84676098
    std::cout << original(5) << '\n'; // 185669635
    std::cout << original(6) << '\n'; // 236199428
    std::cout << original(7) << '\n'; // 404302853
    std::cout << original(8) << '\n'; // 605961222

    std::cout << improved(1) << '\n'; // 131328
    std::cout << improved(2) << '\n'; // 17040128
    std::cout << improved(3) << '\n'; // 17237505
    std::cout << improved(4) << '\n'; // 84676098
    std::cout << improved(5) << '\n'; // 185669635
    std::cout << improved(6) << '\n'; // 236199428
    std::cout << improved(7) << '\n'; // 404302853
    std::cout << improved(8) << '\n'; // 605961222
}
