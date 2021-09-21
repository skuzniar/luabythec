//
//  utils.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/21/21.
//

#ifndef utils_hpp
#define utils_hpp

#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

namespace luabythec {
namespace utils {

inline std::string Package()
{
    return "luabythec";
}

inline std::string StripProto(const std::string& filename)
{
    return filename.substr(0, filename.rfind(".proto"));
}

inline std::string Stem(const std::string& name, char delimiter='.')
{
    auto pos = name.rfind(delimiter);
    return name.substr(0, pos == std::string::npos ? 0 : pos);
}

inline std::string Filename(const std::string& path)
{
    return Stem(path, '/');
}

inline std::string Replace(std::string str, const std::string& from, const std::string& to)
{
    for (auto p = str.find(from); p != std::string::npos; p = str.find(from, p + to.length()))
    {
        str.replace(p, from.length(), to);
    }
    return str;
}

inline std::string Type(std::string name)
{
    return Replace(name, ".", "::");
}

inline std::vector<std::string> Tokenize(const std::string& src, const std::string& delimiters = " ")
{
    std::string::size_type val_pos = src.find_first_not_of(delimiters, 0);
    std::string::size_type dlm_pos = src.find_first_of(delimiters, val_pos);

    std::vector<std::string> tokens;
    while (std::string::npos != dlm_pos || std::string::npos != val_pos)
    {
        tokens.push_back(src.substr(val_pos, dlm_pos - val_pos));
        val_pos = src.find_first_not_of(delimiters, dlm_pos);
        dlm_pos = src.find_first_of(delimiters, val_pos);
    }
    return tokens;
}

// End of line indentation manipulator
std::ostream& endi   (std::ostream& os);
std::ostream& indent (std::ostream& os);
std::ostream& outdent(std::ostream& os);

// Arrange the range such that the same elements are grouped together.
template <typename ITER, typename PRED>
void Group(ITER b, ITER e, PRED p)
{
    while (b != e)
    {
        b = std::stable_partition(std::next(b), e, [=](const auto& item) { return p(*b, item); });
    }
}

}
}


#endif /* utils_hpp */
