
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { FILE* stream; } WriteStream;
typedef struct { FILE* stream; } ReadStream;

WriteStream getWriteStream(FILE* file) {
    WriteStream ws = { .stream = file };
    return ws;
}

typedef struct { char* data; unsigned size; } String;

String toString(const char* str) { 
    String data;
    data.size = strlen(str) + 1;
    
    data.data = malloc(data.size);
    memcpy(data.data, str, data.size);
    
    return data;
}

void safePuts (WriteStream str, const String s) {
    fputs(s.data, str.stream);
}

int main () {
    String str = toString("test");

    WriteStream outWriteStream = getWriteStream(stdout);
    
    safePuts(outWriteStream, str);
    
    fflush(stdout);
}