#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "DFSM.h"
#include "Lexeme.h"
#include "Hash_Table.h"

//Текущее расположение анализатора и последнея прочитанная лексема 
struct position {
    std::vector<int> _pos;
    std::string _last_read_word;
};

// Класс лексического анализатора
class Lexical_Analyzer {
    // Входящий текст
    std::stringstream _input_text;
    position _position;
    Hash_Table _lexemes;

    //Обновлени позиции анализатора
    void update_position(char);

    //Проверка на тип лексемы
    bool is_separators(char);
    bool is_separators(std::string&);
    bool is_keyword(std::string&);

    //Возвращет тип лексемы
    type_lexeme get_separator_type(std::string&);
    type_lexeme get_keyword_type(std::string&);

    //Возвращает следущее по тексту слово
    std::string get_next_word();
public:
    Lexical_Analyzer(const char*);
    ~Lexical_Analyzer() { _input_text.clear(); }

    //Возвращает хеш-таблицу 
    Hash_Table get_lexemes_hash_table() { return _lexemes; }
    //Возвращет текущую позицию анализатора и последнюю прочитанную лексему
    position position() const { return _position; }

    //Возвращет следущую по тексту лексему
    Lexeme get_next_lexeme();

    //Откат прочитанного слова
    void return_last_read_word();

    // Метод возвращает хеш таблицу со всеми лексемами прочитанными из файла
    Hash_Table get_all_lexemes();
};

#endif // LEXICAL_ANALYZER_H

