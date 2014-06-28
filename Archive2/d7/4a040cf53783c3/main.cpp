#define UINT16 unsigned short

int main() {
    UINT16 data[32];   
    static_assert(sizeof data == sizeof(UINT16) * 32, "Uh-oh");
}