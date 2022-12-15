#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include "lexical_item.h"
#include "Lexeme.h"
#include "terminal.h"
#include <vector>

using pitem = std::shared_ptr<lexical_item>;
class Parse_Tree;

//Класс узла дерева
class Tree_Node {
private:
    pitem _value;
    std::vector<std::shared_ptr<Tree_Node>> _children;

public:
    Tree_Node() : _value(nullptr), _children(std::vector<std::shared_ptr<Tree_Node>>()) {}
    Tree_Node(const Terminal& obj) : _children(std::vector<std::shared_ptr<Tree_Node>>()), _value(std::static_pointer_cast<lexical_item>(std::make_shared<Terminal>(obj))) {}
    Tree_Node(const Lexeme& obj) : _children(std::vector<std::shared_ptr<Tree_Node>>()), _value(std::static_pointer_cast<lexical_item>(std::make_shared<Lexeme>(obj))) {}
    Tree_Node(const Tree_Node&);
    friend class Parse_Tree;
};

using node = std::shared_ptr<Tree_Node>;

//Класс дерева для синтаксического анализатора
class Parse_Tree {
public:
    enum product {
        PROGRAM, BEGIN, END,
        DESCRIPTION_1, DESCRIPTION_2,
        DESCR,
        TYPE_1, TYPE_2,
        VAR_LIST_1, VAR_LIST_2,
        OPERATORS_1, OPERATORS_2,
        OP,
        EXPR_1, EXPR_2, EXPR_3,
        SIMPLE_EXPR_1, SIMPLE_EXPR_2, SIMPLE_EXPR_3, SIMPLE_EXPR_4, SIMPLE_EXPR_5,
        CONST_1, CONST_2
    };

    Parse_Tree() : _root(std::make_shared<Tree_Node>(Tree_Node{ Terminal{Terminal::PROGRAM} })) {}
    Parse_Tree(const Parse_Tree& obj) { copy_tree(_root, obj._root); }
    Parse_Tree(const Terminal& root) : _root(std::make_shared<Tree_Node>(Tree_Node(root))) {}

    //Добавление узлов дерева
    void add_lexeme(const Terminal& add_to, const Lexeme& lex);
    void add_product(const Terminal& add_to, const product& prdct);

    //Вставка и добавление поддеревьев
    void insert_tree(const Terminal& add_to, const Parse_Tree& tree_) { insert_tree(add_to, tree_, _root); }
    void add_tree(const Terminal& to_add, const Parse_Tree& tree) { add_tree(to_add, tree, _root); }

    void clear() { _root->_children.clear(); }
    //Печатает дерево
    void print(std::ostream&);
private:
    node _root;

    //Добавления узлов
    bool add_lexeme(const Terminal&, const Lexeme&, node&);
    bool add_product(const Terminal& add_to, const product& prdct, node& position);
    void add_product_items(std::vector<std::shared_ptr<Tree_Node>>&, const product&);

    //Вставка и добавление поддеревьев
    void insert_tree(const Terminal&, const Parse_Tree&, const node&);
    void add_tree(const Terminal&, const Parse_Tree&, const node&);
    void copy_tree(node&, node);

    //Печатает дерево
    void print(std::ostream& out, node pos, size_t level);
};


#endif // PARSE_TREE_H

