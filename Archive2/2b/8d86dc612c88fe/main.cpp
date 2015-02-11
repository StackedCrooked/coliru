define void @main(i32 %n, void(i32*)* %f) {
    %a = alloca i32, i32 %n
    call void %f(i32* %a)
    unreachable
}