//
// Created by SJS on 11/01/2024.
//

#include <string.h>
#include "StringUtil.h"
#include "LogosTypes.h"
#include <ctype.h>
#include <cstdlib>
#include <errno.h>
#include <limits.h>

long StringUtil::toLong( const char* s, long defaultValue, long minValue, long maxValue )
{
  if ( s == nullptr ) {
    return defaultValue;
  }
  
  errno = 0;
  char *endPoint;
  long returnValue = strtol( s, &endPoint, 10 );
  
   // If the value read is out of the range of representable values by a long int, the function returns LONG_MAX or LONG_MIN (defined in <climits>), and errno is set to ERANGE.
  if ( ( returnValue == LONG_MAX || returnValue == LONG_MIN ) && errno != 0  ) {
    return defaultValue;
  }

  // EndPoint Reference to an object of type char*, whose value is set by the function to the next character in str after the numerical value.
  if ( endPoint == s || endPoint == nullptr || *endPoint != '\0' ) {
    return defaultValue;
  }
  
  if ( returnValue < minValue || returnValue > maxValue ) {
    return defaultValue;
  }
  return returnValue;
}

bool StringUtil::containsDigits( const char* s, size_t size )
{
  if ( s == nullptr ) {
    return false;
  }
  for ( size_t i= 0; i < size; i++ ) {
    if ( isdigit( s[ i ] ) ) {
      return true;
    }
  }
  
  return false;
}

void StringUtil::copyLeastSignificantDigits( char* dst, size_t dst_size, const char* src, size_t src_size, char pad_char )
{
  if ( dst == nullptr || dst_size == 0 ) {
    return;
  }
  dst[ --dst_size ] = '\0';
  while ( dst_size > 0 && src_size > 0 ) {
    if ( isdigit( src[ src_size - 1 ] ) ) {
      dst[ dst_size - 1 ] = src[ src_size - 1 ];
      --dst_size;
    }
    --src_size;
  }
  while ( dst_size > 0 ) {
    dst[ dst_size - 1 ] = pad_char;
    --dst_size;
  }
}
