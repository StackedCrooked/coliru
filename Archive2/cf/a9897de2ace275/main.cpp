#include <iostream>
#include <string>
#include <vector>

#include <cstdio>

// include "SR.h"

class SR
{
    public:
    
      SR(int& dest)
       : m_ref_to_orig(dest),
         m_orig_value(dest)
      {
      }
      
      ~SR()
      {
          m_ref_to_orig = m_orig_value;
      }
    
    private:
       int& m_ref_to_orig;
       int  m_orig_value;
};

// include "SR.h"
 
int main()
{
    int j = 5;
    int a[] = {10, 15};
    {
        SR x(j), y(a[0]), z(a[1]);
 
        j = a[0];
        a[0] = a[1];
        a[1] = j;
 
        printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
    }
 
    printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
}