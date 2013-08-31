struct A { };
struct B : virtual A { };
struct C : B { };
struct D : virtual A { D(A*); };
struct X { X(A*); };

struct E : C, D, X {
    E() : D(this),  // undefined: upcast from E* to A*
                    // might use path E* ! D* ! A*
                    // but D is not constructed
                    // D((C*)this), // defined:
                    // E* ! C* defined because E() has started
                    // and C* ! A* defined because
                    // C fully constructed
          X(this) { // defined: upon construction of X,
                    // C/B/D/A sublattice is fully constructed
          }
};