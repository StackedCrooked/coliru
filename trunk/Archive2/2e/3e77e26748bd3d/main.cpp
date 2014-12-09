#define BUFFER_SIZE 2048
 
int main (int argc, char **argv)
{
	// Test if math works.
	_Static_assert(2 + 2 == 4, "Whoa dude!");
 
        // This will produce an error at compile time.
        _Static_assert(BUFFER_SIZE <= 1024, "BUFFER_SIZE is too big");
 
	return 0;
}