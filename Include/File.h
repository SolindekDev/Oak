/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#ifndef __OAK__File__H__
#define __OAK__File__H__

#include <Libs.h>

namespace File {

bool file_exists(std::string filename);
std::string read_file(std::string filename);

}

#endif /* __OAK__File__H__ */