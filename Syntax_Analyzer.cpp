#include "Syntax_Analyzer.h"

//Проверка слова на лексические ошибки
void Syntax_Analyzer::check_lexical_error(Lexeme& curr) {
    if (curr.type() == UNKNOWN && !curr.text().empty()) {
        std::cout << "Unknown lexeme " << curr.text() << '\n';
    }
}


//Обработка начала файла
bool Syntax_Analyzer::begin(Parse_Tree& tree_) {
    tree_.add_product(Terminal::BEGIN, Parse_Tree::BEGIN);
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != INT) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the start of FUNCTION: the start of FUNCTION should starts with TYPE\n";
        return false;
    }
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != ID) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the function name: the name must be the correct identifier\n";
        return false;
    }
    tree_.add_lexeme(Terminal::ID, curr_lex);
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != LBRACKET) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the start of FUNCTION: the start of FUNCTION should starts with (\n";
        return false;
    }
    tree_.add_lexeme(Terminal::BEGIN, curr_lex);
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != RBRACKET) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the start of FUNCTION: the start of FUNCTION should starts with )\n";
        return false;
    }
    tree_.add_lexeme(Terminal::BEGIN, curr_lex);
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != LBRACES) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the start of FUNCTION: the start of FUNCTION should starts with {\n";
        return false;
    }
    tree_.add_lexeme(Terminal::BEGIN, curr_lex);
    return true;
}


//Обработка инициализации переменных
bool Syntax_Analyzer::description(Parse_Tree& tree_) {
    Parse_Tree short_d_tree(Terminal::DESCR);
    if (!short_descriptions(short_d_tree))
        return false;
    while (true) {
        Lexeme curr_lex = _lexemes.get_next_lexeme();
        if (curr_lex.type() != INT && curr_lex.type() != Double) {
            _lexemes.return_last_read_word();
            tree_.add_tree(Terminal::DESCRIPTION, short_d_tree);
            return true;
        }

        tree_.add_product(Terminal::DESCRIPTION, Parse_Tree::DESCRIPTION_2);
        tree_.insert_tree(Terminal::DESCR, short_d_tree);
        short_d_tree.clear();

        _lexemes.return_last_read_word();
        if (!short_descriptions(short_d_tree))
            return false;
    }
}
bool Syntax_Analyzer::short_descriptions(Parse_Tree& tree_) {
    tree_.add_product(Terminal::DESCR, Parse_Tree::DESCR);
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != INT && curr_lex.type() != Double) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the description: the description should start with the type of variable\n";
    }
    if (curr_lex.type() == INT)
        tree_.add_product(Terminal::TYPE, Parse_Tree::TYPE_1);
    else if (curr_lex.type() == Double)
        tree_.add_product(Terminal::TYPE, Parse_Tree::TYPE_2);

    Parse_Tree var_list_tree(Terminal::VAR_LIST);
    if (!var_list(var_list_tree))
        return false;

    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != SEMICOLON) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "error in the descr ending: no identifier ;\n";
        return false;
    }
    tree_.insert_tree(Terminal::VAR_LIST, var_list_tree);
    return true;
}







bool Syntax_Analyzer::var_list(Parse_Tree& tree_) {
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != ID) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the description: no identifier in description\n";
        return false;
    }
    Lexeme prev = curr_lex;
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != COMMA) {
        _lexemes.return_last_read_word();
        tree_.add_product(Terminal::VAR_LIST, Parse_Tree::VAR_LIST_1);
        tree_.add_lexeme(Terminal::ID, prev);
        return true;
    }

    tree_.add_product(Terminal::VAR_LIST, Parse_Tree::VAR_LIST_2);
    tree_.add_lexeme(Terminal::ID, prev);
    return var_list(tree_);
}


//Обработка операций
bool Syntax_Analyzer::operators(Parse_Tree& tree_) {
    Parse_Tree short_o_tree(Terminal::OP);
    if (!short_operators(short_o_tree))
        return false;
    while (true) {
        Lexeme curr_lex = _lexemes.get_next_lexeme();
        if (curr_lex.type() != ID) {
            _lexemes.return_last_read_word();
            tree_.add_tree(Terminal::OPERATORS, short_o_tree);
            return true;
        }
        tree_.add_product(Terminal::OPERATORS, Parse_Tree::OPERATORS_2);
        tree_.insert_tree(Terminal::OP, short_o_tree);
        short_o_tree.clear();
        _lexemes.return_last_read_word();
        if (!short_operators(short_o_tree))
            return false;
    }
}

bool Syntax_Analyzer::short_operators(Parse_Tree& tree_) {
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != ID) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in operators: expression must be assigned to the variable\n";
        return false;
    }
    Lexeme prev = curr_lex;
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != EQUALS) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in operators: not find =\n";
        return false;
    }

    tree_.add_product(Terminal::OP, Parse_Tree::OP);
    tree_.add_lexeme(Terminal::ID, prev);
    Parse_Tree expr_tree(Terminal::EXPR);

    if (!expr(expr_tree))
        return false;
    tree_.insert_tree(Terminal::EXPR, expr_tree);
    expr_tree.clear();
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != SEMICOLON) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "error in the OP ending: no identifier ;\n";
        return false;
    }
    return true;
}

