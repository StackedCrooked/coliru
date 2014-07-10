Main() {
    local := cplusplus.std.string("Fail.", cplusplus.std.allocator(int8)());
    ref := cplusplus.std.string.lvalue(local);
    ref = "Hello, World!";
    cplusplus.std.cout << local;
}using cplusplus := cpp("/Archive2/38/e2282273b393c7/main.cpp");