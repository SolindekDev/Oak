/*
    Oak programming language
    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Lexer.h>
#include <Token.h>
#include <Error.h>
#include <Libs.h>

namespace OakLexer {

std::string identifier_constant = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_?@";
std::string number_constant = "0123456789";

Token* Lexer::get_last_token(std::vector<Token> &tokens) {
    if (tokens.size() == 0)
        return new Token("", this->filename, TokenKind::None, create_pos(0,0));
    else
        return &(tokens[tokens.size() - 1]);
}

void Lexer::newline(std::vector<Token> &tokens) {
    auto before_col = this->curr_col;
    this->space = true;
    this->comment_opened_inline = false;
    this->curr_row++;
    this->curr_col = 0;
    tokens.push_back(
        *(
            new Token("\0", this->filename, TokenKind::Newline, create_pos(this->curr_row, before_col)
        )
    ));
}

void Lexer::comment_inline(std::vector<Token> &tokens) {
    if (this->string_opened == true)
        tokens[tokens.size() - 1].value += this->curr_char;
    else
        this->comment_opened_inline = true;
}

void Lexer::comment_multiline(std::vector<Token> &tokens) {
    if (this->string_opened == true)
        tokens[tokens.size() - 1].value += this->curr_char;
    else {
        if (this->comment_opened_multi == false) {
            this->comment_opened_multi = true;
        } else {
            this->comment_opened_multi = false;
        }
    }
}

void Lexer::string_creator(std::vector<Token> &tokens) {
    if (this->string_opened == true) 
        this->string_opened = false;
    else {
        tokens.push_back(
            *(
                new Token("", this->filename, TokenKind::String, create_pos(this->curr_row, this->curr_row)
            )
        ));
        this->string_opened = true;
    }
}

void Lexer::string_append(std::vector<Token> &tokens) {
    tokens[tokens.size() - 1].value += this->curr_char;
}

TokenKind Lexer::detect_char(char next_char) {
    switch (this->curr_char) {
        case '\n':
            return TokenKind::Newline; // \n
        case '(':
            return TokenKind::Lparen; // (
        case ')':
            return TokenKind::Rparen; // )
        case '+':
            if (next_char != (char)6019 && next_char == '=') { // +=
                this->index++;
                this->do_next_char();
                return TokenKind::AddAssignment;
            }
            if (next_char != (char)6019 && next_char == '+') { // ++
                this->index++;
                this->do_next_char();
                return TokenKind::Increment;
            }
            return TokenKind::Plus; // +
        case '-':
            if (next_char != (char)6019 && next_char == '=') { // -=
                this->index++;
                this->do_next_char();
                return TokenKind::SubtractAssignment;
            }
            if (next_char != (char)6019 && next_char == '-') { // --
                this->index++;
                this->do_next_char();
                return TokenKind::Increment;
            }
            return TokenKind::Minus; // -
        case '%':
            return TokenKind::Modulus; // %
        case '>':
            if (next_char != (char)6019 && next_char == '=') { // >=
                this->index++;
                this->do_next_char();
                return TokenKind::BiggerThanOrEquals;
            }
            return TokenKind::BiggerThan; // >
        case '<':
            return TokenKind::LessThan; // <
        case '*':
            if (next_char != (char)6019 && next_char == '=') { // *=
                this->index++;
                this->do_next_char();
                return TokenKind::MultiplyAssignment;
            }
            return TokenKind::Multiply; // *
        case '/':
            if (next_char != (char)6019 && next_char == '=') { // /=
                this->index++;
                this->do_next_char();
                return TokenKind::DivideAssignment;
            }
            return TokenKind::Divide; // /
        case '=':
            if (next_char != (char)6019 && next_char == '=') { // ==
                std::cout << "creating equals token" << std::endl;
                this->index++;
                this->do_next_char();
                return TokenKind::Equals;
            }
            return TokenKind::Assignment; // =
        case '!':
            if (next_char != (char)6019 && next_char == '=') { // !=
                this->index++;
                this->do_next_char();
                return TokenKind::NotEquals;
            }
            return TokenKind::Bang; // =
        case '|':
            return TokenKind::Or;
        case '&':
            return TokenKind::And;
        case '[':
            return TokenKind::LeftBracketRectangle; // [
        case ']':
            return TokenKind::RightBracketRectangle; // ]
        case '{':
            return TokenKind::LeftCurlyBrackets; // {
        case '}':
            return TokenKind::RightCurlyBrackets; // }
        default:
            return TokenKind::None;
    }
}

char Lexer::get_next_char() {
    if (this->value.length() == this->index)
        return '\2';
    else
        return this->value[this->index+1];
}

void Lexer::eof(std::vector<Token> &tokens) {
    tokens.push_back(
        *(
            new Token("\0", this->filename, TokenKind::Eof, create_pos(this->curr_row, this->curr_col)
        )
    ));
}

void Lexer::add_and_create_token_char(char curr_char, std::string filename, TokenKind type, TokenPos pos, std::vector<Token> &tokens) {
    std::string value;
    value.assign(1, curr_char);
    tokens.push_back(
        *(
            new Token(value, this->filename, type, create_pos(this->curr_row, this->curr_col)
        )
    ));
}

void Lexer::identifier_creator(std::vector<Token> &tokens, Token last_token) {
    if (last_token.type == TokenKind::None) {
        Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
        this->space = false;
    } else {
        if (this->space == false) { 
            if (last_token.type == TokenKind::Identifier) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else {
                Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
                this->space = false;
            }
        } else {
            Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
            this->space = false;
        }
    }
}

void Lexer::number_creator(std::vector<Token> &tokens, Token last_token) {
    if (last_token.type == TokenKind::None) {
        Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col), tokens);
        this->space = false;
    } else {
        if (this->space == false) { 
            if (last_token.type == TokenKind::Int) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else if (last_token.type == TokenKind::Float) {
                tokens[tokens.size() - 1].value += this->curr_char;
                this->space = false;
            } else if (last_token.type == TokenKind::Identifier && this->space == false) {
                tokens[tokens.size() - 1].value += this->curr_char;
                tokens[tokens.size() - 1].type = TokenKind::Identifier;
                this->space = false;
            } else {
                Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col), tokens);
                this->space = false;
            }
        } else {
            Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col), tokens);
            this->space = false;
        }
    }
}

void Lexer::unsupported_char() { 
    std::ostringstream ss;
    ss << "Unsupported character: '" << this->curr_char << "'(" << (int)this->curr_char << ")";

    Error::print_error_with_positional_args(UNSUPPORTED_CHAR, ss.str(), create_pos(this->curr_row, this->curr_col), this->filename);
    this->is_error_message = true;
}

void Lexer::float_creator(std::vector<Token> &tokens, Token last_token) {
    if (last_token.type == TokenKind::None) {
        tokens.push_back(
            *(
                new Token("0.", this->filename, TokenKind::Float, create_pos(this->curr_row, this->curr_col)
            )
        ));
        this->space = false;
    } else {
        if (last_token.type == TokenKind::Int) {
            tokens[tokens.size() - 1].value += this->curr_char;
            tokens[tokens.size() - 1].type = TokenKind::Float;
            this->space = false;
        } else if (last_token.type == TokenKind::Float) {
            if (last_token.value.find('.') != std::string::npos) {
                Error::print_error_with_positional_args(SYNTAX_ERROR, "This float already contains a '.'", create_pos(this->curr_row, this->curr_col), this->filename);
                this->is_error_message = true;
            } else {
                tokens[tokens.size() - 1].value += this->curr_char;
                tokens[tokens.size() - 1].type = TokenKind::Float;
            }
        } else {
            tokens.push_back(
                *(
                    new Token("0.", this->filename, TokenKind::Float, create_pos(this->curr_row, this->curr_col)
                )
            ));
            this->space = false;  
        }
    }
}

void Lexer::print_all_tokens(std::vector<Token> &tokens) {
    for (auto &token : tokens)
        std::cout << token.value << ":" << token.type_string() << std::endl;
}

void Lexer::is_string_ends() {
    if (this->string_opened == true) {
        Error::print_error(SYNTAX_ERROR, "You didn't close string with '\"'");
        this->is_error_message = true;
    }
}

void Lexer::do_next_char() {
    this->curr_char = this->value[this->index];
    this->last_token = this->get_last_token(tokens);
    this->next_char = this->get_next_char();
}

std::vector<Token> Lexer::start() {
    this->last_token = new Token("", this->filename, TokenKind::None, create_pos(0, 0));
    this->curr_row = 0;
    this->curr_col = 0;
    this->next_char = '\0';
    this->curr_char = '\0';

    for (this->index = 0; this->index < this->value.size(); this->index++) {
        this->do_next_char();
        if (this->curr_char == '\0')
            this->eof(tokens);
        else if (this->curr_char == '\n') 
            this->newline(tokens);
        else if (this->curr_char == '\r' || (int)this->curr_char == -1)
            continue;
        else if (this->curr_char == '#')
            this->comment_inline(tokens);
        else if (this->comment_opened_inline == true)
            continue;
        else if (this->curr_char == '"')
            this->string_creator(tokens);
        else if (this->string_opened == true)
            this->string_append(tokens);
        else if (this->curr_char == ' ')
            this->space = true;
        else if (this->detect_char(next_char) != TokenKind::None)
            this->add_and_create_token_char(this->curr_char, this->filename, this->detect_char(next_char), create_pos(this->curr_row, this->curr_col), tokens);
        else if (identifier_constant.find(this->curr_char) != std::string::npos)
            this->identifier_creator(tokens, *last_token);
        else if (number_constant.find(this->curr_char) != std::string::npos)
            this->number_creator(tokens, *last_token);
        else if (this->curr_char == '.')
            this->float_creator(tokens, *last_token);
        else
            this->unsupported_char();

        this->curr_col++;
    }

    this->is_string_ends();
    this->eof(tokens);

    this->print_all_tokens(tokens);

    if (this->is_error_message == true)
        exit(1);

    return tokens;
}

}