#include <string>
#include <vector>
#include <stack>
#include <typeinfo>
#include <iostream>
#include <typeindex>

template<typename T>
struct Option { T* value; };

struct Identifier { std::string identifier; };

enum BaseType {
    //VOID, BYTE, SHORT,
    INT, 
    //LONG,
    //CHAR, FLOAT, DOUBLE, BOOLEAN
};

struct TypeExpression { virtual ~TypeExpression(){} };
struct Base : TypeExpression { BaseType b; };

struct BinopOperator {
    virtual int execute(int first, int second) = 0;
};

/*
EQ, NE, LT, LE, GT, GE,
AND, OR, XOR, LAZY_AND, LAZY_OR
*/

struct PLUS_OPERATOR : BinopOperator
{
    virtual int execute(int first, int second) override
    {
        return first + second;
    }
};

struct MINUS_OPERATOR : BinopOperator
{
    virtual int execute(int first, int second) override
    {
        return first - second;
    }
};

struct TIMES_OPERATOR : BinopOperator
{
    virtual int execute(int first, int second) override
    {
        return first * second;
    }
};

struct DIVIDE_OPERATOR : BinopOperator
{
    virtual int execute(int first, int second) override
    {
        return first / second;
    }
};

struct MODULO_OPERATOR : BinopOperator
{
    virtual int execute(int first, int second) override
    {
        return first % second;
    }
};

enum UnopOperator {
    NEGATE//, COMPLEMENT
};

// Expressions
struct Expression { virtual ~Expression(){} protected: Expression() {} };
struct Binop : Expression
{ 
    public:
        Binop(Expression* first_operand, BinopOperator* b_operator, Expression* second_operand)
        : first_operand(first_operand), b_operator(b_operator), second_operand(second_operand)
        {}
    
    public:
        Expression* first_operand;
        BinopOperator* b_operator;
        Expression* second_operand;
};

struct Unop : Expression { UnopOperator u_operator; Expression* operand; };

struct IntegerConstant : Expression
{
    public:
        IntegerConstant(int value)
        : value(value)
        {}
        
    public:
        int value;
};

//struct CharConstant : Expression { char value; };
//struct StringConstant : Expression { std::string value; };

struct BooleanConstant : Expression
{
    public:
        BooleanConstant(bool value)
        : value(value)
        {};
    
    public:
        bool value; 
};

struct Null : Expression {};
struct This : Expression {};

// Statements
struct Statement { virtual ~Statement(){}; protected: Statement() {} };
struct ExpressionStatement : Statement { Expression* expression; };

struct IfThen : Statement
{
    public:
        IfThen(Expression* condition, Statement* true_body)
        : condition(condition), true_body(true_body)
        {}
        
    public:
        Expression* condition;
        Statement* true_body;
};

struct IfThenElse : Statement { Expression* condition; Statement* true_body; Statement* false_body; };

struct While : Statement
{ 
    public:
        While(Expression* condition, Statement* loop_body)
        : condition(condition), loop_body(loop_body)
        {}
    
    public:
        Expression* condition;
        Statement* loop_body;
};

struct Empty : Statement {};
struct Block : Statement { std::vector<Statement*> block; };
//struct VoidReturn : Statement {};
//struct ValueReturn : Statement { Expression* return_value; };
struct LocalDeclaration : Statement { TypeExpression* type; Identifier* name; Option<Expression*> initial_value; };
//struct Throw : Statement { Expression* throw_value; };
//struct SuperCall : Statement { std::vector<Expression*> arguments; };
//struct ThisCall : Statement { std::vector<Expression*> arguments; };
struct Print : Statement
{
    public:
        Print(Expression* value_to_print)
        : value_to_print(value_to_print)
        {}
        
    public:
        Expression* value_to_print;
};

struct Environment
{
    std::stack<int> stack;
};

template<typename T, typename Input, typename Lambda_Function>
void switcher(Input stm, Environment* env, Lambda_Function lambda_func)
{
    T typed_statement = dynamic_cast<T>(stm);
    if( typed_statement != 0)
    {
        lambda_func(typed_statement, env);
    }
}

void evaluate(Expression* exp, Environment* env)
{
    switcher<BooleanConstant*>(exp, env, [](BooleanConstant* exp, Environment* env)
    {
        env->stack.push(exp->value);
    });
    switcher<IntegerConstant*>(exp, env, [](IntegerConstant* exp, Environment* env)
    {
        env->stack.push(exp->value);
    });
    switcher<Binop*>(exp, env, [](Binop* exp, Environment* env)
    {
        evaluate(exp->first_operand, env);
        int value_first_operand = env->stack.top();
        env->stack.pop();
        
        evaluate(exp->second_operand, env);
        int value_second_operand = env->stack.top();
        env->stack.pop();
        
        int combined_value = exp->b_operator->execute(value_first_operand, value_second_operand);
        env->stack.push(combined_value);
    });
}

void evaluate(Statement* stm, Environment* env)
{
    switcher<While*>(stm, env, [](While* stm, Environment* env)
    {
        while(true)
        {
            evaluate(stm->condition, env);
            int value = env->stack.top();
            env->stack.pop();
            if(value == 0)
            {
                break;
            }
            evaluate(stm->loop_body, env);
        }
    });
    switcher<IfThen*>(stm, env, [](IfThen* stm, Environment* env)
    {
        evaluate(stm->condition, env);
        int value = env->stack.top();
        env->stack.pop();
        if(value == 1)
        {
            evaluate(stm->true_body, env);
        }
    });
    switcher<Print*>(stm, env, [](Print* stm, Environment* env)
    {
        evaluate(stm->value_to_print, env);
        std::cout << env->stack.top();
        env->stack.pop();
    });
}

int main()
{
    Environment *env = new Environment();
    
    Statement *stm = new IfThen(new BooleanConstant(true), new Print(new Binop(new IntegerConstant(55), new PLUS_OPERATOR, new IntegerConstant(45))));
    evaluate(stm, env);
}