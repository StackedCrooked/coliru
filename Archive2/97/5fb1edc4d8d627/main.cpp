#include <iostream>

using namespace std;

void prime3_norev(const int& n)
{
   int m=n+1;
   int pi=0;
   bool *pFlag = new bool[m];
   for(int i=0; i<m; i++) pFlag[i] = false;
   int *p = new int[n/3];
   for(int i=0; i<n/3; i++) p[i] = 0;
   int pi0;
   #pragma omp parallel for schedule(static)
   for(int i=2;i<m;i++) {     
     if(!pFlag[i]) {
         #pragma omp atomic capture 
         { pi0 = pi; pi++; } 
         p[pi0] = i;
     }
     for(int j=0;(j<pi)&&(i*p[j]<m);j++){
       pFlag[i*p[j]]=true;
       if(i%p[j]==0) break;
     }
   }
   for(int i=0;i<pi;i++)
     cout<<p[i]<<' '; cout << endl;
}

int main() {

    prime3_norev(200);
}