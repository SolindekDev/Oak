/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Error.h>
#include <Token.h>
#include <Libs.h>

namespace Error {

void print_error_with_exit(std::string title, std::string message) {
    std::cout << RED << title << RESET << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

void print_error(std::string title, std::string message) {
    std::cout << RED << title << RESET << ": " << message << std::endl;
}

void print_error_with_positional_args(std::string title, std::string message, TokenPos pos, std::string filename) {
    std::cout << RED << title << RESET << ": " << filename << ":" << pos.row+1 << ":" << pos.col << ": " << message << std::endl;
}

void todo(std::string to_implement) {
    std::cout << YELLOW << "TODO" << RESET << ": " << to_implement << "is not implemented yet" << std::endl;
}

}
