# luabythec

Luabytec (Lua by the C++) is a protobuf compiler plugin that generates Lua bindings for Google protobuf C++ API. 
Automatically generated bindings for protobuf are useful when one wants to embed Lua in a C++ application that handles 
protobuf messages. The host application can pass protobuf message to Lua script to perform some action on it. 

## Requirements

To build the compiler plugin you will need the following libraries.

- protoc 

Lua protobuf binding generator relies on [sol2](https://github.com/ThePhD/sol2) library. To use that library you need 
a fairly recent C++ compiler. See the library web page for details. 

For the example projects you must have the following programs and libraries.

- protobuf compiler
- luabythec compiler plugin
- protobuf
- sol2
- lua

## Installation

1. Install required libraries.
2. Adjust cmake files to ensure the compiler finds necessary headers and libraries.
3. Build protobuf compiler plugin and example programs.

   ```sh
   cmake -B build
   cmake --build build
   ```
## Usage

The example projects show how to call Lua script from C++ host application and access protobuf messages.

The example below uses Lua script as a normalization filter. The protbuf message contains phone numbers in different 
format and we pass that message through Lua script to normalize them.

We use protobuf definition below to generate both C++ API and Lua bindings.

```protobuf
syntax = "proto2";
package tutorial;

enum Drink {
  COFFEE = 0;
  TEA    = 1;
  WINE   = 2;
  BEER   = 3;
}

message Person {
  optional string   name          = 1;
  optional string   email         = 2;
  optional Drink    morning_drink = 3;
  optional Drink    evening_drink = 4;

  enum PhoneType {
    MOBILE = 0;
    HOME   = 1;
    WORK   = 2;
  }

  message PhoneNumber {
    optional string number  = 1;
    optional PhoneType type = 2;
  }

  repeated PhoneNumber phones = 5;
}

message AddressBook {
  optional string name   = 1;
  repeated Person people = 2;
}
```
1. Construct protobuf message.

```cpp
   //--- Create protobuf message
   tutorial::AddressBook address_book;

   auto person = address_book.add_people();

   person->set_name("Mary Moe");
   person->set_email("mary.moe@gmail.com");

   auto phone = person->add_phones();

   phone->set_number("111.222.3333");
   phone->set_type(tutorial::Person::WORK);

   phone = person->add_phones();

   phone->set_number("222-333 - 4444");
   phone->set_type(tutorial::Person::HOME);

   std::cout << "---------------------------------------\n"
             << "----- Before executing Lua script -----\n"
             << "---------------------------------------\n"
             << address_book.DebugString() << std::endl;
```

2. Run Lua script on the original message

```cpp
   //--- Initilize Lua environment
   sol::state lua;
   lua.open_libraries(sol::lib::base, sol::lib::string);

   //--- Bind C++ types into Lua
   luabythec::bind<tutorial::AddressBook>(lua);

   //--- Demonstrate changing protobuf message using Lua
   lua["address_book"] = std::ref(address_book);

   lua.script(
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
             << address_book.DebugString() << std::endl;
```

Running the program will produce the following result. Note that after applying Lua script the phone numbers have the 
same format.

```txt
---------------------------------------
----- Before executing Lua script -----
---------------------------------------
people {
  name: "Mary Moe"
  email: "mary.moe@gmail.com"
  phones {
    number: "111.222.3333"
    type: WORK
  }
  phones {
    number: "222-333 - 4444"
    type: HOME
  }
}

---------------------------------------
----- After executing Lua script ------
---------------------------------------
people {
  name: "Mary Moe"
  email: "mary.moe@gmail.com"
  phones {
    number: "(111) 222-3333"
    type: WORK
  }
  phones {
    number: "(222) 333-4444"
    type: HOME
  }
}
```


## Credits

Lua bindings generator is a simple wrapper on top of [sol2](https://github.com/ThePhD/sol2), an excellent library for 
binding C++ to Lua.

## License

[MIT](LICENSE)
