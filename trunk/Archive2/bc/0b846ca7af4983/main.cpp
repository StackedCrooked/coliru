// Misc

template <bool B, typename T>
struct enable_if;

template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool B, typename T, typename F>
struct enable;

template <typename T, typename F>
struct enable<true, T, F>
{
    using type = T;
};

template <typename T, typename F>
struct enable<false, T, F>
{
    using type = F;
};

// Environnement

template <typename... Entries>
struct env;

template <typename Key, typename Value>
struct pair;

template <typename Env, typename Key, typename Value>
struct env_add;

template <typename Env, typename Key>
struct env_get;

template <typename Entry, typename Env>
struct env_add_first;

template <typename Entry, typename... Entries>
struct env_add_first<Entry, env<Entries...>>
{
    using type = env<Entry, Entries...>;
};

template <typename Key, typename Value, typename V, typename... Entries>
struct env_add<env<pair<Key, V>, Entries...>, Key, Value>
{
    using type = env<pair<Key, Value>, Entries...>;
};

template <typename Key, typename Value, typename Entry, typename... Entries>
struct env_add<env<Entry, Entries...>, Key, Value>
{
    using type = typename env_add_first<Entry, typename env_add<env<Entries...>, Key, Value>::type>::type;
};

template <typename Key, typename Value>
struct env_add<env<>, Key, Value>
{
    using type = env<pair<Key, Value>>;
};

template <typename Key, typename Value, typename... Entries>
struct env_get<env<pair<Key, Value>, Entries...>, Key>
{
    using type = Value;
};

template <typename Key, typename Entry, typename... Entries>
struct env_get<env<Entry, Entries...>, Key>
{
    using type = typename env_get<env<Entries...>, Key>::type;
};

// Name

template <char... Cs>
struct name;

template <char C, typename Name>
struct name_append;

template <int I>
struct name_of_int;

template <char C, char... Cs>
struct name_append<C, name<Cs...>>
{
    using type = name<C, Cs...>;
};

template <int I>
struct name_of_int
{
    using type = name<'0' + I>;
};

// Program Input

template <typename... Args>
struct arg_list;

// Program Output
#include <iostream>

template <typename... Values>
struct stack;

template <typename Expr, typename Stack>
struct stack_push;

template <typename Stack>
struct stack_pop;

template <>
struct stack<>
{
    static void print() { }
};

template <typename Value, typename... Values>
struct stack<Value, Values...>
{
    static void print() {
        Value::print();
        std::cout << std::endl;
        stack<Values...>::print();
    }
};

template <typename Expr, typename... Es>
struct stack_push<Expr, stack<Es...>>
{
    using type = stack<Expr, Es...>;
};

template <typename E, typename... Es>
struct stack_pop<stack<E, Es...>>
{
    using type = stack<Es...>;
    using value = E;
};

// Program
template <typename... Declarations>
struct program;

template <typename... Instructions>
struct sequence;

// Déclarations

template <typename Sequence>
struct entry_point;

template <typename Name, typename Params, typename Sequence>
struct fun_decl;

template <typename... Names>
struct param_list;

// Instructions

template <typename Expr>
struct push;

struct pop;

struct stop;

template <typename Expr>
struct ret;

template <typename Name, typename Expr>
struct var_set;

template <char... Cs>
struct incr;

template <char... Cs>
struct decr;

template <typename Cond, typename T, typename F>
struct ifthenelse;

template <typename Cond, typename Sequence>
struct loop;

template <typename Cond, typename Sequence>
struct until;

template <typename Name, typename From, typename To, typename Sequence>
struct iter;

template <typename Name, typename From, typename To, typename Sequence>
struct down_iter;

// Expressions

template <typename Left, typename Right>
struct plus;

template <typename Left, typename Right>
struct minus;

template <typename Left, typename Right>
struct times;

template <typename Left, typename Right>
struct divide;

template <typename Left, typename Right>
struct modulo;

template <typename Left, typename Right>
struct equal;

template <typename Left, typename Right>
struct not_equal;

template <typename Left, typename Right>
struct sup;

template <typename Left, typename Right>
struct inf;

template <typename Left, typename Right>
struct sup_equal;

template <typename Left, typename Right>
struct inf_equal;

template <typename Left, typename Right>
struct any;

template <typename Left, typename Right>
struct both;

template <typename Left, typename Right>
struct exclusive_or;

template <typename Expr>
struct uminus;

template <typename Expr>
struct no;

