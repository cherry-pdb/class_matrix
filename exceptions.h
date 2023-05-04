#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class Exceptions
{
    std::string err_text;
public:
    explicit Exceptions(std::string str) {err_text = std::move(str);}
    friend std::ostream& operator << (std::ostream &os, Exceptions &exc);
};

#endif // EXCEPTIONS_H
