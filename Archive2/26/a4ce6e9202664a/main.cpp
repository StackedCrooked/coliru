// these two declarations are indistinguishable
template < typename T > void hahaha( T a ) ;
template < typename T > void hahaha( const T a ) ;

// these two declarations are indistinguishable
template <> void hahaha<int*>( int* a ) ;
template <> void hahaha<int*>( int* const a ) ;

// these two are declarations indistinguishable
template <> void hahaha<const int*>( const int* a ) ;
template <> void hahaha<const int*>( const int* const a ) ;


/////////////////////////////////////////////////////////////////////////

template < typename T > void hahaha( T a ) { /* ... */ } // definition

// *** error: redefinition of 'template < typename T > void hahaha( T )'
template < typename T > void hahaha( const T a ) { /* ... */ }

/////////////////////////////////////////////////////////////////////////
template <> void hahaha<int*>( int* a ) { /* ... */ }

// *** error: redefinition of 'template <> void hahaha<int*>( int* )'
template <> void hahaha<int*>( int* const a ) { /* ... */ }

/////////////////////////////////////////////////////////////////////////
template <> void hahaha<const int*>( const int* const a ) { /* ... */ }

// *** error: redefinition of 'template <> void hahaha<const int*>( const int* )'
template <> void hahaha<const int*>( const int* a ) { /* ... */ }
