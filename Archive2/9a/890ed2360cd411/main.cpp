#include <zlib.h>
#include <iostream>
#include <algorithm>

static const unsigned BUFLEN = 1024;

void error(const char* const msg)
{
    std::cerr << msg << "\n";
    exit(255);
}

void process(gzFile in)
{
    char buf[BUFLEN];
    char* offset = buf;

    for (;;) {
        int err, len = sizeof(buf)-(offset-buf);
        if (len == 0) error("Buffer to small for input line lengths");

        len = gzread(in, offset, len);

        if (len == 0) break;    
        if (len <  0) error(gzerror(in, &err));

        char* cur = buf;
        char* end = offset+len;

        for (char* eol; (cur<end) && (eol = std::find(cur, end, '\n')) < end; cur = eol + 1)
        {
            std::cout << std::string(cur, eol) << "\n";
        }

        // any trailing data in [eol, end) now is a partial line
        offset = std::copy(cur, end, buf);
    }

    // BIG CATCH: don't forget about trailing data without eol :)
    std::cout << std::string(buf, offset);

    if (gzclose(in) != Z_OK) error("failed gzclose");
}

int main()
{
    process(gzopen("test.gz", "rb"));
}
