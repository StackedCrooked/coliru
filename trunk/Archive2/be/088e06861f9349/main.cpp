
//Library code
struct Boundary {};

template <class UserBoundaries, template <Boundary UserBoundaries::*> class LocalInfo, Boundary UserBoundaries::*m_ptr>
struct Space_LocalParameters : LocalInfo <m_ptr> {};


//User code
struct Boundaries_Problem7 {
    Boundary b1, b2, b3;
};

template <Boundary Boundaries_Problem7::*m_ptr>
struct LocalInfo_Problem7 {};

template <Boundary Boundaries_Problem7::*ptr>
struct Problem7_Functions : Space_LocalParameters < Boundaries_Problem7, LocalInfo_Problem7, ptr> {};              // <-- C3201



int main(){}
