//
//  generator.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#ifndef generator_hpp
#define generator_hpp

#include <google/protobuf/compiler/code_generator.h>
#include <string>

namespace luabythec
{
using google::protobuf::FileDescriptor;
using google::protobuf::compiler::CodeGenerator;
using google::protobuf::compiler::GeneratorContext;

class Generator : public CodeGenerator
{
  public:
    bool Generate (const FileDescriptor *file, const std::string &parameter, GeneratorContext *context,
                   std::string *error) const override;
};

}

#endif /* generator_hpp */
