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
#include "../include/panel.hpp"
//String////////////////////////////////////////////////////////////////
std::string JSM_Panel::getAutoHide(int num){
	debug_out("std::string getAutoHide(int num)");
	std::string retval;
	if(newStyle()>=0){
		if(num==0){retval="off";}
		else{
			std::string layout=getElementAttribute(currentPanel(),"Tray","layout");
			std::string halign=getElementAttribute(currentPanel(),"Tray","halign");
			std::string valign=getElementAttribute(currentPanel(),"Tray","valign");
			if(layout.compare("vertical")==0){
				if((halign.compare("right")==0)||(halign.compare("left")==0)){
					retval=halign;
				}
				else{retval="off";}
			}
			else{
				if((valign.compare("top")==0)||(valign.compare("bottom")==0)){
					retval=valign;
				}
				else{retval="off";}
			}
		}
		
	}
	else{
		if(num==0){retval="false";}
		else{retval="true";}
	}
	return retval;
}
std::string JSM_Panel::getClock(std::string timeString){
	debug_out("std::string getClock(std::string timeString)");
	time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,timeString.c_str(),timeinfo);
    std::string stringBuffer = buffer;
    return stringBuffer;
}
std::string JSM_Panel::getClock(){return getElementAttribute(currentPanel(),"Tray","Clock","format");}
std::string JSM_Panel::getClockText(int position){return getItemText(getTraySubElement(position));}
std::string JSM_Panel::getImageMenu(std::string item){return getAttribute(getMenu(item),"icon");}
std::string JSM_Panel::getLabelMenu(std::string item){
	debug_out("std::string getLabelMenu(std::string "+item+")");
	std::string tmp= getAttribute(getMenu(item),"label");
	debug_out("Label="+tmp);
	return tmp;
}
std::string JSM_Panel::getButtonTooltip(std::string item){
	debug_out("std::string getButtonTooltip(std::string "+item+")");
	std::string tmp= getAttribute(getMenu(item),"tooltip");
	if(tmp.compare("")==0){tmp=getLabelMenu(item);}
	debug_out("Label="+tmp);
	return tmp;
}
std::string JSM_Panel::getItemVal(int position, std::string attribute){
	debug_out("std::string getItemVal(int position, std::string "+attribute+")");
	return getAttribute(getTraySubElement(position),attribute);
}
std::string JSM_Panel::getTrayStyleattribute(std::string item){
	std::string value=getAttribute(parseNodes(1,"TrayStyle"),item);
	std::string defaultval;
	if(item.compare("list")==0)defaultval="desktop";
	if(item.compare("group")==0)defaultval="false";
	if(item.compare("decorations")==0)defaultval="flat";
	if(value.compare("")==0){value=defaultval;}
	return value;
}
std::string JSM_Panel::Menu_Label(int num){
	debug_out("std::string Menu_Label(int num)");
	changePanel(num);
	currentPanel();
	std::string numero=convert(num);
	std::string LABEL = gettext("Panel");
	LABEL +=" ";
	LABEL +=numero;
	return LABEL;
}
//double////////////////////////////////////////////////////////////////
double JSM_Panel::getItemH(int position){return getItemWH(position,"height");}
double JSM_Panel::getItemW(int position){return getItemWH(position,"width");}
double JSM_Panel::getSpacing(int position){return getItemWH(position,"spacing");}
double JSM_Panel::getTaskW(int position){return getItemWH(position,"maxwidth");}
double JSM_Panel::getItemWH(int position, std::string attribute){
	debug_out("std::string getItemWH(int position, std::string "+attribute+")");
	std::string tmp=getItemVal(position, attribute);
	double val=linuxcommon::convert_string_to_double(tmp);
	return val;
}
//Integer///////////////////////////////////////////////////////////////
int JSM_Panel::getBorder(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","border").c_str());}
int JSM_Panel::getCoordinate(std::string xy){return linuxcommon::convert_string_to_number(getElementAttribute("Tray",xy).c_str());}
int JSM_Panel::getHeight(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","height").c_str());}
int JSM_Panel::getWidth(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","width").c_str());}
int JSM_Panel::taskLabeled(int position){
  std::string tmp=getItemVal(position,"labeled");
  if(tmp.compare("")==0){return 1;}
  if(TRUEorFALSE(tmp)){return 1;}
  return 0;
}
//Boolean///////////////////////////////////////////////////////////////
bool JSM_Panel::addApp(std::string element){return addSubElement(currentPanel(),"Tray",element);}
bool JSM_Panel::addApp(std::string element, std::string attribute,std::string value,std::string text){return addSubElementWithTextandAttribute(currentPanel(),"Tray",element,text,attribute,value);}
bool JSM_Panel::addApp(std::string element,std::string attribute,std::string value){return addSubElementWithAttribute(currentPanel(),"Tray",element,attribute,value);}
bool JSM_Panel::addButton(std::string icon,std::string execLine,std::string popup,int border){
	if(execLine.compare("")==0){errorOUT("Exec line is empty");return false;}
	if(execLine.find("exec:")>execLine.length()){execLine="exec:"+execLine;}
	debug_out("void addButton(std::string "+icon+",std::string "+execLine+",std::string "+popup+",int border)");
	if(!addSubElementWithText(currentPanel(),"Tray","TrayButton",execLine)){
		errorOUT("Could not add the TrayButton");
		return false;
	}
	else{loadTemp();}
	if(setLastTrayButtonAttribute("icon",icon)){
		if(setLastTrayButtonAttribute("popup",popup)){
			if(setLastTrayButtonAttribute("border",linuxcommon::convert_num_to_string(border))){
				return addButtonToLastTray("mask","123",execLine);
			}
			debug_out("addButton failed to set the border");
			return false;
		}
		debug_out("addButton failed to set the popup");
		return false;
	}
	debug_out("addButton failed to set the icon attribute");
	return false;
}
bool JSM_Panel::add_new_shortcut(Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Input* tooltip,Fl_Box* icon_name,int border){
	debug_out("void add_new_shortcut(Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Input* tooltip)");
	const char* ICON= icon_name->label();
	std::string icon;
	if(ICON!=NULL){icon=ICON;}
	std::string execLine = "exec:";
	const char* APPCOMMAND= app_command->value();
	if(APPCOMMAND!=NULL){execLine +=APPCOMMAND;}
	else{return false;}
	if ((icon.compare("")!=0)&&(execLine.compare("exec:")!=0)){
		const char* POPUP = tooltip->value();
		std::string popup;
		if(POPUP!=NULL){popup=POPUP;}
		if(newStyle()==-1){
			if(addShortcut(icon,execLine,popup, border)){
				shortcut_browser->clear();
				getShortcuts(shortcut_browser);
				shortcut_browser->redraw();
				return true;
			}
			return false;
		}
		else{
			if(addButton(icon,execLine,popup, border)){
				shortcut_browser->clear();
				getShortcuts(shortcut_browser);
				shortcut_browser->redraw();
				return true;
			}
			return false;
		}
	}
	return false;
}
bool JSM_Panel::addShortcut(std::string icon,std::string execLine,std::string popup,int border){
	if(execLine.find("exec:")>execLine.length()){execLine="exec:"+execLine;}
	debug_out("void addShortcut(std::string "+icon+",std::string "+execLine+",std::string "+popup+",int border)");
	setAttribute(addNode(currentPanel(),"Tray", "TrayButton"),"icon",icon);
	setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"popup",popup);
	setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"border",linuxcommon::convert_num_to_string(border));
	return setNodeText(getLastSubNode(currentPanel(),"Tray", "TrayButton"),execLine);
}
bool JSM_Panel::style_gone(){
	debug_out("bool style_gone()");
	if(newStyle() ==1){return true;}
	return false;
}
bool JSM_Panel::setClockText(int position,std::string text, std::string mask){
	if(JWMversion()<230){return setItemText(position,text);}
	return setNodeButtonTextByMask(getTraySubElement(position),text,mask);
}
bool JSM_Panel::setItemH(int value,int position){return setItemWH("height",value,position);}
bool JSM_Panel::setItemW(int value,int position){return setItemWH("width",value,position);}
bool JSM_Panel::setTaskW(int value, int position){return setItemWH("maxwidth",value,position);}
bool JSM_Panel::setItemWH(std::string attribute, int value,int position){
	debug_out("bool setItemWH(std::string "+attribute+", int value,int position)");
	std::string val=linuxcommon::convert_num_to_string(value);
	return setItemWH(attribute,val,position);
}
bool JSM_Panel::setItemWH(std::string attribute, std::string value,int position){
	debug_out("bool setItemWH(std::string "+attribute+", std::string "+value+",int position)");
	return setAttribute(getTraySubElement(position),attribute,value);
}
bool JSM_Panel::setItemText(int position, std::string text){
	debug_out("bool setItemText(int position, std::string "+text+")");
	return setNodeText(getTraySubElement(position),text);
}
bool JSM_Panel::TRUEorFALSE(std::string boolean){
	if(boolean.compare("true")==0){return true;}
	return false;
}
bool JSM_Panel::toomanypanels(){
	debug_out("bool toomanypanels()");
	if(numPanels()>=4){return true;}
	return false;
}
//Void//////////////////////////////////////////////////////////////////
//////A
void JSM_Panel::addBattery(){
	checkDock();
	std::string batt="torios-battery";
	if(!isExec(batt)){
		batt="xfce4-power-manager";
		if(!isExec(batt)){
			errorOUT("No known battery indicator found");
			return;
		}
	}
	addIndicator(batt);
}
void JSM_Panel::addClock(){
	debug_out("");
	std::string defaultFormat="%a, %e %b %l:%M %p";
	std::string defaultclock=linuxcommon::term_out("which torios-calendar");
	if(defaultclock.compare("")==0){defaultclock=linuxcommon::term_out("which xclock");}
	//TODO more??
	if(defaultclock.compare("")==0){
		debug_out("FAILED to find clock program... using 'showdesktop' instead ");
		defaultclock="showdesktop";
	}
	else{defaultclock="exec:"+defaultclock;}
	int curr_panel=currentPanel();
	setAttribute(addNode(curr_panel,"Tray", "Clock"),"format",defaultFormat);
	if(JWMversion()>230){
		addSubNodewithAttributeAndText(getLastSubNode(curr_panel,"Tray", "Clock"),"Button","mask","123",defaultclock);
	}
	else{
		setNodeText(getLastSubNode(curr_panel,"Tray", "Clock"),defaultclock);
	}
}
void JSM_Panel::addIndicator(std::string indicator){
	if(!linuxcommon::look_for_string_in_vector(AnythingVector("StartupCommand"),indicator)){
		bool isauto=false;
		std::vector<std::string> myVec=XDGautostart();
		std::string currentInclude;
		for(std::vector<std::string>::iterator it = myVec.begin();it!=myVec.end();++it){
			currentInclude=*it;
			currentInclude=linuxcommon::grep(indicator,currentInclude);
			if(currentInclude.compare("")!=0){isauto=true;}
		}
		if(!isauto){
			bool tryADD=addElementWithText("StartupCommand",indicator);
			if(!tryADD){errorOUT("ADDING  StartupCommand->"+indicator+" FAILED");return;}
			if(!linuxcommon::program_is_running(indicator)){linuxcommon::run_a_program_in_background(indicator);}
		}
	}
}
void JSM_Panel::addNetworkMonitor(){
	checkDock();
	std::string nm="nm-applet";
	if(!isExec(nm)){
		nm="wicd-gtk";
		if(linuxcommon::program_is_running(nm)){return;}
		if(isExec(nm)) nm+=" -t";
	}
	else{if(linuxcommon::program_is_running(nm)){return;}}
	if(!isExec(nm)){
		debug_out("No known network applet found");
		return;
	}
	addIndicator(nm);
}
void JSM_Panel::add_new_menu(){
	debug_out("void add_new_menu()");
	//TODO... launcher window for a 'root' rather than exec
	//showMenu();
}
void JSM_Panel::addPager(){
	debug_out("void addPager()");
	if(!setAttribute(addNode(currentPanel(),"Tray", "Pager"),"labeled","true")){
		debug_out("Couldn't add the Pager");
	}
}
void JSM_Panel::addPanel(){
	debug_out("void addPanel()");
	std::string position=getSmartLayout();
	debug_out("Using position: "+position);
	std::string valign = getSmartVert(position);
	std::string halign = getSmartHoriz(position);
	debug_out("using valign:"+valign+"\nhalign:"+halign);
	int vert = whichAlign(valign);
	int horiz = whichAlign(halign);
	int panels=numPanels();
	panels+=1;
	std::string numPanels=linuxcommon::convert_num_to_string(panels);
	if(!setJSMItem("panel", numPanels)){
		errorOUT("Could not set new panel as the current");
	}
	//Now we will start guessing the width and height to use
    std::string w,h;
    int screenHeight = Fl::h();
    //a nice starter for a vertical panel is screenheight/2.5
    std::string guessHeight = linuxcommon::convert_num_to_string(screenHeight /2.5);
    if(vert==1 && horiz==3){
        //if it is a top or bottom panel
        //0 means the FULL width
        w = "0";
        h = "34";
    }
    else if(horiz==2 && vert==3){
        //if it is a left or right panel
        //make it 34 wide and screenHeight /2.5 tall
        w = "34";
        h = guessHeight;
    }
    else{
        //if it is something else... just make it visible?
        w = "34";
        h = "34";
    }//
    if(!addElementAndSub("Tray","Separator")){errorOUT("FAILED to create Panel with separator");}
	if(!setAttribute(parseNodes(panels,"Tray"),"width",w)){errorOUT("FAILED to set width");}
	if(!setAttribute(parseNodes(panels,"Tray"),"height",h)){errorOUT("FAILED to set height");}
    if(!setAttribute(parseNodes(panels,"Tray"),"valign",valign)){errorOUT("FAILED to set valign");}
    if(!setAttribute(parseNodes(panels,"Tray"),"halign",halign)){errorOUT("FAILED to set halign");}
    if(!setAttribute(parseNodes(panels,"Tray"),"border","false")){errorOUT("FAILED to set border");}
}
void JSM_Panel::addSpacer(double w, double h, int position){
	std::string width=linuxcommon::convert_num_to_string(w);
	std::string height=linuxcommon::convert_num_to_string(h);
	debug_out("void addSpacer(double "+width+", double "+height+")");
	addSubElement(currentPanel(),"Tray","Spacer");
	if(w>0.0){
		setAttribute(getTraySubElement(position),"width",width);
		//add width
	}
	if(h>0.0){
		//add height
		setAttribute(getTraySubElement(position),"height",height);
	}
}
void JSM_Panel::addTaskList(){
	debug_out("void addTaskList()");
	if(!setAttribute(addNode(currentPanel(),"Tray", "TaskList"),"maxwidth","256")){debug_out("Could not add the TaskList");}	
}
void JSM_Panel::addVolume(){
	checkDock();
	std::string vol="torios-volume";
	if(!isExec(vol)){
		vol="volumeicon";
		if(!isExec(vol)){
			errorOUT("No known volume icon found...");
			return;
		}
	}
	addIndicator(vol);
}
void JSM_Panel::app_command_CB(Fl_Input* o, Fl_Input* app_command){
	debug_out("void app_command_CB(Fl_Input* o, Fl_Input* app_command)");
	const char* result = o->value();
	if(result!=NULL){
		std::string exec = result;
		unsigned found = exec.rfind("//");
		exec=exec.erase(0,found+1);
		app_command->value(exec.c_str());
	}
}
void JSM_Panel::autohide(Fl_Check_Button* autohide_check,Fl_Widget* choose_autohide){
	debug_out("void autohide(Fl_Check_Button* autohide_check,Fl_Widget* choose_autohide)");
	std::string a = getElementAttribute("Tray","autohide");
	autohide_check->value(0);
	if(newStyle()==-1){
		choose_autohide->hide();
		if(a=="true"){autohide_check->value(1);}
	}
	else{
		if((a.compare("")!=0)&&(a.compare("off")!=0)){autohide_check->value(1);}
	}		
}
void JSM_Panel::autohide_position(std::string where,Fl_Output *autohide_pos){
	debug_out("void autohide_position(std::string "+where+")");
	if(where.compare("")==0){return;}
	autohide_pos->value(where.c_str());
	autohide_pos->redraw();
	setElementAttribute(currentPanel(),"Tray","autohide",where);
}
//////C
void JSM_Panel::changeClock(std::string style){
	debug_out("void changeClock(std::string "+style+")");
	std::string DAY=gettext("Day");
	std::string TWELVE=gettext("12");
	std::string TWENTYFOUR=gettext("24");
	std::string YEAR=gettext("Year");
	std::string format;
	if (style.compare(DAY)==0){format="%a, %e %b %l:%M %p";}
    else if(style.compare(TWELVE)==0){format="%l:%M %p";}
    else if(style.compare(TWENTYFOUR)==0){format="%H:%M";}
    else if(style.compare(YEAR)==0){format="%F %H:%M";}
    else{format=style;}
    setElementAttribute(currentPanel(),"Tray","Clock","format",format);
}
void JSM_Panel::change_layer(std::string position,Fl_Output * layer){
	if(!setElementAttribute(currentPanel(),"Tray","layer",position)){
		errorOUT("Could not set layer to "+position);
	}
	else{
		layer->value(position.c_str());
		layer->redraw();
	}
}
void JSM_Panel::changePanel(int number){
	debug_out("void changePanel(int number)");
	if(!setJSMItem("panel",linuxcommon::convert_num_to_string(number))){debug_out("FAILED to change panel");}
}
void JSM_Panel::checkDock(){
	if(!isTrayElement("Dock")){addSubElement(currentPanel(),"Tray","Dock");}
}
//////D
void JSM_Panel::deleteBattery(){
	debug_out("void deleteBattery()");
	std::string TORI="torios-battery";
	std::string XFCEB="xfce4-power-manager";
	if(checkExec("yad")&&checkExec(TORI)){deleteSomeIndicator(TORI);}
	if(checkExec(XFCEB)){deleteSomeIndicator(XFCEB);}
}
void JSM_Panel::deleteNetworkMonitor(){
	debug_out("void deleteNetworkMonitor()");
	//std::string TORI="torios-network";
	std::string NM="nm-applet";
	if(checkExec(NM)){deleteSomeIndicator(NM);}
	std::string WICD="wicd-gtk";
	if(checkExec(WICD)){deleteSomeIndicator(WICD);}
	//else if(.compare("")!=0){deleteSomeIndicator();}
}
void JSM_Panel::deletePanel(){removeElement(currentPanel(),"Tray");}


void JSM_Panel::deleteSomeIndicator(std::string indicator){
	debug_out("void deleteSomeIndicator(std::string "+indicator+")");
	if(indicator.find("torios-")<indicator.length()){
		debug_out("found torios program");
		linuxcommon::run_a_program(indicator+" --kill");
	}
	if(!linuxcommon::pkill(indicator)){debug_out("Couldn't stop "+indicator);}
	if(linuxcommon::program_is_running(indicator)){linuxcommon::run_a_program("pkill "+indicator);}
	removeAutostart(indicator);
}
void JSM_Panel::deleteTrayButton(std::string text_to_find){
	debug_out("void deleteTrayButton(std::string "+text_to_find+")");
	
}
void JSM_Panel::deleteVolume(){
	debug_out("void deleteVolume()");
	std::string TORI="torios-volume";
	std::string VOL="volumeicon";
	if(checkExec("yad")&&checkExec(TORI)){deleteSomeIndicator(TORI);}
	else if(checkExec(VOL)){deleteSomeIndicator(VOL);}
}
//////E
void JSM_Panel::editButton(int whichbutton, std::string MENU,std::string PROG,std::string ICON,std::string LABEL,std::string MASK){
	debug_out("void editButton(std::string "+MENU+",std::string "+PROG+",std::string "+ICON+",std::string "+LABEL+",std::string "+MASK+")");
	if(MASK.compare("")!=0){
		if((PROG.compare("")!=0)&&(MENU.compare("")!=0)){errorOUT("Both program and Menu are together on the same mask.... This will default to MENU");}
	  //edit the current mouse button mask
		std::string RES;
		if(PROG.compare("")!=0){RES=PROG;}
		if(MENU.compare("")!=0){RES=MENU;}
		if(RES.compare("")!=0){
			if(!setNodeText(getMenuButtonByMask(MASK,whichbutton),RES)){errorOUT("Could not set the button text correctly");}
		}
	}
	if(ICON.compare("")!=0){
		if(!setAttribute(getTraySubElement(whichbutton),"icon",ICON)){
			debug_out("Didn't set the icon "+ICON+" for the Menu");
		}
	}
	if(LABEL.compare("")!=0){
		if(!setAttribute(getTraySubElement(whichbutton),"label",LABEL)){
			debug_out("Didn't set the label "+LABEL+" for the Menu");
		}
	}
}
//////G
void JSM_Panel::getTrayStyleattribute(std::string item,Fl_Output* list_out){
	std::string value=getTrayStyleattribute(item);
	list_out->value(value.c_str());
	list_out->redraw();
}
void JSM_Panel::getColorFromItem(bool active, std::string element,std::string subelement,Fl_Button* o){
	debug_out("void getColorFromItem(bool active, std::string "+element+",std::string "+subelement+")");
	unsigned int color=0;
	std::string COLOR=getElementText(element,subelement);
	if(active)COLOR=getElementText(element,"Active",subelement);
	o->color(color);
}
void JSM_Panel::getGroupWin(Fl_Check_Button *o){
	std::string val=getTrayStyleattribute("group");
	if(val.compare("true")==0){
		o->value(1);
	}
	else{o->value(0);}
	
}
void JSM_Panel::getIndicators(Fl_Browser* o){
	debug_out("void getIndicators(Fl_Browser* o)");
	o->clear();
	o->redraw();
	//TODO xdg dir
	std::string filename=linuxcommon::test_file_in_vector_path("jwm-settings-manager/indicators.list",linuxcommon::desktop_dirs());
	std::vector<std::string> myVec;
	if(linuxcommon::test_file(filename)){myVec=linuxcommon::file_to_vector(filename);}
	else{
		myVec.push_back("wicd-gtk");
		myVec.push_back("nm-applet");
		myVec.push_back("torios-volume");
		myVec.push_back("volumeicon");
		myVec.push_back("torios-battery");
		myVec.push_back("xfce4-power-manager");
		myVec.push_back("torios-installer");
	}
	getIndicatorsPopulate(o,myVec);
	
}
void JSM_Panel::getIndicatorsPopulate(Fl_Browser* o,std::vector<std::string> list){
	for(std::vector<std::string>::iterator it = list.begin();it!=list.end();++it){
		std::string item=*it;
		if(checkExec(item)){o->add(item.c_str());}
	}
	o->redraw();
}
//////H
void JSM_Panel::hide_menu(Fl_Menu_Item * o, int whichOne){
	debug_out("void hide_menu(Fl_Menu_Item * o, int whichOne)");
	int num = numPanels();
	if (whichOne > num) o->hide();
	else o->show();
}
//////I
void JSM_Panel::icon_for_desktop(Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Box* icon_name,Fl_Input* tooltip,Fl_Button* app_icon_box){
	debug_out("void icon_for_desktop(Fl_Input* app_command,Fl_Box* icon_name,Fl_Input* tooltip,Fl_Box* app_icon_box)");
	std::string chooseName=gettext("Choose a program");
	std::string result=nativeFileDialog(chooseName,"/usr/share/applications","*.desktop");
	if(result.compare("")==0){return;}
	if(result.find(".desktop")>result.length()){return;}
	std::string name = linuxcommon::get_line_with_equal(result,"Name=");
	std::string executable = linuxcommon::get_line_with_equal(result,"Exec=");
	app_command->value(executable.c_str());
	std::string iconName = linuxcommon::get_line_with_equal(result,"Icon=");
	icon_name->copy_label(iconName.c_str());
	std::string iconFILE=iconName;
	makeWidgetIcon(iconFILE,app_icon_box,48);
	app_icon_box->redraw();
    tooltip->value(name.c_str());
    app_command->redraw();
    //Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Input* tooltip,Fl_Box* icon_name,int border
    add_new_shortcut(shortcut_browser,app_command,tooltip,icon_name,0);
}
void JSM_Panel::input_width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension){
	debug_out("void input_width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension)");
	if(dimension==NULL){return;}
	std::string border=dimension;
	int panelSize=input_o->value();
	slider_o->value(panelSize);
	std::string stringInt =convert(panelSize);
	if(border.compare("border")==0){
		debug_out("Border size: "+stringInt);
		if (panelSize == 0){
			setValue(dimension,"false");
			return;
		}
	}
	setValue(dimension,stringInt);
}
//////L
void JSM_Panel::labelMenu(std::string testNum,std::string newLabel){
	debug_out("void labelMenu(unsigned int testNum,std::string newLabel)");
	testNum="root:"+testNum;
	if(!setAttribute(getMenu(testNum),"label",newLabel)){
		debug_out("Didn't set the label "+newLabel+" for the Menu");
	}
}
void JSM_Panel::layout(std::string position,Fl_Output *layOut){
	if(!setElementAttribute(currentPanel(),"Tray","layout",position)){
		errorOUT("Could not set layout to "+position);
	}
	else{
		layOut->value(position.c_str());
		layOut->redraw();
	}
}
void JSM_Panel::listIndicators(Fl_Browser *o){
	std::string filename=linuxcommon::test_file_in_vector_path("jwm-settings-manager/indicators.list",linuxcommon::desktop_dirs());
	std::vector<std::string> myVec;
	if(linuxcommon::test_file(filename)){myVec=linuxcommon::file_to_vector(filename);}
	else{
		myVec.push_back("wicd-gtk");
		myVec.push_back("nm-applet");
		myVec.push_back("torios-volume");
		myVec.push_back("volumeicon");
		myVec.push_back("torios-battery");
		myVec.push_back("xfce4-power-manager");
		myVec.push_back("torios-installer");
	}
	for( std::vector<std::string>::iterator it = myVec.begin();
	it!=myVec.end();
	++it){
		std::string tester=*it;
		if(isExec(tester)){o->add(tester.c_str());}
	}
}
//////N
void JSM_Panel::new_panel_items(Fl_Browser *o){
	debug_out("void new_panel_items(Fl_Browser *o)");
	std::string RUNNINGAPPLIST=gettext("Running App List");
	std::string INDICATORS=gettext("Indicators");
	std::string CLOCK=gettext("Clock");
	std::string SWALLOW=gettext("Swallow");
	std::string MENU=gettext("Menu");
	std::string DESKSWITCH=gettext("Desktop Switcher");
	std::string LAUNCHER=gettext("Program Launcher");
	std::string SPACER=gettext("Spacer");
	o->add(MENU.c_str());
	o->add(CLOCK.c_str());
	o->add(DESKSWITCH.c_str());
	o->add(INDICATORS.c_str());
	o->add(RUNNINGAPPLIST.c_str());
	o->add(LAUNCHER.c_str());
	o->add(SWALLOW.c_str());
	o->add(SPACER.c_str());
}
void JSM_Panel::num_desktop_wh_CB(std::string whichone, int value,Fl_Value_Input* num_desktop_w, Fl_Value_Input* num_desktop_h){
	debug_out("void num_desktop_wh_cb(std::string "+whichone+", int value)");
	std::string VAL=linuxcommon::convert_num_to_string(value);
	setElementAttribute("Desktops",whichone,VAL);
	int w = int((num_desktop_w->value()));
	int h = int((num_desktop_h->value()));
	std::string defaultValue = "1";
	if(w==0){setElementAttribute("Desktops","width",defaultValue);}
	if(h==0){setElementAttribute("Desktops","height",defaultValue);}
}
//////P
void JSM_Panel::panel_label(Fl_Menu_Button *o){
	debug_out("void panel_label(Fl_Menu_Button *o)");
	std::string PANEL=gettext("Panel");
	int num = 1;
	std::string x = convert(num);
	std::string l = PANEL + " " + x;
	o->copy_label(l.c_str());
	o->redraw();
}
void JSM_Panel::panel_h(int num, Fl_Output * align){panel_hv("halign",num,align);}
void JSM_Panel::panel_v(int num, Fl_Output * align){panel_hv("valign",num,align);}
void JSM_Panel::panel_hv(std::string attrib, int num, Fl_Output * align){
	std::string item;
	switch(num){
		case 1:
			item="fixed";
			break;
		case 2:
			item="top";
			if(attrib.compare("halign")==0)
				item="left";
			break;
		case 3:
			item="center";
			break;
		case 4:
			item="bottom";
			if(attrib.compare("halign")==0)
				item="right";
			break;
		default:
			std::string tmp=linuxcommon::convert_num_to_string(num);
			errorOUT("Invalid choice:"+tmp);
			return;
	}
	if(!setElementAttribute(currentPanel(),"Tray",attrib,item)){
		errorOUT("Could not set "+attrib+" to "+item);
	}
	else{
		align->value(item.c_str());
		align->redraw();
	}
}
void JSM_Panel::panel_menu_button_label(Fl_Menu_Button* o){
	debug_out("void panel_menu_button_label(Fl_Menu_Button* o)");
	int num=currentPanel();
	std::string labeler=linuxcommon::convert_num_to_string(num);
	std::string LABEL=gettext("Panel");
	LABEL+=" ";
	LABEL+=labeler;
	debug_out("Label="+LABEL);
	o->copy_label(LABEL.c_str());
	o->redraw();
}
void JSM_Panel::panel_position(std::string position){
	//TODO set w/h to normal values
	debug_out("void panel_position(std::string "+position+")");
	int tH = getHeight();
	int tW = getWidth();
		//This is my standard icon size for the panel
	std::string StandardHeight = "32";
	std::string StandardWidth = "0";
	if((position.compare("top")==0)||(position.compare("bottom")==0)){
		if( (tW < 100) && (tW != 0 ) ){
			//Is the panel long enough??  Or will it look weird??  If so... make it the full screen width
			int screenW = Fl::w();
			std::string Width = linuxcommon::convert_num_to_string(screenW);
			setElementAttribute(currentPanel(),"Tray","width",Width);
		}
		//Is is too tall??
		if( (tH > 100) || (tH == 0 ) ){
			setElementAttribute(currentPanel(),"Tray","height",StandardHeight);
		}
		setElementAttribute(currentPanel(),"Tray","halign","fixed");
		setElementAttribute(currentPanel(),"Tray","layout","horizontal");
		setElementAttribute(currentPanel(),"Tray","valign",position);
	}
	else{
		if( (tH < 100) && (tH != 0 ) ){
			int screenH = Fl::h();
			//Is the panel long enough??  Or will it look weird??  If so... make it the full screen height
			std::string Height = linuxcommon::convert_num_to_string(screenH);
			setElementAttribute(currentPanel(),"Tray","height",Height);
		}
		//Is is too wide??
		if( (tW > 100) || ( tW == 0 ) ){
			setElementAttribute(currentPanel(),"Tray","width",StandardWidth);
		}
		setElementAttribute(currentPanel(),"Tray","layout","vertical");
		setElementAttribute(currentPanel(),"Tray","valign","center");
		setElementAttribute(currentPanel(),"Tray","halign",position);
	}
}
void JSM_Panel::populateClocks(Fl_Browser* o){
	debug_out("void populateClocks(Fl_Browser* o)");
	std::string filename = linuxcommon::find_xdg_data_dir_subdir("jwm-settings-manager");
	if(filename.compare("")==0){
		debug_out("couldn't get file path for time file");
		//TODO... something to make this work out..
		return;
	}
	filename +="time";
    std::string line;
    std::ifstream ifs (filename.c_str(), std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            o->add(line.c_str());
        }
    }
}
//////R
void JSM_Panel::refresh_app_browser(Fl_Browser* app_browser){populateApps(app_browser);}
void JSM_Panel::remove_app(Fl_Browser* app_browser){
	debug_out("void remove_app(Fl_Browser* app_browser)");
	if(checkFlBrowserItem(app_browser)){
		deletePanelItem(app_browser->value());
		refresh_app_browser(app_browser);
	}
}
void JSM_Panel::removeIndicator(Fl_Browser* o){
	debug_out("void removeIndicator(Fl_Browser* o)");
	if(!checkFlBrowserItem(o))return;
	std::string item=o->text(o->value());
	#if 0
	//possibly need this at some point?
	std::string filename=linuxcommon::test_file_in_vector_path("jwm-settings-manager/indicators.list",linuxcommon::desktop_dirs());
	std::vector<std::string> myVec;
	if(linuxcommon::test_file(filename)){myVec=linuxcommon::file_to_vector(filename);}
	else{
		myVec.push_back("wicd-gtk");
		myVec.push_back("nm-applet");
		myVec.push_back("torios-volume");
		myVec.push_back("volumeicon");
		myVec.push_back("torios-battery");
		myVec.push_back("xfce4-power-manager");
		myVec.push_back("torios-installer");
	}
	if(linuxcommon::program_is_running(item)){
		if(!linuxcommon::pkill(item))errorOUT("Could not kill the program: "+item);
		
	}
	#endif
	deleteSomeIndicator(item);
	getIndicators(o);
}
void JSM_Panel::removeAutostart(std::string exec){
	debug_out("void removeAutostart(std::string "+exec+")");
	removeElement("StartupCommand",exec);
	//TODO xdg remove autostart
}
//////S
void JSM_Panel::setImageMenu(std::string testNum,std::string icon){
	debug_out("void setImageMenu(unsigned int testNum,std::string "+icon+")");
	if(!setAttribute(getMenu(testNum),"icon",icon)){
		debug_out("Did not set "+icon+" for Menu");
	}
	
}
void JSM_Panel::setCoordinate(std::string xy, int value){if(!setElementAttribute(currentPanel(),"Tray",xy,convert(value))){debug_out("Couldn't set value of "+xy);}}
void JSM_Panel::setTaskListValue(std::string attribute, std::string value){
	if(!setElementAttribute("TrayStyle",attribute,value)){
		errorOUT("Could not set "+attribute+" to "+value+" for the TrayStyle");
	}
}
void JSM_Panel::setValue(std::string attribute, std::string value){
	debug_out("void setValue(std::string "+attribute+", std::string "+value+")");
	unsigned int panel = currentPanel();
	setElementAttribute(panel,"Tray",attribute,value);
	saveChangesTemp();
}
void JSM_Panel::setItemBool(int position, int value){
	std::string retval="true";
	if(value==0){retval="false";}
	if(!setItemWH("labeled",retval,position)){errorOUT("Labeled Not set...");}
}
void JSM_Panel::switchButton(std::string OLD,std::string NEW,std::string tooltip,std::string icon,std::string label){
	debug_out("void switchButton(std::string "+OLD+",std::string "+NEW+",std::string "+tooltip+",std::string "+icon+",std::string "+label+")");
	if(icon.compare("")!=0){
		if(!setAttribute(getMenu(OLD),"icon",icon)){debug_out("Did not set icon="+icon+" for Item");}
	}
	if(tooltip.compare("")!=0){
		if(!setAttribute(getMenu(OLD),"tooltip",tooltip)){debug_out("Did not set tooltip="+tooltip+" for Item");}
	}
	if(label.compare("")!=0){
		if(!setAttribute(getMenu(OLD),"label",label)){debug_out("Did not set label="+label+" for Item");}
	}
	if(OLD.compare(NEW)!=0){
		if(!setNodeText(getMenu(OLD),NEW)){debug_out("Did not set text="+NEW+" for Item");}
	}
}
//////W
void JSM_Panel::width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension){
	debug_out("void width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension)");
	if(dimension==NULL){return;}
	int panelSize=slider_o->value();
	input_o->value(panelSize);
	std::string border = dimension;
	std::string stringInt =convert(panelSize);
	if(border.compare("border")==0){
		debug_out("Border size: "+stringInt);
		if (panelSize == 0){
			setValue(dimension,"false");
			return;
		}
	}
	setValue(dimension,stringInt);
}
