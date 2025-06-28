//
// Created by toper on 23.06.2025.
//

#ifndef TESTCOMPILER_PARSEERROR_HPP
#define TESTCOMPILER_PARSEERROR_HPP

#include <stdexcept>
#include <string>

struct ParseError : std::runtime_error {
    int line;
    int column;
    std::string lexeme;

    ParseError(const std::string& message, int ln, int col, const std::string& lex)
        : std::runtime_error(message), line(ln), column(col), lexeme(lex) {}
};

#endif // TESTCOMPILER_PARSEERROR_HPP
