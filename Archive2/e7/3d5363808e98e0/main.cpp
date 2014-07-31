
//Library code
struct Boundary {};

template <class UserBoundaries, template <Boundary UserBoundaries::*, bool ...> class LocalInfo, Boundary UserBoundaries::*m_ptr, bool... args>
struct Space_LocalParameters : LocalInfo < m_ptr, args... > {} ;

//User code
struct Boundaries_Problem7 {
    Boundary b1, b2, b3;
};

template <Boundary Boundaries_Problem7::*m_ptr, bool... args> 
struct LocalInfo_Problem7 {};

template <Boundary Boundaries_Problem7::*ptr, bool... args>
struct Problem7_Functions : Space_LocalParameters < Boundaries_Problem7, LocalInfo_Problem7, ptr, args... > {};

int main() {}

