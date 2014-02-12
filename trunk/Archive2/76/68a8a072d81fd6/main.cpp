#include <regex>
#include <iostream>
     
using namespace std;
     
// types of operators
enum class opType: char { unary, lasso, rasso, none };
     
// operator descriptors
struct opDesc {
    string symbol;
    opType type;
    char priority;
     
    // partial order comparison
    bool operator< (const opDesc& a) const
    {
        // unary operators first
        if (symbol == a.symbol) return type < a.type;
        return symbol < a.symbol;
    }
    
    // display
    friend ostream& operator<<(ostream& os, const opDesc& op);
};
     
ostream& operator<<(ostream& os, const opDesc& op)
{
    os << op.symbol << "[" << (int)op.type << ":" << (int)op.priority << "]";
    return os;
}
     
static opDesc op_descriptors[] = {
    { "+" , opType::unary, 8 }, // unary +
    { "-" , opType::unary, 8 }, // unary -
    { "~" , opType::unary, 8 }, // bitwise not
    { "**", opType::rasso, 7 }, // power
    { "*" , opType::lasso, 6 }, // multiplication
    { "/" , opType::lasso, 6 }, // division
    { "%" , opType::lasso, 6 }, // remainder
    { "+" , opType::lasso, 5 }, // addition
    { "-" , opType::lasso, 5 }, // substraction
    { "<<", opType::lasso, 4 }, // left shift
    { ">>", opType::lasso, 4 }, // right shift
    { "&" , opType::lasso, 3 }, // bitwise and
    { "^" , opType::lasso, 2 }, // bitwise xor
    { "|" , opType::lasso, 1 }, // bitwise or
    { "(" , opType::none , 0 }, // braces
    { ")" , opType::none , 0 }
};
     
int main(void) {
    
    // sort descriptors by value and type
    sort(begin(op_descriptors), end(op_descriptors));
     
    // do some searches
    string patterns[] = { "+", "-", ">>", "**" };
     
    for (string s : patterns)
    {
        pair<opDesc*, opDesc*> ops;
        // this won't work
        
        opDesc val = { s, opType::none , 0 };
        ops = equal_range(
            std::begin(op_descriptors),
            std::end (op_descriptors),
            val);
        
        cout << s <<": "<< ops.first[0] << ops.second[-1] << endl;
    }
}
    