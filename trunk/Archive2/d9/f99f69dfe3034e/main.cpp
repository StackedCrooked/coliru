struct obj { };

int assign(obj&&);        // compiles if you comment this line out
int assign(const obj&);

struct foo {
    operator const obj();
};
 
int x = assign(foo());
