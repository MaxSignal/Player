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

#if !(defined(OPENDINGUX) || defined(GEKKO) || defined(USE_LIBRETRO))

#include <unordered_map>
#include <sstream>
// Headers
#include "input_buttons.h"
#include "keys.h"
#include "filefinder.h"
#include "wincehelper.h"

std::unordered_map<std::string, Input::InputButton> Input::buttonMap = {
	{"UP", Input::UP},
	{"DOWN", Input::DOWN},
	{"LEFT", Input::LEFT},
	{"RIGHT", Input::RIGHT},
	{"DECISION", Input::DECISION},
	{"CANCEL", Input::CANCEL},
	{"SHIFT", Input::SHIFT},
	{"N0", Input::N0},
	{"N1", Input::N1},
	{"N2", Input::N2},
	{"N3", Input::N3},
	{"N4", Input::N4},
	{"N5", Input::N5},
	{"N6", Input::N6},
	{"N7", Input::N7},
	{"N8", Input::N8},
	{"N9", Input::N9},
	{"PLUS", Input::PLUS},
	{"MINUS", Input::MINUS},
	{"MULTIPLY", Input::MULTIPLY},
	{"DIVIDE", Input::DIVIDE},
	{"PERIOD", Input::PERIOD},
	{"DEBUG_MENU", Input::DEBUG_MENU},
	{"DEBUG_THROUGH", Input::DEBUG_THROUGH},
	{"DEBUG_SAVE", Input::DEBUG_SAVE},
	{"TOGGLE_FPS", Input::TOGGLE_FPS},
	{"TAKE_SCREENSHOT", Input::TAKE_SCREENSHOT},
	{"SHOW_LOG", Input::SHOW_LOG},
	{"RESET", Input::RESET},
	{"PAGE_UP", Input::PAGE_UP},
	{"PAGE_DOWN", Input::PAGE_DOWN},
	{"SCROLL_UP", Input::SCROLL_UP},
	{"SCROLL_DOWN", Input::SCROLL_DOWN},
	{"FAST_FORWARD", Input::FAST_FORWARD},
	{"TOGGLE_FULLSCREEN", Input::TOGGLE_FULLSCREEN},
	{"TOGGLE_ZOOM", Input::TOGGLE_ZOOM},
	{"BUTTON_COUNT", Input::BUTTON_COUNT}
};

