#include <iostream>

template<typename Scalar>
struct Quaternion {
 constexpr int GetErrorStateSize() const {
   return 3;
 }
};

template<typename Scalar>
struct Vector3 {
 constexpr int GetErrorStateSize() const {
   return 3;
 }
};

template<typename Scalar>
struct Pose {
  Quaternion<Scalar> q;
  Vector3<Scalar> p;
  constexpr int GetErrorStateSize() const {
      // See how the value is calculated at compile time before the members are instantiated.
    return q.GetErrorStateSize() + p.GetErrorStateSize();
  }
};  
    

template<typename Scalar, int Size>
struct SquareMatrix {
 static const int kLocalSize = Size;
 Scalar values[kLocalSize * kLocalSize];   
};

template<typename Scalar>
SquareMatrix<Scalar, Vector3().GetErrorStateSize()> GetSquareMatrixOfSize3() {
    
}

int main() {
  typedef double Scalar;
  // Now we can get the static size by creating a compile time "instantiation".
  SquareMatrix<Scalar, Pose<Scalar>().GetErrorStateSize()> matrix;
  // Or from a local variable, which is probably what you would do for your class.
  Pose<Scalar> some_pose;
  SquareMatrix<Scalar, some_pose.GetErrorStateSize()> matrix_2;  
  
  auto matrix_3 = GetSquareMatrixOfSize3<double>();
  
  std::cout << "Matrix sizes: " << matrix.kLocalSize << " " << matrix_2.kLocalSize << " " << matrix_3.kLocalSize << std::endl;
}