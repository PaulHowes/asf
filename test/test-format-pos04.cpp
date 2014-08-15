#include <asf.hpp>

int main() {
  std::string expected("Hello, world!");
  std::string actual;

  try {
    actual = asf::format("{1}, {0}!", "world", "Hello");
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}