template <typename Expr>
struct is_nul;

template <typename Expr>
struct is_positive;

template <typename Expr>
struct is_negative;

template <typename Expr>
struct is_strictly_positive;

template <typename Expr>
struct is_strictly_negative;

template <typename Name>
struct var_get;

template <int Argc>
struct arg_get;

template <typename Name, typename Args>
struct fun_call;

struct empty;

template <typename E, typename List>
struct cons;

template <typename List>
struct is_empty;

template <typename List>
struct length;

template <typename List>
struct head;

template <typename List>
struct tail;

template <typename Index, typename List>
struct nth;

// Variables

template <char... Cs>
struct get;

template <typename Expr, char... Cs>
struct set;

// Values
template <int N>
struct number
{
    using value = number<N>;
    
    static void print() {
        std::cout << N;
    }
};

template <bool B>
struct boolean
{
    using value = boolean<B>;
    
    static void print() {
        std::cout << (B ? "true" : "false");
    }
};

template <char... Cs>
struct str;

template <>
struct str<>
{
    using value = str<>;
    
    static void print() { }
};

template <char C, char... Cs>
struct str<C, Cs...>
{
    using value = str<C, Cs...>;
    
    static void print() {
        std::cout << C;
        str<Cs...>::print();
    }
};

template <typename... Values>
struct list;

template <>
struct list<>
{
    using value = list<>;
    
    static void print() {
        std::cout << "[]";
    }
};

template <typename Value, typename... Values>
struct list<Value, Values...>
{
    using value = list<Value, Values...>;
    
    static void print() {
        Value::print();
        std::cout << " :: ";
        list<Values...>::print();
    }
};

// Executor

template <typename Program, typename Args>
struct exec;

template <typename Env, int Id, typename... Args>
struct exec_set_args;

template <typename Stack, typename Env, typename T>
struct executor;

template <typename Stack, typename Env, typename T>
struct seq_executor;

template <typename Stack, typename Env, typename T>
struct instr_executor;

template <typename Stack, typename Env, typename Cond, typename Seq, typename RealCond>
struct loop_executor;

template <typename Env, typename Expr>
struct evaluator;

template <typename Env, typename Name, typename Args, typename Inner>
struct fun_evaluator;

template <typename Global, typename Local, typename Args, typename Params>
struct fun_evaluator_assoc_params;

template <typename Program, typename... Args>
struct exec<Program, arg_list<Args...>>
{
    using env_t = typename exec_set_args<env<>, 0, Args...>::type;
    using type = typename executor<stack<>, env_t, Program>::type;
};

template <typename Env, int Id>
struct exec_set_args<Env, Id>
{
    using type = Env;
};

template <typename Env, int Id, typename Arg, typename... Args>
struct exec_set_args<Env, Id, Arg, Args...>
{
    using name_t = typename name_of_int<Id>::type;
    using env_t = typename env_add<Env, name_t, Arg>::type;
    using type = typename exec_set_args<env_t, Id + 1, Args...>::type;
};

template <typename Stack, typename Env>
struct executor<Stack, Env, program<>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename Name, typename Params, typename Sequence, typename... Declarations>
struct executor<Stack, Env, program<fun_decl<Name, Params, Sequence>, Declarations...>>
{
    using new_env_t = typename env_add<Env, Name, pair<Params, Sequence>>::type;
    using type = typename executor<Stack, new_env_t, program<Declarations...>>::type;
    using env = typename executor<Stack, new_env_t, program<Declarations...>>::env;
};

template <typename Stack, typename Env, typename Sequence>
struct executor<Stack, Env, program<entry_point<Sequence>>>
{
    using type = typename seq_executor<Stack, Env, Sequence>::type;
    using env = typename seq_executor<Stack, Env, Sequence>::env;
};

template <typename Stack, typename Env>
struct seq_executor<Stack, Env, sequence<>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename... Instructions>
struct seq_executor<Stack, Env, sequence<stop, Instructions...>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename Expr, typename... Instructions>
struct seq_executor<Stack, Env, sequence<ret<Expr>, Instructions...>>
{
    using type = Stack;
    using expr_value_t = typename evaluator<Env, Expr>::value;
    using env = typename env_add<Env, name<'r', 'e', 't', 'u', 'r', 'n'>, expr_value_t>::type;
};

