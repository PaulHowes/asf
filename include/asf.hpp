/**
 * @file
 * @brief Public API for the Advanced String Formatter project.
 *
 * The ASF public API contains multiple overloads of the asf::format function that accept either
 * a C or C++ format string, and zero or more replacement values that are referenced by the format
 * string.
 *
 * Also @c operator% is overloaded to provided functionality similar to that found in Python, where
 * a std::map that contains replacement values can be supplied and referenced by name instead of by
 * index.
 */
#pragma once

#include <asf/internal.hpp>
#include <map>
#include <stdexcept>

/**
 * @defgroup asf
 */
namespace asf {
  /**
   * @brief Implementation of asf::format that contains a format string but no arguments.
   * @ingroup asf
   * @param[in] s Format string.
   * @return Formatted string.
   *
   * This function is provided as a "catch-all" in case the variadic templace invocation evaluates
   * to no parameters.
   */
  std::string format(const char* s) {
    auto error_cb = [](const std::string& arg) -> boost::any {
      (void)(arg);
      throw std::invalid_argument("Insufficient arguments to format string.");
    };

    return asf::internal::parse(s, error_cb);
  }

  /**
   * @brief Implementation of asf::format that contains a format string but no arguments.
   * @ingroup asf
   * @param[in] s Format string.
   * @return Formatted string.
   *
   * This function is provided as a "catch-all" in case the variadic templace invocation evaluates
   * to no parameters.
   */
  std::string format(const std::string& s) {
    return asf::format(s.c_str());
  }

  /**
   * @brief Implementaion of asf::format that accepts one or more arguemnts referenced in the
   *        format string.
   * @ingroup asf
   * @param[in] s Format string.
   * @param[in] args Variadic argument list.
   * @return    Formatted string.
   *
   * asf::format is invoked similar to the classic C `printf` function. The first argument to the
   * function is the format string and the remaining arguments are parameters referenced from the
   * format string.
   *
   * Parameter references in the format string are positional, similar to those found in other
   * languages. Each reference is enclosed in curly braces and contains a zero-based index to the
   * parameters included as arguments to the asf::format function.
   *
   * For example:
   *
   *     std::cout << asf::format("{0}, {1}!", "Hello", "world")
   *
   * Produces:
   *
   *     "Hello, world!"
   *
   * The arguments can be of any integral type, as well as `NULL` terminated character arrays
   * (C strings) and std::string.
   */
  template<typename... Args>
  std::string format(const char* s, Args... args) {
    // Unrolls the variadic argument template into a vector of arguments that can be accessed.
    std::vector<boost::any> a;
    asf::internal::unroll(a, args...);

    auto cb = [&](const std::string& arg) {
      return a.at(std::stoul(arg));
    };

    return asf::internal::parse(s, cb);
  }

  /**
   * @brief Implementaion of asf::format that accepts one or more arguemnts referenced in the
   *        format string.
   * @ingroup asf
   * @param[in] s Format string.
   * @param[in] args Variadic argument list.
   * @return    Formatted string.
   *
   * asf::format is invoked similar to the classic C `printf` function. The first argument to the
   * function is the format string and the remaining arguments are parameters referenced from the
   * format string.
   *
   * Parameter references in the format string are positional, similar to those found in other
   * languages. Each reference is enclosed in curly braces and contains a zero-based index to the
   * parameters included as arguments to the asf::format function.
   *
   * For example:
   *
   *     std::cout << asf::format("{0}, {1}!", "Hello", "world")
   *
   * Produces:
   *
   *     "Hello, world!"
   *
   * The arguments can be of any integral type, as well as `NULL` terminated character arrays
   * (C strings) and std::string.
   */
  template<typename... Args>
  std::string format(const std::string& s, Args... args) {
    return asf::format(s.c_str(), args...);
  }

}

