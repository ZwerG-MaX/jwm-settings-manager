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
#include "../include/menu.hpp"
//String////////////////////////////////////////////////////////////////
std::string getLabel(std::string MENU){
	debug_out("std::string getLabel(std::string "+MENU+")");
	if(MENU.compare("")==0){
		debug_out("Sent in something empty");
		return "";
	}
	std::string thisMenu = getMenuAttribute(MENU,"label");
	return thisMenu;
}
std::string getItemIcon(int menu, int itemline,std::string element){
	debug_out("std::string getItemIcon(int menu, int itemline,std::string "+element+")");
	return getMenuAttribute(menu,itemline,element,"icon");
}
std::string getItemIcon(std::string text2, std::string menu){
	debug_out("std::string getItemIcon(std::string "+text2+",std::string "+menu+")");
	return getElementAttributeFromElementWithAttributeAndValueAndText("RootMenu","onroot",menu,"Program","icon",text2);
}
std::string getItemLabel(int menu, int itemline,std::string element){
	debug_out("std::string getItemLabel(int menu, int itemline,std::string "+element+")");
	return getMenuAttribute(menu,itemline,element,"label");
}
std::string getItemLabel(std::string text2, std::string menu){
	debug_out("std::string getItemLabel(std::string "+text2+", std::string "+menu+")");
	return getElementAttributeFromElementWithAttributeAndValueAndText("RootMenu","onroot",menu,"Program","label",text2);
}
std::string getItemAttribute(int menu, int itemline,std::string element,std::string attrib){
	debug_out("std::string getItemAttribute(int menu, int itemline,std::string "+element+",std::string "+attrib+")");
	return getMenuAttribute(menu,itemline,element,attrib);
}
std::string getItemAttribute(std::string EXIT,std::string menu,std::string attrib){
	debug_out("std::string getItemAttribute(std::string "+EXIT+",std::string "+menu+",std::string "+attrib+")");
	return getElementAttributeFromElementWithAttributeAndValue("RootMenu","onroot",menu,EXIT,attrib);
}
//  debug_out("");

//if(!checkFlBrowserItem(root_menu)){return;}
//Boolean///////////////////////////////////////////////////////////////
bool addRoot(std::string rootmenu){return addElementWithAttribute("RootMenu","onroot",rootmenu);}
bool checkMenuItems(Fl_Browser* menuElement,Fl_Browser* menuElementText){return checkMenuItems(menuElement,"test",menuElementText);}
bool checkMenuItems(Fl_Browser* menuElement,std::string menu,Fl_Browser* menuElementText){
	if(!checkFlBrowserItem(menuElement)){return false;}
	if(!checkFlBrowserItem(menuElementText)){return false;}
	if(menu.compare("")==0){return false;}
	return true;
}
bool ConfigMenuItem(int menu,int item,Fl_Input* prog_label,Fl_Input* prog_icon,Fl_Input* prog_input,Fl_Check_Button* conf_button){
	debug_out("bool ConfigMenuItem(int menu,int item,Fl_Input* prog_label,Fl_Input* prog_icon,Fl_Input* prog_input,Fl_Check_Button* conf_button)");
	const char* lbl=NULL;
	if(prog_label!=NULL)lbl=prog_label->value();
	const char* icn=NULL;
	if(prog_icon!=NULL)icn=prog_icon->value();
	const char* prog=NULL;
	if(prog_input!=NULL)prog=prog_input->value();
	bool retval = true;
	if(lbl!=NULL){if(!editMenuItem(menu,item,"label",lbl)){retval=false;}}
	if(icn!=NULL){if(!editMenuItem(menu,item,"icon",icn)){retval=false;}}
	if(prog!=NULL){if(!editMenuItem(menu,item,prog)){retval=false;}}
	//TODO toggle button issue...
	return retval;
}
bool ConfigMenuItem(Fl_Browser* menuElement,
					Fl_Browser* menuElementText,
					Fl_Input* prog_label,
					Fl_Input* prog_icon,
					Fl_Input* prog_input,
					Fl_Check_Button* conf_button){
	debug_out("bool ConfigMenuItem(Fl_Browser* menuElement,Fl_Browser* menuElementText,Fl_Input* prog_label,Fl_Input* prog_icon,Fl_Input* prog_input,Fl_Check_Button* conf_button)");
	if(!checkFlBrowserItem(menuElement)){return false;}
	if(!checkFlBrowserItem(menuElementText)){return false;}
	const char* menuele=menuElement->text(menuElement->value());
	const char* menueletext=menuElementText->text(menuElementText->value());
	const char* lbl=prog_label->value();
	const char* icn=prog_icon->value();
	const char* prog=prog_input->value();
	if((lbl==NULL)||(icn==NULL)||(prog==NULL)){
		debug_out("Fl_Input with NULL value");
		return false;
	}
	
	return false;
}
//Void//////////////////////////////////////////////////////////////////
void changeMenuInclude(std::string newInclude, std::string old, std::string MENU){
	debug_out("void changeMenuInclude(std::string "+newInclude+", std::string "+old+", std::string "+MENU+")");
	if((newInclude.compare("")==0)||(old.compare("")==0)||(MENU.compare("")==0)){
		debug_out("User sent in an empty value");
		return;
	}
}
void listMenus(Fl_Browser* list_browser){
	debug_out("void listMenus(Fl_Browser* o)");
	list_browser->clear();
    std::string tempString,convertString,tempString2,convertString2,attributeValue,test1,test2;
    if(newStyle() == -1){
        for (int i = 0; i<=9;i++){
            convertString = convert(i);
            if(!isRootMenu(convertString)){
                debug_out("Adding: "+convertString);
                list_browser->add(convertString.c_str());
            }
        }
    }
    else{
        debug_out("New Style Menu");
        for(char i = '0';i<='z';i++){
            convertString=i;
            if((i < ':')||(i > '`')){
                if(!isRootMenu(convertString)){
                    debug_out("Adding: "+convertString);
                    list_browser->add(convertString.c_str());
                }
            }
        }
    }
    list_browser->redraw();
}

