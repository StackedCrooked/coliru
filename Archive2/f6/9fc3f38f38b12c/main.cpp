class Matrix {
    float* M;
    int n, k;
    void allocM(int _n, int _k) {
        n = _n;
        k = _k;
        M = new float[n * k];
    }
    void delM() {
        delete[] M;
    }
    public:
    inline float operator()(int i, int j) const { return M[i * k + j]; }
    inline float& operator()(int i, int j) { return M[i * k + j]; }
    Matrix(int _n, int _k) {
        allocM(_n, _k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                operator()(i, j) = 0;
            }
        }
    }
    Matrix(const Matrix& source) {
        allocM(source.n, source.k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                operator()(i, j) = source(i, j);
            }
        }
    }
    ~Matrix() {
        delM();
    }
    Matrix& operator=(const Matrix& source) {
        delM();
        allocM(source.n, source.k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                operator()(i, j) = source(i, j);
            }
        }
        return *this;
    }
    Matrix operator*(const Matrix& other) const {
        Matrix matrix = Matrix(n, other.k);
        for (int i = 0; i < matrix.n; ++i) {
            for (int j = 0; j < matrix.k; ++j) {
                for (int l = 0; l < k; ++l) {
                    matrix(i, j) += operator()(i, l) * other(l, j);
                }
            }
        }
        return matrix;
    }
    Matrix transpose() const {
        Matrix matrix = Matrix(k, n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                matrix(k, n) = operator()(n, k);
            }
        }
        return matrix;
    }
};

int main() {
    Matrix matrix1(3, 4);
    Matrix matrix2(3, 4);
    Matrix matrix0(1, 1);
    matrix0 = matrix1 * matrix2.transpose();
    return 0;
}