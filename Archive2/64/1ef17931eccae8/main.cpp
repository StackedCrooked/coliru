f() {
    throw true;
}
Main() {
    try {
        f();
    } catch(var := int64.lvalue) {
        std.cout << var;
    } catch(var := bool.lvalue) {
        std.cout << var;
    }
}
    