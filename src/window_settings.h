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

#ifndef EP_WINDOW_SETTINGS_H
#define EP_WINDOW_SETTINGS_H

// Headers
#include <vector>
#include "window_help.h"
#include "window_selectable.h"
#include "filefinder.h"

/**
 * Window_GameList class.
 */
class Window_Settings : public Window_Selectable {

public:
	/**
	 * Constructor.
	 */
	Window_Settings(int ix, int iy, int iwidth, int iheight);

	/**
	 * Refreshes the item list.
	 */
	void Refresh();

	/**
	 * Draws an item together with the quantity.
	 *
	 * @param index index of item to draw.
	 */
	void DrawItem(std::string text, int idx);
};

#endif