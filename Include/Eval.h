/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Eval__H__
#define __OAK__Eval__H__

#include <Token.h>
#include <Lexer.h>
#include <AST.h>
#include <Libs.h>

namespace OakEval {

class Eval {
public:
    ProgramAST* program;

    void print_implementation();

    void println_implementation();

<<<<<<< HEAD
    void push_statement_implementation(PushStatementAST* node);

    void call_function_implementation(CallFunctionAST* node);

    void find_main();

    void execute_main(FunctionAST* fn);

=======
>>>>>>> 1d0324510ff6cf9ced96c3d2f99d440d2ecff3f7
    void start();

    Eval(ProgramAST* eprogram)
          : program(eprogram) {}
private:
};

};

#endif /* __OAK__Eval__H__ */
