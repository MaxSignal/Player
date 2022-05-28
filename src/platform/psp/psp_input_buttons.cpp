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
		{DECISION, Keys::JOY_1}, // Circle
		{DECISION, Keys::JOY_2}, // Cross
		{CANCEL, Keys::JOY_3}, // Square
		{SHIFT, Keys::JOY_0}, // Triangle

		{TOGGLE_FPS, Keys::JOY_10}, // Select
		{DEBUG_MENU, Keys::JOY_11}, // Start
		{SHOW_LOG, Keys::JOY_13}, // Hold

		{FAST_FORWARD, Keys::JOY_4}, // Left trigger
		{RESET, Keys::JOY_5}, // Right trigger

		{DOWN, Keys::JOY_6}, // Down
		{LEFT, Keys::JOY_7}, // Left
		{UP, Keys::JOY_8}, // Up
		{RIGHT, Keys::JOY_9}, // Right
#endif

#if defined(USE_JOYSTICK_AXIS)  && defined(SUPPORT_JOYSTICK_AXIS)
		{LEFT, Keys::JOY_AXIS_X_LEFT},
		{RIGHT, Keys::JOY_AXIS_X_RIGHT},
		{DOWN, Keys::JOY_AXIS_Y_DOWN},
		{UP, Keys::JOY_AXIS_Y_UP},
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