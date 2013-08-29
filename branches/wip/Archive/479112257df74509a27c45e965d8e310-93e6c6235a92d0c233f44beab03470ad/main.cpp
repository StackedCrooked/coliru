#ifndef _COMPILER_AST_HPP
#define _COMPILER_AST_HPP

#include "Lexer_Position.hpp"
#include "Utility.hpp"

#include <Maybe/Maybe.hpp>

#include <string>
#include <list>
#include <utility>

/************************************************************************/
/** AST type produced by the parser                                     */
/************************************************************************/
/** PASSES JOOS1 AND JOOS2 */
namespace Ast
{
    struct identifier
    {
        identifier(std::string identifier_string, LexerPosition position = lexer_null_value)
            : position(position), identifier_string(identifier_string)
        {
        }

        LexerPosition position;
        std::string identifier_string;
    };

    struct name
    {
        protected:
            name(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~name() {}
            LexerPosition position;
    };

    typedef name namedtype;

    struct name_simple final : inherit_super<name>
    {
        name_simple(identifier name, LexerPosition position = lexer_null_value)
            : super(position), name(name)
        {
        }

        identifier name;
    };

    struct name_qualified final : inherit_super<name>
    {
        name_qualified(std::list<identifier> name, LexerPosition position = lexer_null_value)
            : super(position), name(name)
        {
        }

        std::list<identifier> name;
    };

    /* *************** Types *************** */
    struct base_type
    {
        protected:
            base_type() {}
        public:
            virtual ~base_type() {}
    };
    struct base_type_void final : inherit_super<base_type> {};
    struct base_type_byte final : inherit_super<base_type> {};
    struct base_type_short final : inherit_super<base_type> {};
    struct base_type_int final : inherit_super<base_type> {};
    struct base_type_long final : inherit_super<base_type> {};
    struct base_type_char final : inherit_super<base_type> {};
    struct base_type_float final : inherit_super<base_type> {};
    struct base_type_double final : inherit_super<base_type> {};
    struct base_type_boolean final : inherit_super<base_type> {};

    struct type_expression
    {
        protected:
            type_expression(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~type_expression() {}
            LexerPosition position;
    };

    struct type_expression_base final : inherit_super<type_expression>
    {
        type_expression_base(const base_type* type, LexerPosition position = lexer_null_value)
            : super(position), type(type)
        {
        }

        const base_type* type;
    };

    struct type_expression_tarray final : inherit_super<type_expression>
    {
        type_expression_tarray(const type_expression* type, LexerPosition position = lexer_null_value)
            : super(position), type(type)
        {
        }

        const type_expression* type;
    };

    
    struct type_expression_named final : inherit_super<type_expression>
    {
        type_expression_named(const namedtype* type, LexerPosition position = lexer_null_value)
            : super(position), type(type)
        {
        }

        const namedtype* type;
    };

    /* *************** Operators *************** */
    // Binary operators
    struct binop
    {
        protected:
            binop() {}
        public:
            virtual ~binop() {} 
    };
    // Arithmetic operators
    struct binop_plus final : inherit_super<binop> {};
    struct binop_minus final : inherit_super<binop> {};
    struct binop_times final : inherit_super<binop> {};
    struct binop_divide final : inherit_super<binop> {};
    struct binop_modulo final : inherit_super<binop> {};
    // Comparison operators
    struct binop_eq final : inherit_super<binop> {};
    struct binop_ne final : inherit_super<binop> {};
    struct binop_lt final : inherit_super<binop> {};
    struct binop_le final : inherit_super<binop> {};
    struct binop_gt final : inherit_super<binop> {};
    struct binop_ge final : inherit_super<binop> {};
    struct binop_and final : inherit_super<binop> {};
    struct binop_or final : inherit_super<binop> {};
    // Binary operators
    struct binop_xor final : inherit_super<binop> {};
    struct binop_lazyand final : inherit_super<binop> {};
    struct binop_lazyor final : inherit_super<binop> {};

