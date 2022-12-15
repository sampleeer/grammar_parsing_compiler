#include "Parse_Tree.h"

Tree_Node::Tree_Node(const Tree_Node& obj) {
    _children = std::vector<std::shared_ptr<Tree_Node>>(obj._children);
    if (obj._value == nullptr) {
        _value = nullptr;
        return;
    }
    if (obj._value->node_type() == "terminal")
        _value = std::dynamic_pointer_cast<Terminal>(obj._value);
    if (obj._value->node_type() == "lexeme")
        _value = std::dynamic_pointer_cast<Lexeme>(obj._value);
}

//Печатает дерево
void Parse_Tree::print(std::ostream& out) {
    print(out, _root, 0);
}

//Добавление узлов дерева
void Parse_Tree::add_lexeme(const Terminal& add_to, const Lexeme& lex) {
    add_lexeme(add_to, lex, _root);
}
void Parse_Tree::add_product(const Terminal& add_to, const product& prdct) {
    add_product(add_to, prdct, _root);
}

bool Parse_Tree::add_lexeme(const Terminal& add_to, const Lexeme& lex, node& position) {
    if (!position) return false;

    if (position->_value->node_type() == "terminal" && position->_children.empty()) {
        Terminal temp = *std::dynamic_pointer_cast<Terminal>(position->_value);
        if (temp.type() == add_to.type()) {
            position->_children.push_back(std::make_shared<Tree_Node>(lex));
            return true;
        }
    }
    for (auto& item : position->_children)
        if (add_lexeme(add_to, lex, item))
            return true;
    return false;
}
bool Parse_Tree::add_product(const Terminal& add_to, const product& prdct, node& position) {
    if (!position) return false;
    if (position->_value->node_type() == "terminal" && position->_children.empty()) {
        Terminal temp = *std::dynamic_pointer_cast<Terminal>(position->_value);
        if (temp.type() == add_to.type()) {
            add_product_items(position->_children, prdct);
            return true;
        }
    }
    for (auto& item : position->_children)
        if (add_product(add_to, prdct, item))
            return true;
    return false;
}
void Parse_Tree::add_product_items(std::vector<std::shared_ptr<Tree_Node>>& children, const product& prdct) {
    if (prdct == PROGRAM) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::BEGIN }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::DESCRIPTION }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::OPERATORS }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::END }));
    }
    else if (prdct == BEGIN) {
        //children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::PROGRAM, "PROGRAM" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::LBRACKET, "(" }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::RBRACKET, ")" }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::LBRACES, "{" }));
    }
    else if (prdct == END) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::END, "return" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::SEMICOLON, ";" }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::RBRACES, "}" }));

    }
    else if (prdct == DESCRIPTION_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::DESCR }));
    }
    else if (prdct == DESCRIPTION_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::DESCR }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::DESCRIPTION }));
    }
    else if (prdct == OPERATORS_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::OP }));
    }
    else if (prdct == OPERATORS_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::OP }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::OPERATORS }));
    }
    else if (prdct == DESCR) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::TYPE }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::VAR_LIST }));
    }
    else if (prdct == TYPE_1) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::INT, "INT" }));
    }
    else if (prdct == TYPE_2) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::Double, "Double" }));
    }
    else if (prdct == VAR_LIST_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
    }
    else if (prdct == VAR_LIST_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::COMMA, "," }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::VAR_LIST }));
    }
    else if (prdct == OP) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::EQUALS, "=" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
    }
    else if (prdct == SIMPLE_EXPR_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::ID }));
    }
    else if (prdct == SIMPLE_EXPR_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::CONST }));
    }
    else if (prdct == SIMPLE_EXPR_3) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::LBRACKET, "(" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::RBRACKET, ")" }));
    }
    else if (prdct == SIMPLE_EXPR_4) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::itod, "itod" }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::LBRACKET, "(" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::RBRACKET, ")" }));
    }
    else if (prdct == SIMPLE_EXPR_5) {
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::dtoi, "dtoi" }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::LBRACKET, "(" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::RBRACKET, ")" }));
    }
    else if (prdct == EXPR_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::SIMPLE_EXPR }));
    }
    else if (prdct == EXPR_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::SIMPLE_EXPR }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::SUM, "+" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
    }
    else if (prdct == EXPR_3) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::SIMPLE_EXPR }));
        children.push_back(std::make_shared<Tree_Node>(Lexeme{ type_lexeme::MINUS, "-" }));
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::EXPR }));
    }
    else if (prdct == CONST_1) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::INTNUMBER }));
    }
    else if (prdct == CONST_2) {
        children.push_back(std::make_shared<Tree_Node>(Terminal{ Terminal::Double }));
    }
}

//Вставка и добавление поддеревьев
void Parse_Tree::insert_tree(const Terminal& add_to, const Parse_Tree& tree, const node& position) {
    if (!position) return;
    for (auto& item : position->_children) {
        if (item->_value->node_type() == "terminal" && item->_children.empty()) {
            Terminal temp = *std::dynamic_pointer_cast<Terminal>(item->_value);
            if (temp.type() == add_to.type()) {
                item = nullptr;
                copy_tree(item, tree._root);
                return;
            }
        }
        insert_tree(add_to, tree, item);
    }
}
void Parse_Tree::add_tree(const Terminal& add_to, const Parse_Tree& tree, const node& position) {
    if (!position) return;
    if (position->_value->node_type() == "terminal" && position->_children.empty()) {
        Terminal temp = *std::dynamic_pointer_cast<Terminal>(position->_value);
        if (temp.type() == add_to.type()) {
            position->_children.push_back(std::make_shared<Tree_Node>());
            copy_tree(*position->_children.begin(), tree._root);
            return;
        }
    }
    for (const auto& item : position->_children)
        add_tree(add_to, tree, item);
}
void Parse_Tree::copy_tree(node& to_, node from_) {
    to_ = std::make_shared<Tree_Node>(*from_);
    for (size_t i = 0; i < from_->_children.size(); i++)
        copy_tree(to_->_children[i], from_->_children[i]);
}

//Печатает дерево
void Parse_Tree::print(std::ostream& out, node position, size_t level) {
    if (!position)
        return;
    if (level != 0)
        out << "	*	*	*	*	";
    if (position->_value->node_type() == "terminal")
        out << *std::dynamic_pointer_cast<Terminal>(position->_value);
    if (position->_value->node_type() == "lexeme")
        out << *std::dynamic_pointer_cast<Lexeme>(position->_value);
    out << '\n';
    bool flag = true;
    for (auto& item : position->_children) {
        for (size_t i = 0; i < level; i++)
            out << "*\t";
        out << "*";
        print(out, item, level + 1);
    }
}
