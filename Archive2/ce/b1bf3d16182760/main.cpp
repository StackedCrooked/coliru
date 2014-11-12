 #include <algorithm> # Include <algorithm>
#include <string> # Include <cadena>
#include <iostream> # Include <iostream>

int main ( ) int main ()
{ {
    std:: string s = "123" ; std :: string s = "aba";
    std:: sort ( s. begin ( ) , s. end ( ) ) ; std :: sort (. s. begin (), s end ());
    do { do {
        std:: cout << s << ' \n ' ; std :: cout << s << '\ n';
    } while ( std :: next_permutation ( s. begin ( ) , s. end ( ) ) ) ; } While (std :: next_permutation (s. begin (), s end ()).);
} } 