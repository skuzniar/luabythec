//
//  enum.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 4/1/21.
//

#ifndef enum_hpp
#define enum_hpp

#include <google/protobuf/descriptor.pb.h>

#include <iostream>
#include <vector>

namespace luabythec
{
using google::protobuf::EnumDescriptor;

class EnumGenerator
{
public:
    EnumGenerator(const EnumDescriptor* descriptor, std::string& error);

    bool Generate(std::ostream& os);
    
    bool MakeBindFunction(std::ostream& os);
    bool CallBindFunction(std::ostream& os);

private:
    bool make_bind_function(std::ostream& os);
    bool call_bind_function(std::ostream& os);

    std::string make_namespace(std::string where, std::ostream& os);
    std::string make_namespace(std::string where, const std::string& name, std::ostream& os);
    
    void make_type(const std::string& where, std::ostream& os);

    const EnumDescriptor*   m_descriptor;
    std::string             m_full_name;
    std::string             m_full_type;
    std::string             m_type;
    std::string&            m_error;
};

}

#endif /* enum_hpp */
