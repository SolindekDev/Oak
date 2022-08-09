/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__AST__H__
#define __OAK__AST__H__

#include <Token.h>
#include <Libs.h>

class NodeAST {
public:
    std::string type;

    NodeAST() { type = "NodeAST"; };
private:
};

class NumberNodeAST : public NodeAST {
public:
    std::variant<int, float, double> number;

    NumberNodeAST(std::variant<int, float, double> num)
      : number(num) { type = "NumberNodeAST"; }
private:
};

class FunctionAST : public NodeAST {
public:
    Token* name;
    std::vector<NodeAST*> body;

    void print();

    FunctionAST(Token* _name)
      : name(_name) { type = "FunctionAST"; }
private:
};

class PushStatementAST : public NodeAST {
public:
    Token* value_to_stack;

    void print();

    PushStatementAST(Token* &_value_to_stack)
      : value_to_stack(_value_to_stack) { type = "PushStatementAST"; }
private:
};

class CallFunctionAST : public NodeAST {
public:
    std::string function_name;
    FunctionAST* function_call;

    void print();

    CallFunctionAST(std::string _function_name, FunctionAST* _function_call)
      : function_name(_function_name)
      , function_call(_function_call) { type = "CallFunctionAST"; }
private:
};

class VariableDeclarationAST : public NodeAST {
public:
    std::string variable_name;
    std::string variable_value;
    TokenKind variable_type;
    bool is_constant;
    FunctionAST* in_function;

    void print();

    VariableDeclarationAST(std::string _variable_name, std::string _variable_value, TokenKind _variable_type, bool _is_constant, FunctionAST* _in_function)
      : variable_name(_variable_name)
      , variable_value(_variable_value)
      , variable_type(_variable_type)
      , is_constant(_is_constant)
      , in_function(_in_function) { type = "VariableDeclarationAST"; }
private:
};

class ProgramAST {
public:
    std::string type = "Program";
    std::vector<NodeAST*> body;

    ProgramAST() {};
private:
};

#endif /* __OAK__AST__H__ */
