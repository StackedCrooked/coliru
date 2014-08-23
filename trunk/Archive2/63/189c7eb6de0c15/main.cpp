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
        : mx{ szn, vector<T>(szm) }
        , n{ szn }
        , m{ szm }
        {}
        
        const T& Get(int i, int j) const {
                return mx[i][j];
        }
        
        T& Get(int i, int j) {
                return mx[i][j];
        }
 
        void Set(int i, int j, const T& val){
                mx[i][j] = val;
        }
};

