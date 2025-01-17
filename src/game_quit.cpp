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
#ifdef UNDER_CE
#include "wincehelper.h"
#endif

#include "game_quit.h"
#include "options.h"
#include "input.h"
#include "scene.h"

constexpr int num_seconds = 2;
constexpr int start_time = num_seconds * DEFAULT_FPS;

constexpr int window_height = 32;

Game_Quit::Game_Quit()
	: window(SCREEN_TARGET_WIDTH / 4, SCREEN_TARGET_HEIGHT / 2 - window_height / 2, SCREEN_TARGET_WIDTH / 2, window_height, Drawable::Flags::Global)
{
	window.SetBackOpacity(128);
	window.SetZ(Priority_Overlay - 20);
	Reset();
}

void Game_Quit::Update() {
	if (Scene::instance == nullptr || Scene::instance->type == Scene::Title || !Input::IsPressed(Input::RESET)) {
		if (time_left != start_time) {
			Reset();
		}
		return;
	}

	window.SetVisible(true);

	if (time_left > 0) {
		--time_left;
	}

	// FIXME Need to write the text every frame in case system graphic changes..
	auto s = (time_left + DEFAULT_FPS - 1) / DEFAULT_FPS;
	window.SetText("Restarting in " + std::to_string(s) + " sec ...");
	window.Update();
}

void Game_Quit::Reset() {
	window.SetVisible(false);
	time_left = DEFAULT_FPS * num_seconds;
}

