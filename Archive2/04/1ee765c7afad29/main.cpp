int main() 
{
    int foo, bar;
    int &choice = [&]() -> int & {
        if (true /* some condition */) {
            return foo;
        } else {
            return bar;
        }
    }();
    (void)choice; // Use choice
}