#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    auto articleName_vector = vector<string>{"abc", "def", "ghi"};
    auto barcode_vector = articleName_vector;
    auto amount_vector = articleName_vector;
    auto price_vector = articleName_vector;
    
    auto idx = 1;
    
    auto barcode = "barcode";
    
    string articleName = articleName_vector[idx];
    cout << "Test" << endl;
    
    barcode_vector.erase(barcode_vector.begin() + idx);  
    amount_vector.erase(amount_vector.begin() + idx);
    articleName_vector.erase(articleName_vector.begin() + idx);
    price_vector.erase(price_vector.begin() + idx);
    
    cout << "Artikel " << barcode << " (" << articleName << ") verwijderd." << endl;
}