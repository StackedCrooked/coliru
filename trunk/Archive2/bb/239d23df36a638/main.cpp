    #include <ostream>
    #include <istream>

    namespace std
    {
        extern istream cin;
        extern ostream cout;


        // this is explained below
        static ios_base::Init __foo;    // not its real name
    } 
