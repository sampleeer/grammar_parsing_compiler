#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Lexeme.h"

// Класс узла хеш-таблицы
class Table_Node {
private:
    Lexeme _info;
    bool _isdel;
public:
    Table_Node() : _info(Lexeme()), _isdel(false) {}
    Table_Node(Lexeme& info_, bool isdel_) : _info(info_), _isdel(isdel_) {}

    friend class Hash_Table;
};

using Node = Table_Node*;

// Класс хеш-таблицы
class Hash_Table {
private:
    const size_t DEFAULT_SIZE = 7;
    // Коэффициент заполнения таблицы
    const double REHASH = 0.75;
    // Размер хеш-таблицы(без удаленных узлов)
    size_t _size;
    std::vector<Node> _table;

    // Метод рехеширования(увеличение размера выделенной памяти)
    void rehash();

    // Хеш-функция для строк
    size_t hash_function(const std::string&, size_t);

public:
    Hash_Table() : _size(0), _table(std::vector<Node>(DEFAULT_SIZE, nullptr)) {}
    Hash_Table(const Hash_Table&);
    ~Hash_Table();

    size_t size() const { return _size; }

    void add(Lexeme);
    void remove(Lexeme);

    // Метод возвращает токен с данным текстовым представлением
    Lexeme find_lexeme(std::string&);

    // Метод печати хеш-таблицы в консоль
    void print();

    // Метод возвращает вектор данных хеш-таблицы
    std::vector<std::pair<size_t, Lexeme>> to_vector() const;
};

#endif // HASH_TABLE_H
