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

#ifndef jwm_shutdown_h
#define jwm_shutdown_h
#include <FL/Fl.H>
#include <libintl.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../include/flPanel.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>

class shutdown {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *shutdown_window;
  Fl_Button *shut;
private:
  inline void cb_shut_i(Fl_Button*, void*);
  static void cb_shut(Fl_Button*, void*);
public:
  Fl_Button *restart;
private:
  inline void cb_restart_i(Fl_Button*, void*);
  static void cb_restart(Fl_Button*, void*);
public:
  Fl_Button *log;
private:
  inline void cb_log_i(Fl_Button*, void*);
  static void cb_log(Fl_Button*, void*);
public:
  Fl_Button *sus;
private:
  inline void cb_sus_i(Fl_Button*, void*);
  static void cb_sus(Fl_Button*, void*);
public:
  Fl_Button *can;
private:
  inline void cb_can_i(Fl_Button*, void*);
  static void cb_can(Fl_Button*, void*);
public:
  void window_bg();
  void under_mouse(Fl_Window *o);
};
#endif
