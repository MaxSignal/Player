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

#if defined(PSP)

// Headers
#include "input_buttons.h"
#include "keys.h"

Input::ButtonMappingArray Input::GetDefaultButtonMappings() {
	return {
#if defined(USE_JOYSTICK) && defined(SUPPORT_JOYSTICK)
		{DECISION, Keys::JOY_B}, // Circle
		{DECISION, Keys::JOY_X}, // Cross
		{CANCEL, Keys::JOY_Y}, // Square
		{SHIFT, Keys::JOY_A}, // Triangle

		{TOGGLE_FPS, Keys::JOY_BACK}, // Select
		{DEBUG_MENU, Keys::JOY_START}, // Start
		{SHOW_LOG, Keys::JOY_Z}, // Hold

		{FAST_FORWARD, Keys::JOY_REAR_LEFT_1}, // Left trigger
		{RESET, Keys::JOY_REAR_RIGHT_1}, // Right trigger

		{DOWN, Keys::JOY_DPAD_DOWN}, // Down
		{LEFT, Keys::JOY_DPAD_LEFT}, // Left
		{UP, Keys::JOY_DPAD_UP}, // Up
		{RIGHT, Keys::JOY_DPAD_RIGHT}, // Right
#endif

#if defined(USE_JOYSTICK_AXIS)  && defined(SUPPORT_JOYSTICK_AXIS)
		{LEFT, Keys::JOY_STICK_PRIMARY_LEFT},
		{RIGHT, Keys::JOY_STICK_PRIMARY_RIGHT},
		{DOWN, Keys::JOY_STICK_PRIMARY_DOWN},
		{UP, Keys::JOY_STICK_PRIMARY_UP},
#endif
	};
}

Input::DirectionMappingArray Input::GetDefaultDirectionMappings() {
	return {
		{ Direction::DOWN, DOWN },
		{ Direction::LEFT, LEFT },
		{ Direction::RIGHT, RIGHT },
		{ Direction::UP, UP },
	};
}

#endif