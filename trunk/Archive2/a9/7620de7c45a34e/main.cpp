struct Z { int z; };
template < typename T > struct Y { int y; };
template < typename T > struct A: public B< T >, public Z {
  int i;
  int getI() const { return i; }            // refers to i declared above
  int getI2() const { return A::i; }        // refers to i declared above
  int getI3() const { return A< T >::i; }   // refers to i declared above
  int getJ() const { return A< T >::j; }    // could perhaps be B< T >::j
  int getK() const { return A< T * >::k; }  // could perhaps be B< T >::k
                                            //  or a member k of a 
                                            //  partial or explicit 
                                            //  specializaton of A
  int getZ() const { return z; }            // refers to Z::z
  int getY() const { return Y< T >::y; }    // refers to Y< T >::y	      
 
  static int getI(A *a) { return a->i; }        // refers to A::i in (*a)
  static int getJ(A *a) { return a->j; }        // could perhaps be B< T >::j in (*a)
  static int getK(A< T > *a) { return a->k; }   // could perhaps be B< T >::k in (*a)
                                                //  or a member k of a partial or 
                                                //  explicit specializaton of A in (*a)
  static int getZ(A *a) const { return a->z; }  // refers to Z::z in (*a)	
};