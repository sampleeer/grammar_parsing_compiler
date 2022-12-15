#ifndef LEXEME_H
#define LEXEME_H
#include <string>
#include <iostream>
#include "lexical_item.h"

// Тип лексемы
enum type_lexeme {
    UNKNOWN,
    INTEGER, END,
    PROGRAM, RBRACES, Double,
    LBRACES, SEMICOLON, INT,
    itod, dtoi, ID,
    INTNUMBER, DoubleNUMBER,
    SUM, MINUS,
    LBRACKET, RBRACKET,
    EQUALS, COMMA, RETURN
};

// Класс лексемы
class Lexeme : public lexical_item {
private:
    type_lexeme _type;
    std::string _text;

public:
    Lexeme() : _type(UNKNOWN), _text() {}
    Lexeme(const type_lexeme& type_, std::string  text_) : _type(type_), _text(text_) {}
    Lexeme(const type_lexeme&, char);
    Lexeme(const Lexeme& obj) : _type(obj._type), _text(obj._text) {}

    //Возвращает тип содержимого класса
    std::string node_type() const { return "lexeme"; }
    type_lexeme type() const { return _type; }
    std::string text() const { return _text; }

    bool operator==(const Lexeme&) const&;
    Lexeme& operator=(const Lexeme&);
    friend std::ostream& operator<<(std::ostream&, const Lexeme&);
};


#endif // LEXEME_H

