SymbolicAddition operator + (int a, int b)
{
    return SymbolicAddtion(a, b);
}

int main()
{
    SymbolicAddition sym = 1 + 2;
    
    sym.toString(); // returns "1 + 2"
    sym.evaluate(); // returns 3
}
