namespace test
{
    // template magic for building a bit mask from control characters
  template <char...> struct CtrlVec ; 
  template <char c> struct CtrlVec<c>
  { 
    static_assert( ( c < 0x20 ), "Only for control characters" ) ; 
    enum { mask = ( 1 << c ) } ; 
  } ; 
  template <char c, char... cs> struct CtrlVec<c, cs...>
  { 
    static_assert( ( c < 0x20 ), "Only for control characters" ) ; 
    enum { mask = ( 1 << c ) | CtrlVec<cs...>::mask } ; 
  } ; 

  static_assert( CtrlVec<'\0', '\001', '\002'>::mask == 0x7, "") ; 

    /// 

  class test_scanner
  { 
    public:
          // this version works fine in GCC, but gives an error in Clang 3.2
      test_scanner( unsigned int avec = CtrlVec<'\n','\r'>::mask ) ;

          // adding the () makes it work
      test_scanner( int good, unsigned int avec = ( CtrlVec<'\n','\r'>::mask ) ) ; 
  } ; 

} ;

int main() {}