#include "Lexeme.h"

Lexeme::Lexeme(const type_lexeme& type, const char text) {
    _type = type;
    _text = std::string();
    _text += text;
}

bool Lexeme::operator==(const Lexeme& obj) const& {
    return _type == obj._type && _text == obj._text;
}

Lexeme& Lexeme::operator=(const Lexeme& obj) {
    if (&obj == this)
        return *this;
    _type = obj._type;
    _text = obj._text;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Lexeme& obj) {
    switch (obj._type) {
    case ID:
        out << "ID";
        break;
    case INT:
        out << "Keyword INT";
        break;
    case INTEGER:
        out << "Keyword INTEGER";
        break;
    case Double:
        out << "Keyword Double";
        break;
    case PROGRAM:
        out << "Keyword PROGRAM";
        break;
    case RBRACES:
        out << "Right Braces ";
        break;
    case LBRACES:
        out << "Left Braces";
        break;
    case SEMICOLON:
        out << "SEMICOLON";
        break;
    case END:
        out << "Keyword Return";
        break;
    case itod:
        out << "Keyword itod";
        break;
    case dtoi:
        out << "Keyword dtoi";
        break;
    case INTNUMBER:
        out << "Integer number";
        break;
    case DoubleNUMBER:
        out << "Double number";
        break;
    case SUM:
        out << "Sum";
        break;
    case MINUS:
        out << "Minus";
        break;
    case LBRACKET:
        out << "Left Bracket";
        break;
    case RBRACKET:
        out << "Right Bracket";
        break;
    case EQUALS:
        out << "Equals";
        break;
    case RETURN:
        out << "Return";
        break;

    case COMMA:
        out << "Comma";
        break;
    case UNKNOWN:
        out << "Unknown";
        break;
    default:
        break;
    }
    out << "\t" << obj._text;
    return out;
}
