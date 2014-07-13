#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <omp.h>

// available lattices
enum LatticeTypes {
  kSquare1NN,
  kSquare1NN2NN,
  kCube1NN,
  kCube1NN2NN,
  kHypercube1NN,
  kHypercube1NN2NN,
  kAllLatticeTypes,
};
// definition of multidimensional coordinate array type
template<int kDimension>
using GenericCoordinateArrayType = std::array<int, kDimension>;
// calculate index of vertex displaced from given coordinates 'x' by
// given displacement vector 'kDx0, kDx1, ...'
template<int kDx>
inline int MoveCoordinate(const int x, const int xmax) {
  if      (0 == kDx) {return x;}
  else if (kDx < 0)  {return x + kDx + xmax * (x < -kDx);}
  else               {return x + kDx - xmax * (x > xmax - 1 - kDx);}
}
template<int kDx0, typename Tx, typename Txmax>
inline int Move1D(const Tx x, const Txmax xmax) {
  return MoveCoordinate<kDx0>(x[0], xmax[0]);    
}
template<int kDx0, int kDx1, typename Tx, typename Txmax>
inline int Move2D(const Tx x, const Txmax xmax) {
  return MoveCoordinate<kDx0>(x[0], xmax[0])
       + MoveCoordinate<kDx1>(x[1], xmax[1]) * xmax[0];    
}
template<int kDx0, int kDx1, int kDx2, typename Tx, typename Txmax>
inline int Move3D(const Tx x, const Txmax xmax) {
  return MoveCoordinate<kDx0>(x[0], xmax[0])
       + MoveCoordinate<kDx1>(x[1], xmax[1]) * xmax[0]
       + MoveCoordinate<kDx2>(x[2], xmax[2]) * xmax[0] * xmax[1];    
}
template<int kDx0, int kDx1, int kDx2, int kDx3, typename Tx, typename Txmax>
inline int Move4D(const Tx x, const Txmax xmax) {
  return MoveCoordinate<kDx0>(x[0], xmax[0])
       + MoveCoordinate<kDx1>(x[1], xmax[1]) * xmax[0]
       + MoveCoordinate<kDx2>(x[2], xmax[2]) * xmax[0] * xmax[1]
       + MoveCoordinate<kDx3>(x[3], xmax[3]) * xmax[0] * xmax[1] * xmax[2];    
}
// constants like dimension, sublattices, unit vectors for each lattice type
template<LatticeTypes kLatticeType>
class LatticeConstants {
  public:
  static constexpr int dimension_   = 0;
  static constexpr int sublattices_ = 0;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {        
    default: return 0;
    }
  }
};
template<>
class LatticeConstants<LatticeTypes::kSquare1NN> {
  public:
  static constexpr int dimension_   = 2;
  static constexpr int sublattices_ = 2;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {
    case 's' * 'n'     : return 1; // own site
    case 's' * 'v'     : return Move2D< 0, 0>(x, xmax);
    case 's' * 'e'     : return 0;
    case 'i' * 'n'     : return 2; // incoming neighbors
    case 'i' * 'v' +  0: return Move2D<-1, 0>(x, xmax);
    case 'i' * 'e' +  0: return 0;
    case 'i' * 'v' +  1: return Move2D< 0,-1>(x, xmax);
    case 'i' * 'e' +  1: return 1;
    case 'o' * 'n'     : return 2; //outgoing neighbors        
    case 'o' * 'v' +  0: return Move2D<+1, 0>(x, xmax);
    case 'o' * 'e' +  0: return 0;
    case 'o' * 'v' +  1: return Move2D< 0,+1>(x, xmax);
    case 'o' * 'e' +  1: return 1;
    }
  }
};
template<>
class LatticeConstants<LatticeTypes::kSquare1NN2NN> {
  public:
  static constexpr int dimension_   = 2;
  static constexpr int sublattices_ = 4;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {
    // own site
    case 's' * 'v'     : return Move2D< 0, 0>(x, xmax);
    // incoming neighbors
    case 'i' * 'n'     : return 4;
    case 'i' * 'v' +  0: return Move2D<-1, 0>(x, xmax);
    case 'i' * 'e' +  0: return 0;
    case 'i' * 'v' +  1: return Move2D< 0,-1>(x, xmax);
    case 'i' * 'e' +  1: return 1;
    case 'i' * 'v' +  2: return Move2D<-1,-1>(x, xmax);
    case 'i' * 'e' +  2: return 2;
    case 'i' * 'v' +  3: return Move2D<+1,-1>(x, xmax);
    case 'i' * 'e' +  3: return 3;
    //outgoing neighbors
    case 'o' * 'n'     : return 4;        
    case 'o' * 'v' +  0: return Move2D<+1, 0>(x, xmax);
    case 'o' * 'v' +  0: return 0;
    case 'o' * 'v' +  1: return Move2D< 0,+1>(x, xmax);
    case 'o' * 'v' +  1: return 1;        
    case 'o' * 'v' +  2: return Move2D<+1,+1>(x, xmax);
    case 'o' * 'v' +  2: return 2;
    case 'o' * 'v' +  3: return Move2D<-1,+1>(x, xmax);
    case 'o' * 'v' +  3: return 3;
    //
    default            : return 0;
    }
  }
};
template<>
class LatticeConstants<LatticeTypes::kCube1NN> {
  public:
  static constexpr int dimension_   = 3;
  static constexpr int sublattices_ = 2;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {
    // own site
    case 's' * 'v'     : return Move3D< 0, 0, 0>(x, xmax);
    // incoming neighbors
    case 'i' * 'n'     : return 3;
    case 'i' * 'v' +  0: return Move3D<-1, 0, 0>(x, xmax);
    case 'i' * 'e' +  0: return 0;
    case 'i' * 'v' +  1: return Move3D< 0,-1, 0>(x, xmax);
    case 'i' * 'e' +  1: return 1;
    case 'i' * 'v' +  2: return Move3D< 0, 0,-1>(x, xmax);
    case 'i' * 'e' +  2: return 2;
    //outgoing neighbors
    case 'o' * 'n'     : return 3;        
    case 'o' * 'v' +  0: return Move3D<+1, 0, 0>(x, xmax);
    case 'o' * 'e' +  0: return 0;
    case 'o' * 'v' +  1: return Move3D< 0,+1, 0>(x, xmax);
    case 'o' * 'e' +  1: return 1;
    case 'o' * 'v' +  2: return Move3D< 0, 0,+1>(x, xmax);
    case 'o' * 'e' +  2: return 2;
    //
    default            : return 0;
    }
  }
};
template<>
class LatticeConstants<LatticeTypes::kCube1NN2NN> {
  public:
  static constexpr int dimension_   = 3;
  static constexpr int sublattices_ = 4;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {
    // own site
    case 's' * 'v'     : return Move3D< 0, 0, 0>(x, xmax);
    // incoming neighbors
    case 'i' * 'n'     : return 9;
    case 'i' * 'v' +  0: return Move3D<-1, 0, 0>(x, xmax);
    case 'i' * 'e' +  0: return 0;
    case 'i' * 'v' +  1: return Move3D< 0,-1, 0>(x, xmax);
    case 'i' * 'e' +  1: return 1;
    case 'i' * 'v' +  2: return Move3D< 0, 0,-1>(x, xmax);
    case 'i' * 'e' +  2: return 2;
    case 'i' * 'v' +  3: return Move3D<-1,-1, 0>(x, xmax);
    case 'i' * 'e' +  3: return 3;
    case 'i' * 'v' +  4: return Move3D<-1, 0,-1>(x, xmax);
    case 'i' * 'e' +  4: return 4;
    case 'i' * 'v' +  5: return Move3D< 0,-1,-1>(x, xmax);
    case 'i' * 'e' +  5: return 5;
    case 'i' * 'v' +  6: return Move3D<+1,-1, 0>(x, xmax);
    case 'i' * 'e' +  6: return 6;
    case 'i' * 'v' +  7: return Move3D<+1, 0,-1>(x, xmax);
    case 'i' * 'e' +  7: return 7;
    case 'i' * 'v' +  8: return Move3D< 0,+1,-1>(x, xmax);
    case 'i' * 'e' +  8: return 8;
    //outgoing neighbors
    case 'o' * 'n'     : return 9;        
    case 'o' * 'v' +  0: return Move3D<+1, 0, 0>(x, xmax);
    case 'o' * 'e' +  0: return 0;
    case 'o' * 'v' +  1: return Move3D< 0,+1, 0>(x, xmax);
    case 'o' * 'e' +  1: return 1;
    case 'o' * 'v' +  2: return Move3D< 0, 0,+1>(x, xmax);
    case 'o' * 'e' +  2: return 2;
    case 'o' * 'v' +  3: return Move3D<+1,+1, 0>(x, xmax);
    case 'o' * 'e' +  3: return 3;
    case 'o' * 'v' +  4: return Move3D<+1, 0,+1>(x, xmax);
    case 'o' * 'e' +  4: return 4;
    case 'o' * 'v' +  5: return Move3D< 0,+1,+1>(x, xmax);
    case 'o' * 'e' +  5: return 5;
    case 'o' * 'v' +  6: return Move3D<-1,+1, 0>(x, xmax);
    case 'o' * 'e' +  6: return 6;
    case 'o' * 'v' +  7: return Move3D<-1, 0,+1>(x, xmax);
    case 'o' * 'e' +  7: return 7;
    case 'o' * 'v' +  8: return Move3D< 0,-1,+1>(x, xmax);
    case 'o' * 'e' +  8: return 8;
    //
    default            : return 0;
    }
  }
};
template<>
class LatticeConstants<LatticeTypes::kHypercube1NN> {
  public:
  static constexpr int dimension_   = 4;
  static constexpr int sublattices_ = 2;
  template<typename Tx, typename Txmax>
  int NeighborHood(const Tx x, 
                   const Txmax xmax, 
                   const int self_or_in_or_out,
                   const int element,
                   const int index) const {
    switch(self_or_in_or_out * element + index) {
    // own site
    case 's' * 'v'     : return Move3D< 0, 0, 0, 0>(x, xmax);
    // incoming neighbors
    case 'i' * 'n'     : return 4;
    case 'i' * 'v' +  0: return Move3D<-1, 0, 0, 0>(x, xmax);
    case 'i' * 'e' +  0: return 0;
    case 'i' * 'v' +  1: return Move3D< 0,-1, 0, 0>(x, xmax);
    case 'i' * 'e' +  1: return 1;
    case 'i' * 'v' +  2: return Move3D< 0, 0,-1, 0>(x, xmax);
    case 'i' * 'e' +  2: return 2;
    case 'i' * 'v' +  3: return Move3D< 0, 0, 0,-1>(x, xmax);
    case 'i' * 'e' +  3: return 3;
    //outgoing neighbors
    case 'o' * 'n'     : return 4;        
    case 'o' * 'v' +  0: return Move3D<+1, 0, 0, 0>(x, xmax);
    case 'o' * 'e' +  0: return 0;
    case 'o' * 'v' +  1: return Move3D< 0,+1, 0, 0>(x, xmax);
    case 'o' * 'e' +  1: return 1;
    case 'o' * 'v' +  2: return Move3D< 0, 0,+1, 0>(x, xmax);
    case 'o' * 'e' +  2: return 2;
    case 'o' * 'v' +  3: return Move3D< 0, 0, 0,+1>(x, xmax);
    case 'o' * 'e' +  3: return 3;
    //
    default            : return 0;
    }
  }
};
// the Lattice class inherits a type of lattice defined in LatticeConstants
// and wraps the constants into user friendly functions
template<LatticeTypes kLatticeType>
class Lattice : public LatticeConstants<kLatticeType> {
  public:
  using TLattice = LatticeConstants<kLatticeType>;
  using CoordinateArrayType = GenericCoordinateArrayType<TLattice::dimension_>;
  // constructor
  Lattice(std::vector<int> xmax_user) : xmax_(AdjustXmax(xmax_user)) {
    num_vertices_ = 1;
    for (int i = 0; i < dimension(); i++) {
      num_vertices_ *= xmax(i);    
    }
  }
  static constexpr int dimension(void) {return TLattice::dimension_;}
  static constexpr int sublattices(void) {return TLattice::sublattices_;}
  // adjusts user provided edge length array to correct dimension
  CoordinateArrayType AdjustXmax(std::vector<int> xmax_user) {
    xmax_user.resize(dimension());
    CoordinateArrayType xmax_new;
    for (int i = 0; i < dimension(); i++) {
      xmax_new[i] = xmax_user[i];   
    }
    return xmax_new;
  }
  template<typename Tx>
  int VertexIndex(const Tx x) const {
    return TLattice::NeighborHood(x, xmax_, 's', 'v', 0);
  }
  template<typename Tx>
  int NumIncomingNeighbor(const Tx x) const {
    return TLattice::NeighborHood(x, xmax_, 'i', 'n', 0);
  }
  template<typename Tx>
  int VertexIndexIncomingNeighbor(const Tx x, const int index) const {
    return TLattice::NeighborHood(x, xmax_, 'i', 'v', index);
  }
  template<typename Tx>
  int EdgeTypeIncomingNeighbor(const Tx x, const int index) const {
    return TLattice::NeighborHood(x, xmax_, 'i', 'e', index);
  }
  template<typename Tx>
  int NumOutgoingNeighbor(const Tx x) const {
    return TLattice::NeighborHood(x, xmax_, 'o', 'n', 0);
  }
  template<typename Tx>
  int VertexIndexOutgoingNeighbor(const Tx x, const int index) const {
    return TLattice::NeighborHood(x, xmax_, 'o', 'v', index);
  }
  template<typename Tx>
  int EdgeTypeOutgoingNeighbor(const Tx x, const int index) const {
    return TLattice::NeighborHood(x, xmax_, 'o', 'e', index);
  }
  int xmax(int component) const { return xmax_[component]; }
  int num_vertices(void) const {return num_vertices_; }
  private:
  const CoordinateArrayType xmax_;
  int num_vertices_;
};
// checkerboard loops for each dimension and sublattice type 
#define for_each_vertex(_x_, _A_, _pragmaopts_, _stuff_)                      \
  switch(_A_.dimension()) {                                                   \
  case 2:                                                                     \
    switch(_A_.sublattices()) {                                               \
    case 2:                                                                   \
      _Pragma(_pragmaopts_)                                                   \
      for (int _x1_ = 0;          _x1_ < _A_.xmax(1); _x1_++) {               \
      for (int _x0_ = (_x1_ & 1); _x0_ < _A_.xmax(0); _x0_+=2) {              \
        const GenericCoordinateArrayType<2> _x_{_x0_, _x1_};                  \
        {_stuff_}                                                             \
      }}                                                                      \
      _Pragma(_pragmaopts_)                                                   \
      for (int _x1_ = 0;           _x1_ < _A_.xmax(1); _x1_++) {              \
      for (int _x0_ = !(_x1_ & 1); _x0_ < _A_.xmax(0); _x0_+=2) {             \
        const GenericCoordinateArrayType<2> _x_{_x0_, _x1_};                  \
        {_stuff_}                                                             \
      }}                                                                      \
    break;                                                                    \
    case 4:                                                                   \
    break;                                                                    \
    }                                                                         \
  break;                                                                      \
  case 3:                                                                     \
    switch(_A_.sublattices()) {                                               \
    case 2:                                                                   \
        _Pragma(_pragmaopts_)                                                 \
        for (int _x2_ = 0;                   _x2_ < _A_.xmax(2); _x2_++) {    \
        for (int _x1_ = 0;                   _x1_ < _A_.xmax(1); _x1_++) {    \
        for (int _x0_ = ((_x2_ + _x1_) & 1); _x0_ < _A_.xmax(0); _x0_+=2) {   \
            const GenericCoordinateArrayType<3> _x_{_x0_, _x1_, _x2_};        \
            {_stuff_}                                                         \
        }}}                                                                   \
        _Pragma(_pragmaopts_)                                                 \
        for (int _x2_ = 0;                   _x2_ < _A_.xmax(2); _x2_++) {    \
        for (int _x1_ = 0;                   _x1_ < _A_.xmax(1); _x1_++) {    \
        for (int _x0_ = !((_x2_ + _x1_) & 1); _x0_ < _A_.xmax(0); _x0_+=2) {  \
            const GenericCoordinateArrayType<3> _x_{_x0_, _x1_, _x2_};        \
            {_stuff_}                                                         \
        }}}                                                                   \
    break;                                                                    \
    case 4:                                                                   \
    break;                                                                    \
    }                                                                         \
  break;                                                                      \
  case 4:                                                                     \
    switch(_A_.sublattices()) {                                               \
    case 2:                                                                   \
        _Pragma(_pragmaopts_)                                                 \
        for (int _x3_ = 0;                      _x3_ < _A_.xmax(3); _x3_++) { \
        for (int _x2_ = 0;                      _x2_ < _A_.xmax(2); _x2_++) { \
        for (int _x1_ = 0;                      _x1_ < _A_.xmax(1); _x1_++) { \
        for (int _x0_ = ((_x3_+_x2_+_x1_) & 1); _x0_ < _A_.xmax(0); _x0_+=2) {\
            const GenericCoordinateArrayType<4> _x_{_x0_, _x1_, _x2_, _x3_};  \
            {_stuff_}                                                         \
        }}}}                                                                  \
        _Pragma(_pragmaopts_)                                                 \
        for (int _x3_ = 0;                      _x3_ < _A_.xmax(3); _x3_++) { \
        for (int _x2_ = 0;                      _x2_ < _A_.xmax(2); _x2_++) { \
        for (int _x1_ = 0;                      _x1_ < _A_.xmax(1); _x1_++) { \
        for (int _x0_ = ((_x3_+_x2_+_x1_) & 1); _x0_ < _A_.xmax(0); _x0_+=2) {\
            const GenericCoordinateArrayType<4> _x_{_x0_, _x1_, _x2_, _x3_};  \
            {_stuff_}                                                         \
        }}}}                                                                  \
    break;                                                                    \
    case 4:                                                                   \
    break;                                                                    \
    }                                                                         \
  break;                                                                      \
  }

