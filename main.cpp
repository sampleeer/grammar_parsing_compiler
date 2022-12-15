#include <vector>
#include <algorithm>
#include "Hash_Table.h"
#include "Lexical_Analyzer.h"
#include "Syntax_Analyzer.h"
#include "Parse_Tree.h"

bool cmp(const std::pair<size_t, Lexeme>& first, const std::pair<size_t, Lexeme>& second) {
    return first.second.type() < second.second.type();
}

// Функция выводит в файл отсортированную хеш таблицу
void print_hash_table_vc(std::vector<std::pair<size_t, Lexeme>>& res_to_arr, std::ofstream& fout) {
    sort(res_to_arr.begin(), res_to_arr.end(), cmp);
    for (const auto& item : res_to_arr)
        fout << "Key=" << item.first << '\t' << item.second << '\n';
}

int main() {
    std::ofstream fout("output.txt");
    Syntax_Analyzer par("input.txt");

    if (par.go_analyze()) {
        fout << "HASH TABLE\n\n";
        Hash_Table res = par.get_hash_table();
        std::vector<std::pair<size_t, Lexeme>> res_arr = res.to_vector();
        print_hash_table_vc(res_arr, fout);
        fout << "\nTREE\n\n";
        par.print_tree(fout);
        std::cout << "No error\n";
    }
    else {
        std::cout << "Error\n";
    }

    fout.close();
    return 0;
}