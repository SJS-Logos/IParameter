#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>

struct StringHelper {
  static bool from_string( std::string* dst, const std::string src );
  static std::string to_string(const std::string& zString);
  static bool from_string(int* dst, const std::string src);
  static std::string to_string(int value );
};

#endif //STRING_HELPER_H
