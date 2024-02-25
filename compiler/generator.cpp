//
//  generator.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#include "generator.hpp"
#include "file.hpp"
#include "utils.hpp"

#include <fstream>

namespace luabythec
{

bool
Generator::Generate (const FileDescriptor *file, const std::string &parameter, GeneratorContext *context,
                     std::string *error) const
{
    std::string ofile = utils::StripProto (file->name ()) + ".pb.lbc.h";

    std::ofstream ofs(ofile.c_str());
    if (ofs) {
        return FileGenerator (file, ofile, *error).Generate (ofs);
    }

    *error = "Unable to open " + ofile + " for writing.";
    return false;
}

}
