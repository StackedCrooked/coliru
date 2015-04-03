 #include <iostream> #include <iostream>
#include <functional> #include <functional>
#include <string> #include <string>

struct S struct S
{ {
    std:: string first_name ; std :: string primeiro_nome;
    std:: string last_name ; std :: string ultimo_nome;
} ; };

template < class T > template <class T>
class MyHash ; classe MyHash;

template <> template <>
class MyHash < S > classe MyHash <S>
{ {
public : público:
    std:: size_t operator ( ) ( S const & s ) const std :: size_t operator () (S & const s) const 
    { {
        std:: size_t h1 = std :: hash < std:: string > ( ) ( s. first_name ) ; std :: size_t h1 = std :: haxixe < std :: string > () (s prenome.);
        std:: size_t h2 = std :: hash < std:: string > ( ) ( s. last_name ) ; std :: size_t h2 = std :: haxixe < std :: string > () (s ultimo_nome.);
        return h1 ^ ( h2 << 1 ) ; voltar ^ h1 (h2 << 1);
    } }
} ; };

int main ( ) int main ()
{ {
    std:: string s1 = "Hubert" ; std :: string s1 = "Hubert";
    std:: string s2 = "Farnsworth" ; std :: string s2 = "Farnsworth";
    std :: hash < std:: string > h1 ; std :: haxixe < std :: string > h1;

     S n1 ; S n1;
    n1. first_name = s1 ; n1 first_name = s1.;
    n1. last_name = s2 ; n1 ultimo_nome = s2.;

    std:: cout << "hash(s1) = " << h1 ( s1 ) << " \n " std :: cout << "de hash (S1) =" << h1 (S1) << "\ n"
              << "hash(s2) = " << std :: hash < std:: string > ( ) ( s2 ) << " \n " << "De hash (s2) =" << std :: haxixe < std :: string > () (s2) << "\ n"
	      << "hash(n1) = " << MyHash < S > ( ) ( n1 ) << " \n " ; << "De hash (n1) =" << MyHash <S> () (n1) << "\ n";

} } 