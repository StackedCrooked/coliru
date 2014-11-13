#include <iostream>
#include <vector>
#include <list>

using namespace std;

list<int> devolver_cambio(const int n)
{
  vector<int> M = { 200, 100, 50, 20, 10, 5, 2, 1 };
  
  list<int> S;
  int suma = 0;
  
  int pos = 0;
  while (suma != n) {
    int i = pos, x = 0;
    while (i < M.size() && x == 0) {
      if (suma + M[i] <= n) {
        x = M[i];
        pos = i;
      }
      else i++;
    }

    if (x == 0) return list<int>();
    S.push_back(x);
    suma += x;
  }
 
  return S;
}

int main()
{ 
    int n = 741;
    list<int> S = devolver_cambio(n);
    int suma = 0;
    cout << "n: " << n << endl;
    cout << "Solución: ";
    for (auto &s: S) {
        cout << s << " ";
        suma += s;
    }
    cout << endl << "Suma: " << suma << endl;
}
