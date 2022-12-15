#include "Lexical_Analyzer.h"
#include <cctype>
#include <algorithm>

//Обновлени позиции анализатора
void Lexical_Analyzer::update_position(const char str) {
    if (str == '\n')
        _position._pos.push_back(0);
    else
        (*_position._pos.rbegin())++;

    _position._last_read_word += str;
}

//Проверка на тип лексемы
bool Lexical_Analyzer::is_separators(char str) {
    std::vector<char> sep_symbol = { '+', '-', '(', ')', ',', '=','/','*',';','}','{' };
    return std::find(sep_symbol.begin(), sep_symbol.end(), str) != sep_symbol.end();
}
bool Lexical_Analyzer::is_separators(std::string& str) {
    std::vector<std::string> sep_symbol = { "/","*","+", "-", "(", ")", ",", "=",";","{","}" };
    return std::find(sep_symbol.begin(), sep_symbol.end(), str) != sep_symbol.end();
}

bool Lexical_Analyzer::is_keyword(std::string& str) {
    return str == "PROGRAM" ||
        str == "END" ||
        //str == "INTEGER" || 
        str == "INT" ||
        str == "Double" ||
        str == "RETURN" ||
        str == "itod" ||
        str == "dtoi";
}

//Возвращет тип лексемы
type_lexeme Lexical_Analyzer::get_separator_type(std::string& str) {
    if (str == "+") return SUM;
    if (str == "-") return MINUS;
    if (str == "(") return LBRACKET;
    if (str == ")") return RBRACKET;
    if (str == ",") return COMMA;
    if (str == ";") return SEMICOLON;
    if (str == "}") return RBRACES;
    if (str == "{") return LBRACES;
    if (str == "=") return EQUALS;
    return UNKNOWN;
}
type_lexeme Lexical_Analyzer::get_keyword_type(std::string& str) {
    if (str == "PROGRAM") return PROGRAM;
    if (str == "RETURN") return END;
    if (str == "INTEGER") return INTEGER;
    if (str == "INT") return INT;
    if (str == "Double") return Double;
    if (str == "itod") return itod;
    if (str == "dtoi") return dtoi;
    return UNKNOWN;
}

//Возвращает следущее по тексту слово
std::string Lexical_Analyzer::get_next_word() {
    std::string word;
    _position._last_read_word = "";
    while (true) {
        char symbol;
        _input_text.get(symbol);

        if (_input_text.eof()) break;
        update_position(symbol);

        if (symbol == ' ' || symbol == '\n' || symbol == '\t') {
            if (word.empty()) continue;
            return word;
        }

        if (is_separators(symbol)) {
            if (word.empty())
                return word + symbol;
            //Если кроме сепараторов что-то уже было, то возвращаем лишний прочитанный сепаратор
            _input_text.unget();
            //и обновляем поизицию в тексте
            (*_position._pos.rbegin())--;
            return word;
        }
        word += symbol;
    }
    return word;
}

Lexical_Analyzer::Lexical_Analyzer(const char* file_name) {
    std::ifstream fin(file_name);
    _input_text << fin.rdbuf();
    fin.close();
    _position._pos = std::vector<int>(1);
}

//Возвращет следущую по тексту лексему
Lexeme Lexical_Analyzer::get_next_lexeme() {
    std::string curr_word = get_next_word();

    if (curr_word.empty()) return Lexeme();
    if (is_separators(curr_word)) {
        _lexemes.add(Lexeme(get_separator_type(curr_word), curr_word));
        return Lexeme(get_separator_type(curr_word), curr_word);
    }
    if (is_keyword(curr_word)) {
        _lexemes.add(Lexeme(get_keyword_type(curr_word), curr_word));
        return { get_keyword_type(curr_word), curr_word };
    }

    DFSM automat;
    _lexemes.add(Lexeme(automat.getTypeLex(curr_word), curr_word));
    return Lexeme(automat.getTypeLex(curr_word), curr_word);
}

//Откат прочитанного слова
void Lexical_Analyzer::return_last_read_word() {
    std::reverse(_position._last_read_word.begin(), _position._last_read_word.end());
    for (const char& symbol : _position._last_read_word) {
        if (symbol == '\n' || (*_position._pos.rbegin()) == 0)
            _position._pos.pop_back();
        else
            (*_position._pos.rbegin())--;
        _input_text.putback(symbol);
    }
    if (*_position._pos.rbegin() == 0)
        _position._pos.pop_back();
}

// Метод возвращает хеш таблицу со всеми лексемами прочитанными из файла
Hash_Table Lexical_Analyzer::get_all_lexemes() {
    DFSM automat = DFSM();
    while (true) {
        Lexeme curr = get_next_lexeme();

        if (_input_text.eof()) break;
        if (curr.text().empty()) continue;

        _lexemes.add(curr);
    }
    return _lexemes;
}