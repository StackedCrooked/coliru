#include <iostream>
#include <string>
#include <vector>

#include <time.h>       /* time_t, struct tm, time, localtime, strftime */
#include <locale.h> 
#include <stdio.h>
#include <assert.h>


using namespace std;

int main()
{
    short x = 66;
    
    short y = ((x << 1) & 0x7F) | (((x << 1) & 0x80) >> 7);

    assert(y == 5);
    
    cout << "X: " << x << "  Y: " << y << endl;
    
  
  
  return 0;
}
