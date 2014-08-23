#include <iostream>
#include <vector>

using namespace std;

template<typename T> 
class Matrix {
        vector<vector<T>> mx;
        int n;
        int m;
public:
        Matrix(int szn, int szm) 
        : mx( szn, vector<T>(szm) )
        , n{ szn }
        , m{ szm }
        {}
        
        const T& at(int i, int j) const {
                return mx[i][j];
        }
        
        T& at(int i, int j) {
                return mx[i][j];
        }
};

int main() {
    Matrix<int> m(10, 10);
    m.at(5, 5) = 123;
    cout << m.at(5, 5) << endl;
}
