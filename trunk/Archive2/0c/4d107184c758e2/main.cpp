enum Dim2D {x2d, y2d};
enum Dim3D {x3d, y3d, z3d};

void foo(Dim3D dim)
{
    return;
}

int main(){
    Dim2D dim = x2d;
    foo(dim);
    return 0;
}