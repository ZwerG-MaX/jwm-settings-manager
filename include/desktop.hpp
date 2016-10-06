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

#ifndef desktop_hpp
#define desktop_hpp
#include <FL/Fl.H>
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "jwmrc.h"
#include "ui.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Value_Input.H>
//void
void background(Fl_Box*o,std::string thisBG);
void background1(Fl_Box*o,std::string thisBG);
void background2(Fl_Box*o,std::string thisBG);
void bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Output *current_bg,Fl_Box *color_display1,Fl_Box *color_display2);
void bg_name(Fl_Output *o,std::string thisBG);
void num_desktop_wh_cb(std::string whichone, int value,Fl_Value_Input* num_desktop_w,Fl_Value_Input* num_desktop_h, Fl_Check_Button* check);
void one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg);
void setFMBackground(std::string type,std::string wallpaper);
void svgGradient(std::string color);
void two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg);
void useMultipleDesktops(Fl_Value_Input *num_desktop_w,Fl_Value_Input *num_desktop_h);

//bool
bool icons_on_desktop();
bool filemanagerRunning();
bool filemanagerRunning(std::string filemanagerToCheck);
bool multipleDesktops();
bool setBackground(std::string type,std::string result);
bool setIconsOnDesktop();
bool use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string thisBG);
bool isIconsOnDesktop();
//string
std::string getBackground();
std::string whichFileManagerRunning();
std::string whichFileManager();
std::string getFMBackground();
//vector
std::vector<std::string> ListFileManagers();
#endif
