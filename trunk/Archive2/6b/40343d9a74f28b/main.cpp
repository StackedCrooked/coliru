#include <iostream>
#include <cstring>
#include <string>

int main() {
    char S[100], R[100], T[200];
    /*
     * strcpy copies contents form right to left pointers up untill NULL.
     * You have to make sure there is enough space to do so, have big enough
     * array or malloc'd sufficient bytes (dont forget the NULL!)
     *
     * "something" gets changed to a predefined pointer, that is resolved on
     * compile time.
     */
    std::strcpy (S, "something");
    
    //std::cin.getline (R, 100); cant have cin here ):
    std::strcpy (R, "something else");
    
    #if 0 // change 0 to 1, but who cares, it will do the same anyway
    /*
     * this is really intuitive and easy to understand, but it's not scalable
     * (as you see, 2 strings only) and may not be as fast
     */
    std::sprintf (T, "%s, %s", S, R);
    
    #else
    /*
     * it may not be apparent at first, but this can be put to a loop an be
     * used to join a lot of strings
     */
    char*write_to = T;
    std::strcpy (write_to, S);
    write_to += std::strlen (S);
    std::strcpy (write_to, ", ");
    write_to += 2; // NULL gets overwritten, so we don't care about it
    std::strcpy (write_to, R);
    #endif
    
    std::printf (T);
    
    return 0;
}
