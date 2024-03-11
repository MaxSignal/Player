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
#include "scene_gamebrowser.h"
#include "audio_secache.h"
#include "cache.h"
#include "game_system.h"
#include "input.h"
#include "player.h"
#include "scene_title.h"
#include "bitmap.h"
#include "audio.h"
#include "keys.h"
#include "input_buttons.h"
#include "wincehelper.h"

#ifdef _WIN32
	#include <Windows.h>
#endif

namespace {
	std::string browser_dir;
}

Scene_GameBrowser::Scene_GameBrowser() {
	type = Scene::GameBrowser;
}

void Scene_GameBrowser::Start() {
	initial_debug_flag = Player::debug_flag;
	Game_System::SetSystemGraphic(CACHE_DEFAULT_BITMAP, RPG::System::Stretch_stretch, RPG::System::Font_gothic);
	CreateWindows();
	Game_Clock::ResetFrame(Game_Clock::now());
}

void Scene_GameBrowser::Continue(SceneType /* prev_scene */) {
#if defined(_WIN32) && !defined(UNDER_CE)
	SetCurrentDirectory(L"..");
#endif

	Main_Data::SetProjectPath(browser_dir);

	Cache::Clear();
	AudioSeCache::Clear();
	Data::Clear();
	Main_Data::Cleanup();
	FileFinder::Quit();

	Player::game_title = "";
	Player::engine = Player::EngineNone;

	Game_System::SetSystemGraphic(CACHE_DEFAULT_BITMAP, RPG::System::Stretch_stretch, RPG::System::Font_gothic);
	Game_System::BgmStop();

	Player::debug_flag = initial_debug_flag;
}

void Scene_GameBrowser::Update() {
	if (game_loading) {
		BootGame();
		return;
	}

	command_window->Update();
	gamelist_window->Update();
	settings_window->Update();

	if (command_window->GetActive()) {
		UpdateCommand();
	}
	else if (gamelist_window->GetActive()) {
		UpdateGameListSelection();
	}
	else if (settings_window->GetActive()) {
		UpdateSettings();
	}
}

void Scene_GameBrowser::CreateWindows() {
	// Create Options Window
	std::vector<std::string> options;

	options.push_back("Games");
	options.push_back("About");
	options.push_back("Setting");	
	options.push_back("Exit");

	command_window.reset(new Window_Command(options, 60));
	command_window->SetY(32);
	command_window->SetIndex(0);

	gamelist_window.reset(new Window_GameList(60, 32, SCREEN_TARGET_WIDTH - 60, SCREEN_TARGET_HEIGHT - 32));
	gamelist_window->Refresh();

	if (!gamelist_window->HasValidGames()) {
		command_window->DisableItem(0);
	}

	help_window.reset(new Window_Help(0, 0, SCREEN_TARGET_WIDTH, 32));
	help_window->SetText("EasyRPG Player - RPG Maker 2000/2003 interpreter");

	load_window.reset(new Window_Help(SCREEN_TARGET_WIDTH / 4, SCREEN_TARGET_HEIGHT / 2 - 16, SCREEN_TARGET_WIDTH / 2, 32));
	load_window->SetText("Loading...");
	load_window->SetVisible(false);

	about_window.reset(new Window_About(60, 32, SCREEN_TARGET_WIDTH - 60, SCREEN_TARGET_HEIGHT - 32));
	about_window->Refresh();
	about_window->SetVisible(false);

	settings_window.reset(new Window_Settings(60, 32, SCREEN_TARGET_WIDTH - 60, SCREEN_TARGET_HEIGHT - 32));
	settings_window->Refresh();
	settings_window->SetVisible(false);

	key_window.reset(new Window_Help(SCREEN_TARGET_WIDTH / 4, SCREEN_TARGET_HEIGHT / 2 - 16, SCREEN_TARGET_WIDTH / 2, 32));
	key_window->SetText("press a key to bind");
	key_window->SetVisible(false);
}

void Scene_GameBrowser::UpdateCommand() {
	int menu_index = command_window->GetIndex();

	switch (menu_index) {
		case GameList:
			gamelist_window->SetVisible(true);
			about_window->SetVisible(false);
			settings_window->SetVisible(false);
			break;
		case About:
			gamelist_window->SetVisible(false);
			about_window->SetVisible(true);
			settings_window->SetVisible(false);
			break;
		case Settings:
			gamelist_window->SetVisible(false);
			about_window->SetVisible(false);
			settings_window->SetVisible(true);
			break;
		default:
			break;
	}

	if (Input::IsTriggered(Input::CANCEL)) {
		Game_System::SePlay(Game_System::GetSystemSE(Game_System::SFX_Cancel));
		Scene::Pop();
	} else if (Input::IsTriggered(Input::DECISION)) {

		switch (menu_index) {
			case GameList:
				if (!gamelist_window->HasValidGames()) {
					return;
				}
				settings_window->SetActive(false);
				command_window->SetActive(false);
				command_window->SetIndex(-1);
				gamelist_window->SetActive(true);
				gamelist_window->SetIndex(old_gamelist_index);
				break;
			case About:
				break;
			case Settings:
				command_window->SetActive(false);
				command_window->SetIndex(-1);
				gamelist_window->SetActive(false);
				settings_window->SetActive(true);
				settings_window->SetIndex(0);
				break;
			default:
				Scene::Pop();
		}
	}
}

