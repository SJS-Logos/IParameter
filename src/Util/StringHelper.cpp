#include "Util/StringHelper.h"
#include "Util/StringUtil.h"

#include <stdio.h>
#include <stddef.h>
#include <climits>

std::string StringHelper::from_string(const std::string& zString, const std::string& /*defaultValue*/)
{
  std::string result( zString );
  return result;
}

std::string StringHelper::to_string(const std::string& zString)
{
  return std::string(zString);
}

int StringHelper::from_string(const std::string& zString, int defaultValue)
{
  return StringUtil::toLong( zString.c_str(), defaultValue, INT_MIN, INT_MAX);
}

std::string StringHelper::to_string(int value )
{
  char buffer[12];
  snprintf( buffer, sizeof(buffer), "%d", value );
  return std::string( buffer );
}