    // Unary operators
    struct unop
    {
        protected:
            unop() {}
        public:
            virtual ~unop() {} 
    };
    struct unop_negate final : inherit_super<unop> {};     // minus
    struct unop_complement final : inherit_super<unop> {}; // complement

    // Increment/Decrement operators
    struct inc_dec_op
    {
        protected:
            inc_dec_op() {}
        public:
            virtual ~inc_dec_op() {} 
    };
    struct inc_dec_op_preinc final : inherit_super<inc_dec_op> {};
    struct inc_dec_op_predec final : inherit_super<inc_dec_op> {};
    struct inc_dec_op_postinc final : inherit_super<inc_dec_op> {};
    struct inc_dec_op_postdec final : inherit_super<inc_dec_op> {};

    /* *************** Expressions *************** */
    // Prototype for expression;
    struct expression;

    // L-Value
    struct lvalue
    {
        protected:
            lvalue(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~lvalue() {}
            LexerPosition position;
    };

    struct lvalue_non_static_field final : inherit_super<lvalue>
    {
        lvalue_non_static_field(const expression* exp, identifier name, LexerPosition position = lexer_null_value)
            : super(position), exp(exp), name(name)
        {
        }

        const expression* exp;
        identifier name;
    };

    struct lvalue_array final : inherit_super<lvalue>
    {
        lvalue_array(const expression* array_exp, const expression* index_exp, LexerPosition position = lexer_null_value)
            : super(position), array_exp(array_exp), index_exp(index_exp)
        {
        }

        const expression* array_exp;
        const expression* index_exp;
    };
    
    struct lvalue_ambiguous_name final : inherit_super<lvalue>
    {
        lvalue_ambiguous_name(const name* ambiguous, LexerPosition position = lexer_null_value)
            : super(position), ambiguous(ambiguous)
        {
        }

        const name* ambiguous;
    };

    // Expressions
    struct expression
    {
        protected:
            expression(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~expression() {}
            LexerPosition position;
    };

    struct expression_binop final : inherit_super<expression>
    {
        expression_binop(const expression* operand1, const binop* operatur, const expression* operand2, LexerPosition position = lexer_null_value)
            : super(position), operand1(operand1), operatur(operatur), operand2(operand2)
        {
        }

        const expression* operand1;
        const binop* operatur;
        const expression* operand2;
    };

    struct expression_unop final : inherit_super<expression>
    {
        expression_unop(const unop* operatur, const expression* operand, LexerPosition position = lexer_null_value)
            : super(position), operatur(operatur), operand(operand)
        {
        }

        const unop* operatur;
        const expression* operand;
    };

    struct expression_integer_constant final : inherit_super<expression>
    {
        expression_integer_constant(std::string value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        std::string value;
    };
    
    struct expression_character_constant final : inherit_super<expression>
    {
        expression_character_constant(std::string value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        std::string value;
    };

    struct expression_string_constant final : inherit_super<expression>
    {
        expression_string_constant(std::string value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        std::string value;
    };

    struct expression_boolean_constant final : inherit_super<expression>
    {
        expression_boolean_constant(bool value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        bool value;
    };

    struct expression_null final : inherit_super<expression>
    {
        expression_null(LexerPosition position = lexer_null_value)
            : super(position)
        {
        }
    };

    struct expression_this final : inherit_super<expression>
    {
        expression_this(LexerPosition position = lexer_null_value)
            : super(position)
        {
        }
    };

    struct expression_static_invoke final : inherit_super<expression>
    {
        expression_static_invoke(const namedtype* type, identifier method_name, std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), type(type), method_name(method_name), arguments(arguments)
        {
        }

        const namedtype* type;
        identifier method_name;
        std::list<const expression*> arguments;
    };

    struct expression_non_static_invoke final : inherit_super<expression>
    {
        expression_non_static_invoke(const expression* context, identifier method_name, std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), context(context), method_name(method_name), arguments(arguments)
        {
        }

