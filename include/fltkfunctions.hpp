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
#include "jwmrc.h"
std::string choose_a_directory(std::string directory, std::string label);
std::string choose_a_directory_to_save(std::string directory, std::string label);
std::string choose_a_file();
std::string choose_a_file(std::string directory);
std::string choose_a_file(std::string directory,std::string pattern);
std::string choose_a_program();
std::string choose_an_icon();
std::string choose_an_icon(std::string directory);
std::string nativeFileDialog(std::string title,std::string path,std::string filters);
//char*
char* Get_Fl_Icon(const char** pIcon);
//double*
double* choose_a_color(int &c,Fl_Widget *o);
//void
void choose_a_program(Fl_Input *o);
void clearOutput(Fl_Output* o);
void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int wh);
void makeWidgetIcon(std::string icon_file,Fl_Widget * widget,int w,int h);
void populateBrowserWithTextFile(Fl_Browser *o, std::string filename);
void populateBrowserWithString(Fl_Browser *o, std::string STRING);
void startup(Fl_Window *o);
void startup(Fl_Window *o ,const char** windowIcon);
//bool
bool OutputIsEmpty(Fl_Output* o);
#endif
