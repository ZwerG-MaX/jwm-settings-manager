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
#ifndef menu_hpp
#define menu_hpp
//std
#include <libintl.h>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
//mine
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
//FLTK
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
class JSM_Menu : public FLTK_FUNCTIONS
{
	public:
	//string
		std::string getLabel(std::string MENU);
		std::string getItemIcon(int menu, int itemline,std::string element);
		std::string getItemIcon(int menu, int item, int sub);
		std::string getItemIcon(std::string text2, std::string menu);
		std::string getItemLabel(int menu, int itemline, int sub);
		std::string getItemLabel(int menu, int itemline,std::string element);
		std::string getItemLabel(std::string text2, std::string menu);
		std::string getItemAttribute(int menu, int itemline,std::string element,std::string attrib);
		std::string getItemAttribute(std::string EXIT,std::string menu,std::string attrib);
//bool
		bool addRoot(std::string rootmenu);
		bool ConfigMenuItem(int menu,int item,Fl_Input* prog_label,Fl_Input* prog_icon,Fl_Input* prog_input,Fl_Check_Button* conf_button);
		bool ConfigSubMenuItem(int menu,int item,int sub,Fl_Input* prog_label,Fl_Input* prog_icon,Fl_Input* prog_input,Fl_Check_Button* conf_button);
		bool checkMenuItems(Fl_Browser* menuElement,std::string menu,Fl_Browser* menuElementText);
		bool checkMenuItems(Fl_Browser* menuElement,Fl_Browser* menuElementText);
//void
		void changeMenuInclude(std::string newInclude, std::string old, std::string MENU);
		void listMenus(Fl_Browser* o);
};
#endif
