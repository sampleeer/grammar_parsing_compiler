cmake_minimum_required(VERSION 3.24)
project(grammar_parsing_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(grammar_parsing_compiler
        DFSM.cpp
        DFSM.h
        Hash_Table.cpp
        Hash_Table.h
        Lexeme.cpp
        Lexeme.h
        Lexical_Analyzer.cpp
        Lexical_Analyzer.h
        lexical_item.h
        main.cpp
        Parse_Tree.cpp
        Parse_Tree.h
        Syntax_Analyzer.cpp
        Syntax_Analyzer.h
        Terminal.cpp
        Terminal.h)