/**
 * @brief Overload for the `%` operator to provide Python-like formatting functionality.
 * @ingroup asf
 * @param[in] s Format string as a `NULL` terminated character array.
 * @param[in] m std::map of arguments referenced from the format string by name.
 * @return    Formatted string.
 *
 * Overloading `operator%` provides a syntax very similar that used in Python to format strings.
 * When invoking `operator%`, the left parameter is the format string and the right parameter
 * contains the replacement values. The container class is a `std::map` indexed by `std::string`
 * keys. The key is used directly in the format string rather than an index.
 *
 * For example:
 *
 *     std::map<std::string, std::string> args;
 *     args["a"] = "Hello";
 *     args["b"] = "world";
 *
 *     std::cout << "{a}, {b}!" % args;
 *
 * Produces:
 *
 *     "Hello, world!"
 */
template<typename T>
std::string operator%(const char* s, std::map<std::string, T>& m) {
  auto cb = [&](const std::string& arg) {
    return m[arg];
  };
  return asf::internal::parse(s, cb);
}

/**
 * @brief Overload for the `%` operator to provide Python-like formatting functionality.
 * @ingroup asf
 * @param[in] s Format string as a std::string.
 * @param[in] m std::map of arguments referenced from the format string by name.
 * @return    Formatted string.
 *
 * Overloading `operator%` provides a syntax very similar that used in Python to format strings.
 * When invoking `operator%`, the left parameter is the format string and the right parameter
 * contains the replacement values. The container class is a `std::map` indexed by `std::string`
 * keys. The key is used directly in the format string rather than an index.
 *
 * For example:
 *
 *     std::map<std::string, std::string> args;
 *     args["a"] = "Hello";
 *     args["b"] = "world";
 *
 *     std::string format("{a}, {b}!");
 *
 *     std::cout << format % args;
 *
 * Produces:
 *
 *     "Hello, world!"
 */
template<typename T>
std::string operator%(const std::string& s, std::map<std::string, T>& m) {
  auto cb = [&](const std::string& arg) {
    return m[arg];
  };
  return asf::internal::parse(s.c_str(), cb);
}

/**
 * @brief Overload for the `%` operator to provide Python-like formatting functionality.
 * @ingroup asf
 * @param[in] s Format string as a `NULL` terminated character array.
 * @param[in] v Vector of arguments referenced from the format string by index.
 * @return    Formatted string.
 *
 * Overloading `operator%` provides a syntax very similar that used in Python to format strings.
 * When invoking `operator%`, the left parameter is the format string and the right parameter
 * contains the replacement values. As with asf::format(), the format string references the
 * replacement values by index.
 *
 * For example:
 *
 *     std::vector<std::string> args;
 *     args.push_back("Hello");
 *     args.push_back("world");
 *
 *     std::cout << "{0}, {1}!" % args;
 *
 * Produces:
 *
 *     "Hello, world!"
 */
template<typename T>
std::string operator%(const char* s, std::vector<T>& v) {
  auto cb = [&](const std::string& arg) {
    return v.at(std::stoul(arg));
  };
  return asf::internal::parse(s, cb);
}

/**
 * @brief Overload for the `%` operator to provide Python-like formatting functionality.
 * @ingroup asf
 * @param[in] s Format string as a `NULL` terminated character array.
 * @param[in] v Vector of arguments referenced from the format string by index.
 * @return    Formatted string.
 *
 * Overloading `operator%` provides a syntax very similar that used in Python to format strings.
 * When invoking `operator%`, the left parameter is the format string and the right parameter
 * contains the replacement values. As with asf::format(), the format string references the
 * replacement values by index.
 *
 * For example:
 *
 *     std::vector<std::string> args;
 *     args.push_back("Hello");
 *     args.push_back("world");
 *
 *     std::string format("{0}, {1}!");
 *
 *     std::cout << format % args;
 *
 * Produces:
 *
 *     "Hello, world!"
 */
template<typename T>
std::string operator%(const std::string& s, std::vector<T>& v) {
  auto cb = [&](const std::string& arg) {
    return v.at(std::stoul(arg));
  };
  return asf::internal::parse(s.c_str(), cb);
}
