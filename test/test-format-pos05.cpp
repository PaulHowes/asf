#include <asf.hpp>

int main() {
  std::string expected("string 1 3.3");
  std::string actual;

  try {
    actual = asf::format("{0} {1} {2}", "string", 1, 3.3);
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}
