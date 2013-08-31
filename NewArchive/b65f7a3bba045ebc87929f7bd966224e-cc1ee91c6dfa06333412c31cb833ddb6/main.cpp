#include <stdio.h>

int getData(int i) { return i; }

int main()
{
    char buf[100*24]; // or some other nice, large enough size
    char* const last = buf+sizeof(buf);
    char* out = buf;

    for (int i = 0; i < 100; i++) {
        out += snprintf(out, last-out, "data: %d\n", getData(i));
    }

    *out = '\0';
    printf("%s", buf);
}
