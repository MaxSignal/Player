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

#ifndef EP_PLATFORM_NSPIRE_CLOCK_H
#define EP_PLATFORM_NSPIRE_CLOCK_H

#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <chrono>

struct NspireClock {
	using rep = int64_t;
	using period = std::milli;
	using duration = std::chrono::duration<rep,period>;
	using time_point = std::chrono::time_point<NspireClock,duration>;

	static constexpr bool is_steady = true;

	static time_point now();

	template <typename R, typename P>
	static void SleepFor(std::chrono::duration<R,P> dt);

	static constexpr const char* Name();
};

inline NspireClock::time_point NspireClock::now() {
	auto ticks = SDL_GetTicks();
	return time_point(duration(ticks));
}

template <typename R, typename P>
inline void NspireClock::SleepFor(std::chrono::duration<R,P> dt) {
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dt);
	SDL_Delay(ms.count());
}

constexpr const char* NspireClock::Name() {
	return "NspireClock";
}

#endif