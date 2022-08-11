/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Parser.h>
#include <Token.h>
#include <Error.h>
#include <AST.h>
#include <Libs.h>

const std::string Oak_Keywords[13] = {
    "fn", // DONE
    "if", // TODO
    "elif", // TODO
    "else", // TODO
    "let", // TODO
    "const", // TODO
    "while", // TODO
    "for", // TODO
    "class", // TODO
    "call", // DONE
    "push", // DONE
    "pop", // TODO: now
    "namespace", // TODO
};

Token* Oak_Builtin_Functions[5] = {
    new Token("println", "runtime.oak", TokenKind::Identifier, create_pos(0,0)),
    new Token("print", "runtime.oak", TokenKind::Identifier, create_pos(0,0)),
    new Token("puts", "runtime.oak", TokenKind::Identifier, create_pos(0,0)),
    new Token("sleep", "runtime.oak", TokenKind::Identifier, create_pos(0,0)),
    new Token("exit", "runtime.oak", TokenKind::Identifier, create_pos(0,0)),
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
const std::string Oak_Keyword_Call      = "call";
const std::string Oak_Keyword_Push      = "push";
const std::string Oak_Keyword_Pop       = "pop";
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

bool Parser::is_function_name_already_declared_bool(std::string name) {
    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST")
            if (((FunctionAST*)node)->name->value == name)
                return true;
    }

    return false;
}

FunctionAST* Parser::is_function_name_already_declared_node(std::string name) {
    FunctionAST* fn_ast;
    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST")
            if (((FunctionAST*)node)->name->value == name)
                fn_ast = ((FunctionAST*)node);
    }
    return fn_ast;
}

