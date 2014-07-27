int main(){
    int c = 0;
    typedef int & IREF;
    int & c1 = c;
    IREF & c2 = c1;
    int & & c3 = c1;
}
