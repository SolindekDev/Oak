/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Eval__H__
#define __OAK__Eval__H__

#include <Token.h>
#include <Lexer.h>
#include <AST.h>
#include <Libs.h>

namespace OakEval {

class VariableEval {
public:
    std::string name;
    std::variant<int, double, float, std::string> value;
    TokenKind type;
    bool constant;
    FunctionAST* func;

    void print();

    VariableEval(std::string _name, std::variant<int, double, float, std::string> _value, TokenKind _type, bool _constant, FunctionAST* _func)
      : name(_name)
      , value(_value)
      , type(_type)
      , constant(_constant)
      , func(_func) {}
private:
};

class Eval {
public:
    ProgramAST* program;

    VariableEval* find_var(std::string name, bool is_constant);

    void print_implementation();

    void println_implementation();

    void exit_implementation();

    void sleep_implementation();

    void system_implementation();

    void push_statement_implementation(PushStatementAST* node, FunctionAST* fn);

    void call_function_implementation(CallFunctionAST* node);

    void pop_statement_implementation(PopStatementAST* node);

    void variable_declaration_implementation(VariableDeclarationAST* node);

    void const_declaration_implementation(VariableDeclarationAST* node);

    void find_main();

    void execute_function(FunctionAST* fn);

    void is_stack_empty(std::string fn);

    void start();

    Eval(ProgramAST* eprogram)
          : program(eprogram) {}
private:
};

};

#endif /* __OAK__Eval__H__ */
