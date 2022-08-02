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
    return tokens.size() == 0
            ? new Token("", this->filename, TokenKind::None, create_pos(0,0))
            : &(tokens[tokens.size() - 1]);
}

void Lexer::newline(std::vector<Token> &tokens) {
    auto before_col = this->curr_col;
    this->space = true;
    this->comment_opened_inline = false;
    this->hexadecimal_opened = false;
    this->octal_opened = false;
    this->binary_opened = false;
    this->curr_row++;
    this->curr_col = 0;

    if (this->comment_opened_multi)
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
            this->index++;
            this->advance();
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

bool Lexer::next_char_is_not_empty_and_is(char equals) {
    return next_char != (char)6019 && next_char == equals;
}

TokenKind Lexer::detect_char(char next_char) {
    switch (this->curr_char) {
        case '\n': return TokenKind::Newline; // \n
        case '(':
            this->paren_opened = true;
            return TokenKind::Lparen; // (
        case ')':
            this->paren_opened = false;
            return TokenKind::Rparen; // )
        case '+':
            if (next_char_is_not_empty_and_is('=')) { // +=
                this->index++;
                this->advance();
                return TokenKind::AddAssignment;
            }
            if (next_char_is_not_empty_and_is('+')) { // ++
                this->index++;
                this->advance();
                return TokenKind::Increment;
            }
            return TokenKind::Plus; // +
        case '-':
            if (next_char_is_not_empty_and_is('=')) { // -=
                this->index++;
                this->advance();
                return TokenKind::SubtractAssignment;
            }
            if (next_char_is_not_empty_and_is('-')) { // --
                this->index++;
                this->advance();
                return TokenKind::Increment;
            }
            return TokenKind::Minus; // -
        case '%': return TokenKind::Modulus; // %
        case '>':
            if (next_char_is_not_empty_and_is('=')) { // >=
                this->index++;
                this->advance();
                return TokenKind::BiggerThanOrEquals;
            }
            return TokenKind::BiggerThan; // >
        case '<':
            if (next_char_is_not_empty_and_is('=')) { // >=
                this->index++;
                this->advance();
                return TokenKind::LessThanOrEquals;
            }
            return TokenKind::LessThan; // <
        case '*':
            if (next_char_is_not_empty_and_is('=')) { // *=
                this->index++;
                this->advance();
                return TokenKind::MultiplyAssignment;
            }
            return TokenKind::Multiply; // *
        case '/':
            if (next_char_is_not_empty_and_is('=')) { // /=
                this->index++;
                this->advance();
                return TokenKind::DivideAssignment;
            }
            return TokenKind::Divide; // /
        case '=':
            if (next_char_is_not_empty_and_is('=')) { // ==
                this->index++;
                this->advance();
                return TokenKind::Equals;
            }
            return TokenKind::Assignment; // =
        case '!':
            if (next_char_is_not_empty_and_is('=')) { // !=
                this->index++;
                this->advance();
                return TokenKind::NotEquals;
            }
            return TokenKind::Bang; // =
        case '|': return TokenKind::Or;
        case '&': return TokenKind::And;
        case '[':
            this->bracket_rectangle_opened = true;
            return TokenKind::LeftBracketRectangle; // [
        case ']':
            this->bracket_rectangle_opened = false;
            return TokenKind::RightBracketRectangle; // ]
        case '{':
            this->bracket_curly_opened = true;
            return TokenKind::LeftCurlyBrackets; // {
        case '}':
            this->bracket_curly_opened = false;
            return TokenKind::RightCurlyBrackets; // }
        case '?': return TokenKind::QuestionMark; // ?
        default: return TokenKind::None; // none
    }
}

char Lexer::get_next_char() {
    return this->value.length() == this->index
           ? -1
           : this->value[this->index+1];
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
    if (last_token.type == TokenKind::None)
        Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
    else
        if (this->space == false)
            if (last_token.type == TokenKind::Identifier)
                tokens[tokens.size() - 1].value += this->curr_char;
            else
                Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
        else
            Lexer::add_and_create_token_char(this->curr_char, this->filename, TokenKind::Identifier, create_pos(this->curr_row, this->curr_col), tokens);
    this->space = false;
}

void Lexer::number_creator(std::vector<Token> &tokens, Token last_token) {
    if (
        this->curr_char == '0' &&
        (
          tolower(this->next_char) == 'x' ||
          tolower(this->next_char) == 'o' ||
          tolower(this->next_char) == 'b')
    ) {
      switch(this->next_char) {
        case 'x':
          this->create_hexadecimal();
          break;
        case 'o':
          this->create_octal();
          break;
        case 'b':
          this->create_binary();
          break;
        default:
          Error::print_error_with_positional_args(COMPILER_ERROR, "We shouldn't be here, tell about this error on github issue this might be a very serious compiler error. Code #001", create_pos(this->curr_row, this->curr_col), this->filename);
          break;
      }
      return;
    }
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
    if (this->string_opened == true)
        Error::print_error(SYNTAX_ERROR, "You didn't close string with '\"'");
    this->is_error_message = true;
}

void Lexer::advance() {
    this->curr_char = this->value[this->index];
    this->last_token = this->get_last_token(this->tokens);
    this->next_char = this->get_next_char();
}

void Lexer::is_brackets_ends() {
    if (this->paren_opened) {
      Error::print_error(SYNTAX_ERROR, "You didn't close string with '\"'");
      this->is_error_message = true;
    }

    if (this->bracket_curly_opened) {
      Error::print_error(SYNTAX_ERROR, "You didn't close string with '\"'");
      this->is_error_message = true;
    }

    if (this->bracket_rectangle_opened) {
      Error::print_error(SYNTAX_ERROR, "You didn't close string with '\"'");
      this->is_error_message = true;
    }
}

void Lexer::while_hexadecimal() {
    if (isxdigit(this->curr_char))
        tokens[tokens.size() - 1].value += this->curr_char;
    else {
        std::ostringstream ss;
        ss << "You used invalid literal in hexadecimal value " << "'" << this->curr_char << "'";
        Error::print_error_with_positional_args(SYNTAX_ERROR, ss.str(), create_pos(this->curr_row, this->curr_col), this->filename);
    }
}

void Lexer::create_hexadecimal() {
    this->index++;
    this->advance();

    this->tokens.push_back(
        *(
            new Token("0x", this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col)
        )
    ));

    this->hexadecimal_opened = true;
    this->space = false;
}

