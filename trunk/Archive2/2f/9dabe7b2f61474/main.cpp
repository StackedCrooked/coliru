#include <string>

using std::string;

void split(string line, int &carnet, string &nom, int &not1, int &not2, int &not3, int &not4);

void split(string line, int &carnet, string &nom, int &not1, int &not2, int &not3, int &not4){
        //Doing super cool stuff...
}

int main() {
    string nombre = "";
    string linea = "";
    int carnet = 0, nota1 = 0, nota2 = 0, nota3 = 0, nota4 = 0;
//    inFile >> linea;
    split(linea, carnet, nombre, nota1, nota2, nota3, nota4);
}