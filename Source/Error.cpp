/*
    Oak programming langauge

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Error.h>
#include <Libs.h>

namespace Error {

void print_error_with_exit(std::string title, std::string message) {
    std::cout << RED << title << RESET << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

void print_error(std::string title, std::string message) {
    std::cout << RED << title << RESET << ": " << message << std::endl;
}

}