std::unordered_map<std::string, Input::Keys::InputKey> Input::keyMap = {
	{"NONE", Input::Keys::NONE},
	{"BACKSPACE", Input::Keys::BACKSPACE},
	{"TAB", Input::Keys::TAB},
	{"CLEAR", Input::Keys::CLEAR},
	{"RETURN", Input::Keys::RETURN},
	{"PAUSE", Input::Keys::PAUSE},
	{"ESCAPE", Input::Keys::ESCAPE},
	{"SPACE", Input::Keys::SPACE},
	{"PGUP", Input::Keys::PGUP},
	{"PGDN", Input::Keys::PGDN},
	{"ENDS", Input::Keys::ENDS},
	{"HOME", Input::Keys::HOME},
	{"LEFT", Input::Keys::LEFT},
	{"UP", Input::Keys::UP},
	{"RIGHT", Input::Keys::RIGHT},
	{"DOWN", Input::Keys::DOWN},
	{"SNAPSHOT", Input::Keys::SNAPSHOT},
	{"INSERT", Input::Keys::INSERT},
	{"DEL", Input::Keys::DEL},
	{"SHIFT", Input::Keys::SHIFT},
	{"LSHIFT", Input::Keys::LSHIFT},
	{"RSHIFT", Input::Keys::RSHIFT},
	{"CTRL", Input::Keys::CTRL},
	{"LCTRL", Input::Keys::LCTRL},
	{"RCTRL", Input::Keys::RCTRL},
	{"ALT", Input::Keys::ALT},
	{"LALT", Input::Keys::LALT},
	{"RALT", Input::Keys::RALT},
	{"N0", Input::Keys::N0},
	{"N1", Input::Keys::N1},
	{"N2", Input::Keys::N2},
	{"N3", Input::Keys::N3},
	{"N4", Input::Keys::N4},
	{"N5", Input::Keys::N5},
	{"N6", Input::Keys::N6},
	{"N7", Input::Keys::N7},
	{"N8", Input::Keys::N8},
	{"N9", Input::Keys::N9},
	{"A", Input::Keys::A},
	{"B", Input::Keys::B},
	{"C", Input::Keys::C},
	{"D", Input::Keys::D},
	{"E", Input::Keys::E},
	{"F", Input::Keys::F},
	{"G", Input::Keys::G},
	{"H", Input::Keys::H},
	{"I", Input::Keys::I},
	{"J", Input::Keys::J},
	{"K", Input::Keys::K},
	{"L", Input::Keys::L},
	{"M", Input::Keys::M},
	{"N", Input::Keys::N},
	{"O", Input::Keys::O},
	{"P", Input::Keys::P},
	{"Q", Input::Keys::Q},
	{"R", Input::Keys::R},
	{"S", Input::Keys::S},
	{"T", Input::Keys::T},
	{"U", Input::Keys::U},
	{"V", Input::Keys::V},
	{"W", Input::Keys::W},
	{"X", Input::Keys::X},
	{"Y", Input::Keys::Y},
	{"Z", Input::Keys::Z},
	{"LOS", Input::Keys::LOS},
	{"ROS", Input::Keys::ROS},
	{"MENU", Input::Keys::MENU},
	{"KP0", Input::Keys::KP0},
	{"KP1", Input::Keys::KP1},
	{"KP2", Input::Keys::KP2},
	{"KP3", Input::Keys::KP3},
	{"KP4", Input::Keys::KP4},
	{"KP5", Input::Keys::KP5},
	{"KP6", Input::Keys::KP6},
	{"KP7", Input::Keys::KP7},
	{"KP8", Input::Keys::KP8},
	{"KP9", Input::Keys::KP9},
	{"MULTIPLY", Input::Keys::MULTIPLY},
	{"ADD", Input::Keys::ADD},
	{"SUBTRACT", Input::Keys::SUBTRACT},
	{"PERIOD", Input::Keys::PERIOD},
	{"DIVIDE", Input::Keys::DIVIDE},
	{"F1", Input::Keys::F1},
	{"F2", Input::Keys::F2},
	{"F3", Input::Keys::F3},
	{"F4", Input::Keys::F4},
	{"F5", Input::Keys::F5},
	{"F6", Input::Keys::F6},
	{"F7", Input::Keys::F7},
	{"F8", Input::Keys::F8},
	{"F9", Input::Keys::F9},
	{"F10", Input::Keys::F10},
	{"F11", Input::Keys::F11},
	{"F12", Input::Keys::F12},
	{"CAPS_LOCK", Input::Keys::CAPS_LOCK},
	{"NUM_LOCK", Input::Keys::NUM_LOCK},
	{"SCROLL_LOCK", Input::Keys::SCROLL_LOCK},
	{"AC_BACK", Input::Keys::AC_BACK},
	{"SELECT", Input::Keys::SELECT},
	{"KEYS_COUNT", Input::Keys::KEYS_COUNT}
};

std::unordered_map<Input::Keys::InputKey, std::string> createReverseMap(const std::unordered_map<std::string, Input::Keys::InputKey>& map) {
    std::unordered_map<Input::Keys::InputKey, std::string> reverseMap;
    for (const auto& pair : map) {
        reverseMap[pair.second] = pair.first;
    }
    return reverseMap;
}

std::unordered_map<Input::Keys::InputKey, std::string> Input::reverseKeyMap = createReverseMap(Input::keyMap);

void Input::LoadButtonMapping(FILE* file) {

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        std::istringstream iss(line);
        std::string buttonName, keyName;
        if (iss >> buttonName >> keyName) {
            auto it = buttonMap.find(buttonName);
			auto it2 = keyMap.find(keyName);
            if (it != buttonMap.end() && it2 != keyMap.end()) {
                buttons[it->second].push_back(it2->second);
            }
        }
    }
}

