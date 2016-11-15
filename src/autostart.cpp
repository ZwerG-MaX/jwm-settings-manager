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
#include <libintl.h>
#include "../include/autostart.hpp"
int desktopFileEdit(Fl_Browser* o){
	const char* line=o->text(o->value());
	if(line==NULL) return 1;
	std::string temp=line;
	std::string casa=linuxcommon::home_path();
	std::string desktopeditor=linuxcommon::term_out("which desktop-file-editor");
    if(desktopeditor.compare("")!=0){
		desktopeditor+=" ";
		desktopeditor+=temp;
		if(temp.find(casa)>temp.length()){
			std::string pkexec=linuxcommon::term_out("which pkexec");
			if(pkexec.compare("")==0) pkexec=linuxcommon::term_out("which gksudo");
			if(pkexec.compare("")==0) pkexec=linuxcommon::term_out("which gksu");
			if(pkexec.compare("")==0) pkexec=linuxcommon::term_out("which sudo");
			if(pkexec.compare("")!=0) desktopeditor= pkexec + " " +desktopeditor ;
		}
		int sys=system(desktopeditor.c_str());
		if(sys!=0){debug_out(desktopeditor+" did not work");}
		return sys;
	}
	else{debug_out("Desktop File editor was not found!");}
	return -1;
}

void add_program_to_autostart(Fl_Browser *o,std::string input) {
	o->clear();
	bool tryADD=addElementWithText("StartupCommand",input);
	if(!tryADD){errorOUT("ADDING  StartupCommand->"+input+" FAILED");return;}
	if(!linuxcommon::program_is_running(input)){linuxcommon::run_a_program_in_background(input);}
	if((loadTemp())&&(saveNoRestart())){
		load();
		populateFLBrowser(o,"StartupCommand");
		o->redraw();
	}
	else{errorOUT("Couldn't save the file correctly");}
}
void remove_program_from_autostart(Fl_Browser *o) {
	const char * item = o->text(o->value());
	if (item !=NULL){
		removeElement("StartupCommand",item);
		if(saveNoRestart()){
			o->clear();
			load();
			populateFLBrowser(o,"StartupCommand");
			o->redraw();
		}
		else{std::cerr<<"Couldn't save the file correctly"<<std::endl;}
	}
	else{std::cerr<<"Please click on an item to remove!"<<std::endl;}
}
