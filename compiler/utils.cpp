//
//  utils.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/21/21.
//

#include "utils.hpp"

namespace luabythec
{
namespace utils
{

namespace
{
int indentation = 0;
}

//--- Output end of line and add indentation
std::ostream &
endi (std::ostream &os)
{
    os << '\n';
    for (int i = 0; i < indentation; ++i)
        os << ' ';
    return os;
}

//--- Increase indentation
std::ostream &
indent (std::ostream &os)
{
    indentation += 4;
    os << endi;
    return os;
}
//--- Decrease indentation
std::ostream &
outdent (std::ostream &os)
{
    indentation >= 4 ? indentation -= 4 : indentation;
    os << endi;
    return os;
}

}
}
