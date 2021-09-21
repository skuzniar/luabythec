//
//  generator.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#ifndef generator_hpp
#define generator_hpp

#include <string>
#include <google/protobuf/compiler/code_generator.h>

namespace luabythec
{
using google::protobuf::compiler::CodeGenerator;
using google::protobuf::compiler::GeneratorContext;
using google::protobuf::FileDescriptor;

class Generator : public CodeGenerator
{
    public:
    bool Generate(const FileDescriptor* file,
                  const std::string& parameter,
                  GeneratorContext* context,
                  std::string* error) const override;
};

}

#endif /* generator_hpp */