//=============================================================================

//Ising model

unsigned rngs[] = {1234, 5678, 9098, 7654, 3211, 2345, 6789, 8765};

inline double rand_uniform(unsigned* rng) {
  *rng = 1664525 * (*rng) + 1013904223;
  return (2.32830643653869629E-10 * (*rng));
} 

double exptable[9];

void fill_exptable(const double beta) {
  for (int dE = -4; dE <= 4; dE++) {
    exptable[4 + dE] = std::exp(-beta * 2 * dE);
  }
  return;
}

template<typename Tspins, typename Tlattice>
void myfunc(Tspins& v, const Tlattice A) {
  #pragma omp parallel
  {
    unsigned rng_copy = rngs[omp_get_thread_num()];
    for_each_vertex(x, A, "omp for",
      int sum = 0;
      for (int z = 0; z < A.NumIncomingNeighbor(x); z++) {
        sum += v[A.VertexIndexIncomingNeighbor(x, z)];
      }
      for (int z = 0; z < A.NumOutgoingNeighbor(x); z++) {
        sum += v[A.VertexIndexOutgoingNeighbor(x, z)];
      }
      int dE = v[A.VertexIndex(x)] * sum;
      if (exptable[4 + dE] > rand_uniform(&rng_copy))
        v[A.VertexIndex(x)] = -v[A.VertexIndex(x)];    
    )
    rngs[omp_get_thread_num()] = rng_copy;
  }
  return;
}

int main(int argc, char** argv) {
  using MyLattice = Lattice<LatticeTypes::kSquare1NN>; 
  int L = std::stoi(argv[1]);
  MyLattice A({L,L,L,L});
  std::vector<int> v(A.num_vertices(), 1);
  fill_exptable(1.0 / 2.269);
  double start = omp_get_wtime();
  for (int t = 0; t < 100; t++) {
    myfunc(v, A);
  }
  double end = omp_get_wtime();
  std::cout << end - start << std::endl;
  double sum = 0.0;
  #pragma omp parallel for reduction (+:sum)
  for (unsigned i = 0; i < v.size(); i++) {
    sum += v[i];   
  }
  sum /= (1.0 * A.num_vertices());
  std::cout << "sum = " << sum << std::endl;
  return 0;   
}