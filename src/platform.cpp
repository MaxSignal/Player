/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include "platform.h"
#include "utils.h"
#include <cassert>
#include <utility>
#include "output.h"

#ifdef UNDER_CE
#include "wincehelper.h"
#include <windows.h>
/*std::wstring s2ws(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}*/
#endif

#ifndef DT_UNKNOWN
#define DT_UNKNOWN 0
#endif
#ifndef DT_REG
#define DT_REG DT_UNKNOWN
#endif
#ifndef DT_DIR
#define DT_DIR DT_UNKNOWN
#endif

Platform::File::File(std::string name) :
#if defined(_WIN32)// && !defined(UNDER_CE)
		filename(Utils::ToWideString(name))
#else
		filename(std::move(name))
#endif
{
	// no-op
}

bool Platform::File::Exists() const {
#if defined(_WIN32)// && !defined(UNDER_CE)
	return ::GetFileAttributesW(filename.c_str()) != (DWORD)-1;
#elif (defined(GEKKO) || defined(_3DS) || defined(__SWITCH__))
	struct stat sb;
	return ::stat(filename.c_str(), &sb) == 0;
#elif defined(PSP2)
	struct SceIoStat sb;
	return (::sceIoGetstat(filename.c_str(), &sb) >= 0);
#else
	return ::access(filename.c_str(), F_OK) != -1;
#endif
}

bool Platform::File::IsFile(bool follow_symlinks) const {
	return GetType(follow_symlinks) == FileType::File;
}

bool Platform::File::IsDirectory(bool follow_symlinks) const {
	return GetType(follow_symlinks) == FileType::Directory;
}

Platform::FileType Platform::File::GetType(bool follow_symlinks) const {
#if defined(_WIN32)
	(void)follow_symlinks;
	int attribs = ::GetFileAttributesW(filename.c_str());

	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return FileType::Unknown;
	} else if ((attribs & FILE_ATTRIBUTE_DIRECTORY) == 0) {
		return FileType::File;
	} else if ((attribs & (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_REPARSE_POINT)) == FILE_ATTRIBUTE_DIRECTORY) {
		return FileType::Directory;
	}
	return FileType::Other;
#elif defined(PSP2)
	(void)follow_symlinks;
	struct SceIoStat sb = {};
	if (::sceIoGetstat(filename.c_str(), &sb) >= 0) {
		return SCE_S_ISREG(sb.st_mode) ? FileType::File :
			SCE_S_ISDIR(sb.st_mode) ? FileType::Directory :
			FileType::Other;
	}
	return FileType::Unknown;
#else
	struct stat sb = {};
#  if (defined(GEKKO) || defined(_3DS) || defined(__SWITCH__)
	(void)follow_symlinks;
	auto fn = ::stat;
#  else
	auto fn = follow_symlinks ? ::stat : ::lstat;
#  endif
	if (fn(filename.c_str(), &sb) == 0) {
		return S_ISREG(sb.st_mode) ? FileType::File :
			S_ISDIR(sb.st_mode) ? FileType::Directory :
			FileType::Other;
	}
	return FileType::Unknown;
#endif
}

int64_t Platform::File::GetSize() const {
#if defined(_WIN32)
	WIN32_FILE_ATTRIBUTE_DATA data;
	BOOL res = ::GetFileAttributesExW(filename.c_str(),
			GetFileExInfoStandard,
			&data);
	if (!res) {
		return -1;
	}

	return ((int64_t)data.nFileSizeHigh << 32) | (int64_t)data.nFileSizeLow;
#elif defined(PSP2)
	struct SceIoStat sb = {};
	int result = ::sceIoGetstat(filename.c_str(), &sb);
	return (result >= 0) ? (int64_t)sb.st_size : (int64_t)-1;
#else
	struct stat sb = {};
	int result = ::stat(filename.c_str(), &sb);
	return (result == 0) ? (int64_t)sb.st_size : (int64_t)-1;
#endif
}

Platform::Directory::Directory(const std::string& name) {
#if defined(UNDER_CE)
	//printf("opendir(compat): %s\n", name.c_str());
	dir_handle = FindFirstFile(Utils::ToWideString(name + "\\*").c_str(), &entry);
	LOAD_FIRSTFILE = 1;
	LOAD_FIRSTFILE_DATA = entry;
#elif defined(_WIN32) // && !defined(UNDER_CE)
	dir_handle = ::_wopendir(Utils::ToWideString(name).c_str());
#elif defined(PSP2)
	dir_handle = ::sceIoDopen(name.c_str());
#else
	dir_handle = ::opendir(name.c_str());
#endif
}

Platform::Directory::~Directory() {
	Close();
}

bool Platform::Directory::Read() {
#if defined(PSP2)
	assert(dir_handle >= 0);

	valid_entry = ::sceIoDread(dir_handle, &entry) > 0;
#else
	assert(dir_handle);

#   if defined(UNDER_CE)
	if (LOAD_FIRSTFILE == 0){
		valid_entry = FindNextFile(dir_handle, &entry);
	} else {
		valid_entry = true;
		entry = LOAD_FIRSTFILE_DATA;
		LOAD_FIRSTFILE = 0;
	}

#	elif defined(_WIN32)// && !defined(UNDER_CE)
	entry = ::_wreaddir(dir_handle);
#	else
	entry = ::readdir(dir_handle);
#	endif

#ifndef UNDER_CE
	valid_entry = entry != nullptr;
/*#else
	if (dir_handle != INVALID_HANDLE_VALUE) {
		valid_entry = true;
	} else {
		valid_entry = false;
	}*/
#endif
#endif

	return valid_entry;
}

std::string Platform::Directory::GetEntryName() const {
	assert(valid_entry);

#if defined(PSP2)
	return entry.d_name;
#elif defined(UNDER_CE)
    return Utils::FromWideString(entry.cFileName);
#elif defined(_WIN32) && !defined(UNDER_CE)
	return Utils::FromWideString(entry->d_name);
#else
	char tempstr[260];
	strncpy(tempstr, entry->d_name, strlen(entry->d_name)+1);
	return (char*)entry->d_name;
#endif
}

#ifndef PSP2
static inline Platform::FileType GetEntryType(...) {
	return Platform::FileType::Unknown;
}

template <typename T, typename = decltype(std::declval<T>().d_type)>
static inline Platform::FileType GetEntryType(T* entry) {
	return entry->d_type == DT_REG ? Platform::FileType::File :
		   entry->d_type == DT_DIR ? Platform::FileType::Directory :
		   entry->d_type == DT_UNKNOWN ? Platform::FileType::Unknown : Platform::FileType::Other;
}
#endif

Platform::FileType Platform::Directory::GetEntryType() const {
	assert(valid_entry);

#if defined(PSP2)
	return SCE_S_ISREG(entry.d_stat.st_mode) ? FileType::File :
			SCE_S_ISDIR(entry.d_stat.st_mode) ? FileType::Directory : FileType::Other;
#else
	return ::GetEntryType(entry);
#endif
}

void Platform::Directory::Close() {
	if (*this) {
#if defined(UNDER_CE)
		FindClose(dir_handle);
		dir_handle = nullptr;
		LOAD_FIRSTFILE = 0;
#elif defined(_WIN32)// && !defined(UNDER_CE)
		::_wclosedir(dir_handle);
		dir_handle = nullptr;
#elif defined(PSP2)
		::sceIoDclose(dir_handle);
		dir_handle = -1;
#else
		::closedir(dir_handle);
		dir_handle = nullptr;
#endif
	}

	valid_entry = false;
}
