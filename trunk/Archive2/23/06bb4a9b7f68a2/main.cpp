bool f(int t){
    struct
    {
        int a[2];
        int b[2];
    } foo = {{1, 2}, {3, 4}};
    for(int i = 0; i <= 2; i++){
        if(foo.a[i] == t) return true;
    }
    return false;
}
int main(int argc, char* argv[])
{
    return (int)f(100);
}