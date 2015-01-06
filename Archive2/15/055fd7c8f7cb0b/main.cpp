
struct ISwearToGodIAllocatedWithNew {
    ISwearToGodIAllocatedWithNew(char* s_) : s(s_) {}
    char* s;
};

struct RawString {
    RawString(ISwearToGodIAllocatedWithNew&& t) : s(t.s) {}
    char* s;
};

int main() {
    char* t = new char[10]();
    RawString a = ISwearToGodIAllocatedWithNew(t);
}
