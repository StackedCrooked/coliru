
struct Gray{
    Gray(int x){}
};

template <class T1> 
struct Pixel{
    Pixel(T1 i){ foo=i; }
    T1 foo;
};


int main(){
    Gray g(4); 
    Pixel<Gray> pi(g);
    return 0;
}