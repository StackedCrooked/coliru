#include <cstring>

int main() {
    const int largo = 3;
    char** vector = new char* [largo+1];
    for (int i = 0; i < largo + 1; ++i)
        vector[i] = new char[10];
    strcpy(vector[0], "Futbol");
    strcpy(vector[0], "AUTOmata");
    strcpy(vector[0], "fUT");
    strcpy(vector[0], "auto");
}