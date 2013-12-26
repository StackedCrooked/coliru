#include <iostream>
#include <vector>
using namespace std;

int sz;

string ArrayAddition(int arr[]) {
  vector<int> a[2];
  for (int i = 0; i < sz; ++i) {
    if (arr[i] > 0) a[0].push_back(arr[i]);
    if (arr[i] < 0) a[1].push_back(-arr[i]);
  }
  if (a[0].empty()) return "false";  
  int maxa = 0;
  for (unsigned int i = 1; i < a[0].size(); ++i) {
    if (a[0][maxa] < a[0][i]) maxa = i;
  }
  swap(a[0][maxa],a[0][a[0].size()-1]);
  maxa = a[0].back();
  a[0].pop_back();
    
  vector<bool> can[2];
  for (int i = 0; i <= 1; ++i) {
    int sum = 0;
    for (int j = a[i].size()-1; j >= 0; --j)
      sum += a[i][j];
    can[i].resize(sum+1);
    can[i][0] = true;
    for (int j = a[i].size()-1; j >= 0; --j)
      for (int k = sum-a[i][j]; k >= 0; --k)
        if (can[i][k]) can[i][k+a[i][j]] = true;
  }
  for (int i = can[0].size()-1; i >= maxa; i--)
    if (can[0][i] && can[1][i-maxa]) return "true";
  return "false";
}

int main() { 
   
  // keep this function call here
  /* Note: In C++ you first have to initialize an array and set 
     it equal to the stdin to test your code with arrays. 
     To see how to enter arrays as arguments in C++ scroll down */
     
  int A[] = {4,1,2,3};
  sz = sizeof(A)/sizeof(int);
  cout << ArrayAddition(A);
  return 0;
    
}           
