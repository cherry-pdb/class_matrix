#include "exceptions.h"

std::ostream& operator << (std::ostream &os, Exceptions &exc)
{
    os << "error: " << exc.err_text << std::endl;
    return os;
}
