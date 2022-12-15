#ifndef PARSER_H
#define PARSER_H

#include "Lexical_Analyzer.h"
#include "Lexeme.h"
#include "Parse_Tree.h"

//Класс синтаксического анализатора
class Syntax_Analyzer {
private:
    Lexical_Analyzer _lexemes;
    Parse_Tree _tree;

    //Проверка лексических ошибок слова
    void check_lexical_error(Lexeme& curr);

    //Обработчики текста по грамматике
    bool begin(Parse_Tree&);

    bool description(Parse_Tree&);
    bool short_descriptions(Parse_Tree&);
    bool var_list(Parse_Tree&);

    bool operators(Parse_Tree&);
    bool short_operators(Parse_Tree&);
    bool expr(Parse_Tree&);
    bool simple_expr(Parse_Tree&);
    bool string_expr(Parse_Tree&);

    bool end(Parse_Tree&);

public:
    Syntax_Analyzer(const char* file_name) : _lexemes(file_name) {}

    //Печатает дерево 
    void print_tree(std::ostream& out) { _tree.print(out); }
    //Возвращает дерево
    Parse_Tree get_tree() const { return _tree; }
    //Возвращает хеш-таблицу по тексту
    Hash_Table get_hash_table() { return _lexemes.get_lexemes_hash_table(); }

    //Основная функция анализа возвращает true если текст был обработан без ошибок и false если есть ошибки 
    bool go_analyze();
};


#endif // PARSER_H


