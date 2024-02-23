#include <iostream>

#include "addressbook.pb.h"
#include "addressbook.pb.lbc.h"

#include <sol/sol.hpp>

int
main (int argc, char *argv[])
{
    //--- Create protobuf message
    tutorial::AddressBook address_book;

    auto person = address_book.add_people ();

    person->set_name ("Mary Moe");
    person->set_email ("mary.moe@gmail.com");

    auto phone = person->add_phones ();

    phone->set_number ("111.222.3333");
    phone->set_type (tutorial::Person::WORK);

    phone = person->add_phones ();

    phone->set_number ("222-333 - 4444");
    phone->set_type (tutorial::Person::HOME);

    std::cout << "---------------------------------------\n"
              << "----- Before executing Lua script -----\n"
              << "---------------------------------------\n"
              << address_book.DebugString () << std::endl;

    //--- Initilize Lua environment
    sol::state lua;
    lua.open_libraries (sol::lib::base, sol::lib::string);

    //--- Bind C++ types into Lua
    luabythec::bind<tutorial::AddressBook> (lua);

    //--- Demonstrate changing protobuf message using Lua
    lua["address_book"] = std::ref (address_book);

    lua.script (
        R"""(
           -- Normalize phone numbers
	       for _, p in ipairs(address_book:people()) do
	           for _, ph in ipairs(p:phones()) do
                   a, b, c = string.match(ph.number, "(%d%d%d)[%D]*(%d%d%d)[%D]*(%d%d%d%d)")
		           ph.number = '(' .. a .. ')' .. ' ' .. b .. '-' .. c
	           end
	       end
           )""");

    std::cout << "---------------------------------------\n"
              << "----- After executing Lua script ------\n"
              << "---------------------------------------\n"
              << address_book.DebugString () << std::endl;

    return 0;
}
