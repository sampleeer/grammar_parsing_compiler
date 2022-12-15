#include"Terminal.h"

std::ostream& operator<<(std::ostream& out, const Terminal& obj) {
    switch (obj._type) {
    case Terminal::PROGRAM:
        out << "FUNCTION";
        break;
    case Terminal::BEGIN:
        out << "BEGIN";
        break;
    case Terminal::END:
        out << "END";
        break;
    case Terminal::DESCRIPTION:
        out << "DESCRIPTION";
        break;
    case Terminal::DESCR:
        out << "DESCR";
        break;
    case Terminal::TYPE:
        out << "TYPE";
        break;
    case Terminal::VAR_LIST:
        out << "VAR_LIST";
        break;
    case Terminal::OPERATORS:
        out << "OPERATORS";
        break;
    case Terminal::OP:
        out << "OP";
        break;
    case Terminal::EXPR:
        out << "EXPR";
        break;
    case Terminal::SIMPLE_EXPR:
        out << "SIMPLE_EXPR";
        break;
    case Terminal::ID:
        out << "ID";
        break;
    case Terminal::CONST:
        out << "Const";
        break;
    case Terminal::INTNUMBER:
        out << "INTNUMBER";
        break;
    case Terminal::Double:
        out << "DOUBLENUMBER";
        break;
    default:
        break;
    }
    return out;
}
