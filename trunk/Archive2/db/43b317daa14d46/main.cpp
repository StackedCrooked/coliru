#include <zlib.h>
#include <iostream>

static const unsigned BUFLEN = 32<<10ul;

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
        int len = gzread(in, offset, sizeof(buf)-(offset-buf));

        if (len == 0) 
            break;    

        std::cout.write(offset, len);

        // while (found eol in [buf...(offset+len)))
        //     Process a single line
        // 
        // use std::rotate (or memmov?) to move the remaining input to the front and 
        // set offset to directly after the last available byte

        int err;
        if (len < 0) 
            error (gzerror(in, &err));

    }

    if (gzclose(in) != Z_OK) error("failed gzclose");
}

int main()
{
    process(gzopen("test.gz", "rb"));
}