void Input::InitButtonsFromConfig(const std::string& configFile) {
    buttons.resize(BUTTON_COUNT);

    FILE* file = FileFinder::fopenUTF8(configFile.c_str(), "r");
    if (file) {
        LoadButtonMapping(file);
        fclose(file);
    } else {
        FILE* file = FileFinder::fopenUTF8(configFile.c_str(), "w");
		if (file) {
			fputs(
				"UP UP\n"
				"UP K\n"
				"UP KP8\n"
				"UP W\n"
				"DOWN DOWN\n"
				"DOWN J\n"
				"DOWN KP2\n"
				"DOWN S\n"
				"LEFT LEFT\n"
				"LEFT H\n"
				"LEFT KP4\n"
				"LEFT A\n"
				"RIGHT RIGHT\n"
				"RIGHT L\n"
				"RIGHT KP6\n"
				"RIGHT D\n"
				"DECISION Z\n"
				"DECISION Y\n"
				"DECISION SPACE\n"
				"DECISION RETURN\n"
				"DECISION SELECT\n"
				"CANCEL AC_BACK\n"
				"CANCEL X\n"
				"CANCEL C\n"
				"CANCEL V\n"
				"CANCEL B\n"
				"CANCEL N\n"
				"CANCEL ESCAPE\n"
				"CANCEL KP0\n"
				"SHIFT LSHIFT\n"
				"SHIFT RSHIFT\n"
				"N0 N0\n"
				"N1 N1\n"
				"N2 N2\n"
				"N3 N3\n"
				"N4 N4\n"
				"N5 N5\n"
				"N6 N6\n"
				"N7 N7\n"
				"N8 N8\n"
				"N9 N9\n"
				"PLUS ADD\n"
				"MINUS SUBTRACT\n"
				"MULTIPLY MULTIPLY\n"
				"DIVIDE DIVIDE\n"
				"PERIOD PERIOD\n"
				"DEBUG_MENU F9\n"
				"DEBUG_THROUGH LCTRL\n"
				"DEBUG_THROUGH RCTRL\n"
				"DEBUG_SAVE F11\n"
				"TAKE_SCREENSHOT F10\n"
				"TOGGLE_FPS F2\n"
				"SHOW_LOG F3\n"
				"TOGGLE_FULLSCREEN F4\n"
				"TOGGLE_ZOOM F5\n"
				"PAGE_UP NONE\n"
				"PAGE_DOWN NONE\n"
				"RESET F12\n"
				"FAST_FORWARD F\n",
				file
			);
			fclose(file);
    	}
		file = FileFinder::fopenUTF8(configFile.c_str(), "r");
		LoadButtonMapping(file);
		fclose(file);
	}
}

