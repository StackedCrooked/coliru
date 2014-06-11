f() {
    return type { x := int; y := int; }({0, 0});
}
Main() {
    local := f();
    std.cout << "x" << local.x << "y" << local.y;
}
    