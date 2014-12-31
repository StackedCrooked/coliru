#include <iostream>
int main()
{
    FILE *f1;
	f1 = fopen("data.bin", "wb");

	for (int i = 0; i < 268435456; ++i)
	{
		fwrite(&i, sizeof(i), 1, f1);
	}
	fclose();
		

	return 0;
}