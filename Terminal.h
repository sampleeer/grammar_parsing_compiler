#ifndef TERMINAL_H
#define TERMINAL_H

#include "lexical_item.h"

//Класс Терминалов
class Terminal : public lexical_item {
public:
    enum type_terminal {
        PROGRAM, BEGIN, END,
        DESCRIPTION, DESCR,
        TYPE, VAR_LIST,
        OPERATORS, OP,
        EXPR, SIMPLE_EXPR,
        ID, CONST,
        INTNUMBER, RBRACES, Double,
        LBRACES,
    };
    Terminal() : _type(PROGRAM) {}
    Terminal(type_terminal type_) : _type(type_) {}
    Terminal(const Terminal& obj) : _type(obj._type) {}

    type_terminal type() const { return _type; }

    //Возвращает тип узла для дерева
    std::string node_type() const { return "terminal"; }

    friend std::ostream& operator<<(std::ostream&, const Terminal&);

private:
    type_terminal _type;
};

#endif // TERMINAL_H
