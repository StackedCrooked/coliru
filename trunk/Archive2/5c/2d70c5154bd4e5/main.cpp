f() {
    throw int32(1);
}
Main() {
    try {
        f();
    } catch(var := int64.lvalue) {
        std.cout << var;
    } catch(var := int32.lvalue) {
        std.cout << var;
    }
}
    