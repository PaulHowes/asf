/**
 * @brief Internal header for the Advanced String Formatter project.
 * @internal
 */
#pragma once

#include <any.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace asf {
  namespace internal {
    /**
     * Recursion terminator for asf::internal::unroll(v, value, args...)
     *
     * @param[in] v The std::vector to add @p value to.
     * @param[in] value Value to add to @p v
     */
    template<typename T>
    static void unroll(std::vector<type::any>& v, const T& value) {
      v.push_back(type::any(value));
    }

    /**
     * Unrolls a variadic template of arguments into a vector.
     *
     * @param[in] v The std::vector to add @p value to.
     * @param[in] value Value to add to std::vector @p v
     * @param[in] args Remaining variadic template arguments to be processed.
     */
    template<typename T, typename... Args>
    static void unroll(std::vector<type::any>& v, const T& value, const Args&... args) {
      v.push_back(type::any(value));
      unroll(v, args...);
    }

    /**
     * Converts the value contained in @p value to its string representation.
     *
     * @param value Value to convert.
     * @return std::string representation of @p value
     */
    std::string convert(const type::any& value) {
      std::ostringstream oss;
      if(typeid(double) == value.type()) {
        oss << value.as<double>();
      }
      else if(typeid(char const*) == value.type()) {
        oss << value.as<char const*>();
      }
      else if(typeid(int) == value.type()) {
        oss << value.as<int>();
      }
      else if(typeid(std::string) == value.type()) {
        oss << value.as<std::string>();
      }
      return oss.str();
    }

    /**
     * Parses a format string.
     *
     * This function is not part of the public API and therefore not intended to be invoked
     * directly from a client.
     */
    std::string parse(const char* s, std::function<type::any (const std::string&)> cb) {
      // Builds the returned string.
      std::ostringstream oss;

      // Used to find argument references in the format string.
      char* tok = NULL;

      while(*s) {
        if(*s == '{') {
          // A left-brace denotes the begining of an argument reference.
          if(*(s + 1) == '{') {
            // Specifying "{{" in the format string emits a literal '{' character.
            oss.put(*s);
            ++s;
          }
          else {
            // tok now points to the first character in the argument reference.
            tok = (char*)(s + 1);
          }
        }
        else if(*s == '}') {
          // A right-brace denotes the end of an argument reference.
          if(*(s + 1) == '}') {
            // Specifying "}}" in the format string emits a literal '}' character.
            oss.put(*s);
            ++s;
          }
          else {
            // Use the callback to obtain the argument, then emit it.
            oss << asf::internal::convert(cb(std::string(tok, (size_t)(s - tok))));
            tok = NULL;
          }
        }
        else {
          if(!tok) {
            // All other characters are added to the output stream.
            oss.put(*s);
          }
        }

        ++s;
      }

      return oss.str();
    }
  }
}

/**
 * @endinternal
 */
