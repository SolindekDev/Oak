/*
    Oak programming langauge

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Args.h>
#include <Libs.h>

namespace Args {

Parser::Parser(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

bool Parser::is_flag(std::string flag) {
    bool to_return = false;
    for (int i = 0; i < this->argc; ++i) {
        if (this->argv[i] == flag)
            to_return = true;
    }
    return to_return;
}

// Get first argument without -- prefix
Filename Parser::get_filename() {
    Filename arg;
    arg.exists = false;
    for (int i = 1; i < this->argc; i++) {
        if (strlen(this->argv[i]) > 2) {
            if (this->argv[i][0] != '-' && this->argv[i][0] != '-') {// is prefix -- 
                arg.filename = this->argv[i];
                arg.exists = true;
                break;
            }
        }
    }
    return arg;
}

}