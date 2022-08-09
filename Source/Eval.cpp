/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Eval.h>
#include <Parser.h>
#include <Token.h>
#include <Error.h>
#include <AST.h>
#include <Utils.h>
#include <Libs.h>

namespace OakEval {

std::vector<std::variant<int, float, std::string, double>> stack;

void Eval::print_implementation() {
    std::visit([](const auto &x) {
        try {
            auto get_str = std::get<std::string>(stack.at(stack.size() - 1));
            auto replaced = Utils::replace_all(get_str, std::string("\\n"), std::string("\n"));
            replaced = Utils::replace_all(replaced, std::string("\\t"), std::string("\t"));
            replaced = Utils::replace_all(replaced, std::string("\\\\"), std::string("\\"));
            std::cout << replaced;
        } catch (const std::bad_variant_access& ex) {
            std::cout << x;
        }
    }, stack.at(stack.size() - 1));
}

void Eval::println_implementation() {
    std::visit([](const auto &x) {
        try {
            auto get_str = std::get<std::string>(stack.at(stack.size() - 1));
            auto replaced = Utils::replace_all(get_str, std::string("\\n"), std::string("\n"));
            replaced = Utils::replace_all(replaced, std::string("\\t"), std::string("\t"));
            replaced = Utils::replace_all(replaced, std::string("\\\\"), std::string("\\"));
            std::cout << replaced << std::endl;
        } catch (const std::bad_variant_access& ex) {
            std::cout << x << std::endl;
        }
    }, stack.at(stack.size() - 1));
}

void Eval::push_statement_implementation(PushStatementAST* node) {
    if (node->value_to_stack->type == TokenKind::Int ||
        node->value_to_stack->type == TokenKind::Float) {
          if (node->value_to_stack->value.find('.') != std::string::npos)
              stack.push_back(std::stod(node->value_to_stack->value));
          else if (node->value_to_stack->value.find('o') != std::string::npos)
              Error::todo("octal in math operations ");
          else if (node->value_to_stack->value.find('x') != std::string::npos)
              Error::todo("hexadecimal in math operations ");
          else if (node->value_to_stack->value.find('b') != std::string::npos)
              Error::todo("binary in math operations ");
          else
              stack.push_back(std::stoi(node->value_to_stack->value));
    } else if (node->value_to_stack->type == TokenKind::String) {
        stack.push_back(node->value_to_stack->value);
    }
}

void Eval::call_function_implementation(CallFunctionAST* node) {
    if (node->function_name == "print" || node->function_name == "puts") {
        this->print_implementation();
    } else if (node->function_name == "println") {
        this->println_implementation();
    } else {
        execute_function(node->function_call);
    }
}

void Eval::execute_function(FunctionAST* fn) {
    for (auto& node : fn->body) {
        if (node->type == "PushStatementAST")
            push_statement_implementation((PushStatementAST*)node);
        else if (node->type == "CallFunctionAST")
            call_function_implementation((CallFunctionAST*)node);
    }
}

void Eval::find_main() {
    for (auto& node : this->program->body) {
        if (node->type == "FunctionAST") {
            if (((FunctionAST*)node)->name->value == "main")
                this->execute_function((FunctionAST*)node);
        } else
            Error::todo("eval: node evaluation ");
    }
}

void Eval::start() {
    // Search for main function and start eval it
    find_main();
}

};
