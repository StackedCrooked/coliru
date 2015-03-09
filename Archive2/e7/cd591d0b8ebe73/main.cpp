#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main(int argc, char* argv[]){
    srand(time(NULL));
    
	char *ar;
	
    int size;
    
    {
        std::stringstream converter;
        converter << argv[1];
        converter >> size;
    }
    
	ar = new char[size];
	for (int i = 0; i < size; i++) {
		ar[i] = (char)rand() % 40;
	}
	
	
	for (int i = 0; i < size; i++){
		cout << &ar[i] << " \n";
		cout << *(&ar[i]) << endl;
	}
	
}