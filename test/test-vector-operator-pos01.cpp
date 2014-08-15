#include <asf.hpp>

int main() {
  std::string expected("string 1 3.3");
  std::string actual;
  std::vector<boost::any> args;
  args.push_back("string");
  args.push_back(1);
  args.push_back(3.3);

  try {
    actual = std::string("{0} {1} {2}") % args;
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}


