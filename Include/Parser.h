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
#include <AST.h>
#include <Libs.h>

typedef struct Precedences {
  std::string operator_;
  int left;
  int right;
} Precedences;

namespace OakParser {

class Parser {
public:
    OakLexer::Lexer* lexer;
    ProgramAST* program = new ProgramAST();
    Token* next_token;
    Token* current_token;
    Token* fn_name;

    bool is_error_message { 0 };
    bool binary_exp_open { 0 };
    bool is_fn_open { 0 };
    int index { 0 };
    int fn_declared_in_program { 0 };

    Token* get_next_token();

    Token* get_function_name();

    NumberNodeAST* number_search();

    NumberNodeAST* token_to_number_node_ast(Token* &tk);

    NumberNodeAST* parse_number();

    FunctionAST* find_fn_node();

    bool is_eof();

    bool is_math_operator();

    bool is_identifier_keyword(std::string value_id);

    void is_function_name_already_declared(std::string name);

    void append_node(NodeAST* node);

    void advance();

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

    void is_function_open();

    void is_there_brackets_to_open_function();

    void close_function();

    void start();

    Parser(OakLexer::Lexer* plexer)
          : lexer(plexer) {}
private:
};

}

#endif /* __OAK__Parser__H__ */
