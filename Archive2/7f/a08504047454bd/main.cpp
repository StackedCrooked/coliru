#include <fstream>
#include <initializer_list>

using namespace std;

void writeSomething(initializer_list<ofstream&> args) {
    for (auto f : args )
        f << "hello" << endl;
}

int main() {
    ofstream outputFile("data_1.txt");
    ofstream outputFile2("data_2.txt");
    writeSomething({outputFile, outputFile2});
}