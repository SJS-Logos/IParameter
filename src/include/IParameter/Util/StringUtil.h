//
// Created by SJS on 05/02/2024.
//

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>

struct StringUtil {

  /** Will convert a string representing a number to a long integer. 
      A valid number, consists of digits and possibly a sign ('-')
      This function does not raise exceptions.
      @param s A zero terminated string.
      @param defaultValue The value which is returned if s is not a number. 
      @param minValue the smallest value, which is regarded a valid number
      @param maxValue the largest value, which is regarded a valid number 
      @return The value represented by s or defaultValue */
  static
  long toLong( const char* s, long defaultValue, long minValue, long maxValue );

  /** @param s A zero terminated string
      @param size The size of the string 
      @retval true If the string contains a digit. */      
  static
  bool containsDigits( const char* s, size_t size );

  /** Will copy characters from the end of the src to the end dst buffer.
      Only characters where isdigit(c)!=0 will be copied.
      dst will be leftpadded with pad_char, until it contains dst_size-1 digits.
      @param dst Represents a zero terminated string. The destination to which characters are copied
      @param dst_size The size of the destination buffer. If dst_size>0 dst will be zero terminated.
      @param src The source buffer
      @param src_size The size of the src buffer 
      @param pad_char Character being filled into dst */
  static
  void copyLeastSignificantDigits( char* dst, size_t dst_size, const char* src, size_t src_size, char pad_char );

};

#endif // STRING_UTIL_H
