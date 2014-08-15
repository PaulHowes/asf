# include <asf.hpp>

int main() {
  std::string actual;

  try {
    actual = asf::format("abcdef {0}");
  }
  catch(...) {
    return 0;
  }

  return -1;
}
