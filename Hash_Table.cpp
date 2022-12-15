#include "Hash_Table.h"

// Метод рехеширования(увеличение размера выделенной памяти)
void Hash_Table::rehash() {
    _size = 0;
    std::vector<Node> arr(_table);
    std::fill(_table.begin(), _table.end(), nullptr);
    _table.resize(_table.size() * 2, nullptr);

    for (auto& item : arr)
        if (item != nullptr && !item->_isdel)
            add(item->_info);

    for (auto& item : arr)
        delete item;
}

// Хеш-функция для строк
size_t Hash_Table::hash_function(const std::string& str, const size_t table_size) {
    size_t hash_result = 0;
    const size_t coef = 53;

    for (char item : str)
        hash_result = (coef * hash_result + item) % table_size;
    hash_result = (hash_result * 2 + 1) % table_size;

    return hash_result;
}

Hash_Table::Hash_Table(const Hash_Table& obj) : _size(obj._size) {
    _table = std::vector<Node>(obj._table.size(), nullptr);
    for (size_t i = 0; i < obj._table.size(); i++) {
        if (obj._table[i] == nullptr) continue;
        _table[i] = new Table_Node(obj._table[i]->_info, obj._table[i]->_isdel);
    }
}

Hash_Table::~Hash_Table() {
    for (auto& item : _table)
        delete item;
    _table.clear();
}

void Hash_Table::add(Lexeme value) {
    if (REHASH <= (_size * 1.0 / _table.size()))
        rehash();

    size_t idx = hash_function(value.text(), _table.size());
    // Ищем место, куда можно вставить элемент
    while (_table[idx] != nullptr && !_table[idx]->_isdel) {
        if (_table[idx]->_info == value) return;
        idx = (idx + 1) % _table.size();
    }

    _size++;
    if (_table[idx] == nullptr) {
        _table[idx] = new Table_Node(value, false);
    }
    else {
        _table[idx]->_info = value;
        _table[idx]->_isdel = false;
    }
}

void Hash_Table::remove(Lexeme value) {
    size_t idx = hash_function(value.text(), _table.size());
    while (_table[idx] != nullptr) {
        if (_table[idx]->_info == value) {
            _table[idx]->_isdel = true;
            _size--;
            return;
        }
        idx++;
    }
}

// Метод возвращает лексему
Lexeme Hash_Table::find_lexeme(std::string& text) {
    size_t idx = hash_function(text, _table.size());
    while (_table[idx] != nullptr && _table[idx]->_info.text() != text)
        idx = (idx + 1) % _table.size();
    if (_table[idx] != nullptr && _table[idx]->_info.text() == text && !_table[idx]->_isdel)
        return _table[idx]->_info;
    return Lexeme();
}

// Метод печати хеш-таблицы в консоль
void Hash_Table::print() {
    for (int i = 0; i < _table.size(); i++) {
        if (_table[i] == nullptr || _table[i]->_isdel) continue;
        std::cout << "Key: " << i << "\tvalue: " << _table[i]->_info << '\n';
    }
}

// Метод возвращает вектор данных хеш-таблицы
std::vector<std::pair<size_t, Lexeme>> Hash_Table::to_vector() const {
    std::vector<std::pair<size_t, Lexeme>> res;
    for (size_t i = 0; i < _table.size(); i++) {
        if (_table[i] == nullptr || _table[i]->_isdel) continue;
        Lexeme lx(_table[i]->_info);
        res.push_back(std::make_pair(i, lx));
    }
    return res;
}