void Input::InitButtons() {
	buttons.resize(BUTTON_COUNT);
	InitButtonsFromConfig(std::string(get_wceh_cwd())+"\\config.txt");

	// buttons[buttonMap.find("UP")->second].push_back(keyMap.find("UP")->second);
	// buttons[buttonMap.find("UP")->second].push_back(keyMap.find("K")->second);
	// buttons[buttonMap.find("UP")->second].push_back(keyMap.find("KP8")->second);
	// buttons[UP].push_back(Keys::W);
	// buttons[DOWN].push_back(Keys::DOWN);
	// buttons[DOWN].push_back(Keys::J);
	// buttons[DOWN].push_back(Keys::KP2);
	// buttons[DOWN].push_back(Keys::S);
	// buttons[LEFT].push_back(Keys::LEFT);
	// buttons[LEFT].push_back(Keys::H);
	// buttons[LEFT].push_back(Keys::KP4);
	// buttons[LEFT].push_back(Keys::A);
	// buttons[RIGHT].push_back(Keys::RIGHT);
	// buttons[RIGHT].push_back(Keys::L);
	// buttons[RIGHT].push_back(Keys::KP6);
	// buttons[RIGHT].push_back(Keys::D);
	// buttons[DECISION].push_back(Keys::Z);
	// buttons[DECISION].push_back(Keys::Y);
	// buttons[DECISION].push_back(Keys::SPACE);
	// buttons[DECISION].push_back(Keys::RETURN);
	// buttons[DECISION].push_back(Keys::SELECT);
	// buttons[CANCEL].push_back(Keys::AC_BACK);
	// buttons[CANCEL].push_back(Keys::X);
	// buttons[CANCEL].push_back(Keys::C);
	// buttons[CANCEL].push_back(Keys::V);
	// buttons[CANCEL].push_back(Keys::B);
	// buttons[CANCEL].push_back(Keys::N);
	// buttons[CANCEL].push_back(Keys::ESCAPE);
	// buttons[CANCEL].push_back(Keys::KP0);
	// buttons[SHIFT].push_back(Keys::LSHIFT);
	// buttons[SHIFT].push_back(Keys::RSHIFT);
	// buttons[N0].push_back(Keys::N0);
	// buttons[N1].push_back(Keys::N1);
	// buttons[N2].push_back(Keys::N2);
	// buttons[N3].push_back(Keys::N3);
	// buttons[N4].push_back(Keys::N4);
	// buttons[N5].push_back(Keys::N5);
	// buttons[N6].push_back(Keys::N6);
	// buttons[N7].push_back(Keys::N7);
	// buttons[N8].push_back(Keys::N8);
	// buttons[N9].push_back(Keys::N9);
	// buttons[PLUS].push_back(Keys::ADD);
	// buttons[MINUS].push_back(Keys::SUBTRACT);
	// buttons[MULTIPLY].push_back(Keys::MULTIPLY);
	// buttons[DIVIDE].push_back(Keys::DIVIDE);
	// buttons[PERIOD].push_back(Keys::PERIOD);
	// buttons[DEBUG_MENU].push_back(Keys::F9);
	// buttons[DEBUG_THROUGH].push_back(Keys::LCTRL);
	// buttons[DEBUG_THROUGH].push_back(Keys::RCTRL);
	// buttons[DEBUG_SAVE].push_back(Keys::F11);
	// buttons[TAKE_SCREENSHOT].push_back(Keys::F10);
	// buttons[TOGGLE_FPS].push_back(Keys::F2);
	// buttons[SHOW_LOG].push_back(Keys::F3);
	// buttons[TOGGLE_FULLSCREEN].push_back(Keys::F4);
	// buttons[TOGGLE_ZOOM].push_back(Keys::F5);
	// buttons[PAGE_UP].push_back(Keys::PGUP);
	// buttons[PAGE_DOWN].push_back(Keys::PGDN);
	// buttons[RESET].push_back(Keys::F12);
	// buttons[FAST_FORWARD].push_back(Keys::F);

#if defined(USE_MOUSE) && defined(SUPPORT_MOUSE)
	buttons[DECISION].push_back(Keys::MOUSE_LEFT);
	buttons[CANCEL].push_back(Keys::MOUSE_RIGHT);
	buttons[SHIFT].push_back(Keys::MOUSE_MIDDLE);
	buttons[SCROLL_UP].push_back(Keys::MOUSE_SCROLLUP);
	buttons[SCROLL_DOWN].push_back(Keys::MOUSE_SCROLLDOWN);
#endif

#if defined(USE_JOYSTICK) && defined(SUPPORT_JOYSTICK)
	// FIXME: Random joystick keys mapping, better to read joystick configuration from .ini
	buttons[UP].push_back(Keys::JOY_8);
	buttons[DOWN].push_back(Keys::JOY_2);
	buttons[LEFT].push_back(Keys::JOY_4);
	buttons[RIGHT].push_back(Keys::JOY_6);
	buttons[DECISION].push_back(Keys::JOY_1);
	buttons[CANCEL].push_back(Keys::JOY_3);
	buttons[SHIFT].push_back(Keys::JOY_5);
	buttons[N0].push_back(Keys::JOY_10);
	buttons[N1].push_back(Keys::JOY_11);
	buttons[N2].push_back(Keys::JOY_12);
	buttons[N3].push_back(Keys::JOY_13);
	buttons[N4].push_back(Keys::JOY_14);
	buttons[N5].push_back(Keys::JOY_15);
	buttons[N6].push_back(Keys::JOY_16);
	buttons[N7].push_back(Keys::JOY_17);
	buttons[N8].push_back(Keys::JOY_18);
	buttons[N9].push_back(Keys::JOY_19);
	buttons[PLUS].push_back(Keys::JOY_20);
	buttons[MINUS].push_back(Keys::JOY_21);
	buttons[MULTIPLY].push_back(Keys::JOY_22);
	buttons[DIVIDE].push_back(Keys::JOY_23);
	buttons[PERIOD].push_back(Keys::JOY_24);
	buttons[DEBUG_MENU].push_back(Keys::JOY_7);
	buttons[DEBUG_THROUGH].push_back(Keys::JOY_9);
#endif

#if defined(USE_JOYSTICK_HAT)  && defined(SUPPORT_JOYSTICK_HAT)
	buttons[DOWN].push_back(Keys::JOY_HAT_DOWN);
	buttons[LEFT].push_back(Keys::JOY_HAT_LEFT);
	buttons[RIGHT].push_back(Keys::JOY_HAT_RIGHT);
	buttons[UP].push_back(Keys::JOY_HAT_UP);

#endif

#if defined(USE_JOYSTICK_AXIS)  && defined(SUPPORT_JOYSTICK_AXIS)
	buttons[LEFT].push_back(Keys::JOY_AXIS_X_LEFT);
	buttons[RIGHT].push_back(Keys::JOY_AXIS_X_RIGHT);
	buttons[DOWN].push_back(Keys::JOY_AXIS_Y_DOWN);
	buttons[UP].push_back(Keys::JOY_AXIS_Y_UP);
#endif

#if defined(USE_TOUCH) && defined(SUPPORT_TOUCH)
	buttons[DECISION].push_back(Keys::ONE_FINGER);
	buttons[CANCEL].push_back(Keys::TWO_FINGERS);
#endif

	dir_buttons.resize(10);
	dir_buttons[2].push_back(DOWN);
	dir_buttons[4].push_back(LEFT);
	dir_buttons[6].push_back(RIGHT);
	dir_buttons[8].push_back(UP);
}

#endif
