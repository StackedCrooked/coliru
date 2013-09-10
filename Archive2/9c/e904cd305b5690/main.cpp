#include<vector>
#include<iostream>

using namespace std;

const int n          = 10000;
const int baseLength = 100;

int f(int ii) {
  return ii;
}

int recursiveSumBody(int * begin, int * end){

  size_t length  = end - begin;
  size_t mid     = length/2;
  int    sum     = 0;


  if ( length < baseLength ) {
    for(size_t ii = 1; ii < length; ii++ ){
        begin[ii] += begin[ii-1];
    }
  } else {
#pragma omp task shared(sum)
    {
      sum = recursiveSumBody(begin    ,begin+mid);
    }
#pragma omp task
    {
      recursiveSumBody(begin+mid,end      );
    }
#pragma omp taskwait

#pragma omp parallel for
    for(size_t ii = mid; ii < length; ii++) {
      begin[ii] += sum;
    }

  }
  return begin[length-1];
}

void recursiveSum(int * begin, int * end){

#pragma omp single
  {
    recursiveSumBody(begin,end);
  }    
}


int main() {

  vector<int> a(n,0);

#pragma omp parallel
  {
    #pragma omp for
    for(int ii=0; ii < n; ii++) {          
      a[ii] = f(ii);
    }  

    recursiveSum(&a[0],&a[n]);

  }
  cout << n*(n-1)/2 << endl;
  cout << a[n-1] << endl;

  return 0;
}