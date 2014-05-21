#include <iostream>
#include <algorithm>
#include <stack>

class infix_buffer : public std::streambuf
{
public:
    infix_buffer(std::streambuf* sbuf)
        : m_sbuf(sbuf),
          ctype(&std::use_facet<std::ctype<char>>(getloc()))
    { }
    
    int_type overflow(int_type c)
    {
        if (c == traits_type::eof())
        {
            while (!stack.empty())
            {
                int_type a, b;
                char_type c = operators.top(); operators.pop();
                
                a = values.top();
                values.pop();
                b = values.top();
                
                switch (char_type op = operators.top())
                {
                    
                }
            }
        }
        
        if (c != traits_type::eof())
        {
            auto it = std::find(ops.begin(), ops.end(), c);
            
            if (it != ops.end())
                operators.push(*it);
            else if (ctype->is(ctype->digit, c))
                values.push(digit);
        }
    }
private:
    std::streambuf* m_sbuf;
    std::stack<int> values;
    std::stack<int> operators;
    
    std::string ops{ '+', '-', '*', '/' };
    const std::ctype<char>* ctype;
};

int main()
{
    
}