#include <asf.hpp>

int main() {
  std::string expected("string 1 3.3");
  std::string actual;
  std::map<std::string, type::any> args;
  args["first"]  = "string";
  args["second"] = 1;
  args["third"]  = 3.3;

  try {
    actual = "{first} {second} {third}" % args;
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}


