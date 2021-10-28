//
//  main.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#include "generator.hpp"
#include <google/protobuf/compiler/plugin.h>

int
main (int argc, char *argv[])
{
    luabythec::Generator generator;
    return google::protobuf::compiler::PluginMain (argc, argv, &generator);
}
