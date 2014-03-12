#include <iostream>
#include <vector>

#define unused __attribute__((unused)) //warning removal

struct Matrix {
    Matrix(int size1, int size2) : size1_(size1), vec_(size1 * size2) {std::cout << "Normal Matrix created\n";}
    Matrix(const Matrix &) {std::cout << "Expensive copy!\n";}
    
private:
    unused int size1_;
    std::vector<int> vec_;
};

Matrix operator+(const Matrix &, const Matrix &) {
    std::cout << "Expensive addition!\n";
    return Matrix(5000, 6000);
}

int main() {
    Matrix m1(5000, 6000);
    Matrix m2(5000, 6000);
    Matrix m3(5000, 6000);
    
    Matrix m4 = m1 + m2 + m3;
}
