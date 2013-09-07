struct test {
    int x;
    test() try : x{123} {
    }
    catch (...) {
    }
};

int main() {}
