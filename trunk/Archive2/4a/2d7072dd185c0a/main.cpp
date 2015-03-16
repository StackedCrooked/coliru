#include <iostream>

class GiganticDatabase { // Gigantic database - several GBs
public:
    GiganticDatabase(const GiganticDatabase&) {} // Initialize GiganticDatabase from another object

    GiganticDatabase (char *file) {} // Initialize GiganticDatabase from file
 };

class Registry {
public:    
   GiganticDatabase graph;

   Registry(char* filename) : graph(*new GiganticDatabase(filename)) // <-- Leaks several GBs FTW
   {}
};

int main() {
   char file[] = "C:\\whatever.db";
   Registry stupidObject(file);
}
