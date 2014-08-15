int main()
{
    #define _lang_macro_identity(x) x
    #define _lang_macro_concat(A, B) A ## B
    #define _lang_macro_join(A, B) _lang_macro_concat(A,B)
     
    #define _lang_macro_num_args_impl(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23,c24,c25,c26,c27,c28,c29,c30,c31,c32,c33,c34,c35,c36,c37,c38,c39,c40,c41,c42,c43,c44,c45,c46,N, ...) N
    //return 1 if more than 2 args
    #define _lang_macro_has_3args(...) _lang_macro_identity(_lang_macro_num_args_impl(__VA_ARGS__, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0))
     
    //define some vars
    #define DEF(...) _lang_macro_join(DEF_HELPER, _lang_macro_has_3args(__VA_ARGS__)) (__VA_ARGS__)
    //define a single var
    #define DEF_HELPER0(T, n) T n
    //define more than one var
    #define DEF_HELPER1(T0, n0, ...) T0 n0; DEF(__VA_ARGS__)
     
    //define a number of variables
    DEF(int, foo, float, bar);

}