template <typename Stack, typename Env, typename Instruction, typename... Instructions>
struct seq_executor<Stack, Env, sequence<Instruction, Instructions...>>
{
    using new_stack_t = typename instr_executor<Stack, Env, Instruction>::type;
    using new_env_t = typename instr_executor<Stack, Env, Instruction>::env;
    using type = typename seq_executor<new_stack_t, new_env_t, sequence<Instructions...>>::type;
    using env = typename seq_executor<new_stack_t, new_env_t, sequence<Instructions...>>::env;
};

template <typename Stack, typename Env, typename Expr>
struct instr_executor<Stack, Env, push<Expr>>
{
    using expr = typename evaluator<Env, Expr>::value;
    using type = typename stack_push<expr, Stack>::type;
    using env = Env;
};

template <typename Stack, typename Env>
struct instr_executor<Stack, Env, pop>
{
    using type = typename stack_pop<Stack>::type;
    using value = typename stack_pop<Stack>::value;
    using env = Env;
};

template <typename Stack, typename Env, typename Name, typename Expr>
struct instr_executor<Stack, Env, var_set<Name, Expr>>
{
    using subvalue_t = typename evaluator<Env, Expr>::value;
    using type = Stack;
    using env = typename env_add<Env, Name, subvalue_t>::type;
};

template <typename Stack, typename Env, char... Cs>
struct instr_executor<Stack, Env, incr<Cs...>>
{
    using value = typename env_get<Env, name<Cs...>>::type;
    using new_value = typename evaluator<Env, plus<value, number<1>>>::value;
    using type = Stack;
    using env = typename env_add<Env, name<Cs...>, new_value>::type;
};

template <typename Stack, typename Env, char... Cs>
struct instr_executor<Stack, Env, decr<Cs...>>
{
    using value = typename env_get<Env, name<Cs...>>::type;
    using new_value = typename evaluator<Env, minus<value, number<1>>>::value;
    using type = Stack;
    using env = typename env_add<Env, name<Cs...>, new_value>::type;
};

template <typename Stack, typename Env, typename Cond, typename T, typename F>
struct instr_executor<Stack, Env, ifthenelse<Cond, T, F>>
{
    using cond_value_t = typename evaluator<Env, Cond>::value;
    using type = typename instr_executor<Stack, Env, ifthenelse<cond_value_t, T, F>>::type;
    using env = typename instr_executor<Stack, Env, ifthenelse<cond_value_t, T, F>>::env;
};

template <typename Stack, typename Env, typename T, typename F>
struct instr_executor<Stack, Env, ifthenelse<boolean<true>, T, F>>
{
    using type = typename seq_executor<Stack, Env, T>::type;
    using env = typename seq_executor<Stack, Env, T>::env;
};

template <typename Stack, typename Env, typename T, typename F>
struct instr_executor<Stack, Env, ifthenelse<boolean<false>, T, F>>
{
    using type = typename seq_executor<Stack, Env, F>::type;
    using env = typename seq_executor<Stack, Env, F>::env;
};

template <typename Stack, typename Env, typename Cond, typename Seq>
struct instr_executor<Stack, Env, loop<Cond, Seq>>
{
    using cond_value_t = typename evaluator<Env, Cond>::value;
    using type = typename loop_executor<Stack, Env, Cond, Seq, cond_value_t>::type;
    using env = typename loop_executor<Stack, Env, Cond, Seq, cond_value_t>::env;
};

template <typename Stack, typename Env, typename Cond, typename Seq>
struct instr_executor<Stack, Env, until<Cond, Seq>>
{
    using type = typename instr_executor<Stack, Env, loop<no<Cond>, Seq>>::type;
    using env = typename instr_executor<Stack, Env, loop<no<Cond>, Seq>>::env;
};

template <typename Stack, typename Env, template <typename, typename, typename, typename> class Iter, typename Name, typename From, typename To, typename Seq>
struct instr_executor<Stack, Env, Iter<Name, From, To, Seq>>
{
    using from_t = typename evaluator<Env, From>::value;
    using to_t = typename evaluator<Env, To>::value;
    using type = typename instr_executor<Stack, Env, iter<Name, from_t, to_t, Seq>>::type;
    using env = typename instr_executor<Stack, Env, iter<Name, from_t, to_t, Seq>>::env;
};

