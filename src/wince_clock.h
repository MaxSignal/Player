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

#ifndef EP_PLATFORM_WINCE_CLOCK_H
#define EP_PLATFORM_WINCE_CLOCK_H

#ifdef UNDER_CE

#include <windows.h>
#include <winbase.h>
#include <cstdint>
#include <chrono>

struct WinceClock {
	using rep = int64_t;
	using period = std::milli;
	using duration = std::chrono::duration<rep,period>;
	using time_point = std::chrono::time_point<WinceClock,duration>;

	static constexpr bool is_steady = true;

	static time_point now();

	template <typename R, typename P>
	static void SleepFor(std::chrono::duration<R,P> dt);

	static constexpr const char* Name();
};

inline WinceClock::time_point WinceClock::now() {
	auto ticks = GetTickCount();
	return time_point(duration(ticks));
}

template <typename R, typename P>
inline void WinceClock::SleepFor(std::chrono::duration<R,P> dt) {
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dt);
	Sleep(ms.count());
}

constexpr const char* WinceClock::Name() {
	return "WinceClock";
}

#endif
#endif
