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

typedef struct Program {
    std::vector<Statement
} Program;

namespace OakParser {

class Parser {
public:
    OakLexer::Lexer* lexer;

    void start();

    Parser(OakLexer::Lexer* plexer)
          : lexer(plexer) {}
private:
};

}

#endif /* __OAK__Parser__H__ */
