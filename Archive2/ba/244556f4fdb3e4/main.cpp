
template<class T>
void f(const T&) { }



int main(){
    int c = 0;
    typedef int & IREF;
    IREF & c2 = c;
    //f<int &>(c);
}
