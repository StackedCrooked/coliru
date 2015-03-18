#include <vector>
#include <iostream>
#include <functional>
#include <initializer_list>

template <typename T>
class Matrix {
private:
    typedef std::initializer_list<std::initializer_list<T>> init_list_2d;
    T** _array = nullptr;

public:
    // Important properties
    int Rows = 0, Cols = 0;

    // Public access to _array
    bool isVoid() { return _array == nullptr; };
    T* operator [](int row) { return _array[row]; };
    const T* operator [](int row) const { return _array[row]; };

    // Allow for C++11 initializer_list
    Matrix(init_list_2d s) { init_list(s); };
    Matrix<T>& operator=(init_list_2d s) { init_list(s); return *this; };

    // Implement/Override construction, copy, and destruction
    Matrix(int m, int n, T val = 0) { init(m, n, val); };
    Matrix<T>& operator=(const Matrix<T>& a) { copy(a); return *this; };
    Matrix(const Matrix<T>& a) { copy(a); }
    ~Matrix() { clean(); };

private:
    // Private low-level modifiers
    void init_list(init_list_2d s) {
        // Take advantage of vector handling initalizer_list
        std::vector<std::initializer_list<T>> init = s;
        std::vector<std::vector<T>> data;
        for (auto i = init.begin(); i != init.end(); ++i) {
            data.push_back(std::vector<T>(*i));
        }

        clean();
        Rows = data.size();
        Cols = data[0].size();
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = data[i][j];
            }
        }
    };

    void init(int m, int n, T val) {
        clean();
        Rows = m;
        Cols = n;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = val;
            }
        }
    };

    void copy(const Matrix<T>& a) {
        clean();
        Rows = a.Rows;
        Cols = a.Cols;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = a._array[i][j];
            }
        }
    };

    void clean() {
        if (_array != nullptr) {
            for (int i = 0; i < Rows; ++i) {
                delete[] _array[i];
            }
            delete[] _array;
        }
        _array = nullptr;
        Cols = 0;
        Rows = 0;
    };

public:
    // Public low-level modifiers
    void resize(int m, int n) {
        clean();
        Rows = m;
        Cols = n;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
        }
    };

    void each(std::function<void(T&, int, int)> f) {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                f(_array[i][j], i, j);
            }
        }
    };

    void each(std::function<void(T&)> f) {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                f(_array[i][j]);
            }
        }
    };
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& obj) {
    out << std::endl;
    for (int i = 0; i < obj.Rows; ++i) {
        out << "[";
        for (int j = 0; j < obj.Cols; ++j) {
            out << obj[i][j];
            if (j < obj.Cols - 1) {
                out << ", ";
            }
        }
        out << "]" << std::endl;
    }
    out << std::endl;
    return out;
}

int main() {
    Matrix<double> A {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    A.each([](double& d) {
        d *= 5;
    });

    std::cout << A << std::endl;

    return 0;
}
