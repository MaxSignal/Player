#ifndef WINCEHELPER__STD__TO_STRING
#define WINCEHELPER__STD__TO_STRING
#include <cstdio>
#include <string>
#include <limits>

#ifndef WINCEHELPER__FUNC
#define WINCEHELPER__FUNC
char *wceh_getcwd(char *buffer, int maxlen);
int wceh_CHDIR(const char *dirname);
FILE *wceh_fopen(const char *filename, const char *mode);
#endif

///////////////////////////
//part of gcc source code//
///////////////////////////

namespace std {
  std::string to_string(int val);
  std::string to_string(unsigned int val);
  std::string to_string(long val);
  std::string to_string(unsigned long val);
  std::string to_string(long long val);
  std::string to_string(unsigned long long val);
  std::string to_string(float val);
  std::string to_string(double val);
  std::string to_string(long double val);
}

#endif

#ifndef WINCEHELPER__M_PI
#define WINCEHELPER__M_PI
#define M_PI		3.14159265358979323846
#endif