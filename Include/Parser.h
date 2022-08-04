/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

/*

    This is my first time writting parser here i save my site's that will help
    me;
    * https://stackoverflow.com/questions/28530284/generate-an-ast-in-c
    * https://www.101computing.net/abstract-syntax-tree-generator/

*/

#ifndef __OAK__Parser__H__
#define __OAK__Parser__H__

#include <Token.h>
#include <Lexer.h>
#include <Libs.h>

enum StatementKind {
    BinaryExpression,
    FunctionDeclare,
    FunctionCall,
};

typedef struct FunctionArgsAST {
  std::string name;
  Token* value;
  std::vector<FunctionArgsAST*> args;
} FunctionArgsAST;

typedef struct FunctionAST {
  std::string name;
  std::vector<StatementKind*> body;
} FunctionAST;

typedef struct CallFunctionAST {
  std::string name;
  FunctionAST* fn;
  std::vector<FunctionArgsAST*> args;
} CallFunctionAST;

typedef struct StatementAST {
  FunctionAST funcion;
  CallFunctionAST call;

  StatementKind type;
} StatementAST;

typedef struct ProgramAST {
    std::vector<StatementAST*> body;
} ProgramAST;

namespace OakParser {

class Parser {
public:
    OakLexer::Lexer* lexer;
    ProgramAST ast;
    Token* next_token;
    Token* current_token;

    bool is_error_message { 0 };
    int index { 0 };

    Token* get_next_token();

    bool is_eof();

    void advance();

    bool is_identifier_keyword(std::string value_id);

    void parse_if();
    void parse_elif();
    void parse_else();
    void parse_let();
    void parse_namespace();
    void parse_function();
    void parse_const();
    void parse_while();
    void parse_for();
    void parse_class();

    void parse_identifier();

    void parse_keyword();

    void start();

    Parser(OakLexer::Lexer* plexer)
          : lexer(plexer) {}
private:
};

}

#endif /* __OAK__Parser__H__ */
