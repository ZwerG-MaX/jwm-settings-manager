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
#ifndef window_h
#define window_h
//std stuff
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
//My includes
#include "jwmrc.hpp"
#include "fltkfunctions.hpp"
//FLTK
#include <FL/Fl.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Output.H>
class JSM_Window : public FLTK_FUNCTIONS
{
	public:
///Void
	//a
		void active_color_loader(Fl_Button *o, unsigned int one_or_two);
		void add_option_to_group(Fl_Browser *options_available, Fl_Input* icon_value, Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Browser* browser);
		void add_thingie(Fl_Browser *groups_browser,std::string input,std::string Item);
		void add_class(Fl_Browser *groups_browser,std::string input);
		void add_prog(Fl_Browser *groups_browser,std::string input);
		void addGroup();
		void addGroupItem(unsigned int whichone, std::string subelement,std::string value);
	//b
		void border_color_loader(Fl_Widget *o, int Active1_Inactive2, int first_or_second);
		void border_modifier(Fl_Slider *o1, Fl_Value_Input *o2, int change_o1_or_o2);
		void border_modifier(Fl_Slider *o1, Fl_Value_Output *o2);
	//c
		void check_opts(std::string itemValue,Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Input* icon_value, Fl_Menu_Button* layer_chooser);
		void choose_button(std::string whichButton);
		void corner_load(Fl_Slider *o);
		void corner_change(Fl_Slider *o);
	//d
		void display(std::string filename, Fl_Widget *o);
	//f
		void font_color_loader(Fl_Widget *o, int Active1_Inactive2);
	//g
		void get_button(Fl_Widget*o, std::string whichElement,Fl_Widget* a_title_color1);
		void get_button_inactive(Fl_Widget*o, std::string whichElement,Fl_Button* inactive_color,Fl_Button* inactive_font_color);
	//i
		void inactive_color_loader(Fl_Button *o, int one_or_two);
	//o
		void opacity_loader(Fl_Slider *o, int Active1_Inactive2);
	//p
		void populate_groups(Fl_Browser *groups_browser,Fl_Browser *opt_browser,Fl_Browser *class_browser,Fl_Browser *name_browser);
		void populateMouseContext(Fl_Browser *o, std::string conext);
		void populateGTKThemes(Fl_Browser* o);
	//r
		void removeGroup(int hidethis);
		void removeGroupTHING(int hidethis, std::string value,std::string THING);
	//s
		void set_border_color(Fl_Widget *o, int Active1_Inactive2, int first_or_second);
		void set_font_color(Fl_Widget *o, int Active1_Inactive2);
		void set_one_title_color(Fl_Widget *o, int Active1_Inactive2, Fl_Widget* max_a_image, Fl_Widget* max_image, Fl_Widget* min_image, Fl_Widget* close_image);
		void set_one_title_color(Fl_Widget *o,  int Active1_Inactive2);
		void set_opacity(Fl_Slider *o, Fl_Value_Input *o2, int Active1_or_Inactive2);
		void set_two_title_colors(Fl_Widget *o, int Active1_Inactive2);
		void setThing(std::string thing,std::string mode);
		void setThings(std::string thing,std::string mode,int &distance);
	//t
		void title_bar_modifier(Fl_Slider *o1, Fl_Value_Output *o2);
		void title_bar_modifier(Fl_Slider *o1, Fl_Value_Input *o2, int change_o1_or_o2);
	//x
		void XminusG(Fl_Browser *groups_browser);
		void XplusG(Fl_Browser *groups_browser);
///Integer
		int getBorderHeight();
		int getBorderWidth();
		void getGroups(Fl_Browser *o);
		int getSnap();
		unsigned int activeBGColor(unsigned int one_or_two);
		unsigned int fontColor(int Active1_Inactive2);
		unsigned int set_title_color(Fl_Widget *o, int Active1_Inactive2,int First1_or_Second2);
///String
		std::string buttonPath();
		std::string XplusO(Fl_Browser *groups_browser);
///Boolean
		bool addContext(std::string text, std::string context, std::string button, std::string mask);
		bool deleteContext(std::string text, std::string context, std::string button, std::string mask);
		bool modifyContext(std::string old_text, std::string text, std::string context, std::string button, std::string old_button, std::string mask, std::string old_mask);
		bool secondColor(Fl_Widget *o);
		bool setSnap(int &distance);
		bool switchGTKTheme(Fl_Browser* o);
		bool Xminus(Fl_Browser *groups_browser, Fl_Browser *opt_browser, std::string THING);
		bool XminusO(Fl_Browser *groups_browser, Fl_Browser *opt_browser);
		bool XminusN(Fl_Browser *groups_browser,Fl_Browser *opt_browser);
		bool XminusC(Fl_Browser *groups_browser,Fl_Browser *opt_browser);
		bool Xplus(Fl_Browser *groups_browser);
		bool XplusN(Fl_Browser *groups_browser);
		bool XplusC(Fl_Browser *groups_browser);
//Vector
		std::vector<std::string> gtk_themefiles_vector();
};
#endif
