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
    NodeAST() {};

    virtual void print() {};
private:
};

class NumberNodeAST : public NodeAST {
public:
    std::variant<int, float, double> number;

    void print();

    NumberNodeAST(std::variant<int, float, double> num)
      : number(num) {}
private:
};

class MathNodeAST : public NodeAST {
public:
    NumberNodeAST* lhs;
    NumberNodeAST* rhs;
    TokenKind op;

    void print();

    MathNodeAST(NumberNodeAST* _lhs, NumberNodeAST* _rhs, TokenKind _op)
        : lhs(_lhs)
        , rhs(_rhs)
        , op(_op) {}
private:
};

class MathExpressionNodeAST : public NodeAST {
public:
    std::vector<MathNodeAST*> nodes;

    void print();

    MathExpressionNodeAST() {};
private:
};

class ProgramAST {
public:
    std::vector<NodeAST*> body;

    ProgramAST() {};
private:
};

#endif /* __OAK__AST__H__ */
