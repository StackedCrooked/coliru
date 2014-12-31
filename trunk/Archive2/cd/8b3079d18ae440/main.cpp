#define UNUSED(x) (void)x
int main()
{
    char buffer[] = "hello"; UNUSED(buffer);
    char* X = new char[3]{'h', 'i'}; UNUSED(X); // works
    //char* Y = new decltype(buffer){buffer}; UNUSED(Y);  // doesn't work
    //char* Z = new decltype(buffer){"HELLO"}; UNUSED(Z); // doesn't work
}
