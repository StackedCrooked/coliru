#include <iostream>


using namespace std;

int main() {
    int anzahl;
    
    cout << "Wert:" << endl;
    cin >> anzahl;
    int zahlen [anzahl];
    
    for(ssize_t i=0; i<anzahl; ++i) {
        zahlen[i]=0;
    }
    for(ssize_t i=0; i<anzahl; ++i) {
        std::cout << zahlen[i] << std::endl;
    }

}