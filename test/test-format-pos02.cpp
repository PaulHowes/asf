# include <asf.hpp>

int main() {
  std::string expected("abcdef{}");
  std::string actual;

  try {
    actual = asf::format("abcdef{{}}");
  }
  catch(...) {
    return -1;
  }

  return (actual == expected) ? 0 : -1;
}