void Lexer::while_octal() {
    if (this->curr_char >= '0' && this->curr_char < '8')
        tokens[tokens.size() - 1].value += this->curr_char;
    else {
        std::ostringstream ss;
        ss << "You used invalid literal in octal value " << "'" << this->curr_char << "'";
        Error::print_error_with_positional_args(SYNTAX_ERROR, ss.str(), create_pos(this->curr_row, this->curr_col), this->filename);
    }
}

void Lexer::create_octal() {
    this->index++;
    this->advance();

    this->tokens.push_back(
        *(
            new Token("0o", this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col)
        )
    ));

    this->octal_opened = true;
    this->space = false;
}

void Lexer::while_binary() {
    if (this->curr_char == '1' || this->curr_char == '0')
        tokens[tokens.size() - 1].value += this->curr_char;
    else {
        std::ostringstream ss;
        ss << "You used invalid literal in binary value " << "'" << this->curr_char << "', only 1 and 0 beep boop!";
        Error::print_error_with_positional_args(SYNTAX_ERROR, ss.str(), create_pos(this->curr_row, this->curr_col), this->filename);
    }
}

void Lexer::create_binary() {
    this->index++;
    this->advance();

    this->tokens.push_back(
        *(
            new Token("0b", this->filename, TokenKind::Int, create_pos(this->curr_row, this->curr_col)
        )
    ));

    this->binary_opened = true;
    this->space = false;
}

// Main method od lexer class (header <Lexer.h>)
std::vector<Token> Lexer::start() {
    this->last_token = new Token("", this->filename, TokenKind::None, create_pos(0, 0));

    this->curr_row = 0;
    this->curr_col = 0;

    this->next_char = '\0';
    this->curr_char = '\0';

    for (this->index = 0; this->index < this->value.size(); this->index++) {
        this->advance();
        this->detection = this->detect_char(next_char);
        if (this->curr_char == '\0')
            this->eof(tokens);
        else if (this->curr_char == '\n')
            this->newline(tokens);
        else if (this->curr_char == '\r' || (int)this->curr_char == -1)
            continue;
        else if (this->curr_char == '/' && this->next_char == '*' && this->comment_opened_inline == false && this->comment_opened_multi == false)
            this->comment_multiline(tokens);
        else if (this->curr_char == '*' && this->next_char == '/' && this->comment_opened_inline == false && this->comment_opened_multi == true)
            this->comment_multiline(tokens);
        else if (this->comment_opened_multi == true)
            continue;
        else if (this->curr_char == '#')
            this->comment_inline(tokens);
        else if (this->comment_opened_inline == true)
            continue;
        else if (this->curr_char == '"')
            this->string_creator(tokens);
        else if (this->string_opened == true)
            this->string_append(tokens);
        else if (this->curr_char == ' ') {
            this->space = true;
            this->hexadecimal_opened = false; // End of hexadecimal value is when space is true
            this->octal_opened = false; // End of octal value is when space is true
            this->binary_opened = false; // End of binary value is when space is true
        } else if (this->detection != TokenKind::None)
            this->add_and_create_token_char(this->curr_char, this->filename, this->detection, create_pos(this->curr_row, this->curr_col), tokens);
        else if (this->hexadecimal_opened == true && this->space == false)
            this->while_hexadecimal();
        else if (this->octal_opened == true && this->space == false)
            this->while_octal();
        else if (this->binary_opened == true && this->space == false)
            this->while_binary();
        else if (identifier_constant.find(this->curr_char) != std::string::npos)
            this->identifier_creator(tokens, *last_token);
        else if (isdigit(this->curr_char))
            this->number_creator(tokens, *last_token);
        else if (this->curr_char == '.')
            this->float_creator(tokens, *last_token);
        else
            this->unsupported_char();

        this->curr_col++;
    }

    this->is_string_ends();
    this->is_brackets_ends();
    this->eof(tokens);

    this->print_all_tokens(tokens);

    if (this->is_error_message == true)
        exit(1);

    return tokens;
}

}
