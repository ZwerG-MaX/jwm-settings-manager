/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using tinyxml2 and FLTK
 *
 *         Copyright (C) 2014  Israel <israel@torios.org>
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
 * This has been developed by Israel<israel@torios.org>
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef jwm_themes_h
#define jwm_themes_h
#include <FL/Fl.H>
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../include/Config.h"
#include "../include/flThemes.h"
#include "../include/ui.h"
#include <FL/fl_ask.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

class ThemesUI {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *themes_window;
private:
  inline void cb_Main_i(Fl_Button*, void*);
  static void cb_Main(Fl_Button*, void*);
  inline void cb_Gnome_i(Fl_Button*, void*);
  static void cb_Gnome(Fl_Button*, void*);
  inline void cb_Gnome1_i(Fl_Button*, void*);
  static void cb_Gnome1(Fl_Button*, void*);
  inline void cb_Bassem_i(Fl_Button*, void*);
  static void cb_Bassem(Fl_Button*, void*);
  inline void cb_Ambiance_i(Fl_Button*, void*);
  static void cb_Ambiance(Fl_Button*, void*);
public:
  Fl_Button *defaults_button;
private:
  inline void cb_defaults_button_i(Fl_Button*, void*);
  static void cb_defaults_button(Fl_Button*, void*);
public:
  Fl_Button *save_button;
private:
  inline void cb_save_button_i(Fl_Button*, void*);
  static void cb_save_button(Fl_Button*, void*);
public:
  Fl_Button *open_button;
private:
  inline void cb_open_button_i(Fl_Button*, void*);
  static void cb_open_button(Fl_Button*, void*);
public:
  Fl_Input *file_input;
private:
  inline void cb_Choose_i(Fl_Button*, void*);
  static void cb_Choose(Fl_Button*, void*);
public:
  Fl_Output *save_dir;
  void display(Fl_Widget *o, const char* whichTheme);
};
#endif
