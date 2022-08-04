/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Parser.h>
#include <Token.h>
#include <Error.h>
#include <Libs.h>

const std::string Oak_Keywords[10] = {
    "fn",
    "if",
    "elif",
    "else",
    "let",
    "const",
    "while",
    "for",
    "class",
    "namespace",
};

const std::string Oak_Keyword_Function  = "fn";
const std::string Oak_Keyword_If        = "if";
const std::string Oak_Keyword_Elif      = "elif";
const std::string Oak_Keyword_Else      = "else";
const std::string Oak_Keyword_Let       = "let";
const std::string Oak_Keyword_Const     = "const";
const std::string Oak_Keyword_While     = "while";
const std::string Oak_Keyword_For       = "for";
const std::string Oak_Keyword_Class     = "class";
const std::string Oak_Keyword_Namespace = "namespace";

const Precedences Oak_Precedences[5] = {
    Precedences{ "+", 1, 2 },
    Precedences{ "-", 1, 2 },
    Precedences{ "*", 3, 4 },
    Precedences{ "/", 3, 4 },
    Precedences{ "%", 3, 4 },
};

namespace OakParser {

Token* Parser::get_next_token() {
    return this->lexer->tokens.size() == this->index
           ? new Token("", this->lexer->filename, TokenKind::None, create_pos(0, 0))
           : &this->lexer->tokens[this->index+1];
}

void Parser::advance() {
    this->current_token = &this->lexer->tokens[this->index];
    this->next_token = this->get_next_token();
}

bool Parser::is_eof() {
    return this->current_token->type == TokenKind::Eof;
}

bool Parser::is_identifier_keyword(std::string value_id) {
    for (auto keyword : Oak_Keywords)
        if (keyword == value_id)
            return true;
    return false;
}

void Parser::parse_if() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("if ");
}
void Parser::parse_elif() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("elif ");
}
void Parser::parse_else() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("else ");
}
void Parser::parse_let() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("let ");
}
void Parser::parse_namespace() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("namespace ");
}
void Parser::parse_function() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("function ");
}
void Parser::parse_const() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("const ");
    std::cout << this->current_token->value << std::endl;
}

void Parser::parse_while() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("while ");
}

void Parser::parse_for() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("for ");
}

void Parser::parse_class() {
    Error::print_error_with_positional_args(
      UNSUPPORTED_KEYWORD,
      "this keyword is not supported by oak parser.",
      create_pos(
        this->current_token->pos.row,
        this->current_token->pos.col),
      this->lexer->filename
    );
    this->is_error_message = true;
    Error::todo("classes ");
}

void Parser::parse_keyword() {
        if (this->current_token->value == Oak_Keyword_If)
            this->parse_if();
        else if (this->current_token->value == Oak_Keyword_Elif)
            this->parse_elif();
        else if (this->current_token->value == Oak_Keyword_Else)
            this->parse_else();
        else if (this->current_token->value == Oak_Keyword_Let)
            this->parse_let();
        else if (this->current_token->value == Oak_Keyword_Namespace)
            this->parse_namespace();
        else if (this->current_token->value == Oak_Keyword_Function)
            this->parse_function();
        else if (this->current_token->value == Oak_Keyword_Const)
            this->parse_const();
        else if (this->current_token->value == Oak_Keyword_While)
            this->parse_while();
        else if (this->current_token->value == Oak_Keyword_For)
            this->parse_for();
        else if (this->current_token->value == Oak_Keyword_Class)
            this->parse_class();
        else {
            Error::print_error_with_positional_args(
                COMPILER_ERROR,
                "We shouldn't be here, tell about this error on github issue this might be a very serious compiler error. Code #002",
                create_pos(
                    this->current_token->pos.row,
                    this->current_token->pos.col
                ),
                this->lexer->filename
            );
            this->is_error_message = true;
        }
}

bool Parser::is_math_operator() {
    return this->current_token->type == TokenKind::Plus     ||
           this->current_token->type == TokenKind::Minus    ||
           this->current_token->type == TokenKind::Multiply ||
           this->current_token->type == TokenKind::Divide   ||
           this->current_token->type == TokenKind::Modulus;
}

int Parser::get_precendences_by_operator(Token* token) {
    switch (token->type) {
        case TokenKind::Plus:
            return 0;
            break;
        case TokenKind::Minus:
            return 1;
            break;
        case TokenKind::Multiply:
            return 2;
            break;
        case TokenKind::Divide:
            return 3;
            break;
        case TokenKind::Modulus:
            return 4;
            break;
        default:
            Error::print_error_with_positional_args(
                COMPILER_ERROR,
                "We shouldn't be here, tell about this error on github issue this might be a very serious compiler error. Code #003",
                create_pos(
                    this->current_token->pos.row,
                    this->current_token->pos.col
                ),
                this->lexer->filename
            );
            this->is_error_message = true;
            return 0;
            break;
    }
}

Token* Parser::parse_math(int precendence) {
    auto lhs = this->current_token;

    while (1) {
        this->index++;
        this->advance();

        if (this->is_eof())
            break;
        if (!this->is_math_operator()) {
            Error::print_error_with_positional_args(
                SYNTAX_ERROR,
                "Expected an math operator after a number",
                create_pos(
                    this->current_token->pos.row,
                    this->current_token->pos.col
                ),
                this->lexer->filename
            );
            this->is_error_message = true;
          }

          auto precendence_ = Oak_Precedences[get_precendences_by_operator(this->current_token)];
          if (precendence_.left < precendence)
              break;

          this->index++;
          this->advance();

          auto rhs = parse_math(precendence_.right);

          std::cout << lhs->value << ":" << lhs->type_string() << std::endl;
          std::cout << rhs->value << ":" << rhs->type_string() << std::endl;
    }

    return lhs;
}

void Parser::parse_identifier() {
    auto is_keyword = this->is_identifier_keyword(this->current_token->value);

    if (is_keyword) {
        this->parse_keyword();
    } else {
        Error::todo("check is identifier function or a variable ");
    }
}

void Parser::start() {
    for (this->index = 0; this->index < this->lexer->tokens.size(); this->index++) {
        this->advance();

        if (is_eof())
          break;

        if (this->current_token->type == TokenKind::Identifier)
            this->parse_identifier();
        else if (this->current_token->type == TokenKind::Int ||
                 this->current_token->type == TokenKind::Float)
            this->parse_math(0);
    }

    if (this->is_error_message == true)
      exit(1);
}

}
