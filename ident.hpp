#ifndef IDENT_HPP
#define IDENT_HPP

#include "lex.hpp"
#include <string>


class Ident {
public:
    Ident() : declare(false), assign(false) {}
    Ident(const std::string n);\

    bool operator== (const std::string& s) const;
    
    string get_name() const;
    bool get_declare() const;
    void put_declare();
    type_of_lex get_type();
    void put_type(type_of_lex t);
    bool get_assign() const;
    void put_assign();
    int get_value() const;
    void put_value(int v);
private:
    std::string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
};


#endif