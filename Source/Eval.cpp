/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Eval.h>
#include <Parser.h>
#include <Token.h>
#include <Error.h>
#include <AST.h>
#include <Libs.h>

namespace OakEval {

void Eval::print_implementation(std::string value) {
    std::cout << value;
}

void Eval::println_implementation(std::string value) {
    std::cout << value << std::endl;
}

void Eval::start() {
    // TODO
}

};
