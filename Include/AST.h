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
    std::string type;
    std::vector<std::any> nodes;

    virtual void print() {};

    NodeAST() {};
private:
};

class NumberNodeAST : public NodeAST {
public:
    std::variant<int, float, double> number;

    void print();

    NumberNodeAST(std::variant<int, float, double> num)
      : number(num) { type = "NumberNodeAST"; }
private:
};

class MathNodeAST : public NodeAST {
public:
    NumberNodeAST* lhs;
    NumberNodeAST* rhs;
    TokenKind op;
    bool end_to_last;

    void print();

    MathNodeAST(NumberNodeAST* _lhs, NumberNodeAST* _rhs, TokenKind _op)
        : lhs(_lhs)
        , rhs(_rhs)
        , op(_op) { type = "MathNodeAST"; }
private:
};

class MathExpressionNodeAST : public NodeAST {
public:
    std::vector<MathNodeAST*> nodes;

    void print();

    MathExpressionNodeAST() { type = "MathExpressionNodeAST"; };
private:
};

class ProgramAST {
public:
    std::string type = "Program";
    std::vector<NodeAST*> body;

    ProgramAST() {};
private:
};

#endif /* __OAK__AST__H__ */
