#include <iostream>

using namespace std;

int main()
{
    int list_ctr = 25;
    double **alexander_matrix = new double*[list_ctr];
    for ( int i = 0; i < list_ctr; i++){
        alexander_matrix[i] = new double[list_ctr];
    }

    for (int i = 0; i < list_ctr; i++) {
        for (int j = 0; j < list_ctr; j++) {
            alexander_matrix[i][j] = rand() % 2;
            cout << alexander_matrix[i][j] << ", ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < list_ctr; i++){
          delete[] alexander_matrix[i];
    }
    delete[] alexander_matrix;
    
    cout << "yay :)" << endl;
}