        const expression* context;
        identifier method_name;
        std::list<const expression*> arguments;
    };

    struct expression_simple_invoke final : inherit_super<expression>
    {
        expression_simple_invoke(identifier method_name, std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), method_name(method_name), arguments(arguments)
        {
        }

        identifier method_name;
        std::list<const expression*> arguments;
    };

    struct expression_ambiguous_invoke final : inherit_super<expression>
    {
        expression_ambiguous_invoke(const name* ambiguous, identifier method_name, std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), ambiguous(ambiguous), method_name(method_name), arguments(arguments)
        {
        }

        const name* ambiguous;
        identifier method_name;
        std::list<const expression*> arguments;
    };
    
    struct expression_new final : inherit_super<expression>
    {
        expression_new(const type_expression* type, std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), type(type), arguments(arguments)
        {
        }

        const type_expression* type;
        std::list<const expression*> arguments;
    };
    
    struct expression_new_array final : inherit_super<expression>
    {
        expression_new_array(const type_expression* type, const expression* context, std::list<Maybe<const expression*>> arguments, LexerPosition position = lexer_null_value)
            : super(position), type(type), context(context), arguments(arguments)
        {
        }

        const type_expression* type;
        const expression* context;
        std::list<Maybe<const expression*>> arguments;
    };
    
    struct expression_lvalue final : inherit_super<expression>
    {
        expression_lvalue(const lvalue* variable, LexerPosition position = lexer_null_value)
            : super(position), variable(variable)
        {
        }

        const lvalue* variable;
    };
    
    struct expression_assignment final : inherit_super<expression>
    {
        expression_assignment(const lvalue* variable, const expression* value, LexerPosition position = lexer_null_value)
            : super(position), variable(variable), value(value)
        {
        }

        const lvalue* variable;
        const expression* value;
    };
    
    struct expression_incdec final : inherit_super<expression>
    {
        expression_incdec(const lvalue* variable, const inc_dec_op* operatur, LexerPosition position = lexer_null_value)
            : super(position), variable(variable), operatur(operatur)
        {
        }

        const lvalue* variable;
        const inc_dec_op* operatur;
    };
    
    struct expression_cast final : inherit_super<expression>
    {
        expression_cast(const type_expression* type, const expression* value, LexerPosition position = lexer_null_value)
            : super(position), type(type), value(value)
        {
        }

        const type_expression* type;
        const expression* value;
    };
    
    struct expression_ambiguous_cast final : inherit_super<expression>
    {
        expression_ambiguous_cast(const expression* type, const expression* value, LexerPosition position = lexer_null_value)
            : super(position), type(type), value(value)
        {
        }

        const expression* type;
        const expression* value;
    };

    struct expression_instance_of final : inherit_super<expression>
    {
        expression_instance_of(const expression* value, const type_expression* type, LexerPosition position = lexer_null_value)
            : super(position), value(value), type(type)
        {
        }

        const expression* value;
        const type_expression* type;
    };

    struct expression_parentheses final : inherit_super<expression>
    {
        expression_parentheses(const expression* inside, LexerPosition position = lexer_null_value)
            : super(position), inside(inside)
        {
        }

        const expression* inside;
    };

    /* *************** Blocks and statements *************** */
    // Prototype
    struct statement;

    typedef std::list<const statement*> block;

    struct statement
    {
        protected:
            statement(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~statement() {}
            LexerPosition position;
    };

    struct statement_expression final : inherit_super<statement>
    {
        statement_expression(const expression* value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        const expression* value;
    };

    struct statement_if_then final : inherit_super<statement>
    {
        statement_if_then(const expression* condition, const statement* true_statement, LexerPosition position = lexer_null_value)
            : super(position), condition(condition), true_statement(true_statement)
        {
        }

        const expression* condition;
        const statement* true_statement;
    };

