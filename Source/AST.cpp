/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <AST.h>
#include <Parser.h>
#include <Libs.h>

void FunctionAST::print() {
    std::cout << "Function name: "
              << this->name->value
              << " Function body size: "
              << this->body.size()
              << std::endl;
}
