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

void Parser::parse_identifier() {
    auto is_keyword = this->is_identifier_keyword(this->current_token->value);

    if (is_keyword) {
        this->parse_keyword();
    } else {
        Error::todo("check is identifier function or a variable ");
    }
}

NumberNodeAST* Parser::token_to_number_node_ast(Token* &tk) {
    // TODO: implement hex, octal and binary conversion

    if (tk->value.find('.') != std::string::npos)
        return new NumberNodeAST(std::stod(tk->value));
    else if (tk->value.find('o') != std::string::npos)
        Error::todo("octal in math operations ");
    else if (tk->value.find('x') != std::string::npos)
        Error::todo("hexadecimal in math operations ");
    else if (tk->value.find('b') != std::string::npos)
        Error::todo("binary in math operations ");
    else
        return new NumberNodeAST(std::stoi(tk->value));

    return new NumberNodeAST(0);
}

TokenKind Parser::search_for_op() {
    this->index++;
    this->advance();

    if (this->is_eof())
        return TokenKind::None;
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
        exit(1);
    }

    return this->current_token->type;
}

NumberNodeAST* Parser::number_search() {
    this->index++;
    this->advance();

    if (this->is_eof())
        return new NumberNodeAST(0);

    if (this->current_token->type == TokenKind::Int ||
        this->current_token->type == TokenKind::Float)
        return token_to_number_node_ast(this->current_token);
    else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "Expected an number after math operator",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col
            ),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::parse_math() {
    if (this->binary_exp_open == true) {
        if (this->program->body[this->program->body.size() - 1]->type == "MathExpressionNodeAST") {
            if (is_math_operator()) {
                auto lhs = new NumberNodeAST(0);
                auto op = this->current_token->type;
                auto rhs = this->number_search();
                auto math_node = new MathNodeAST(lhs, rhs, op);

                math_node->end_to_last = true;
                std::cout << this->program->body[this->program->body.size() - 1]->nodes.size() << std::endl;
                this->program->
                    body[this->program->body.size() - 1]->
                    nodes.push_back(math_node);

                std::cout << this->program->body[this->program->body.size() - 1]->nodes.size() << std::endl;
            }
        } else {
            Error::print_error_with_positional_args(
                SYNTAX_ERROR,
                "Expected math operation before operator or number",
                create_pos(
                    this->current_token->pos.row,
                    this->current_token->pos.col
                ),
                this->lexer->filename
            );
            this->is_error_message = true;
            exit(1);
        }
    } else {
        this->binary_exp_open = true;
        auto math_exp_node = new MathExpressionNodeAST();

        auto lhs = this->token_to_number_node_ast(this->current_token);
        auto op = this->search_for_op();
        auto rhs = this->number_search();
        auto math_node = new MathNodeAST(lhs, rhs, op);

        math_exp_node->nodes.push_back(math_node);

        std::cout << program->body[program->body.size() - 1]->nodes.size() << std::endl;
        program->body.push_back(math_exp_node);
        std::cout << program->body[program->body.size() - 1]->nodes.size() << std::endl;
    }
}

void Parser::start() {
    for (this->index = 0; this->index < this->lexer->tokens.size(); this->index++) {
        this->advance();

        if (is_eof())
          break;

        if (this->current_token->type == TokenKind::Identifier)
            this->parse_identifier();
        else if (this->binary_exp_open == true)
            this->parse_math();
        else if (this->current_token->type == TokenKind::Int ||
                 this->current_token->type == TokenKind::Float)
            this->parse_math();
    }

    this->program->body[this->program->body.size() - 1]->print();

    if (this->is_error_message == true)
      exit(1);
}

}
