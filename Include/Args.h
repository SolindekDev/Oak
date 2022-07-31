/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__Args__H__
#define __OAK__Args__H__

#include <Libs.h>

namespace Args {

typedef struct Filename {
    bool exists;
    std::string filename;
} Filename;

class Parser {
public:
    Parser(int argc, char** argv);
    bool is_flag(std::string flag);
    Filename get_filename();
private:
    int argc;
    char** argv;
};

}

#endif /* __OAK__Args__H__ */