int main() {
    using UINT16 = unsigned short;    
    UINT16 data[32];   
    static_assert(sizeof data == sizeof(UINT16) * 32, "Uh-oh");
}