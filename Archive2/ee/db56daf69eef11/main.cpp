#include <iostream>
#include <vector>

#define unused __attribute__((unused)) //warning removal

template<typename E>
struct MExpression {
    operator E &() {return static_cast<E &>(*this);}
    operator const E &() const {return static_cast<const E &>(*this);}
};

template<typename E1, typename E2>
struct MAddExpression : MExpression<MAddExpression<E1, E2>> {
    MAddExpression(const E1 &e1, const E2 &e2) : e1_(e1), e2_(e2) {std::cout << "Free MAddExpression created\n";}
    
private:
    const E1 &e1_;
    const E2 &e2_;
};

template<typename E1, typename E2>
MAddExpression<E1, E2> operator+(const E1 &e1, const E2 &e2) {
    return MAddExpression<E1, E2>(e1, e2);
}

//////////////////////////////////////////////////////////////////

//ACTUAL CLASS

struct Matrix : MExpression<Matrix> {
    Matrix(int size1, int size2) : size1_(size1), vec_(size1 * size2) {std::cout << "Normal Matrix created\n";}
    
    template<typename E>
    Matrix(const E &) {
        std::cout << "Expensive construction from expression\n";
        //fill in vec_
    }
    
private:
    unused int size1_;
    std::vector<int> vec_;
};

int main() {
    Matrix m1(5000, 6000);
    Matrix m2(5000, 6000);
    Matrix m3(5000, 6000);
    
    Matrix m4 = m1 + m2 + m3;
}