    struct statement_if_then_else final : inherit_super<statement>
    {
        statement_if_then_else(const expression* condition, const statement* true_statement, const statement* false_statement, LexerPosition position = lexer_null_value)
            : super(position), condition(condition), true_statement(true_statement), false_statement(false_statement)
        {
        }

        const expression* condition;
        const statement* true_statement;
        const statement* false_statement;
    };
    
    struct statement_while final : inherit_super<statement>
    {
        statement_while(const expression* condition, const statement* loop_statement, LexerPosition position = lexer_null_value)
            : super(position), condition(condition), loop_statement(loop_statement)
        {
        }

        const expression* condition;
        const statement* loop_statement;
    };

    struct statement_empty final : inherit_super<statement>
    {
        statement_empty(LexerPosition position = lexer_null_value)
            : super(position)
        {
        }
    };

    struct statement_block final : inherit_super<statement>
    {
        statement_block(block body, LexerPosition position = lexer_null_value)
            : super(position), body(body)
        {
        }

        block body;
    };

    struct statement_void_return final : inherit_super<statement>
    {
        statement_void_return(LexerPosition position = lexer_null_value)
            : super(position)
        {
        }
    };

    struct statement_value_return final : inherit_super<statement>
    {
        statement_value_return(const expression* value, LexerPosition position = lexer_null_value)
            : super(position), value(value)
        {
        }

        const expression* value;
    };

    struct statement_local_declaration final : inherit_super<statement>
    {
        statement_local_declaration(const type_expression* type, identifier name, Maybe<const expression*> optional_initializer, LexerPosition position = lexer_null_value)
            : super(position), type(type), name(name), optional_initializer(optional_initializer)
        {
        }

        const type_expression* type;
        identifier name;
        Maybe<const expression*> optional_initializer;
    };

    struct statement_throw final : inherit_super<statement>
    {
        statement_throw(const expression* throwee, LexerPosition position = lexer_null_value)
            : super(position), throwee(throwee)
        {
        }

        const expression* throwee;
    };
    
    struct statement_super_call final : inherit_super<statement>
    {
        statement_super_call(std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), arguments(arguments)
        {
        }

        std::list<const expression*> arguments;
    };
    
    struct statement_this_call final : inherit_super<statement>
    {
        statement_this_call(std::list<const expression*> arguments, LexerPosition position = lexer_null_value)
            : super(position), arguments(arguments)
        {
        }

        std::list<const expression*> arguments;
    };

    typedef block body;

    /* *************** Package and imports **************** */
    typedef name package_declaration;

    struct import_declaration
    {
        protected:
            import_declaration(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~import_declaration() {}
            LexerPosition position;
    };

    struct import_declaration_on_demand final : inherit_super<import_declaration>
    {
        import_declaration_on_demand(const name* import, LexerPosition position = lexer_null_value)
            : super(position), import(import)
        {
        }

        const name* import;
    };

    struct import_declaration_single final : inherit_super<import_declaration>
    {
        import_declaration_single(const name* import, identifier class_name, LexerPosition position = lexer_null_value)
            : super(position), import(import), class_name(class_name)
        {
        }

        const name* import;
        identifier class_name;
    };

    /* *************** Field and method declarations *************** */
    struct access
    {
        protected:
            access() {}
        public:
            virtual ~access() {}
    };
    struct access_public final : inherit_super<access> {};
    struct access_protected final : inherit_super<access> {};

    typedef std::pair<const expression*, identifier> formal_parameter;

    struct field_declaration
    {
        field_declaration(const access* access_type, bool is_static, bool is_final, const type_expression* type, identifier name, Maybe<const expression*> optional_initializer)
            : access_type(access_type), is_static(is_static), is_final(is_final), type(type), name(name), optional_initializer(optional_initializer)
        {
        }

        const access* access_type;
        bool is_static;
        bool is_final;
        const type_expression* type;
        identifier name;
        Maybe<const expression*> optional_initializer;
    };

