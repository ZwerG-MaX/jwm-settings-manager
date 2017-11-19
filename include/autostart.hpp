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

#ifndef autostart_hpp
#define autostart_hpp
//std
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
//mine
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
//FLTK
#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
class JSM_Autostart : public FLTK_FUNCTIONS
{
	public:
		int desktopFileEdit(Fl_Browser* o);
		int desktopFileEdit(std::string line);
		void add_program_to_autostart(Fl_Browser *o,std::string input);
		void remove_program_from_autostart(Fl_Browser *o);
		void remove_program_from_xdg_autostart(Fl_Browser* o);
		//void removeAutostart(std::string item);
};
#endif
