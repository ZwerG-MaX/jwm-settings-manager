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

#ifndef icons_hpp
#define icons_hpp
#include <FL/Fl.H>
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
//#include "ui.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Input.H>
//Boolean
class JSM_Icon : public FLTK_FUNCTIONS
{
	public:
//Bool
		bool edit_value(Fl_Browser* iconsBrowser,Fl_Input* dir_edit_input);
		bool populateIncludes(std::string themefile,int size_to_use);
		bool save_edit_value(Fl_Browser* iconsBrowser,Fl_Input* dir_edit_input);
		bool switchTheme(Fl_Browser* o,int size);
//Vector
		std::vector<std::string> list_icon_dirs_in_themefile(std::string themefile,int size_to_use);
		std::vector<std::string> icon_themefiles_vector();
//Void
		void populateIconThemes(Fl_Browser* o);
};
#endif
