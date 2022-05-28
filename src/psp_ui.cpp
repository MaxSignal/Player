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

#ifdef PSPUI

// Headers
#include "psp_ui.h"
#include "color.h"
#include "graphics.h"
#include "keys.h"
#include "output.h"
#include "player.h"
#include "bitmap.h"
#include "audio.h"

#include <pspkernel.h>
#include <pspctrl.h>
#include <glib2d.h>

static g2dTexture* main_texture;
static struct timeval time_start;
static SceCtrlData pad;

PspUi::PspUi(int width, int height) :
	BaseUi() {
	gettimeofday(&time_start, NULL);

	// setup joystick
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	// init hardware and tex
	g2dInit();
	main_texture = g2dTexCreate(width, height);

	current_display_mode.width = width;
	current_display_mode.height = height;
	current_display_mode.bpp = 32;

	// setup pixman
	const DynamicFormat format(32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000, PF::NoAlpha);
	Bitmap::SetFormat(Bitmap::ChooseFormat(format));
	main_surface = Bitmap::Create(width, height, true, 32);
}

PspUi::~PspUi() {
	g2dTexFree(&main_texture);
	g2dTerm();
}

void PspUi::Sleep(uint32_t time) {
	const uint32_t max_delay = 0xffffffffUL / 1000;
	if(time > max_delay)
		time = max_delay;
	sceKernelDelayThreadCB(time * 1000);
}

uint32_t PspUi::GetTicks() const {
	struct timeval now;
	gettimeofday(&now, NULL);
	uint32_t ticks=(now.tv_sec-time_start.tv_sec)*1000+(now.tv_usec-time_start.tv_usec)/1000;

	return ticks;
}
void PspUi::BeginDisplayModeChange() {
	// no-op
}

void PspUi::EndDisplayModeChange() {
	// no-op
}

void PspUi::Resize(long /*width*/, long /*height*/) {
	// no-op
}

void PspUi::ToggleFullscreen() {
	// no-op
}

void PspUi::ToggleZoom() {
	// no-op
}

bool PspUi::IsFullscreen() {
	return true;
}

void PspUi::ProcessEvents() {
	sceCtrlPeekBufferPositive(&pad, 1);

	keys[Input::Keys::JOY_0] = pad.Buttons & PSP_CTRL_TRIANGLE;
	keys[Input::Keys::JOY_1] = pad.Buttons & PSP_CTRL_CIRCLE;
	keys[Input::Keys::JOY_2] = pad.Buttons & PSP_CTRL_CROSS;
	keys[Input::Keys::JOY_3] = pad.Buttons & PSP_CTRL_SQUARE;
	keys[Input::Keys::JOY_4] = pad.Buttons & PSP_CTRL_LTRIGGER;
	keys[Input::Keys::JOY_5] = pad.Buttons & PSP_CTRL_RTRIGGER;
	keys[Input::Keys::JOY_6] = pad.Buttons & PSP_CTRL_DOWN;
	keys[Input::Keys::JOY_7] = pad.Buttons & PSP_CTRL_LEFT;
	keys[Input::Keys::JOY_8] = pad.Buttons & PSP_CTRL_UP;
	keys[Input::Keys::JOY_9] = pad.Buttons & PSP_CTRL_RIGHT;
	keys[Input::Keys::JOY_10] = pad.Buttons & PSP_CTRL_SELECT;
	keys[Input::Keys::JOY_11] = pad.Buttons & PSP_CTRL_START;
	keys[Input::Keys::JOY_12] = pad.Buttons & PSP_CTRL_HOME;
	keys[Input::Keys::JOY_13] = pad.Buttons & PSP_CTRL_HOLD;

 	keys[Input::Keys::JOY_AXIS_X_LEFT] = (pad.Lx < 55);
 	keys[Input::Keys::JOY_AXIS_X_RIGHT] = (pad.Lx > 200);
 	keys[Input::Keys::JOY_AXIS_Y_DOWN] = (pad.Ly > 200);
 	keys[Input::Keys::JOY_AXIS_Y_UP] = (pad.Ly < 55);
}

void PspUi::UpdateDisplay() {
	g2dClear(BLACK);

	g2dBeginRects(main_texture);

	// center output
	g2dSetCoordMode(G2D_CENTER);
	g2dSetCoordXY(G2D_SCR_W/2, G2D_SCR_H/2);

#ifdef PSPUI_SCALE
 	g2dSetScaleWH(main_surface->GetWidth()+32, main_surface->GetHeight()+32); // maximise
#else
 	// disable bilinear filter, only useful while scaling
 	g2dSetTexLinear(false);
#endif

	// copy
	for (int y = 0; y < main_surface->GetHeight(); y++) {
		memcpy(main_texture->data + y * main_texture->tw,
			   (char *)main_surface->pixels() + y * main_surface->pitch(),
			   main_surface->GetWidth() * 4);
	}
	g2dAdd();
	g2dEnd();

	// display on screen
	g2dFlip((g2dFlip_Mode) 0);
}

void PspUi::BeginScreenCapture() {
	CleanDisplay();
}

BitmapRef PspUi::EndScreenCapture() {
	return Bitmap::Create(*main_surface, main_surface->GetRect());
}

void PspUi::SetTitle(const std::string& /* title */) {
	// no-op
}

bool PspUi::ShowCursor(bool /* flag */) {
	return true;
}

#endif