#include <iostream>
using namespace std;

void print_primes(int n)
     {
          int primes[n+1],start=2,i=0;

          /* Initialization , if primes[i]=1 it means
             i is prime and if 0 it means i is composite,
             initially assume all are prime */
          for(i=1;i<=n;i++)primes[i]=1;

          /*Seives method*/
          while(start*start<=n)
          {
               for(i=start*start;i<=n;i=i=i+start)
                  primes[i]=0;
               for(i=start+1;i<=n;i++)
               {
                   if(primes[i])
                      break;
               }
               start=i;
          }

          /*Just printing all primes from 1 to n
            if primes[i]=1 it means i is prime 
            and if 0 it means i is composite*/
          for(i=2;i<=n;i++)
          {
              if(primes[i])
                cout<<i<<endl;
          }
     }
    int main()
    {
        /*printing primes till 1000000*/
        print_primes(1000000);
    }
