#include <iostream>
//#include <windows.h>

using namespace std;

int main(int argc, char** argv) {
char items[] = {'bread', 'water', 'crisps', 'sweets', 'vegetables'};
for (int i = 0; i < strlen(items); i++) {
        cout << items[i] << endl;
    }
return 0;
}