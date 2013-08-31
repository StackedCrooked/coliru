#include <iostream>


int main() {
    int rows = 10;
    int cols = 5;
    
    // Initialize the rows
    int** matrix = new int*[rows];
    
    // Initialize the columns
    for(int r = 0; r < rows; ++r) {
        matrix[r] = new int[cols];
    }
    
    // Do something...
    for(int r = 0; r < rows; ++r) {
        for(int c = 0; c < cols; ++c) {
            matrix[r][c] = r * c;
        }
    }
    
    for(int r = 0; r < rows; ++r) {
        for(int c = 0; c < cols; ++c) {
            std::cout << "matrix[" << r << "][" << c << "]: " << matrix[r][c] << std::endl;
        }
    }
    
    // delete the columns
    for(int r = 0; r < rows; ++r) {
        delete[] matrix[r];
    }
    
    // Delete the rows
    delete[] matrix;
}