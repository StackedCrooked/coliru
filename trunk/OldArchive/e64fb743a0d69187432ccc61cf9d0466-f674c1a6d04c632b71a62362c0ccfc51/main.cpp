#ifndef _COMPILER_AST_PP_HPP
#define _COMPILER_AST_PP_HPP

#include "ast.hpp"

namespace Ast
{
    // Type expressions
    void pretty_print(const type_expression* type);
    void pretty_print(const type_expression_base type);
    void pretty_print(const type_expression_tarray type);
    void pretty_print(const type_expression_named type);
    
    // L-Value
    void pretty_print(const lvalue* exp);
    void pretty_print(const lvalue_non_static_field exp);
    void pretty_print(const lvalue_array exp);
    void pretty_print(const lvalue_ambiguous_name exp);

    // Expressions
    void pretty_print(const expression* exp);
    void pretty_print(const expression_binop exp);
    void pretty_print(const expression_unop exp);
    void pretty_print(const expression_integer_constant exp);
    void pretty_print(const expression_character_constant exp);
    void pretty_print(const expression_string_constant exp);
    void pretty_print(const expression_boolean_constant exp);
    void pretty_print(const expression_null exp);
    void pretty_print(const expression_this exp);
    void pretty_print(const expression_static_invoke exp);
    void pretty_print(const expression_non_static_invoke exp);
    void pretty_print(const expression_simple_invoke exp);
    void pretty_print(const expression_ambiguous_invoke exp);
    void pretty_print(const expression_new exp);
    void pretty_print(const expression_new_array exp);
    void pretty_print(const expression_lvalue exp);
    void pretty_print(const expression_assignment exp);
    void pretty_print(const expression_incdec exp);
    void pretty_print(const expression_cast exp);
    void pretty_print(const expression_ambiguous_cast exp);
    void pretty_print(const expression_instance_of exp);
    void pretty_print(const expression_parentheses exp);
    
    // Statements
    void pretty_print(const statement* stm);
    void pretty_print(const statement_expression stm);
    void pretty_print(const statement_if_then stm);
    void pretty_print(const statement_if_then_else stm);
    void pretty_print(const statement_while stm);
    void pretty_print(const statement_empty stm);
    void pretty_print(const statement_block stm);
    void pretty_print(const statement_void_return stm);
    void pretty_print(const statement_value_return stm);
    void pretty_print(const statement_local_declaration stm);
    void pretty_print(const statement_throw stm);
    void pretty_print(const statement_super_call stm);
    void pretty_print(const statement_this_call stm);

    // Declarations
    void pretty_print(const declaration* decl);
    void pretty_print(const declaration_field field);
    void pretty_print(const declaration_method method);
    void pretty_print(const declaration_constructor constructor);

    // Type declarations
    void pretty_print(const type_declaration* type_decl);
    void pretty_print(const type_declaration_class klass);
    void pretty_print(const type_declaration_interface interface);
    
    // Import declarations
    void pretty_print(const import_declaration* import);
    void pretty_print(const import_declaration_on_demand import);
    void pretty_print(const import_declaration_single import);

    // Package declaration
    void pretty_print(const package_declaration* package);

    // Source file
    void pretty_print(source_file sf);

    // Program
    void pretty_print(program prog);
}

#endif //_COMPILER_AST_PP_HPP