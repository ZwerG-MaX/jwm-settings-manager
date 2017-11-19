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
#include "../include/ui.hpp"
//These functions simply call the UI

//panel
int JSM_UI::showPanel(){
	debug_out("Panel UI activated");
    PanelUI uiPanel;
    uiPanel.make_window()->show();
	return Fl::run();
}
//clock
int JSM_UI::showClock(){
	debug_out("Clock UI activated");
    PanelUI uiPanel;
    uiPanel.make_window()->show();
    uiPanel.config_clock_window()->show();
	return Fl::run();
}
//desktop
int JSM_UI::showDesktop(){
debug_out("Desktop UI activated");
    DesktopUI uiDesktop;
    uiDesktop.make_window()->show();
	return Fl::run();
}

//windows
int JSM_UI::showWindow(){
	debug_out("Window UI activated");
    WindowUI uiWindow;
    uiWindow.make_window()->show();
    return Fl::run();
}

//Autostart
int JSM_UI::showAutostart(){
	debug_out("Autostart UI activated");
    AutostartUI uiAutostart;
    uiAutostart.make_window()->show();
	return Fl::run();
}

//fonts
int JSM_UI::showFonts(){
	debug_out("Font UI activated");
    FontUI uiFonts;
    uiFonts.make_window()->show();
	return Fl::run();
}

//keyboard
int JSM_UI::showKeyboard(){
	debug_out("Keyboard UI activated");
    KeyboardUI uiKeyboard;
    uiKeyboard.make_window()->show();
	return Fl::run();
}

//Themes
int JSM_UI::showThemes(){
	debug_out("Themes UI activated");
    ThemesUI uiThemes;
    uiThemes.make_window()->show();
	return Fl::run();
}

//icons
int JSM_UI::showIcons(){
	debug_out("Icons UI activated");
    IconsUI uiIcons;
    //uiIcons.make_window()->xclass("jsm-icons");
    uiIcons.make_window()->show();
	return Fl::run();
}
//mouse
int JSM_UI::showMouse(){
	debug_out("Mouse UI activated");
	std::string progname="fltk-mouse";
	int retval=system(progname.c_str());
	if(retval!=0){
		progname="./"+progname;
		retval=system(progname.c_str());
		if(retval!=0){std::cerr<<"Couldn't run "<<progname<<std::endl;}
	}
	return retval;
}
//menu
int JSM_UI::showMenu(){
	debug_out("Menu UI activated");
    MenuUI Menu;
	std::string menu="";
    Menu.make_window(menu)->show();
	return Fl::run();
}
int JSM_UI::showMenu(std::string menu){
	debug_out("Menu UI activated");
    MenuUI Menu;
    Menu.make_window(menu)->show();
	return Fl::run();
}
//Shortcuts
int JSM_UI::showShortcuts(){
	std::string EDITOR="desktop-file-editor";
    if(!linuxcommon::test_exec(EDITOR)){
		EDITOR="torios-shortcut";
		if(!linuxcommon::test_exec(EDITOR)){EDITOR="lxshortcut";}
	}
	return linuxcommon::run_a_program(EDITOR);
}
//Popups
int JSM_UI::showPopus(){
	debug_out("Popus UI activated");
	PopupsUI Pop;
	Pop.make_window()->show();
	return Fl::run();	
}

