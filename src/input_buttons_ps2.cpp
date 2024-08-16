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

#if defined(PS2)

// Headers
#include "input_buttons.h"
#include "keys.h"

void Input::InitButtons() {
	buttons.resize(BUTTON_COUNT);

	buttons[UP].push_back(Keys::UP);
	buttons[UP].push_back(Keys::K);
	buttons[UP].push_back(Keys::KP8);
	buttons[UP].push_back(Keys::W);
	buttons[DOWN].push_back(Keys::DOWN);
	buttons[DOWN].push_back(Keys::J);
	buttons[DOWN].push_back(Keys::KP2);
	buttons[DOWN].push_back(Keys::S);
	buttons[LEFT].push_back(Keys::LEFT);
	buttons[LEFT].push_back(Keys::H);
	buttons[LEFT].push_back(Keys::KP4);
	buttons[LEFT].push_back(Keys::A);
	buttons[RIGHT].push_back(Keys::RIGHT);
	buttons[RIGHT].push_back(Keys::L);
	buttons[RIGHT].push_back(Keys::KP6);
	buttons[RIGHT].push_back(Keys::D);
	buttons[DECISION].push_back(Keys::Z);
	buttons[DECISION].push_back(Keys::Y);
	buttons[DECISION].push_back(Keys::SPACE);
	buttons[DECISION].push_back(Keys::RETURN);
	buttons[DECISION].push_back(Keys::SELECT);
	buttons[CANCEL].push_back(Keys::AC_BACK);
	buttons[CANCEL].push_back(Keys::X);
	buttons[CANCEL].push_back(Keys::C);
	buttons[CANCEL].push_back(Keys::V);
	buttons[CANCEL].push_back(Keys::B);
	buttons[CANCEL].push_back(Keys::N);
	buttons[CANCEL].push_back(Keys::ESCAPE);
	buttons[CANCEL].push_back(Keys::KP0);
	buttons[SHIFT].push_back(Keys::LSHIFT);
	buttons[SHIFT].push_back(Keys::RSHIFT);
	buttons[N0].push_back(Keys::N0);
	buttons[N1].push_back(Keys::N1);
	buttons[N2].push_back(Keys::N2);
	buttons[N3].push_back(Keys::N3);
	buttons[N4].push_back(Keys::N4);
	buttons[N5].push_back(Keys::N5);
	buttons[N6].push_back(Keys::N6);
	buttons[N7].push_back(Keys::N7);
	buttons[N8].push_back(Keys::N8);
	buttons[N9].push_back(Keys::N9);
	buttons[PLUS].push_back(Keys::ADD);
	buttons[MINUS].push_back(Keys::SUBTRACT);
	buttons[MULTIPLY].push_back(Keys::MULTIPLY);
	buttons[DIVIDE].push_back(Keys::DIVIDE);
	buttons[PERIOD].push_back(Keys::PERIOD);
	buttons[DEBUG_MENU].push_back(Keys::F9);
	buttons[DEBUG_THROUGH].push_back(Keys::LCTRL);
	buttons[DEBUG_THROUGH].push_back(Keys::RCTRL);
	buttons[DEBUG_SAVE].push_back(Keys::F11);
	buttons[TAKE_SCREENSHOT].push_back(Keys::F10);
	buttons[TOGGLE_FPS].push_back(Keys::F2);
	buttons[SHOW_LOG].push_back(Keys::F3);
	buttons[TOGGLE_FULLSCREEN].push_back(Keys::F4);
	buttons[TOGGLE_ZOOM].push_back(Keys::F5);
	buttons[PAGE_UP].push_back(Keys::PGUP);
	buttons[PAGE_DOWN].push_back(Keys::PGDN);
	buttons[RESET].push_back(Keys::F12);
	buttons[FAST_FORWARD].push_back(Keys::F);

#if defined(USE_JOYSTICK) && defined(SUPPORT_JOYSTICK)
	// FIXME: Random joystick keys mapping, better to read joystick configuration from .ini
	buttons[SHIFT].push_back(Keys::JOY_8); //L2
	buttons[LEFT].push_back(Keys::JOY_7); //LEFT
	buttons[DOWN].push_back(Keys::JOY_6); //DOWN
	buttons[RIGHT].push_back(Keys::JOY_5); //RIGHT
	buttons[UP].push_back(Keys::JOY_4); //UP
	buttons[DECISION].push_back(Keys::JOY_3); //START
	buttons[CANCEL].push_back(Keys::JOY_0); //SELECT
	buttons[N3].push_back(Keys::JOY_1); //L3
	buttons[N4].push_back(Keys::JOY_2); //R3
	buttons[N1].push_back(Keys::JOY_9); //L1
	buttons[TOGGLE_FPS].push_back(Keys::JOY_10); //R2
	buttons[N2].push_back(Keys::JOY_11); //R1
	buttons[DECISION].push_back(Keys::JOY_12); //TRIANGLE
	buttons[CANCEL].push_back(Keys::JOY_13); //CIRCLE
	buttons[DECISION].push_back(Keys::JOY_14); //CROSS
	buttons[CANCEL].push_back(Keys::JOY_15); //SQUARE
#endif

#if defined(USE_JOYSTICK_AXIS)  && defined(SUPPORT_JOYSTICK_AXIS)
	buttons[LEFT].push_back(Keys::JOY_AXIS_X_LEFT);
	buttons[RIGHT].push_back(Keys::JOY_AXIS_X_RIGHT);
	buttons[DOWN].push_back(Keys::JOY_AXIS_Y_DOWN);
	buttons[UP].push_back(Keys::JOY_AXIS_Y_UP);
#endif

	dir_buttons.resize(10);
	dir_buttons[2].push_back(DOWN);
	dir_buttons[4].push_back(LEFT);
	dir_buttons[6].push_back(RIGHT);
	dir_buttons[8].push_back(UP);
}

#endif