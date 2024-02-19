//
//  message.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/25/21.
//

#include "message.hpp"
#include "enum.hpp"
#include "field.hpp"

#include "utils.hpp"

namespace luabythec
{

using utils::endi;

MessageGenerator::MessageGenerator (const Descriptor *descriptor, std::string &error)
    : m_descriptor (descriptor), m_error (error)
{
    m_full_name = m_descriptor->full_name ();
    m_full_type = utils::Type (m_full_name);
    m_type      = m_descriptor->name ();
}

bool
MessageGenerator::Generate (std::ostream &os)
{
    return MakeBindFunction (os);
}

bool
MessageGenerator::MakeBindFunction (std::ostream &os)
{
    make_bind_function (os);
    return true;
}

bool
MessageGenerator::CallBindFunction (std::ostream &os)
{
    call_bind_function (os);
    return true;
}

bool
MessageGenerator::make_bind_function (std::ostream &os)
{
    os << endi << "//" << std::string (118, '-') << endi << "// Bind specialization for message "
       << m_descriptor->name () << endi << "//" << std::string (118, '-') << endi << "template <>" << endi
       << "void bind<" << m_full_type << ">(sol::state& lua)" << endi << "{" << utils::indent;

    os << "// Generating namespace definition" << endi;
    auto current = make_namespace ("lua", os);

    os << endi << "// Generating type definition" << endi;
    auto typespc = make_type (current, os);

    make_accessors (typespc, os);

    os << utils::outdent << "}" << endi;
    return true;
}

bool
MessageGenerator::call_bind_function (std::ostream &os)
{
    os << "bind<" << m_full_type << ">(lua);";
    return true;
}

std::string
MessageGenerator::make_namespace (std::string where, std::ostream &os)
{
    for (const auto &token : utils::Tokenize (utils::Stem (m_descriptor->full_name ()), ".")) {
        where = make_namespace (where, token, os);
    }
    return where;
}

std::string
MessageGenerator::make_namespace (std::string where, const std::string &name, std::ostream &os)
{
    os << "auto " << name << " = " << where << "[\"" << name << "\"]"
       << ".get_or_create<sol::table>();" << endi;
    return name;
}

std::string
MessageGenerator::make_type (const std::string &where, std::ostream &os)
{
    std::string typespc = m_type + "_t";
    os << "auto " << typespc << " = " << where << ".new_usertype<" << m_full_type << ">"
       << "(\"" << m_type << "\", sol::constructors<" << m_full_type << "()>());";
    return typespc;
}

bool
MessageGenerator::make_accessors (const std::string &where, std::ostream &os)
{
    for (int i = 0; i < m_descriptor->field_count (); ++i) {
        os << endi;
        FieldGenerator (m_descriptor->field (i), m_full_type, where, m_error).Generate (os);
    }
    return true;
}

}
