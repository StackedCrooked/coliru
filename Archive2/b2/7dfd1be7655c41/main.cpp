
struct NullPtr
{
    NullPtr(decltype(nullptr)) {}
};

struct Bool
{
    Bool(bool b) {}
};

void test(NullPtr /*p*/) {}
void test(Bool /*v*/) {}

int main(int argc, const char *argv[])
{
    test(nullptr);
    test(true);
    test(false);

    return 0;
}
