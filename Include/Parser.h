/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Parser__H__
#define __OAK__Parser__H__

#include <Token.h>
#include <Lexer.h>
#include <Libs.h>

namespace OakParser {

class Parser {
public:
    OakLexer::Lexer lexer;

    void start();

    Parser(OakLexer::Lexer plexer)
          : lexer(plexer) {}
private:
};

}

#endif /* __OAK__Parser__H__ */