template <typename Stack, typename Env, typename Name, int From, int To, typename Seq>
struct instr_executor<Stack, Env, iter<Name, number<From>, number<To>, Seq>>
{
    using env_with_var = typename env_add<Env, Name, number<From>>::type;
    using seq_type = typename seq_executor<Stack, env_with_var, Seq>::type;
    using seq_env = typename seq_executor<Stack, env_with_var, Seq>::env;
    using type = typename instr_executor<seq_type, seq_env, iter<Name, number<From + 1>, number<To>, Seq>>::type;
    using env = typename instr_executor<seq_type, seq_env, iter<Name, number<From + 1>, number<To>, Seq>>::env;
};

template <typename Stack, typename Env, typename Name, int From, int To, typename Seq>
struct instr_executor<Stack, Env, down_iter<Name, number<From>, number<To>, Seq>>
{
    using env_with_var = typename env_add<Env, Name, number<From>>::type;
    using seq_type = typename seq_executor<Stack, env_with_var, Seq>::type;
    using seq_env = typename seq_executor<Stack, env_with_var, Seq>::env;
    using type = typename instr_executor<seq_type, seq_env, down_iter<Name, number<From - 1>, number<To>, Seq>>::type;
    using env = typename instr_executor<seq_type, seq_env, down_iter<Name, number<From - 1>, number<To>, Seq>>::env;
};

template <typename Stack, typename Env, typename Name, int To, typename Seq>
struct instr_executor<Stack, Env, iter<Name, number<To + 1>, number<To>, Seq>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename Name, int To, typename Seq>
struct instr_executor<Stack, Env, down_iter<Name, number<To - 1>, number<To>, Seq>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename Expr, char... Cs>
struct instr_executor<Stack, Env, set<Expr, Cs...>>
{
    using type = Stack;
    using value_t = typename evaluator<Env, Expr>::value;
    using env = typename env_add<Env, name<Cs...>, value_t>::type;
};

template <typename Stack, typename Env, typename Cond, typename Seq>
struct loop_executor<Stack, Env, Cond, Seq, boolean<false>>
{
    using type = Stack;
    using env = Env;
};

template <typename Stack, typename Env, typename Cond, typename Seq>
struct loop_executor<Stack, Env, Cond, Seq, boolean<true>>
{
    using sub_type = typename seq_executor<Stack, Env, Seq>::type;
    using sub_env = typename seq_executor<Stack, Env, Seq>::env;
    
    using cond_value_t = typename evaluator<sub_env, Cond>::value;
    
    using type = typename loop_executor<sub_type, sub_env, Cond, Seq, cond_value_t>::type;
    using env = typename loop_executor<sub_type, sub_env, Cond, Seq, cond_value_t>::env;
};

