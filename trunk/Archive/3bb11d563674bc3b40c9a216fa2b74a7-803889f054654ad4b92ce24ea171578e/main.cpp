// The first param, UTF8Str, is the null-terminated UTF8 encoded input string
// The second parameter, if specified, is the max limit in bytes allowed for this data by the client
// Returns the length of the string in bytes cutting off at MaxLimit between characters
inline unsigned long GetUTF8End(const char* UTF8Str, unsigned long MaxLimit = -1)
{
    unsigned long len=0;
    unsigned next = 0;
    while(next<=MaxLimit) {
        len = next;
        if (UTF8Str[len]>0xF0) next = len + 4;
        else if (UTF8Str[len]>0xE0) next = len + 3;
        else if (UTF8Str[len]>0xC0) next = len + 2;
        else if (UTF8Str[len]) next = len + 1;
        else return len; //null terminator
    }
    return len; //if next is past MaxLimit, return before that character
}

int main() {
    return !GetUTF8End("HI");
}