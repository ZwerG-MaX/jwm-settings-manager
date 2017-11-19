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
#ifndef fltkfunctions_hpp
#define fltkfunctions_hpp
#include <X11/xpm.h>
#include <FL/x.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Menu_Button.H>
#include "jwmrc.hpp"
class FLTK_FUNCTIONS : public JWMRC
{
	public :

	//string
		std::string choose_a_directory(std::string directory, std::string label);
		std::string choose_a_directory_to_save(std::string directory, std::string label);
		std::string choose_a_file();
		std::string choose_a_file(std::string directory);
		std::string choose_a_file(std::string directory,std::string pattern);
		std::string choose_a_program();
		std::string choose_an_icon();
		std::string choose_an_icon(std::string directory);
		std::string nativeFileDialog(std::string title,std::string path,std::string filters);
		std::string widgetColor(Fl_Widget* o);

	///char*
		char* Get_Fl_Icon(const char** pIcon);

	///double*
		double* choose_a_color(int &c,Fl_Widget *o);

	///void
		//c
		void choose_a_program(Fl_Input *o);
		void clearOutput(Fl_Output* o);
		void color_two(Fl_Widget * o, std::string whichElement,std::string subelement);
		//g
		void getDecorations(Fl_Output *o,std::string element);
		//m
		void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int wh);
		void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int w,int h);
		//o
		void one_color(Fl_Widget *o, std::string whichElement);
		void one_color_active(Fl_Widget *o, std::string whichElement);
		void one_color_Font(Fl_Widget *o, std::string whichElement);
		void one_color_Font_active(Fl_Widget *o, std::string whichElement);
		void opacity(Fl_Value_Input *o, Fl_Slider *slider, std::string whichElement);
		void outline_color(Fl_Widget *o, std::string whichElement);
		void outline_two_color(Fl_Widget *a, Fl_Widget *b, std::string whichElement);
		void outline1(Fl_Widget *a, std::string element);
		void outline2(Fl_Widget *a, Fl_Output *b,std::string element);
		//p
		void populateBrowserWithTextFile(Fl_Browser *o, std::string filename);
		void populateBrowserWithString(Fl_Browser *o, std::string STRING);
		void populateBrowserWithStringVector(Fl_Browser *o, std::vector<std::string> STRING_VEC);
		//s
		void searchBrowser(Fl_Input* input,Fl_Browser *browser);
		void searchBrowser(std::string term,Fl_Browser *browser);
		void setDecorations(Fl_Output *o,std::string element,std::string value);
		void startup(Fl_Window *o);
		void startup(Fl_Window *o ,const char** windowIcon);
		//t
		void two_colors(Fl_Widget *a, Fl_Widget *b, std::string whichElement,std::string subelement);

	///bool
		bool InputIsEmpty(Fl_Input* o);
		bool OutputIsEmpty(Fl_Output* o);
};
#endif

