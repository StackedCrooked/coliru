f() {
    throw 1;
}
Main() {
    try {
        f();
    } catch(var := int64.lvalue) {
        std.cout << var;
    }
}
    