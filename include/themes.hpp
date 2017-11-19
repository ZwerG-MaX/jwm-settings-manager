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
#ifndef themes_hpp
#define themes_hpp
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
#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
// void
class Theme : public FLTK_FUNCTIONS
{
	public:
		void change_theme(std::string whichTheme, bool overwrite);
		void save_theme(Fl_Browser *usr_theme);
		void theme_copier(std::string theme);
		void setButton(std::string filename,std::string element);
		void setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement);
		void setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement,std::string SUBsubelement);
		void modCurrentTheme(std::string filename);
		void updateTheme( Fl_Browser *o,
					Fl_Box * button,
					Fl_Box * button_icon,
					Fl_Box *tray,
					Fl_Box *activeW,
					Fl_Box *activeW2,
					Fl_Box *activeW_text,
					Fl_Box *inactiveW,
					Fl_Box *inactiveW2,
					Fl_Box *inactiveW_text,
					Fl_Box *active_min_button,
					Fl_Box *active_max_button,
					Fl_Box *active_close_button,
					Fl_Box *inactive_min_button,
					Fl_Box *inactive_max_button,
					Fl_Box *inactive_close_button,
					std::string filename,
					bool user);
//string
		std::string choose_directory(std::string whichChoice);
		std::string choose_file();
		std::string getTheme(std::string whichTheme);
		std::string sysThemeDir();
		std::string userThemeDir();
		std::string theme_cb(Fl_Browser* browser,bool systemTheme, Fl_Input* current_theme);
		std::string getButton(std::string element,std::string themefile);
//int
		int saveAs(std::string save_name);
		int populateANYThemes(Fl_Browser *o,std::string checkHERE,bool backone);
		int populateThemes(Fl_Browser *o);
		int populateUserThemes(Fl_Browser *o);
		int loadTheme(std::string themePath);
		int themeNewStyle(std::string themefile);
//bool
		bool checkForTheme(std::string theme);
		bool checkThemeVersion();
		bool oldThemesExist();
		bool themesExist();
};
#endif
