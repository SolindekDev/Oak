/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Token__H__
#define __OAK__Token__H__

#include <Libs.h>

enum TokenKind {
    // "Hello, world!"
    String,
    // 100
    Int,
    // 3.14159
    Float,
    // fn
    Identifier,
    // \n
    Newline,
    // (
    Lparen,
    // )
    Rparen,
    // +
    Plus,
    // -
    Minus,
    // /
    Divide,
    // *
    Multiply,
    // =
    Assignment,
    // \0
    Eof,
    // +=
    AddAssignment,
    // -=
    SubtractAssignment,
    // *=
    MultiplyAssignment,
    // /=
    DivideAssignment,
    // ++
    Increment,
    // --
    Decrement,
    // %
    Modulus,
    // <
    BiggerThan,
    // >
    LessThan,
    // ==
    Equals,
    // !=
    NotEquals,
    // <=
    BiggerThanOrEquals,
    // >=
    LessThanOrEquals,
    // ||
    Or,
    // &
    And,
    // !
    Bang,
    // [
    LeftBracketRectangle,
    // ]
    RightBracketRectangle,
    // {
    LeftCurlyBrackets,
    // }
    RightCurlyBrackets,
    // None
    None,
};

typedef struct TokenPos {
    int row;
    int col;
} TokenPos;

TokenPos create_pos(int row, int col);

class Token {
public:
    std::string value;
    std::string filename;
    TokenKind type;
    TokenPos pos;

    Token(std::string t_value, std::string t_filename, TokenKind t_type, TokenPos t_pos)
        : value(t_value)
        , filename(t_filename)
        , type(t_type)
        , pos(t_pos) {}

    std::string type_string();
};

#endif /* __OAK__Token__H__ */
