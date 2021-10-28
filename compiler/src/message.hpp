//
//  message.hpp
//  luabythec
//
//  Created by Slawomir Kuzniar on 3/25/21.
//

#ifndef message_hpp
#define message_hpp

#include <google/protobuf/descriptor.pb.h>

#include <iostream>
#include <vector>

namespace luabythec
{
using google::protobuf::Descriptor;

class MessageGenerator
{
  public:
    MessageGenerator (const Descriptor *descriptor, std::string &error);

    bool Generate (std::ostream &os);

    bool MakeBindFunction (std::ostream &os);
    bool CallBindFunction (std::ostream &os);

  private:
    bool make_bind_function (std::ostream &os);
    bool call_bind_function (std::ostream &os);

    std::string make_namespace (std::string where, std::ostream &os);
    std::string make_namespace (std::string where, const std::string &name, std::ostream &os);

    std::string make_type (const std::string &where, std::ostream &os);

    bool make_accessors (const std::string &where, std::ostream &os);

    const Descriptor *m_descriptor;
    std::string       m_full_name;
    std::string       m_full_type;
    std::string       m_type;
    std::string      &m_error;
};

}

#endif /* message_hpp */
