#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Lexeme.h"

// ����� ���� ���-�������
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

// ����� ���-�������
class Hash_Table {
private:
    const size_t DEFAULT_SIZE = 7;
    // ����������� ���������� �������
    const double REHASH = 0.75;
    // ������ ���-�������(��� ��������� �����)
    size_t _size;
    std::vector<Node> _table;

    // ����� �������������(���������� ������� ���������� ������)
    void rehash();

    // ���-������� ��� �����
    size_t hash_function(const std::string&, size_t);

public:
    Hash_Table() : _size(0), _table(std::vector<Node>(DEFAULT_SIZE, nullptr)) {}
    Hash_Table(const Hash_Table&);
    ~Hash_Table();

    size_t size() const { return _size; }

    void add(Lexeme);
    void remove(Lexeme);

    // ����� ���������� ����� � ������ ��������� ��������������
    Lexeme find_lexeme(std::string&);

    // ����� ������ ���-������� � �������
    void print();

    // ����� ���������� ������ ������ ���-�������
    std::vector<std::pair<size_t, Lexeme>> to_vector() const;
};

#endif // HASH_TABLE_H
