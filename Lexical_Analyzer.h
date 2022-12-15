#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "DFSM.h"
#include "Lexeme.h"
#include "Hash_Table.h"

//������� ������������ ����������� � ��������� ����������� ������� 
struct position {
    std::vector<int> _pos;
    std::string _last_read_word;
};

// ����� ������������ �����������
class Lexical_Analyzer {
    // �������� �����
    std::stringstream _input_text;
    position _position;
    Hash_Table _lexemes;

    //��������� ������� �����������
    void update_position(char);

    //�������� �� ��� �������
    bool is_separators(char);
    bool is_separators(std::string&);
    bool is_keyword(std::string&);

    //��������� ��� �������
    type_lexeme get_separator_type(std::string&);
    type_lexeme get_keyword_type(std::string&);

    //���������� �������� �� ������ �����
    std::string get_next_word();
public:
    Lexical_Analyzer(const char*);
    ~Lexical_Analyzer() { _input_text.clear(); }

    //���������� ���-������� 
    Hash_Table get_lexemes_hash_table() { return _lexemes; }
    //��������� ������� ������� ����������� � ��������� ����������� �������
    position position() const { return _position; }

    //��������� �������� �� ������ �������
    Lexeme get_next_lexeme();

    //����� ������������ �����
    void return_last_read_word();

    // ����� ���������� ��� ������� �� ����� ��������� ������������ �� �����
    Hash_Table get_all_lexemes();
};

#endif // LEXICAL_ANALYZER_H