bool Syntax_Analyzer::expr(Parse_Tree& tree_) {
    Parse_Tree simple_expr_tree(Terminal::SIMPLE_EXPR);
    if (!simple_expr(simple_expr_tree))
        return false;
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != SUM && curr_lex.type() != MINUS) {
        _lexemes.return_last_read_word();
        tree_.add_product(Terminal::EXPR, Parse_Tree::EXPR_1);
        tree_.insert_tree(Terminal::SIMPLE_EXPR, simple_expr_tree);
        return true;
    }
    if (curr_lex.type() == SUM) {
        tree_.add_product(Terminal::EXPR, Parse_Tree::EXPR_2);
        tree_.insert_tree(Terminal::SIMPLE_EXPR, simple_expr_tree);
    }
    else if (curr_lex.type() == MINUS) {
        tree_.add_product(Terminal::EXPR, Parse_Tree::EXPR_3);
        tree_.insert_tree(Terminal::SIMPLE_EXPR, simple_expr_tree);
    }
    return expr(tree_);
}

bool Syntax_Analyzer::simple_expr(Parse_Tree& tree_) {
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() == LBRACKET) {
        tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_3);
        Parse_Tree expr_tree(Terminal::EXPR);
        if (!expr(expr_tree))
            return false;
        curr_pos = _lexemes.position();
        curr_lex = _lexemes.get_next_lexeme();
        if (curr_lex.type() != RBRACKET) {
            check_lexical_error(curr_lex);
            std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
            std::cout << "Error in simple number expression: not find )\n";
            return false;
        }
        tree_.insert_tree(Terminal::EXPR, expr_tree);
        return true;
    }

    position prev_pos = curr_pos;
    if (curr_lex.type() == itod || curr_lex.type() == dtoi) {
        Lexeme prev = curr_lex;
        curr_pos = _lexemes.position();
        curr_lex = _lexemes.get_next_lexeme();
        if (curr_lex.type() == LBRACKET) {
            if (prev.type() == itod)
                tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_4);
            else if (prev.type() == dtoi)
                tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_5);
            Parse_Tree expr_tree(Terminal::EXPR);
            if (!expr(expr_tree))
                return false;
            curr_pos = _lexemes.position();
            curr_lex = _lexemes.get_next_lexeme();
            if (curr_lex.type() != RBRACKET) {
                check_lexical_error(curr_lex);
                std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
                std::cout << "Error in " << prev.text() << " expression: not find )\n";
                return false;
            }
            tree_.insert_tree(Terminal::EXPR, expr_tree);
            return true;
        }
        else {
            check_lexical_error(curr_lex);
            std::cout << curr_pos._pos.size() << ':' << *prev_pos._pos.rbegin() << ' ';
            std::cout << "Error in " << prev.text() << " expression: not find (\n";
            return false;
        }
    }

    if (curr_lex.type() != ID && curr_lex.type() != INTNUMBER && curr_lex.type() != DoubleNUMBER) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in simple number expression: " << curr_lex.text()
            << " must be a number or a variable\n";
        return false;
    }

    if (curr_lex.type() == ID) {
        tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_1);
        tree_.add_lexeme(Terminal::ID, curr_lex);
    }
    else if (curr_lex.type() == INTNUMBER) {
        tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_2);
        tree_.add_product(Terminal::CONST, Parse_Tree::CONST_1);
        tree_.add_lexeme(Terminal::INTNUMBER, curr_lex);
    }
    else if (curr_lex.type() == DoubleNUMBER) {
        tree_.add_product(Terminal::SIMPLE_EXPR, Parse_Tree::SIMPLE_EXPR_2);
        tree_.add_product(Terminal::CONST, Parse_Tree::CONST_2);
        tree_.add_lexeme(Terminal::Double, curr_lex);
    }

    return true;
}


//Обработка конца файла
bool Syntax_Analyzer::end(Parse_Tree& tree_) {
    tree_.add_product(Terminal::END, Parse_Tree::END);
    position curr_pos = _lexemes.position();
    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != END) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "error in the function ending: no keyword END\n";
        return false;
    }

    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != ID) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "error in the function ending: no identifier\n";
        return false;
    }
    tree_.add_lexeme(Terminal::ID, curr_lex);
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != SEMICOLON) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "error in the function ending: no identifier ;\n";
        return false;
    }
    //tree_.add_lexeme(Terminal::END, curr_lex);
    curr_pos = _lexemes.position();
    curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() != RBRACES) {
        check_lexical_error(curr_lex);
        std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
        std::cout << "Error in the end of FUNCTION: the end of FUNCTION should starts with }\n";
        return false;
    }
    //tree_.add_lexeme(Terminal::END, curr_lex);
    return true;
}


//Основная функция анализа возвращает true если текст был обработан без ошибок и false если есть ошибки 
bool Syntax_Analyzer::go_analyze() {
    _tree.add_product(Terminal::PROGRAM, Parse_Tree::product::PROGRAM);

    Parse_Tree b_tree(Terminal::BEGIN);
    if (!begin(b_tree))
        return false;
    _tree.insert_tree(Terminal::BEGIN, b_tree);

    Parse_Tree d_tree(Terminal::DESCRIPTION);
    if (!description(d_tree))
        return false;
    _tree.insert_tree(Terminal::DESCRIPTION, d_tree);

    Parse_Tree o_tree(Terminal::OPERATORS);
    if (!operators(o_tree))
        return false;
    _tree.insert_tree(Terminal::OPERATORS, o_tree);

    Parse_Tree e_tree(Terminal::END);
    if (!end(e_tree))
        return false;
    _tree.insert_tree(Terminal::END, e_tree);

    Lexeme curr_lex = _lexemes.get_next_lexeme();
    if (curr_lex.type() == UNKNOWN && curr_lex.text().empty())
        return true;
    position curr_pos = _lexemes.position();
    std::cout << curr_pos._pos.size() << ':' << *curr_pos._pos.rbegin() << ' ';
    std::cout << "Error: no more one function\n";
    return false;
}

