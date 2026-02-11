#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H

/**
 * @file adder.h
 * @brief Declarations for the maths addition library.
 */

#if defined(_WIN32)
  #if defined(maths_STATIC)
    #define MATHSLIB_API
  #else
    #if defined(maths_EXPORTS)
      #define MATHSLIB_API __declspec(dllexport)
    #else
      #define MATHSLIB_API __declspec(dllimport)
    #endif
  #endif
#else
  #define MATHSLIB_API
#endif

/**
 * @brief Adds two integers.
 *
 * @param a First integer
 * @param b Second integer
 * @return Sum of a and b
 */
extern "C" MATHSLIB_API int add(int a, int b);

#endif
