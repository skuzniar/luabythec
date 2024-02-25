#include <iostream>

#include <sol/sol.hpp>

#include "addressbook.pb.h"
#include "addressbook.pb.lbc.h"

int
main (int argc, char *argv[])
{
    //--- Create protobuf message
    tutorial::AddressBook address_book;
    {
        auto person = address_book.add_people ();

        person->set_name ("Mary Moe");
        person->set_email ("mary.moe@gmail.com");

        auto phone = person->add_phones ();

        phone->set_number ("111.222.3333");
        phone->set_type (tutorial::Person::WORK);

        phone = person->add_phones ();

        phone->set_number ("222-333-4444");
        phone->set_type (tutorial::Person::HOME);

        person->set_morning_drink (tutorial::COFFEE);
    }
    {
        auto person = address_book.add_people ();

        person->set_name ("John Doe");
        person->set_email ("john.doe@gmail.com");

        auto phone = person->add_phones ();

        phone->set_number ("3334445555");
        phone->set_type (tutorial::Person::MOBILE);

        phone = person->add_phones ();

        phone->set_number ("444 - 555 - 6666");
        phone->set_type (tutorial::Person::HOME);

        person->set_morning_drink (tutorial::BEER);
    }

    std::cout << "---------------------------------------\n"
              << "-------- Original address book --------\n"
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
           -- Add new person to the list
           local person = address_book:add_people()
           person.name  = 'Jane Poe'
           person.email = 'jane.poe@gmail.com'

           local phone  = person:add_phones()
           phone.number = '555 666 7777'
           phone.type   = tutorial.Person.PhoneType.HOME

           phone = person:add_phones()
           phone.number = '666 777 8888'
           phone.type   = tutorial.Person.PhoneType.MOBILE
           )""");

    std::cout << "---------------------------------------\n"
              << "------- After adding new person -------\n"
              << "---------------------------------------\n"
              << address_book.DebugString () << std::endl;

    lua.script (
        R"""(
           -- Normalize phone numbers and change drinking habits
	       for _, p in ipairs(address_book:people()) do
               if p.morning_drink == tutorial.Drink.BEER or p.morning_drink == tutorial.Drink.WINE then 
                   p.morning_drink = tutorial.Drink.TEA
               end
	           for _, ph in ipairs(p:phones()) do
                   a, b, c = string.match(ph.number, "(%d%d%d)[%D]*(%d%d%d)[%D]*(%d%d%d%d)")
		           ph.number = '(' .. a .. ')' .. ' ' .. b .. '-' .. c
	           end
	       end
           )""");

    std::cout << "---------------------------------------------------------------\n"
              << "----- After nomalizing phone numbers and drinking habits ------\n"
              << "---------------------------------------------------------------\n"
              << address_book.DebugString () << std::endl;

    lua.script (
        R"""(
           -- Change email of the last person
           local person = address_book:people():at(#address_book:people())
           person.email = 'jane.the.last.poe@gmail.com'
           )""");

    std::cout << "-----------------------------------------------\n"
              << "----- After changing last person's email ------\n"
              << "-----------------------------------------------\n"
              << address_book.DebugString () << std::endl;

    lua.script (
        R"""(
           -- Delete second person - Lua counts from 1
           address_book:people():erase(2)
           )""");

    std::cout << "--------------------------------------------\n"
              << "----- After erasing the second person ------\n"
              << "--------------------------------------------\n"
              << address_book.DebugString () << std::endl;

    return 0;
}
