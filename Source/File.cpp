/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <File.h>
#include <Libs.h>

namespace File {

bool file_exists(std::string filename) {
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string read_file(std::string filename) {
    std::string value;
    std::ifstream file(filename);
    std::string str_value;
    char ac;

    if (file.is_open()) {
        while (file) {
            ac = file.get();
            value.append(1, ac);
        }
    }

    return value;
}

}