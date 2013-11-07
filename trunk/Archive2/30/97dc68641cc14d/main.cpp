#include <iostream>
#include <string>
#include <vector>

int main()
{
    int numbers[5];
    int i = 0;
    for (int &n : numbers) { // Referenz noetig um Inhalte zu modizieren        
        n = i;       
        i++;
    }
    
    for (int n : numbers) { // Keine Referenz zur Ausgabe noetig
        std::cout << n << " ";
    }
    
    return 0;
}
