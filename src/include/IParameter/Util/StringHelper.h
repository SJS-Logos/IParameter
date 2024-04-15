#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>

struct StringHelper {
  static std::string from_string(const std::string& zString, const std::string& defaultValue);
  static std::string to_string(const std::string& zString);
  static int from_string(const std::string& zString, int defaultValue);
  static std::string to_string(int value );
};

#endif //STRING_HELPER_H
