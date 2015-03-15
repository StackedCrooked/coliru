#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int array[100][100];

void* operator new(size_t num, int x, int y) {
    return &array[x][y];    
}

class Custom {
private:
  int i[5];
public:
  Custom(){
      cout << "Constructing Custom" << endl;
  }
};

int main() {
    int* p = new (0,2) int;
    *p = 6;
    cout << *p << std::endl;
    
    int *p2 = new int;
    cout << p2 << std::endl;
    
    Custom *p3 = new (0, 0) Custom;
 
    /*
    for(int i = 0; i < 5; i++){
        int *ip = (int*)p3;
        cout << *(ip+i) << endl;
    }*/
    
    
    return 0;
}