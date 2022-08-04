/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

// Include important headers
#include <Main.h>
#include <Args.h>
#include <File.h>
#include <Error.h>
#include <Token.h>
#include <Lexer.h>
#include <Parser.h>
#include <Libs.h>

// Usage, this function print out usage of oak compiler
void usage() {
    std::cout << "Usage: oak [--version] [--help] [options] [filename.oak]" << std::endl;
    exit(EXIT_SUCCESS);
}

// Detect architecture of actual machine
std::string architecture() {
    #if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
    #elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
        return "x86_32";
    #elif defined(__ARM_ARCH_2__)
        return "ARM2";
    #elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
        return "ARM3";
    #elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
        return "ARM4T";
    #elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
        return "ARM5"
    #elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
        return "ARM6T2";
    #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
        return "ARM6";
    #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7";
    #elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7A";
    #elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7R";
    #elif defined(__ARM_ARCH_7M__)
        return "ARM7M";
    #elif defined(__ARM_ARCH_7S__)
        return "ARM7S";
    #elif defined(__aarch64__) || defined(_M_ARM64)
        return "ARM64";
    #elif defined(mips) || defined(__mips__) || defined(__mips)
        return "MIPS";
    #elif defined(__sh__)
        return "SUPERH";
    #elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
        return "POWERPC";
    #elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
        return "POWERPC64";
    #elif defined(__sparc__) || defined(__sparc)
        return "SPARC";
    #elif defined(__m68k__)
        return "M68K";
    #else
        return "UNKNOWN"; // yo man you are using calculator?
    #endif
}

// Version of oak compiler, version in std::string is saved
// in OAK_VERSION property in header #include <Libs.h>.
// To get version of compiler you need to write --version
// --v flag.
void version() {
    std::cout << "oak ("
              << architecture()
              << ") "
              << OAK_VERSION
              << std::endl;
    exit(EXIT_SUCCESS);
}

// Help of oak compiler you can get it by --help or --h
// flag
void help() {
    std::cout << "Help:\n"
              << "  Flags:\n"
              << "    --h, --help           - Write down this message\n"
              << "    --v, --version        - Show version of oak compiler\n"
              << "    --s, --source-only    - Write generated code to output.cpp file\n"
              << "    --sc, --show-code-gen - Print out generated code\n"
              << "    --b, --build          - Build program to executable\n"
              << "    --br, --build-and-run - Build and run program\n\n"
              << "    --pt, --print-tokens  - Print out tokens from lexer\n\n"
              << "Usage: oak [--version] [--help] [options] [filename.oak]"
              << std::endl;
}

// Main entry of compiler.
int main(int argc, char **argv) {
    // If there's less than 2 argv
    if (argc < 2)
        usage();
    else {
        Args::Parser parser = Args::Parser(argc, argv);  // Argument parser from <Args.h> header file.
        Args::Filename filename = parser.get_filename(); // Get filename from arguments if there's no filename in arguments then filename.exists is false.

        auto source_only_flag   = parser.is_flag("--s")  || parser.is_flag("--source-only");    // Is source-only flag enabled
        auto show_code_gen_flag = parser.is_flag("--sc") || parser.is_flag("--show-code-gen");  // Is show-code-gen flag enabled
        auto build_flag         = parser.is_flag("--b")  || parser.is_flag("--build");          // Is build flag enabled
        auto build_and_run_flag = parser.is_flag("--br") || parser.is_flag("--build-and-run");  // Is build-and-run flag enabled
        auto print_tokens       = parser.is_flag("--pt") || parser.is_flag("--print-tokens");   // Is print-tokens flag enabled

        if (parser.is_flag("--version") || parser.is_flag("--v"))
            version();
        else if (parser.is_flag("--h") || parser.is_flag("--help"))
            help();
        else if (parser.is_flag("--u") || parser.is_flag("--usage"))
            usage();

        // Filename exists!!!
        if (filename.exists == true) {
            bool file_exists = File::file_exists(filename.filename); // First chceck is file existing.
            std::string value = File::read_file(filename.filename); // Read value from file by File namespace.

            // If file exists then start compiling proccess
            if (file_exists == true) {
                // Create lexer class
                auto lexer = new OakLexer::Lexer(value, filename.filename);
                lexer->start(print_tokens);

                // Create parser class
                auto parser = new OakParser::Parser(lexer);
                parser->start();
            } else
                Error::print_error_with_exit(FILE_ERROR, "File that you provided do not exists"); // The file do not exists.
        }
    }
}
