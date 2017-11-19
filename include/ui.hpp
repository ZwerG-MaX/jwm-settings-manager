/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using pugixml and FLTK
 *
 *         Copyright (C) 2016  Israel <israeldahl@gmail.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
//FLTK stuff
#include "../fltk/jwm-autostart.h"
#include "../fltk/jwm-window.h"
//#include "../fltk/jwm-settings.h"
#include "../fltk/jwm-keyboard.h"
#include "../fltk/jwm-fonts.h"
#include "../fltk/jwm-themes.h"
#include "../fltk/jwm-desktop.h"
#include "../fltk/jwm-icons.h"
#include "../fltk/jwm-panel.h"
#include "../fltk/jwm-menu.h"
#include "../fltk/jwm-popups.h"
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
class JSM_UI : public FLTK_FUNCTIONS
{
	public:
		int showPanel();
		int showClock();
		int showDesktop();
		int showThemes();
		int showWindow();
		int showIcons();
		int showFonts();
		int showKeyboard();
		int showMouse();
		int showMenu();
		int showMenu(std::string menu);
		int showAutostart();
		int showShortcuts();
		int showPopus();
};
#endif
