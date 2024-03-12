///////////////////////////////////////////////////////////////////////////////
//  wincehelper.h
//  WinCE での動作を前提としていないプログラムを
//  WinCE で動かせるようにするための自作関数
//  (C) HO_0520_IT
//  CC0, Unlicense, WTFPL Version 2, NYSL Version 0.9982
//  https://github.com/HO-0520-IT/wincehelper
///////////////////////////////////////////////////////////////////////////////

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
char *get_wceh_cwd();
std::wstring stringtowidestring(std::string str);
#endif

/* These functions and namespaces are part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

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