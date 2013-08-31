enum Comparison
{
    LT = __COUNTER__,     // "<"
    GT = __COUNTER__,     // ">"
    EQ = __COUNTER__,     // "=="
    LTEQ = __COUNTER__,   // "<="
    GTEQ = __COUNTER__,   // ">="
    NEQ = __COUNTER__     // "!="
};
enum Arithmetic
{
    ADD = __COUNTER__,    // "+"
    SUB = __COUNTER__,    // "-"
    MUL = __COUNTER__,    // "*"
    DIV = __COUNTER__,    // "/"
    MOD = __COUNTER__,    // "%"
};

int main() {
    Comparison first = LT;
    if (first == LT)  
        unsigned fasfdsaf = MOD;           
    //Arithmetic var = LT; //error: cannot convert ‘Comparison’ to ‘Arithmetic’ in initialization
}