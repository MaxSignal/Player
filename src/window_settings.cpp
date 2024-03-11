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
#include <iomanip>
#include <cstdio>
#include <sstream>
#include "bitmap.h"
#include "font.h"
#include "window_settings.h"
#include "wincehelper.h"

Window_Settings::Window_Settings(int ix, int iy, int iwidth, int iheight) :
	Window_Selectable(ix, iy, iwidth, iheight) {
	column_max = 1;
}

void Window_Settings::Refresh() {
    std::string configFile = std::string(get_wceh_cwd())+"\\config.txt";
    FILE* file = FileFinder::fopenUTF8(configFile.c_str(), "r");

    if(file) {
        char line[256];
        int len = 0;
        while (fgets(line, sizeof(line), file)) {
            ++len;
        }
        item_max = len;

        CreateContents();
        contents->Clear();

        fseek(file, 0, SEEK_SET);

        int i = 0;
        while (fgets(line, sizeof(line), file)) {
            std::istringstream iss(line);
            std::string buttonName, keyName;
            if (iss >> buttonName >> keyName) {
                DrawItem("Button: "+buttonName + " Key: "+ keyName, i);
                ++i;
            }
        }
    } else {
        SetContents(Bitmap::Create(width - 16, height - 16));

        contents->TextDraw(0, 0, Font::ColorKnockout, "Serious Error Occured.");
    }
    fclose(file);
    

    // for (int i=0; i < 10; i++){
    //     DrawItem("asdf", i);
    // }
}

void Window_Settings::DrawItem(std::string text, int idx) {
	Rect rect = GetItemRect(idx);
	contents->ClearRect(rect);

	contents->TextDraw(rect.x, rect.y, Font::ColorDefault, text);
}
