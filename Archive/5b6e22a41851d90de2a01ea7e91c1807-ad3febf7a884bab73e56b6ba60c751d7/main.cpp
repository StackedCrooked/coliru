

int main()
{
    int i = 0;    
    int& i_ref = [](int& n) { return n; }(i);
}
