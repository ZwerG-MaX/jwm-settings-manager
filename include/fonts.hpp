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
#ifndef fonts_hpp
#define fonts_hpp
#include <FL/Fl.H>
#include <libintl.h>
#include <FL/Fl_File_Chooser.H>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <FL/Fl_Color_Chooser.H>
#include "jwmrc.h"
#include "ui.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Output.H>
//integer
unsigned int getFontColor(std::string whichElement);
int get_font_size(std::string whichElement);
//string
std::string fontTest(std::string whichElement);
std::string getDefaultFONT();
std::string processFont(std::string font);
std::string processFontOPTS(std::string font,std::string currentOPTS);
//boolean
bool isFONT(std::string font);
bool newOne();
//void
void missingFont(std::string whichElement);
void font_browser_cb(Fl_Browser* font_browser,Fl_Output *font_name,Fl_Slider* font_size_slider);
void font_chooser_cb(Fl_Output *Widget,Fl_Value_Output *chooser_size,Fl_Output *font_name,std::string currentElement);
void font_color(Fl_Widget *o, std::string active);
void font_populate(Fl_Browser *o);
void get_font(std::string  element, Fl_Output *o);
void get_font_color(Fl_Widget *o, std::string whichStyle);
void get_window_font_color(Fl_Widget *o, int Active1_Inactive2);
void set_font_size(Fl_Value_Output *chooser_size,std::string currentElement);
void setFontName(std::string family, std::string currentElement);
void setSize(unsigned int &fontSize,std::string whichElement);
void setFontColor(const double* colors, std::string whichElement);
void window_font_color(Fl_Widget *o, int Active1_Inactive2);
#endif
