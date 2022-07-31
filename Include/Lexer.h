/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Lexer__H__
#define __OAK__Lexer__H__

#include <Token.h>
#include <Libs.h>

#define NO_CHAR (char)0x4e4f5f43484152

namespace OakLexer {

class Lexer {
public:
    std::string value;
    std::string filename;
    int curr_row { 0 };
    int curr_col { 0 };
    char curr_char { 0 };
    int index { 0 };
    bool space { false };
    bool comment_opened_inline { false };
    bool comment_opened_multi { false };
    bool string_opened { false };
    bool is_error_message { false };

    Token* get_last_token(std::vector<Token> &tokens);

    TokenKind detect_char(char next_char);

    void add_and_create_token_char(char curr_char, std::string filename, TokenKind type, TokenPos pos, std::vector<Token> &tokens);

    char get_next_char();

    void newline(std::vector<Token> &tokens);

    void comment_inline(std::vector<Token> &tokens);

    void comment_multiline(std::vector<Token> &tokens);

    void string_creator(std::vector<Token> &tokens);

    void string_append(std::vector<Token> &tokens);

    void identifier_creator(std::vector<Token> &tokens, Token last_token);

    void number_creator(std::vector<Token> &tokens, Token last_token);

    void float_creator(std::vector<Token> &tokens, Token last_token);

    void unsupported_char();

    void print_all_tokens(std::vector<Token> &tokens);

    void is_string_ends();

    Lexer(std::string lex_value, std::string lex_filename)
        : value(lex_value)
        , filename(lex_filename) {}

    std::vector<Token> start();

    void eof(std::vector<Token> &tokens);
private:
};

}

#endif /* __OAK__Lexer__H__ */