void Scene_GameBrowser::UpdateGameListSelection() {
	if (Input::IsTriggered(Input::CANCEL)) {
		command_window->SetActive(true);
		command_window->SetIndex(0);
		gamelist_window->SetActive(false);
		old_gamelist_index = gamelist_window->GetIndex();
		gamelist_window->SetIndex(-1);
	} else if (Input::IsTriggered(Input::DECISION)) {
		load_window->SetVisible(true);
		game_loading = true;
	} else if (Input::IsTriggered(Input::DEBUG_MENU) || Input::IsTriggered(Input::SHIFT)) {
		Player::debug_flag = true;
		load_window->SetVisible(true);
		game_loading = true;
	}
}

void Scene_GameBrowser::UpdateSettings() {

	if (input_mode == 1) {
		KeyAdd();
	} else if (Input::IsTriggered(Input::CANCEL)) {
		command_window->SetActive(true);
		command_window->SetIndex(2);
		settings_window->SetActive(false);
		settings_window->SetIndex(-1);
		input_mode = -1;
	} else if (Input::IsReleased(Input::DECISION)) {
		if (input_mode == -1) {
			input_mode = 0;
			return;
		}
		key_window->SetVisible(true);
		input_mode = 1;
		Game_Clock::SleepFor(std::chrono::milliseconds(100));
	}
}

void Scene_GameBrowser::KeyAdd() {
	BaseUi::KeyStatus& keys = DisplayUi->GetKeyStates();

	for (size_t i = 0; i < Input::Keys::KEYS_COUNT; ++i) {

		// Check if the key is pressed
		if (keys[i]) {

			int idx = settings_window->GetIndex();
			if (Input::IsTriggered(Input::SCROLL_DOWN) || Input::IsTriggered(Input::DOWN)) {
				idx -= 1;
			} else if (Input::IsTriggered(Input::SCROLL_UP) || Input::IsTriggered(Input::UP)){
				idx += 1;
			} 
			if (Input::IsPressed(Input::DECISION)) {
				input_mode = -1;
			} else {
				input_mode = 0;
			}
			std::string configFile = std::string(get_wceh_cwd())+"\\config.txt";
    		FILE* file = FileFinder::fopenUTF8(configFile.c_str(), "r");
			std::vector<std::string> lines;

			if (file != NULL) {
				char buffer[256];
				while (fgets(buffer, sizeof(buffer), file) != NULL) { 
					lines.emplace_back(buffer);
				}
			}
			fclose(file);

			auto it = Input::reverseKeyMap.find(static_cast<Input::Keys::InputKey>(i));
			std::string keyName = it->second;

			size_t pos = lines[idx].rfind(' ');
			lines[idx] = lines[idx].substr(0, pos) +  " " + keyName + "\n";

			file = FileFinder::fopenUTF8(configFile.c_str(), "w");

			for (const auto& str : lines) {
				fputs(str.c_str(), file);
			}
			fclose(file);

			file = FileFinder::fopenUTF8(configFile.c_str(), "r");
			Input::LoadButtonMapping(file);
			fclose(file);

			// Output the pressed key
			// Output::Warning("Key %zu is pressed.\n", i);
			settings_window->Refresh();

			settings_window->SetIndex(idx);
			key_window->SetVisible(false);
			break;
		}
	}
}

void Scene_GameBrowser::BootGame() {
#if defined(_WIN32) && !defined(UNDER_CE)
	SetCurrentDirectory(Utils::ToWideString(gamelist_window->GetGamePath()).c_str());
	const std::string& path = ".";
#else
	const std::string& path = gamelist_window->GetGamePath();
#endif

	if (browser_dir.empty())
		browser_dir = Main_Data::GetProjectPath();
	Main_Data::SetProjectPath(path);

	std::shared_ptr<FileFinder::DirectoryTree> tree = FileFinder::CreateDirectoryTree(path);
	FileFinder::SetDirectoryTree(tree);

	Player::CreateGameObjects();

	Scene::Push(std::make_shared<Scene_Title>());

	game_loading = false;
	load_window->SetVisible(false);
}