void Parser::is_function_name_already_declared(std::string name) {
    if (is_identifier_keyword(name)) {
        std::ostringstream ss;
        ss << "unexpected use of '" << name << "' keyword";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }

    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST")
            if (((FunctionAST*)node)->name->value == name) {
                std::ostringstream ss;
                ss << "'" << name << "' " << "function name is already in use";

                Error::print_error_with_positional_args(
                    SYNTAX_ERROR,
                    ss.str(),
                    create_pos(
                        this->current_token->pos.row,
                        this->current_token->pos.col),
                    this->lexer->filename
                );
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

void Parser::is_token_in_function() {
    if (this->is_fn_open != true) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "this token can be use only in function body",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
    }
}

void Parser::parse_const() {
    is_token_outside_function();
    is_colon_next("const");
    auto _var_name = get_variable_name();
    is_seperator_here();
    auto _var_value = get_variable_value();
    is_semi_colon_next("variable value");
    is_var_defined_void(_var_name);

    auto var_node = new VariableDeclarationAST(
      _var_name, _var_value->value,
      _var_value->type, true, nullptr);
    append_node(var_node);
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

void Parser::is_colon_next(std::string keyword) {
    this->index++;
    this->advance();

    if (this->current_token->type != TokenKind::Colon) {
        std::ostringstream ss;
        ss << "expected ':' after " << keyword << " keyword";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

std::string Parser::get_function_name_call() {
    this->index++;
    this->advance();

    if (this->current_token->type == TokenKind::Identifier)
        return this->current_token->value;
    else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "after call keyword expected function name to call.",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::is_semi_colon_next(std::string keyword) {
    this->index++;
    this->advance();

    if (this->current_token->type != TokenKind::Colon) {
        std::ostringstream ss;
        ss << "expected ';' after " << keyword;
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::is_fn_name_correct_call(std::string _fn_name) {
    if (!is_function_name_already_declared_bool(_fn_name)) {
        std::ostringstream ss;
        ss << "'" << _fn_name << "' " << "function to call is not declared";

        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }

    if (is_identifier_keyword(_fn_name)) {
        std::ostringstream ss;
        ss << "unexpected use of '" << this->current_token->value << "' keyword";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::is_token_outside_function() {
    if (this->is_fn_open == true) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "this token can be use only outside function body",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
    }
}

void Parser::parse_call() {
    is_token_in_function();
    is_colon_next("call");
    auto _fn_name = get_function_name_call();
    is_fn_name_correct_call(_fn_name);
    is_semi_colon_next("function name to call");

    auto call_node = new CallFunctionAST(
      _fn_name, is_function_name_already_declared_node(_fn_name));
    append_node(call_node);
}


std::string Parser::get_variable_name() {
    this->index++;
    this->advance();

    if (this->current_token->type != TokenKind::Identifier) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "expected variable name after variable keyword and colon",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }

    if (is_identifier_keyword(this->current_token->value)) {
        std::ostringstream ss;
        ss << "unexpected use of '" << this->current_token->value << "' keyword";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }

    return this->current_token->value;
}

Token* Parser::get_variable_value() {
    this->index++;
    this->advance();

    if (this->current_token->type == TokenKind::Identifier) {
        if (is_var_defined(this->current_token->value)) {
            // Error::todo("variable value to new variable ");
            // exit(1);
            auto var_to_ret = is_var_defined_variable(this->current_token->value);
            auto tk = new Token(
                var_to_ret->variable_value,
                this->lexer->filename,
                var_to_ret->variable_type,
                create_pos(0,0)
            );
            return tk;
        } else {
            std::ostringstream ss;
            ss << "'" << this->current_token->value << "' this variable is not defined";
            Error::print_error_with_positional_args(
                SYNTAX_ERROR,
                ss.str(),
                create_pos(
                    this->current_token->pos.row,
                    this->current_token->pos.col),
                this->lexer->filename
            );
            this->is_error_message = true;
            exit(1);
        }
    } else if (
      this->current_token->type == TokenKind::Int    ||
      this->current_token->type == TokenKind::String ||
      this->current_token->type == TokenKind::Float){
        return this->current_token;
    } else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "unexpected type to variable value, expected int, string, float or variable name for value",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::is_seperator_here() {
    this->index++;
    this->advance();

    if (this->current_token->type != TokenKind::Seperator) {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "expected '|' after variable name to seperate name from value",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

bool Parser::is_var_defined(std::string var_name) {
    if (is_fn_open == true) {
        auto ac_function = is_function_name_already_declared_node(fn_name->value);
        for (auto& node : ac_function->body) {
            if (node->type == "VariableDeclarationAST") {
                if (((VariableDeclarationAST*)node)->variable_name == var_name) {
                    return true;
                }
            }
        }
    }

    for (auto& outside_node : this->program->body) {
        if (outside_node->type == "VariableDeclarationAST") {
            if (((VariableDeclarationAST*)outside_node)->variable_name == var_name) {
                return true;
            }
        }
    }

    return false;
}

VariableDeclarationAST* Parser::is_var_defined_variable(std::string var_name) {
    auto ac_function = is_function_name_already_declared_node(fn_name->value);

    for (auto& node : ac_function->body) {
        if (node->type == "VariableDeclarationAST") {
            if (((VariableDeclarationAST*)node)->variable_name == var_name) {
                return (VariableDeclarationAST*)node;
            }
        }
    }

    for (auto& node : program->body) {
        if (node->type == "VariableDeclarationAST") {
            if (((VariableDeclarationAST*)node)->variable_name == var_name) {
                return (VariableDeclarationAST*)node;
            }
        }
    }

    return nullptr;
}

void Parser::is_var_defined_void(std::string var_name) {
    if (is_var_defined(var_name)) {
        std::ostringstream ss;
        ss << "'" << var_name << "' is already declared";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::parse_let() {
    is_token_in_function();
    is_colon_next("let");
    auto _var_name = get_variable_name();
    is_seperator_here();
    auto _var_value = get_variable_value();
    is_semi_colon_next("variable value");
    is_var_defined_void(_var_name);

    auto var_node = new VariableDeclarationAST(
      _var_name, _var_value->value,
      _var_value->type, false,
      is_function_name_already_declared_node(fn_name->value));
    append_node(var_node);
}

Token* Parser::get_value_to_stack() {
    this->index++;
    this->advance();

    if (this->current_token->type == TokenKind::Identifier) {
        return new Token(this->current_token->value, this->lexer->filename, TokenKind::None, create_pos(0,0));
    } else if (
      this->current_token->type == TokenKind::Int    ||
      this->current_token->type == TokenKind::String ||
      this->current_token->type == TokenKind::Float){
        return this->current_token;
    } else {
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            "unexpected type to push, expected int, string, float or variable name",
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col),
            this->lexer->filename
        );
        this->is_error_message = true;
        exit(1);
    }
}

void Parser::parse_push() {
    is_token_in_function();
    is_colon_next("push");
    auto value_to_stack = get_value_to_stack();
    is_semi_colon_next("value to push");

    if (value_to_stack->type == TokenKind::None) {
        auto var = is_var_defined_variable(value_to_stack->value);
        auto push_node = new PushStatementAST(value_to_stack, true, var->is_constant, value_to_stack->value);
        append_node(push_node);
    } else {
        auto push_node = new PushStatementAST(value_to_stack, false, false, "");
        append_node(push_node);
    }
}

void Parser::parse_pop() {
    is_token_in_function();
    is_colon_next("pop");
    Error::todo("pop keyword ");
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
        else if (this->current_token->value == Oak_Keyword_Call)
            this->parse_call();
        else if (this->current_token->value == Oak_Keyword_Push)
            this->parse_push();
        else if (this->current_token->value == Oak_Keyword_Pop)
            this->parse_pop();
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
        std::ostringstream ss;
        ss << "unexpected use of '" << this->current_token->value << "' identifier";
        Error::print_error_with_positional_args(
            SYNTAX_ERROR,
            ss.str(),
            create_pos(
                this->current_token->pos.row,
                this->current_token->pos.col
            ),
            this->lexer->filename
        );
        this->is_error_message = true;
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

void Parser::init_builtin_functions() {
    for (auto fn : Oak_Builtin_Functions) {
        this->program->body.push_back(
          new FunctionAST(fn));
    }
}

void Parser::print_all_functions() {
    for (auto &node : this->program->body) {
        if (node->type == "FunctionAST") {
            std::cout << "Function name: "
                      << ((FunctionAST*)node)->name->value
                      << " | Function address: 0x"
                      << &node
                      << " | Function body size: "
                      << ((FunctionAST*)node)->body.size()
                      << std::endl;
        }
    }
}

void Parser::start() {
    this->init_builtin_functions();
    for (this->index = 0; this->index < this->lexer->tokens.size(); this->index++) {
        this->advance();

        if (is_eof())
          break;

        if (this->current_token->type == TokenKind::Identifier)
            this->parse_identifier();
        else if (this->current_token->type == TokenKind::RightBracketRectangle)
            this->close_function();
    }

    // this->print_all_functions();

    if (this->is_error_message == true)
      exit(1);
}

}
