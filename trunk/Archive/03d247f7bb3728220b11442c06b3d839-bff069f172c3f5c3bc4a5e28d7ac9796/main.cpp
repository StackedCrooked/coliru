#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;
using boost::regex;
using boost::regex_iterator;
#define MAX_BUFFER 255

#if 0 // FAKE INPUT
Tracing route to 11.1.0.1 over a maximum of 30 hops

1     2 ms     3 ms     2 ms  [157.54.48.1]
2    75 ms    83 ms    88 ms  [11.1.0.67]
3    73 ms    79 ms    93 ms  [11.1.0.1]

Trace complete.
#endif

int main()
{
    char buffer[MAX_BUFFER];
    regex e("^\\s*1\\s.*?\\[(.*?)\\]");

    FILE *stream = popen("cat main.cpp", "r");
    while(fgets(buffer, MAX_BUFFER, stream) != NULL)
    {
        typedef regex_iterator<string::iterator> regit;

        string out = buffer;
        regit rit(out.begin(), out.end(), e);
        regit rend;
        while(rit != rend)
        {
            cout << (*rit)[1].str() << endl;
            ++rit;
        }
    }
    pclose(stream);
    cout << "Done.\n";
}
