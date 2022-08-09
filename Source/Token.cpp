/*
    Oak programming language

    Copyright (C) 2022 SolindekDev <ytsolindekttv@gmail.com>
*/

#include <Lexer.h>
#include <Token.h>
#include <Libs.h>

TokenPos create_pos(int row, int col) {
    return TokenPos{row,col};
}

std::string operator_to_str(TokenKind kind) {
    switch (kind) {
      case TokenKind::Plus:
          return (std::string)"+";
          break;
      case TokenKind::Minus:
          return (std::string)"-";
          break;
      case TokenKind::Divide:
          return (std::string)"/";
          break;
      case TokenKind::Multiply:
          return (std::string)"*";
          break;
      case TokenKind::Modulus:
          return (std::string)"%";
          break;
      default:
          return (std::string)"UNKNOWN";
          break;
    }

    return "UNKNOWN";
}

std::string type_string_(TokenKind kind) {
    switch (kind) {
        case TokenKind::String:
            return (std::string)"String";
            break;
        case TokenKind::Int:
            return (std::string)"Int";
            break;
        case TokenKind::Float:
            return (std::string)"Float";
            break;
        case TokenKind::Identifier:
            return (std::string)"Identifier";
            break;
            break;
        case TokenKind::Newline:
            return (std::string)"Newline";
            break;
        case TokenKind::Eof:
            return (std::string)"EOF";
            break;
        case TokenKind::Lparen:
            return (std::string)"Lparen";
            break;
        case TokenKind::Rparen:
            return (std::string)"Rparen";
            break;
        case TokenKind::Plus:
            return (std::string)"Plus";
            break;
        case TokenKind::Minus:
            return (std::string)"Minus";
            break;
        case TokenKind::Divide:
            return (std::string)"Divide";
            break;
        case TokenKind::Multiply:
            return (std::string)"Multiply";
            break;
        case TokenKind::Assignment:
            return (std::string)"Assignment";
            break;
        case TokenKind::AddAssignment:
            return (std::string)"AddAssignment";
            break;
        case TokenKind::SubtractAssignment:
            return (std::string)"SubtractAssignment";
            break;
        case TokenKind::MultiplyAssignment:
            return (std::string)"MultiplyAssignment";
            break;
        case TokenKind::DivideAssignment:
            return (std::string)"DivideAssignment";
            break;
        case TokenKind::Increment:
            return (std::string)"Increment";
            break;
        case TokenKind::Decrement:
            return (std::string)"Decrement";
            break;
        case TokenKind::Modulus:
            return (std::string)"Modulus";
            break;
        case TokenKind::BiggerThan:
            return (std::string)"BiggerThan";
            break;
        case TokenKind::LessThan:
            return (std::string)"LessThan";
            break;
        case TokenKind::Equals:
            return (std::string)"Equals";
            break;
        case TokenKind::NotEquals:
            return (std::string)"NotEquals";
            break;
        case TokenKind::BiggerThanOrEquals:
            return (std::string)"BiggerThanOrEquals";
            break;
        case TokenKind::LessThanOrEquals:
            return (std::string)"LessThanOrEquals";
            break;
        case TokenKind::Seperator:
            return (std::string)"Seperator";
            break;
        case TokenKind::And:
            return (std::string)"And";
            break;
        case TokenKind::Bang:
            return (std::string)"Bang";
            break;
        case TokenKind::LeftBracketRectangle:
            return (std::string)"LeftBracketRectangle";
            break;
        case TokenKind::RightBracketRectangle:
            return (std::string)"RightBracketRectangle";
            break;
        case TokenKind::LeftCurlyBrackets:
            return (std::string)"LeftCurlyBrackets";
            break;
        case TokenKind::RightCurlyBrackets:
            return (std::string)"RightCurlyBrackets";
            break;
        case TokenKind::None:
            return (std::string)"None";
            break;
        default:
            return (std::string)"Unknown Type";
            break;
    }

    return "Unknown Type";
}

std::string Token::type_string() {
        return type_string_(this->type);
}
