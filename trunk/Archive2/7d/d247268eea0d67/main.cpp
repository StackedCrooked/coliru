namespace exp{
    struct M {
        int operator<<(const void *) { return 0; }
    };

    int operator<<(M&, const char*) { return 1; }
}

int main(int argc, char* argv[])
{
    return (exp::M() << "test");
}