#pragma once

#include <string>

class Exception  {
public:
   Exception() {_msg = "Unknown error.";}
  Exception(const std::string& msg) {_msg = msg;}
  Exception(const char * msg) {_msg = msg;}

  inline std::string & GetMessage() {return _msg;}

private:
   std::string _msg;
};
