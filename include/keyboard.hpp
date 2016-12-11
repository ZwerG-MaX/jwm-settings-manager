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
#ifndef keyboard_hpp
#define keyboard_hpp
#include <FL/Fl.H>
#include <libintl.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include "jwmrc.h"
#include "fltkfunctions.hpp"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Output.H>

//void
void addKey(std::string key, std::string shortcut);
void addKey(std::string keyMod, std::string key, std::string shortcut);
void changemod(std::string mod,Fl_Output* Aout,Fl_Output* Bout);
void changemod(std::string mod,Fl_Output* Aout,Fl_Output* Bout,Fl_Output* Cout);
void configureKey(std::string keyShortcut, std::string newmod1, std::string newmod2, std::string newmod3, std::string newkey, std::string newaction);
void Choose_Action(Fl_Input* action_name);
void deleteKey(std::string keyShortcut);
void key_event(Fl_Input* o, Fl_Output* out, Fl_Output* modder);
void keyPopulate(Fl_Browser *o, std::string itemToGet);
void keyLayoutPopulate(Fl_Browser *o);
void keyModelPopulate(Fl_Browser *o);
void keyOptionPopulate(Fl_Browser *o);
void mod_cb(std::string mod, Fl_Output *o);
void mod2_cb(std::string mod, Fl_Output *o);
void remove_key(Fl_Browser* o);
void setLayout(Fl_Input *layoutput, Fl_Input *modeloutput, Fl_Input *optionoutput);
void someLayout(Fl_Input *layoutput, Fl_Input *modeloutput, Fl_Input *optionoutput, bool save);
void testLayout(Fl_Input *layoutput, Fl_Input *modeloutput, Fl_Input *optionoutput);
//string
std::string fixLayoutString(Fl_Browser *o);
std::string getAction(std::string keyShortcut);
std::string getKey(std::string keyShortcut);
std::string getLayout(Fl_Input *o,std::string whichOne);
std::string getMod(std::string keyShortcut);
std::string getMod1(std::string keyShortcut);
std::string getMod2(std::string keyShortcut);
std::string getMod3(std::string keyShortcut);
std::string getINPUT(Fl_Input *o);
std::string getOUTPUT(Fl_Output *o);
std::string grabbedKey();
std::string oldvalue(Fl_Output* old_action, Fl_Output* current_key,Fl_Output* current_mod1,Fl_Output* current_mod2,Fl_Output* current_mod3);
//bool
bool add_cb(Fl_Input *action_name, Fl_Output *key_output, Fl_Output *mod_output, Fl_Output *mod2_output, Fl_Output * mod3_output, Fl_Browser *o);
bool Configure(Fl_Browser *key_browser,
	Fl_Input *action_name1,
	Fl_Output *current_shortcut,
	Fl_Output *mod1_output,
	Fl_Output *mod2_output,
	Fl_Output *mod3_output,
	Fl_Output *old_value);
bool Configure_CB(Fl_Output* mod1_output, Fl_Output* mod2_output,Fl_Output* mod3_output, Fl_Input * keyshortcut,Fl_Input * action_name1,std::string CURRENT);
bool newpanel();
bool getKeys(Fl_Browser* o);
#endif
