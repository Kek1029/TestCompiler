//
// Created by toper on 21.06.2025.
//

#ifndef TESTCOMPILER_TOKEN_HPP
#define TESTCOMPILER_TOKEN_HPP

#include <string>

#pragma once

enum class TokenType {
    // Literals
    IDENTIFIER,
    NUMBER_LITERAL,
    STRING_LITERAL = 128,

    // Keywords
    KW_VAR,
    KW_RETURN,
    KW_FUNC,
    KW_IF,
    KW_ELSE,
    KW_ELSEIF,
    KW_TEMPLATE,
    KW_CLASS,
    KW_PRINT,
    KW_STRUCT,
    KW_WHILE,
    KW_FOR,
    KW_BREAK,
    KW_CONTINUE,
    KW_FOREACH,
    KW_SWITCH,
    KW_AS,

    // Types
    TYPE_INT,
    TYPE_VOID,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_FLOAT,

    // Symbols
    COLON,
    ASSIGN,
    COMMA,
    DOT,
    SEMICOLON,

    // Operators
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_LESS,
    OP_GREATER,
    OP_EQUAL,
    OP_GREATER_EQUAL,
    OP_LESS_EQUAL,
    OP_NOT_EQUAL,
    OP_OR,
    OP_AND,
    OP_NOT,
    OP_CONCAT,

    // Grouping
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,

    // Special
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};


#endif //TESTCOMPILER_TOKEN_HPP
