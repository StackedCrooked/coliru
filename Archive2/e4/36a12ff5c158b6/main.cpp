#include<iostream>


//Ecrire une recherche linéaire dans un tableau d'entiers.
int* LinearSearch(int* values, size_t count, int itemToFind){
    for (; count > 0; count--, values++) {
        if (*values == itemToFind){
            return values;
        }
    }
    return NULL;
}

 

//Ecrire une recherche linéaire à l'envers dans un tableau d'entiers.
int* ReverseLinearSearch(int* values, size_t count, int itemToFind){
    for (values += count - 1; count > 0; count--, values--) {
        if (*values == itemToFind){
            return values;
        }
    }
    return NULL;
}

 

//Ecrire une recherche dichotomique dans un tableau d'entiers.
//Quelle est la précondition sur les données pour pouvoir appeler cette fonction?
// Il faut être sur que le tableau est trié dans un premier temps.
int* BinarySearch(int* values, size_t count, int itemToFind){
    size_t start = 0;
    size_t end = count;

    while(start < end){
        const size_t mid = (end - start)/2 + start;
        if (values[mid] == itemToFind){
            return &values[mid];
        }
        
        if (values[mid] <  itemToFind){
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    
    return NULL;   
}

using namespace std;

int main(){
    static const size_t n = 10;
    int tab[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* found;
    
    
    found = LinearSearch(tab, n, 2);
    if (found) {
        std::cout << "LinearSearch: " << *found << endl;
    } else {
        std::cout << "LinearSearch not found" << endl;
    }
    
    found = LinearSearch(tab, n, -2);
    if (found) {
        std::cout << "LinearSearch: " << *found << endl;
    } else {
        std::cout << "LinearSearch not found" << endl;
    }
    
    
    found = ReverseLinearSearch(tab, n, 2);
    if (found) {
        std::cout << "LinearSearch: " << *found << endl;
    } else {
        std::cout << "LinearSearch not found" << endl;
    }
    
    found = ReverseLinearSearch(tab, n, -2);
    if (found) {
        std::cout << "LinearSearch: " << *found << endl;
    } else {
        std::cout << "LinearSearch not found" << endl;
    }
    
    found = BinarySearch(tab, n, 5);
    if (found) {
        std::cout << "BinarySearch: " << *found << endl;
    } else {
        std::cout << "BinarySearch not found" << endl;
    }
    
    found = BinarySearch(tab, n, -5);
    if (found) {
        std::cout << "BinarySearch: " << *found << endl;
    } else {
        std::cout << "BinarySearch not found" << endl;
    }
    
    return 0;
}