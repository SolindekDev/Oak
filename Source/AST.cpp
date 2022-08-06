/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <AST.h>
#include <Parser.h>
#include <Libs.h>

void NumberNodeAST::print() {
    std::visit([](const auto &x) {
      std::cout << x;
    }, number);
}

void MathNodeAST::print() {
    std::cout << "(";
    lhs->print();
    std::cout << operator_to_str(op);
    rhs->print();
    std::cout << ")";
}

void MathExpressionNodeAST::print() {
    for (auto &node : nodes) {
        node->print();
        std::cout << std::endl;
    }
}
