#include <asf.hpp>

int main() {
  std::string expected("Hello");
  std::string actual;

  try {
    actual = asf::format("{0}", "Hello");
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}