    struct method_declaration
    {
        method_declaration(const access* access_type, bool is_static, bool is_final, bool is_abstract, const type_expression* return_type, identifier name, std::list<formal_parameter> formal_parameters, std::list<const namedtype*> throws, Maybe<body> method_body)
            : access_type(access_type), is_static(is_static), is_final(is_final), is_abstract(is_abstract), return_type(return_type), name(name), formal_parameters(formal_parameters), throws(throws), method_body(method_body)
        {
        }

        const access* access_type;
        bool is_static;
        bool is_final;
        bool is_abstract;
        const type_expression* return_type;
        identifier name;
        std::list<formal_parameter> formal_parameters;
        std::list<const namedtype*> throws;
        Maybe<body> method_body;
    };

    struct constructor_declaration
    {
        constructor_declaration(const access* access_type, identifier name, std::list<formal_parameter> formal_parameters, std::list<const namedtype*> throws, Maybe<body> method_body)
            : access_type(access_type), name(name), formal_parameters(formal_parameters), throws(throws), method_body(method_body)
        {
        }

        const access* access_type;
        identifier name;
        std::list<formal_parameter> formal_parameters;
        std::list<const namedtype*> throws;
        Maybe<body> method_body;
    };

    struct declaration
    {
        protected:
            declaration(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~declaration() {}
            LexerPosition position;
    };

    struct declaration_field final : inherit_super<declaration>
    {
        declaration_field(field_declaration decl, LexerPosition position = lexer_null_value)
            : super(position), decl(decl)
        {
        }

        field_declaration decl;
    };

    struct declaration_method final : inherit_super<declaration>
    {
        declaration_method(method_declaration decl, LexerPosition position = lexer_null_value)
            : super(position), decl(decl)
        {
        }

        method_declaration decl;
    };

    struct declaration_constructor final : inherit_super<declaration>
    {
        declaration_constructor(constructor_declaration decl, LexerPosition position = lexer_null_value)
            : super(position), decl(decl)
        {
        }

        constructor_declaration decl;
    };
    /* *************** Type declarations **************** */
    struct class_declaration
    {
        class_declaration(bool is_final, bool is_abstract, identifier name, const namedtype* extends, std::list<const namedtype*> implements, std::list<const declaration*> members)
            : is_final(is_final), is_abstract(is_abstract), name(name), extends(extends), implements(implements), members(members)
        {
        }

        bool is_final;
        bool is_abstract;
        identifier name;
        const namedtype* extends;
        std::list<const namedtype*> implements;
        std::list<const declaration*> members;
    };

    struct interface_declaration
    {
        interface_declaration(identifier name, std::list<const namedtype*> extends, std::list<const declaration*> members)
            : name(name), extends(extends), members(members)
        {
        }

        identifier name;
        std::list<const namedtype*> extends;
        std::list<const declaration*> members;
    };

    struct type_declaration
    {
        protected:
            type_declaration(LexerPosition position = lexer_null_value)
                : position(position)
            {
            }
        public:
            virtual ~type_declaration() {}
            LexerPosition position;
    };

    struct type_declaration_class final : inherit_super<type_declaration>
    {
        type_declaration_class(class_declaration type, LexerPosition position = lexer_null_value)
            : super(position), type(type)
        {
        }

        class_declaration type;
    };

    struct type_declaration_interface final : inherit_super<type_declaration>
    {
        type_declaration_interface(interface_declaration type, LexerPosition position = lexer_null_value)
            : super(position), type(type)
        {
        }

        interface_declaration type;
    };

    /* *************** Programs **************** */
    struct source_file
    {
        source_file(std::string name, Maybe<const package_declaration*> package, std::list<const import_declaration*> imports, const type_declaration* type)
            : name(name), package(package), imports(imports), type(type)
        {
        }

        std::string name;
        Maybe<const package_declaration*> package;
        std::list<const import_declaration*> imports;
        const type_declaration* type;
    };

    typedef std::list<source_file> program;
}

#endif //_COMPILER_AST_HPP
