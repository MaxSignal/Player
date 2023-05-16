#undef __STRICT_ANSI__
#include <io.h>
#include <stdio.h>
#include <wchar.h>
#include <winsock2.h>
#include <Shlwapi.h>
#include <windows.h>
#include <stdlib.h>
#include <fcntl.h>

#include "wincehelper.h"

char wceh_cwd[MAX_PATH + 1] = "";
char *wceh_getcwd(char *buffer, int maxlen) {
	if (wceh_cwd[0] == 0) {
		TCHAR buf[MAX_PATH + 1];
		if (GetModuleFileName(NULL, buf, MAX_PATH) == 0) {
			printf("Fatal error. GetModuleFileName failed.\n");
			exit(1);
		}
		char buf_char[MAX_PATH + 1] = "";
		WideCharToMultiByte(CP_ACP, 0, buf, -1, buf_char, sizeof(buf_char), NULL, NULL);
		char* dir_backslash;
		dir_backslash = strrchr(buf_char, '\\');
		strncpy(wceh_cwd, buf_char, dir_backslash - buf_char + 1);
		wceh_cwd[dir_backslash - buf_char + 1] = '\0';
		wceh_cwd[dir_backslash - buf_char + 2] = '\0';
	}
	if (maxlen <= strlen(wceh_cwd) ) {
		printf("Fatal error. Insufficient \"buffer\" length.\n");
		exit(1);
	}
	strncpy(buffer, wceh_cwd, strlen(wceh_cwd)+1);
	printf("wceh_cwd set: %s\n", wceh_cwd);
  printf("buffer set: %s\n", buffer);
	return wceh_cwd;
}


int wceh_CHDIR(const char *dirname) {
	if ((dirname[0] != 0) && (strlen(dirname) <= MAX_PATH + 1)) {
		strncpy(wceh_cwd, dirname, strlen(dirname)+1);
		printf("wceh_CHDIR set: %s\n", wceh_cwd);
		return 0;
	} else {
		return -1;
	}
}

////////////////////////////////////////////
//utf8towchar() is part of gcc source code//
////////////////////////////////////////////

static int utf8towchar(const char *utf8, wchar_t **outbuf)
{
  size_t buflen = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (void *)0, 0);
  wchar_t *buf = (wchar_t*)calloc(buflen, sizeof(wchar_t));
  if (MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, buflen) == 0) {
    free(buf);
    return -1;
  }
  *outbuf = buf;
  return 0;
}

FILE *wceh_fopen(const char *filename, const char *mode) {
	FILE *ret;
	printf("fopen: %s\n", filename);
  wchar_t *filename_wc;
  utf8towchar(filename, &filename_wc);
  wchar_t *mode_wc;
  utf8towchar(mode, &mode_wc);
	//ret = fopen(filename, mode);
	ret = _wfopen(filename_wc, mode_wc);
  /*HANDLE hret;
  hret = CreateFile(filename_wc, GENERIC_READ || GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  ret = _fdopen((HANDLE)hret, mode)*/;
	if (ret == NULL) {
		char buf[MAX_PATH + 1] = "";
		// strncpy(buf, wceh_cwd, strlen(wceh_cwd)+1);
    // printf("ret_fopen: %s\n", buf);
		strncat(buf, filename, strlen(filename)+1);
		printf("fopen: %s\n", buf);
    wchar_t *buf_wc;
    utf8towchar(buf, &buf_wc);
		//ret = fopen(buf, mode);
		ret = _wfopen(buf_wc, mode_wc);
    /*hret = CreateFile(buf_wc, GENERIC_READ || GENERIC_WRITE, 0, NULL,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    printf("fopen OK1.\n");
    ret = _fdopen((HANDLE)hret, mode);*/
	}
	if (ret == NULL) {
		printf("file not found!!\n");
		//exit(1);
	}
	return ret;
}

/////////////////////////////////////////////
//this namespace is part of gcc source code//
/////////////////////////////////////////////

namespace std {
  std::string to_string(int val)
  {
    char buffer[std::numeric_limits<int>::digits10 + 1
            + 2]; // '-' + '\0'
    std::sprintf(buffer, "%d", val);
    return buffer;
  }

  std::string to_string(unsigned int val)
  {
    char buffer[std::numeric_limits<unsigned int>::digits10 + 1
            + 1]; // '\0'
    std::sprintf(buffer, "%u", val);
    return buffer;
  }

  std::string to_string(long val)
  {
    char buffer[std::numeric_limits<long>::digits10 + 1
            + 2]; // '-' + '\0'
    std::sprintf(buffer, "%ld", val);
    return buffer;
  }

  std::string to_string(unsigned long val)
  {
    char buffer[std::numeric_limits<unsigned long>::digits10 + 1
            + 1]; // '\0'
    std::sprintf(buffer, "%lu", val);
    return buffer;
  }

  std::string to_string(long long int val)
  {
    char buffer[std::numeric_limits<long long int>::digits10 + 1
            + 2]; // '-' + '\0'
    std::sprintf(buffer, "%lld", val);
    return buffer;
  }

  std::string to_string(unsigned long long int val)
  {
    char buffer[std::numeric_limits<unsigned long long int>::digits10 + 1
            + 1]; // '\0'
    std::sprintf(buffer, "%llu", val);
    return buffer;
  }

  std::string to_string(float val)
  {
    char buffer[std::numeric_limits<float>::max_exponent10 + 1
            + 6   // fixed precision (printf's default)
            + 3]; // '-' + '.' + '\0'
    std::sprintf(buffer, "%f", val);
    return buffer;
  }

  std::string to_string(double val)
  {
    char buffer[std::numeric_limits<double>::max_exponent10 + 1
            + 6   // fixed precision (printf's default)
            + 3]; // '-' + '.' + '\0'
    std::sprintf(buffer, "%f", val);
    return buffer;
  }

  std::string to_string(long double val)
  {
    char buffer[std::numeric_limits<long double>::max_exponent10 + 1
            + 6   // fixed precision (printf's default)
            + 3]; // '-' + '.' + '\0'
    std::sprintf(buffer, "%Lf", val);
    return buffer;
  }
}