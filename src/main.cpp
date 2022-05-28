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

#include "player.h"
#include <cstdlib>

// This is needed on Windows
#ifdef USE_SDL
#  include <SDL.h>
#endif

#ifdef PSP
#  include <pspkernel.h>

		PSP_MODULE_INFO("EasyRPG Player", PSP_MODULE_USER, 0, 53);

 		PSP_HEAP_SIZE_KB(-1024); // leave 1 mb for thread stack space and such	
		PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int psp_exit_callback(int arg1, int arg2, void *common) {
	Player::exit_flag = true;
	return 0;
}

int psp_callback_thread(SceSize args, void *argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", psp_exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int psp_setup_callbacks(void) {
	int thid = sceKernelCreateThread("update_thread", psp_callback_thread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);
	return thid;
}
#endif

extern "C" int main(int argc, char* argv[]) {
#ifdef PSP
 	atexit(sceKernelExitGame);
 	psp_setup_callbacks();
#endif	

	Player::Init(argc, argv);
	Player::Run();

	return EXIT_SUCCESS;
}
