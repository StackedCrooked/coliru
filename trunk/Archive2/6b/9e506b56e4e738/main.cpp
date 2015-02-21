#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int numFiles;
    cout << "How many signal files are there?";
    cin >> numFiles;
    
    vector<string> signalFiles(numFiles);
    vector<string> backgroundFiles(numFiles);
    
    for (int i=0;i<numFiles;i++){
        cout << "Please input the name of singal file" << i << ".";
        cin >> signalFiles[i];
    
        cout << "Please input the name of background file" << i << ".";
        cin >> backgroundFiles[i];
    }
}