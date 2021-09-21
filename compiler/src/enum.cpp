//
//  enum.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 4/1/21.
//

#include "enum.hpp"
#include "field.hpp"

#include "utils.hpp"

namespace luabythec
{

using utils::endi;

EnumGenerator::EnumGenerator(const EnumDescriptor* descriptor, std::string& error)
    : m_descriptor(descriptor), m_error(error)
{
    m_full_name = m_descriptor->full_name();
    m_full_type = utils::Type(m_full_name);
    m_type      = m_descriptor->name();
}

bool EnumGenerator::Generate(std::ostream& os)
{
    return MakeBindFunction(os);
}

bool EnumGenerator::MakeBindFunction(std::ostream& os)
{
    make_bind_function(os);
    return true;
}

bool EnumGenerator::CallBindFunction(std::ostream& os)
{
    call_bind_function(os);
    return true;
}

bool EnumGenerator::make_bind_function(std::ostream& os)
{
    os  << endi
        << "//" << std::string(118, '-') << endi
        << "// Bind specialization for enum " << m_full_type << endi
        << "//" << std::string(118, '-') << endi
        << "template <>" << endi
        << "void bind<" << m_full_type << ">(sol::state& lua)" << endi;

    os  << "{" << utils::indent;
    
    os << "// Generating namespace definition" << endi;
    auto current = make_namespace("lua", os);
    
    os << endi
       << "// Generating type definition" << endi;
    make_type(current, os);

    os << utils::outdent << "}" << endi;
    
    return true;
}

bool EnumGenerator::call_bind_function(std::ostream& os)
{
    os << "bind<" << m_full_type << ">(lua);";
    return true;
}

std::string EnumGenerator::make_namespace(std::string where, std::ostream& os)
{
    for (const auto& token: utils::Tokenize(utils::Stem(m_full_name), "."))
    {
        where = make_namespace(where, token, os);
    }
    return where;
}

std::string EnumGenerator::make_namespace(std::string where, const std::string& name, std::ostream& os)
{
    os << "auto " << name << " = " << where << "[\"" << name << "\"]"
       << ".get_or_create<sol::table>();"
       << endi;
    return name;
}

void EnumGenerator::make_type(const std::string& where, std::ostream& os)
{
    os  << where << ".new_enum<" << m_full_type << '>'
        << '(' << '"' << m_type << '"' << ','
        << utils::indent << '{' << utils::indent;

    for (int i=0; i<m_descriptor->value_count(); ++i)
    {
        os  << '{' << '"' << m_descriptor->value(i)->name() << '"' << ','
            << utils::Type(m_descriptor->value(i)->full_name()) << '}';
        
        if (i + 1 < m_descriptor->value_count())
        {
            os << ',' << endi;
        }
    }
    os << utils::outdent << '}' << utils::outdent << ");";
}

}
