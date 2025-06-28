#include <iostream>
#include <string>
#include <locale.h>

// Фронтенд
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"
#include "AST/SemanticAnalyzer/SemanticAnalyzer.hpp"

// Бэкенд
#include "Generator/CodeGenerator.hpp"

// Регистрация парсеров / анализаторов (загружаются через header-only)
#include "AST/Statement/VarDeclaration.hpp"
#include "AST/Statement/FunctionDeclaration.hpp"
#include "AST/Statement/AssignmentStatement.hpp"
#include "AST/Statement/ExpressionStatement.hpp"
#include "AST/Statement/ReturnStatement.hpp"
#include "AST/Statement/IfStatement.hpp"
#include "AST/Statement/PrintStatement.hpp"
#include "AST/Statement/ClassDeclaration.hpp"
#include "AST/Statement/StructDeclaration.hpp"
#include "AST/Statement/WhileStatement.hpp"
#include "AST/Statement/ForStatement.hpp"
#include "AST/Statement/TemplateDeclaration.hpp"
#include "AST/Statement/ForeachStatement.hpp"

// Эмиттеры
#include "Generator/Emitters/VarEmitter.hpp"
#include "Generator/Emitters/FunctionEmitter.hpp"
#include "Generator/Emitters/ExpressionStatementEmitter.hpp"
#include "Generator/Emitters/ReturnEmitter.hpp"
#include "Generator/Emitters/IfEmitter.hpp"
#include "Generator/Emitters/PrintEmitter.hpp"
#include "Generator/Emitters/AssignmentEmitter.hpp"
#include "Generator/Emitters/ClassEmitter.hpp"
#include "Generator/Emitters/StructEmitter.hpp"
#include "Generator/Emitters/WhileEmitter.hpp"
#include "Generator/Emitters/ForEmitter.hpp"

// Expression-эмиттеры
#include "Generator/Emitters/LiteralEmitter.hpp"
#include "Generator/Emitters/IdentifierEmitter.hpp"
#include "Generator/Emitters/BinaryEmitter.hpp"
#include "Generator/Emitters/CallEmitter.hpp"
#include "Generator/Emitters/TemplateEmitter.hpp"
#include "Generator/Emitters/MethodCallEmitter.hpp"
#include "Generator/Emitters/MemberAcessEmitter.hpp"
#include "Generator/Emitters/StructLiteralEmitter.hpp"
#include "Generator/Emitters/ArrayLiteralEmitter.hpp"
#include "Generator/Emitters/IndexAccessEmitter.hpp"
#include "Generator/Emitters/UnaryExpressionEmitter.hpp"
#include "Generator/Emitters/ForeachEmitter.hpp"
#include "Generator/Emitters/BreakEmitter.hpp"
#include "Generator/Emitters/ContinuteEmitter.hpp"
//#include "Generator/Emitters/MemberAssignmentEmitter.hpp"

int main() {
    system("chcp 65001"); // переключает кодовую страницу на UTF-8
    const char* source = R"alua(
// ========== 1. Переменные и типы ==========
var int: a = 10
var int: b = 4
var float: pi = 3.1415
var string: name = "Максим"
var bool: active = true
var [int]: list = [1, 2, 3, 4]

// ========== 2. Структура ==========
struct Point {
    var int: x = 0
    var int: y = 0
}

var Point: p = Point { x = 5, y = 7 }

// ========== 3. Класс ==========
class Vec2 {
    var float: x = 0.0
    var float: y = 0.0

    fn void: move(float: dx, float: dy) {
        self.x = self.x + dx
        self.y = self.y + dy
    }

    fn float: length() {
        return sqrt(self.x * self.x + self.y * self.y)
    }
}

var Vec2: v = Vec2 { x = 3.0, y = 4.0 }
v:move(1.0, -2.0)


// ========== 4. Функции ==========
fn int: multiply(int: x, int: y) {
    return x * y
}

fn string: greet(string: who) {
    return "Привет, " .. who
}

// ========== 5. Циклы ==========
for (var int: i = 0, i < 3, i = i + 1) {
    print("i " .. string(i))
}

foreach list as int: item {
    if (item == 3) { continue }
    print("Элемент: " .. string(item))
}

// ========== 6. Условия ==========
var int: score = 82
if (score >= 90) {
    print("Отлично")
} elseif (score >= 70) {
    print("Хорошо")
} else {
    print("Нужно подтянуть")
}

// ========== 7. Массив классов ==========
class Enemy {
    var string: name = ""
    var Point: pos = Point { x = 0, y = 0 }

    fn void: move(int: dx, int: dy) {
        self.pos.x = self.pos.x + dx
        self.pos.y = self.pos.y + dy
    }

    fn string: describe() {
        return self.name .. " at (" .. string(self.pos.x) .. "," .. string(self.pos.y) .. ")"
    }
}

var [Enemy]: enemies = [
    Enemy { name = "Goblin", pos = Point { x = 1, y = 2 } },
    Enemy { name = "Orc", pos = Point { x = 5, y = 5 } }
]

foreach enemies as Enemy: e {
    e:move(1, 0)
    print(e:describe())
}

// ========== 8. Завершение ==========
print(greet(name))
print("v = (" .. string(v.x) .. ", " .. string(v.y) .. "), длина = " .. string(v:length()))
print("Сумма = " .. string(a + b))
print("Произведение = " .. string(multiply(a, b)))

)alua";

    std::cout << "// Source code:\n" << source << "\n\n";

    try {
        // Лексический анализ
        Lexer lexer(source);
        auto tokens = lexer.tokenize();
        std::cout << "[Lexer] Готово.\n";

        for (const auto& token : tokens) {
            std::cout << "Token: " << token.lexeme << " (" << static_cast<int>(token.type) << ")\n";
        }

        // Синтаксический анализ
        Parser parser(tokens);
        auto ast = parser.parse();
        std::cout << "[Parser] Готово.\n";

        try {
            SemanticAnalyzer analyzer;
            analyzer.analyze(ast);
            std::cout << "[Semantic Analyzer] Успешно завершён.\n";
        } catch (const std::exception& e) {
            std::cerr << "💥 Semantic error: " << e.what() << "\n";
            return 1;
        }



        // Генерация кода
        CodeGenerator codeGen;
        std::string output = codeGen.generate(ast.statements);

        std::cout << "\n------- ALUA 0.0.1 COMPILER -------\n" << output << "\n";
    } catch (const std::exception& e) {
        std::cerr << "💥 Ошибка компиляции: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
