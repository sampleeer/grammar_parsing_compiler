#ifndef LEXICAL_ITEM_H
#define LEXICAL_ITEM_H

#include <iostream>
#include <string>

//Интерфейс узла для дерева разбора
class lexical_item {
public:
    virtual ~lexical_item() {}
    virtual std::string  node_type() const = 0;
};

#endif // LEXICAL_ITEM_H

