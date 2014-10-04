#include <wchar.h>

void foo(int)
{
}

int main()
{
    wchar_t *a=new wchar_t[2], *b=new wchar_t[2];
	size_t j;

	a[0]=b[0]='A';
	a[1]=b[1]=0;

	foo(wcscmp(a, b));
	delete[] a;
	delete[] b;

	return 0;
}
