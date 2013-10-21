int main()
{
    // a bad pointer containing a custom memory address
	int *bad_pointer = reinterpret_cast<int *> (0xDEADBEEF);
	
	*bad_pointer = 5; // trying to use the pointer
}
