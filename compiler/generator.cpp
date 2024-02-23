//
//  generator.cpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/20/21.
//

#include "generator.hpp"
#include "file.hpp"
#include "ostream.hpp"
#include "utils.hpp"

#include <fstream>
#include <memory>

#include <boost/iostreams/stream.hpp>

namespace luabythec
{

bool
Generator::Generate (const FileDescriptor *file, const std::string &parameter, GeneratorContext *context,
                     std::string *error) const
{
    std::string ofile = utils::StripProto (file->name ()) + ".pb.lbc.h";

    std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> s (context->Open (ofile));
    if (s) {
        google::protobuf::io::Printer p (s.get (), '$');

        // Turn zero copy stream / printer nonsense into std::ostream
        boost::iostreams::stream<utils::zcsink> ofs (p);

        return FileGenerator (file, ofile, *error).Generate (ofs);
    }

    *error = "Unable to open " + ofile + " for writing.";
    return false;
}

}
