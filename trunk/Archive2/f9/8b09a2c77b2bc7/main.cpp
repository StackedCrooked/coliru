
#include <iostream>

int main() {

  int **tab2 = new int*[10];

  for(int i = 0; i < 10; i++) {
    tab2[i] = new int[3];
    tab2[i][0] = 40;
    tab2[i][1] = 10;
    tab2[i][2] = 100;
  }

  for(int i = 0; i < 10; i++) {
    delete [] tab2[i];
  }
  delete [] tab2;

}