template <typename Env, int A, int B>
struct evaluator<Env, plus<number<A>, number<B>>>
{
    using value = number<A + B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, minus<number<A>, number<B>>>
{
    using value = number<A - B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, times<number<A>, number<B>>>
{
    using value = number<A * B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, divide<number<A>, number<B>>>
{
    using value = number<A / B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, modulo<number<A>, number<B>>>
{
    using value = number<A % B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, equal<number<A>, number<B>>>
{
    using value = boolean<A == B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, not_equal<number<A>, number<B>>>
{
    using value = boolean<A != B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, sup<number<A>, number<B>>>
{
    using value = boolean<(A > B)>;
};

template <typename Env, int A, int B>
struct evaluator<Env, inf<number<A>, number<B>>>
{
    using value = boolean<A < B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, sup_equal<number<A>, number<B>>>
{
    using value = boolean<A >= B>;
};

template <typename Env, int A, int B>
struct evaluator<Env, inf_equal<number<A>, number<B>>>
{
    using value = boolean<A <= B>;
};

template <typename Env, bool A, bool B>
struct evaluator<Env, any<boolean<A>, boolean<B>>>
{
    using value = boolean<A || B>;
};

template <typename Env, bool A, bool B>
struct evaluator<Env, both<boolean<A>, boolean<B>>>
{
    using value = boolean<A && B>;
};

template <typename Env, bool A, bool B>
struct evaluator<Env, exclusive_or<boolean<A>, boolean<B>>>
{
    using value = boolean<(A && !B) || (!A && B)>;
};

template <typename Env, int N>
struct evaluator<Env, uminus<number<N>>>
{
    using value = number<-N>;
};

template <typename Env, bool B>
struct evaluator<Env, no<boolean<B>>>
{
    using value = boolean<!B>;
};

template <typename Env, int N>
struct evaluator<Env, is_nul<number<N>>>
{
    using value = boolean<N == 0>;
};

template <typename Env, int N>
struct evaluator<Env, is_positive<number<N>>>
{
    using value = boolean<N >= 0>;
};

template <typename Env, int N>
struct evaluator<Env, is_negative<number<N>>>
{
    using value = boolean<N <= 0>;
};

template <typename Env, int N>
struct evaluator<Env, is_strictly_positive<number<N>>>
{
    using value = boolean<(N > 0)>;
};

template <typename Env, int N>
struct evaluator<Env, is_strictly_negative<number<N>>>
{
    using value = boolean<N < 0>;
};

template <typename Env, template <typename, typename> class Operator, typename A, typename B>
struct evaluator<Env, Operator<A, B>>
{
    using value_a = typename evaluator<Env, A>::value;
    using value_b = typename evaluator<Env, B>::value;
    using value = typename evaluator<Env, Operator<value_a, value_b>>::value;
};

template <typename Env, template <typename> class Operator, typename E>
struct evaluator<Env, Operator<E>>
{
    using sub_value = typename evaluator<Env, E>::value;
    using value = typename evaluator<Env, Operator<sub_value>>::value;
};

template <typename Env, typename Name>
struct evaluator<Env, var_get<Name>>
{
    using value = typename env_get<Env, Name>::type;
};

template <typename Env, int Argc>
struct evaluator<Env, arg_get<Argc>>
{
    using value = typename env_get<Env, typename name_of_int<Argc>::type>::type;
};

template <typename Env, typename Name, typename Args>
struct evaluator<Env, fun_call<Name, Args>>
{
    using value = typename fun_evaluator<Env, Name, Args, typename env_get<Env, Name>::type>::value;
};

template <typename Env>
struct evaluator<Env, empty>
{
    using value = list<>;
};

template <typename Env, typename E, typename... Es>
struct evaluator<Env, cons<E, list<Es...>>>
{
    using e_t = typename evaluator<Env, E>::value;
    using value = list<e_t, Es...>;
};

template <typename Env>
struct evaluator<Env, is_empty<list<>>>
{
    using value = boolean<true>;
};

template <typename Env, typename... Values>
struct evaluator<Env, is_empty<list<Values...>>>
{
    using value = boolean<false>;
};

template <typename Env>
struct evaluator<Env, length<list<>>>
{
    using value = number<0>;
};

template <typename Env, typename Value, typename... Values>
struct evaluator<Env, length<list<Value, Values...>>>
{
    using tail_length = typename evaluator<Env, length<list<Values...>>>::value;
    using value = typename evaluator<Env, plus<tail_length, number<1>>>::value;
};

template <typename Env, typename Value, typename... Values>
struct evaluator<Env, head<list<Value, Values...>>>
{
    using value = Value;
};

template <typename Env, typename Value, typename... Values>
struct evaluator<Env, tail<list<Value, Values...>>>
{
    using value = list<Values...>;
};

template <typename Env, typename Value, typename... Values>
struct evaluator<Env, nth<number<0>, list<Value, Values...>>>
{
    using value = Value;
};

template <typename Env, int Index, typename Value, typename... Values>
struct evaluator<Env, nth<number<Index>, list<Value, Values...>>>
{
    using value = typename evaluator<Env, nth<number<Index - 1>, list<Values...>>>::value;
};

template <typename Env, char... Cs>
struct evaluator<Env, get<Cs...>>
{
    using value = typename env_get<Env, name<Cs...>>::type;
};

template <typename Env, typename Name, typename Args, typename Params, typename Sequence>
struct fun_evaluator<Env, Name, Args, pair<Params, Sequence>>
{
    using recursive_env_t = typename env_add<env<>, Name, pair<Params, Sequence>>::type;
    using local_env_t = typename fun_evaluator_assoc_params<Env, recursive_env_t, Args, Params>::env;
    using result_env_t = typename seq_executor<stack<>, local_env_t, Sequence>::env;
    using value = typename env_get<result_env_t, name<'r', 'e', 't', 'u', 'r', 'n'>>::type;
};

template <typename Global, typename Local, typename FirstArg, typename... Args, typename FirstParam, typename... Params>
struct fun_evaluator_assoc_params<Global, Local, arg_list<FirstArg, Args...>, param_list<FirstParam, Params...>>
{
    using arg_value_t = typename evaluator<Global, FirstArg>::value;
    using new_local_t = typename env_add<Local, FirstParam, arg_value_t>::type;
    using env = typename fun_evaluator_assoc_params<Global, new_local_t, arg_list<Args...>, param_list<Params...>>::env;
};

template <typename Global, typename Local>
struct fun_evaluator_assoc_params<Global, Local, arg_list<>, param_list<>>
{
    using env = Local;
};

template <typename Env, int N>
struct evaluator<Env, number<N>>
{
    using value = number<N>;
};

template <typename Env, bool B>
struct evaluator<Env, boolean<B>>
{
    using value = boolean<B>;
};

template <typename Env, char... Cs>
struct evaluator<Env, str<Cs...>>
{
    using value = str<Cs...>;
};

template <typename Env, typename... Values>
struct evaluator<Env, list<Values...>>
{
    using value = list<Values...>;
};

// Test

int
main()
{
    using prog = program<
        fun_decl<
            name<'f', 'i', 'b', 'o', 'n', 'a', 'c', 'c', 'i'>,
            param_list<name<'n'>>,
            sequence<
                var_set<name<'a'>, number<1>>,
                var_set<name<'b'>, number<0>>,
                iter<
                    name<'i'>,
                    number<1>,
                    get<'n'>,
                    sequence<
                        var_set<name<'t'>, get<'b'>>,
                        var_set<name<'b'>, get<'a'>>,
                        var_set<name<'a'>, plus<get<'a'>, get<'t'>>>
                    >
                >,
                ret<get<'b'>>
            >
        >,
        fun_decl<
            name<'f', 'a', 'c', 't', 'o', 'r', 'i', 'a', 'l'>,
            param_list<name<'n'>>,
            sequence<
                ifthenelse<
                    is_nul<var_get<name<'n'>>>,
                    sequence<ret<number<1>>>,
                    sequence<ret<
                        times<
                            var_get<name<'n'>>,
                            fun_call<
                                name<'f', 'a', 'c', 't', 'o', 'r', 'i', 'a', 'l'>,
                                arg_list<minus<
                                    var_get<name<'n'>>,
                                    number<1>
                                >>
                            >
                        >
                    >>
                >
            >
        >,
        fun_decl<
            name<'a', 'c', 'k', 'e', 'r', 'm', 'a', 'n', 'n'>,
            param_list<
                name<'m'>,
                name<'n'>
            >,
            sequence<
                ifthenelse<
                    is_nul<get<'m'>>,
                    sequence<
                        ret<plus<
                            get<'n'>,
                            number<1>
                        >>
                    >,
                    sequence<
                        ifthenelse<
                            is_nul<get<'n'>>,
                            sequence<
                                ret<fun_call<
                                    name<'a', 'c', 'k', 'e', 'r', 'm', 'a', 'n', 'n'>,
                                    arg_list<
                                        minus<get<'m'>, number<1>>,
                                        number<1>
                                    >
                                >>
                            >,
                            sequence<
                                ret<fun_call<
                                    name<'a', 'c', 'k', 'e', 'r', 'm', 'a', 'n', 'n'>,
                                    arg_list<
                                        minus<get<'m'>, number<1>>,
                                        fun_call<
                                            name<'a', 'c', 'k', 'e', 'r', 'm', 'a', 'n', 'n'>,
                                            arg_list<
                                                get<'m'>,
                                                minus<get<'n'>, number<1>>
                                            >
                                        >
                                    >
                                >>
                            >
                        >
                    >
                >
            >
        >,
        fun_decl<
            name<'h', 'e', 'l', 'l', 'o', '_', 'w', 'o', 'r', 'l', 'd'>,
            param_list<>,
            sequence<
                ret<str<'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'>>
            >
        >,
        entry_point<sequence<
            push<fun_call<
                name<'f', 'i', 'b', 'o', 'n', 'a', 'c', 'c', 'i'>,
                arg_list<arg_get<0>>
            >>,
            push<fun_call<
                name<'f', 'a', 'c', 't', 'o', 'r', 'i', 'a', 'l'>,
                arg_list<arg_get<0>>
            >>,
            push<fun_call<
                name<'a', 'c', 'k', 'e', 'r', 'm', 'a', 'n', 'n'>,
                arg_list<
                    arg_get<2>,
                    arg_get<3>
                >
            >>,
            push<fun_call<
                name<'h', 'e', 'l', 'l', 'o', '_', 'w', 'o', 'r', 'l', 'd'>,
                arg_list<>
            >>
        >>
    >;
    
    using result = typename exec<
        prog,
        arg_list<
            number<8>,
            number<6>,
            number<3>,
            number<3>
        >
    >::type;
    
    result::print();
}
