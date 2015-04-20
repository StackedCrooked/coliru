#include <string>
#include <cstdio>

class Result {
protected:
    const char *error;
public:
    Result() : error(NULL) { }
	Result(const char *e) : error(e) { }

	std::string errorString() const
	{ return error; }

	bool fail() const
	{ return error != NULL; }

	bool ok() const
	{ return error == NULL; }

	operator bool() const
	{ return error == NULL; }
};

int main()
{
    Result a1;
    Result a2("error");

    if (a1)
        printf("a1 is ok\n");
    else
        printf("a1 is not ok\n");
        
    printf("a2 is %sok\n", a2 ? "" : "not ");
    
    return 0;
}
