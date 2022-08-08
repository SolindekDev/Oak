/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Parser.h>
#include <Token.h>
#include <Error.h>
#include <AST.h>
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

void Parser::is_function_open() {
    if (this->is_fn_open) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "you can't open a function in another function.",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
    }
}

Token* Parser::get_function_name() {
    this->index++;
    this->advance();

    if (this->current_token->type == TokenKind::Identifier)
        return this->current_token;
    else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "after function keyword expected function name.",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::is_there_brackets_to_open_function() {
    this->index++;
    this->advance();

    if (this->current_token->type != TokenKind::LeftBracketRectangle) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "expected '[' after function name",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    } else {
        this->is_fn_open = true;
    }
}

void Parser::is_function_name_already_declared(std::string name) {
    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST")
            if (((FunctionAST*)node)->name->value == name) {
                Error::print_error_with_positional_args(
                    SYNTAX_ERROR,
                    "function name is already in use",
                    create_pos(
                        this->current_token->pos.row,
                        this->current_token->pos.col),
                    this->lexer->filename
                );
                Error::todo(" better error when function name is already in use");
                this->is_error_message = true;
                exit(1);
            }
    }
}

void Parser::parse_function() {
    is_function_open();
    auto _fn_name = get_function_name();
    is_there_brackets_to_open_function();

    is_function_name_already_declared(_fn_name->value);

    this->program->body.push_back(new FunctionAST(_fn_name));
    this->fn_name = _fn_name;
    this->fn_declared_in_program++;
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

FunctionAST* Parser::find_fn_node() {
    FunctionAST* _return;
    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST")
            if (((FunctionAST*)node)->name->value == this->fn_name->value)
                _return = (FunctionAST*)node;
    }

    return _return;
}

void Parser::append_node(NodeAST* node) {
    this->is_fn_open == true
      ? this->find_fn_node()->body.push_back(node)
      : this->program->body.push_back(node);
}

bool Parser::is_math_operator() {
    return this->current_token->type == TokenKind::Plus     ||
           this->current_token->type == TokenKind::Minus    ||
           this->current_token->type == TokenKind::Multiply ||
           this->current_token->type == TokenKind::Divide   ||
           this->current_token->type == TokenKind::Modulus;
}

void Parser::parse_identifier() {
    auto is_keyword = this->is_identifier_keyword(this->current_token->value);

    if (is_keyword) {
        this->parse_keyword();
    } else {
        Error::todo("check is identifier function or a variable ");
    }
}

NumberNodeAST* Parser::parse_number() {
    if (this->current_token->value.find('.') != std::string::npos)
        return new NumberNodeAST(std::stod(this->current_token->value));
    else if (this->current_token->value.find('o') != std::string::npos)
        Error::todo("octal in math operations ");
    else if (this->current_token->value.find('x') != std::string::npos)
        Error::todo("hexadecimal in math operations ");
    else if (this->current_token->value.find('b') != std::string::npos)
        Error::todo("binary in math operations ");
    else
        return new NumberNodeAST(std::stoi(this->current_token->value));

    return new NumberNodeAST(0);
}

void Parser::close_function() {
    if (this->is_fn_open)
        this->is_fn_open = false;
    else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
              "unexpected use of ']'",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col
            ),
            this->lexer->filename
        );
        this->is_error_message = true;
    }
}

void Parser::start() {
    for (this->index = 0; this->index < this->lexer->tokens.size(); this->index++) {
        this->advance();

        if (is_eof())
          break;

        if (this->current_token->type == TokenKind::Identifier)
            this->parse_identifier();
        else if (this->current_token->type == TokenKind::RightBracketRectangle)
            this->close_function();
    }

    this->find_fn_node()->print();
    std::cout << this->fn_declared_in_program << std::endl;

    if (this->is_error_message == true)
      exit(1);
}

}
