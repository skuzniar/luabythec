//
//  file.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#ifndef file_hpp
#define file_hpp

#include <google/protobuf/descriptor.pb.h>

#include <iostream>
#include <vector>

namespace luabythec
{

using google::protobuf::FileDescriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::EnumDescriptor;
using google::protobuf::Descriptor;

class FileGenerator 
{
public:
    FileGenerator(const FileDescriptor* descriptor, const std::string& fname, std::string& error);

    bool Generate(std::ostream& os);

private:
    bool generate_header_guard_open (std::ostream& os);
    bool generate_header_guard_close(std::ostream& os);

    bool generate_namespace_open (std::ostream& os);
    bool generate_namespace_close(std::ostream& os);
    
    std::string header_guard() const;

    bool generate_bind_declaration(std::ostream& os);

    std::string bind_declaration_guard() const;

    std::vector<const Descriptor*> messages(const FileDescriptor* d);
    void                           messages(const FileDescriptor* d, std::vector<const Descriptor*>& m);
    void                           messages(const Descriptor*     d, std::vector<const Descriptor*>& m);
 
    std::vector<const EnumDescriptor*> enums(const FileDescriptor* d);
    void                               enums(const FileDescriptor* d, std::vector<const EnumDescriptor*>& e);
    void                               enums(const Descriptor*     d, std::vector<const EnumDescriptor*>& e);

    const FileDescriptor*   m_descriptor;
    std::string             m_fname;
    std::string&            m_error;
};

}

#endif /* file_hpp */
