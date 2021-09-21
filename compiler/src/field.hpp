//
//  field.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/27/21.
//

#ifndef field_hpp
#define field_hpp

#include <google/protobuf/descriptor.pb.h>

#include <iostream>
#include <vector>

namespace luabythec
{
using google::protobuf::FieldDescriptor;

class FieldGenerator
{
public:
    FieldGenerator(const FieldDescriptor* descriptor, const std::string& full_type, const std::string& type, std::string& error);

    bool Generate(std::ostream& os);

private:
    void generate_simple_accessor(std::ostream& os) const;
    void singular_simple_accessor(std::ostream& os) const;
    void repeated_simple_accessor(std::ostream& os) const;
    
    void generate_string_accessor(std::ostream& os) const;
    void singular_string_accessor(std::ostream& os) const;
    void repeated_string_accessor(std::ostream& os) const;
    
    void generate_enum_accessor(std::ostream& os) const;
    void singular_enum_accessor(std::ostream& os) const;
    void repeated_enum_accessor(std::ostream& os) const;
    
    void generate_message_accessor(std::ostream& os) const;
    void singular_message_accessor(std::ostream& os) const;
    void repeated_message_accessor(std::ostream& os) const;
    
    const FieldDescriptor*  m_descriptor;
    std::string             m_full_type;
    std::string             m_type;
    std::string&            m_error;
};

}

#endif /* field_hpp */
