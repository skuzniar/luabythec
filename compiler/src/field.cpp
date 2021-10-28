//
//  field.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/27/21.
//

#include "field.hpp"
#include "utils.hpp"

#include "enum.hpp"
#include "message.hpp"

namespace luabythec
{

using utils::endi;

FieldGenerator::FieldGenerator (const FieldDescriptor *descriptor, const std::string &full_type,
                                const std::string &type, std::string &error)
    : m_descriptor (descriptor), m_full_type (full_type), m_type (type), m_error (error)
{
}

bool
FieldGenerator::Generate (std::ostream &os)
{
    os << endi << "// Generating accessors for" << ' ' << (m_descriptor->is_repeated () ? "repeated" : "singular")
       << " field " << '[' << m_descriptor->name () << ']' << " of type " << m_descriptor->type_name () << endi;

    if (m_descriptor->type () == FieldDescriptor::TYPE_MESSAGE) {
        generate_message_accessor (os);
    } else if (m_descriptor->type () == FieldDescriptor::TYPE_STRING) {
        generate_string_accessor (os);
    } else if (m_descriptor->type () == FieldDescriptor::TYPE_ENUM) {
        generate_enum_accessor (os);
    } else {
        generate_simple_accessor (os);
    }

    return true;
}

void
FieldGenerator::generate_simple_accessor (std::ostream &os) const
{
    m_descriptor->is_repeated () ? repeated_simple_accessor (os) : singular_simple_accessor (os);
}

void
FieldGenerator::singular_simple_accessor (std::ostream &os) const
{
    os << m_type << ".set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << "sol::property(" << '&'
       << m_full_type << "::" << m_descriptor->name () << ',' << ' ' << '&' << m_full_type << "::"
       << "set_" << m_descriptor->name () << "));" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

void
FieldGenerator::repeated_simple_accessor (std::ostream &os) const
{
    os << m_type << ".set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type << "::"
       << "mutable_" << m_descriptor->name () << ");" << endi;

    os << m_type << ".set(" << '"' << "add_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type << "::"
       << "add_" << m_descriptor->name () << ");" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

void
FieldGenerator::generate_string_accessor (std::ostream &os) const
{
    m_descriptor->is_repeated () ? repeated_string_accessor (os) : singular_string_accessor (os);
}

void
FieldGenerator::singular_string_accessor (std::ostream &os) const
{
    os << m_type << ".set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << "sol::property(" << '&'
       << m_full_type << "::" << m_descriptor->name () << ',' << ' ' << "static_cast<void" << '(' << m_full_type
       << "::" << '*' << ')' << "(const std::string&)>" << '(' << '&' << m_full_type << "::"
       << "set_" << m_descriptor->name () << ")));" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

void
FieldGenerator::repeated_string_accessor (std::ostream &os) const
{
    os << m_type << ".wrong-set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << "sol::property(" << '&'
       << m_full_type << "::" << m_descriptor->name () << ',' << ' ' << "static_cast<void (" << m_full_type
       << "::" << '*' << "(const std::string&)>" << '(' << '&' << m_full_type << "::"
       << "set_" << m_descriptor->name () << ')' << "));" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

void
FieldGenerator::generate_enum_accessor (std::ostream &os) const
{
    EnumGenerator (m_descriptor->enum_type (), m_error).CallBindFunction (os);
    os << endi << endi;
    m_descriptor->is_repeated () ? repeated_simple_accessor (os) : singular_simple_accessor (os);
}

void
FieldGenerator::generate_message_accessor (std::ostream &os) const
{
    MessageGenerator (m_descriptor->message_type (), m_error).CallBindFunction (os);
    os << endi << endi;
    m_descriptor->is_repeated () ? repeated_message_accessor (os) : singular_message_accessor (os);
}

void
FieldGenerator::singular_message_accessor (std::ostream &os) const
{
    os << m_type << ".set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << "sol::property(" << '&'
       << m_full_type << "::" << m_descriptor->name () << ',' << ' ' << '&' << m_full_type << "::"
       << "mutable_" << m_descriptor->name () << "));" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

void
FieldGenerator::repeated_message_accessor (std::ostream &os) const
{
    os << m_type << ".set(" << '"' << m_descriptor->name () << '"' << ',' << ' ' << "static_cast<"
       << "google::protobuf::RepeatedPtrField<" << utils::Type (m_descriptor->message_type ()->full_name ()) << ">* ("
       << m_full_type << "::" << '*' << ")()>" << '(' << '&' << m_full_type << "::"
       << "mutable_" << m_descriptor->name () << ')' << ");" << endi;

    os << m_type << ".set(" << '"' << "add_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type << "::"
       << "add_" << m_descriptor->name () << ");" << endi;

    os << m_type << ".set(" << '"' << "clear_" << m_descriptor->name () << '"' << ',' << ' ' << '&' << m_full_type
       << "::"
       << "clear_" << m_descriptor->name () << ");";
}

}
