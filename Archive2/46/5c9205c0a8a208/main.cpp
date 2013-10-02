#include <cstdio>
#include <cstdlib>

int L_R() {
  bool bLeft=true;

  struct xx {
    int iLeft : 16;
    int iRight : 16;
  } aa;

  (bLeft?aa.iLeft:aa.iRight)=5;
  return(aa.iLeft);
} 
int main()
{
 printf("%d", L_R() );
}
