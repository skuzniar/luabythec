//
//  ostream.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/21/21.
//

#ifndef ostream_hpp
#define ostream_hpp

#include <boost/iostreams/concepts.hpp>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>

namespace luabythec
{
namespace utils
{

class zcsink : public boost::iostreams::sink
{
  public:
    zcsink (google::protobuf::io::Printer &p) : m_p (p) {}

    std::streamsize
    write (const char *s, std::streamsize n)
    {
        m_p.WriteRaw (s, n);
        return n;
    }

  private:
    google::protobuf::io::Printer &m_p;
};

}
}

#endif /* ostream_hpp */
