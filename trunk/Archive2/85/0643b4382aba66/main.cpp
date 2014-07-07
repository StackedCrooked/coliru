module x {
    f(totally_not_this := derived.lvalue, arg := int32) {
         std.cout << "Fail.";
    }
}
type base {
    f := x.f;
}
type base2 {
    f(arg := int64) {
        std.cout << "Success";
    }
}
type derived : base : base2 {}
Main() {
    local := derived();
    local.f(int32(0));
}