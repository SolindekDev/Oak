/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Error__H__
#define __OAK__Error__H__

#include <Token.h>
#include <Libs.h>

#define RESET "\e[0m"
#define RED "\e[0;31m"

#define SYNTAX_ERROR (std::string)"SyntaxError"
#define FILE_ERROR (std::string)"FileError"
#define UNSUPPORTED_CHAR (std::string)"UnsupportedChar"

namespace Error {

void print_error_with_exit(std::string title, std::string message);
void print_error(std::string title, std::string message);
void print_error_with_positional_args(std::string title, std::string message, TokenPos pos, std::string filename);

}

#endif /* __OAK__Error__H__ */