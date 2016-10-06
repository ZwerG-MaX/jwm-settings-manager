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
std::string getClock(std::string timeString){
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
std::string getClock(){return getElementAttribute(currentPanel(),"Tray","Clock","format");}
std::string getImageMenu(std::string item){return getAttribute(getMenu(item),"icon");}
std::string getLabelMenu(std::string item){
	debug_out("std::string getLabelMenu(std::string "+item+")");
	std::string tmp= getAttribute(getMenu(item),"label");
	debug_out("Label="+tmp);
	return tmp;
}
std::string getButtonTooltip(std::string item){
	debug_out("std::string getButtonTooltip(std::string "+item+")");
	std::string tmp= getAttribute(getMenu(item),"tooltip");
	if(tmp.compare("")==0){tmp=getLabelMenu(item);}
	debug_out("Label="+tmp);
	return tmp;
}
std::string Menu_Label(int num){
	debug_out("std::string Menu_Label(int num)");
	changePanel(num);
	currentPanel();
	std::string numero=convert(num);
	std::string LABEL = gettext("Panel");
	LABEL +=" ";
	LABEL +=numero;
	return LABEL;
}
//Unsigned Integer//////////////////////////////////////////////////////
unsigned int getActiveBackground(unsigned int c,std::string element){
	debug_out("unsigned int getActiveBackground(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Active","Background");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int getBackground(unsigned int c,std::string element){
	debug_out("unsigned int getBackground(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Background");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int getFontColor(unsigned int c,std::string element){
	debug_out("unsigned int getFontColor(unsigned int c,std::string "+element+")");
	std::string color=getElementText(element,"Foreground");
	unsigned int retval=flCOLOR(color,c);
	return retval;
}
unsigned int switch_panel(Fl_Menu_Item *o){
	debug_out("unsigned int switch_panel(Fl_Menu_Item *o)");
	unsigned int whichPanel = o->value();
	return whichPanel;
}
//Integer///////////////////////////////////////////////////////////////
int getBorder(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","border").c_str());}
int getCoordinate(std::string xy){return linuxcommon::convert_string_to_number(getElementAttribute("Tray",xy).c_str());}
int getHeight(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","height").c_str());}
int getWidth(){return linuxcommon::convert_string_to_number(getElementAttribute(currentPanel(),"Tray","width").c_str());}
//Float/////////////////////////////////////////////////////////////////
float getOpacity(std::string element){return getElementFloat(element);}
//Boolean///////////////////////////////////////////////////////////////
bool addApp(std::string element){return addSubElement(currentPanel(),"Tray",element);}
bool addApp(std::string element, std::string attribute,std::string value,std::string text){return addSubElementWithTextandAttribute(currentPanel(),"Tray",element,text,attribute,value);}
bool addApp(std::string element,std::string attribute,std::string value){return addSubElementWithAttribute(currentPanel(),"Tray",element,attribute,value);}
bool addButton(std::string icon,std::string execLine,std::string popup,int border){
	if(execLine.find("exec:")>execLine.length()){execLine="exec:"+execLine;}
	debug_out("void addButton(std::string "+icon+",std::string "+execLine+",std::string "+popup+",int border)");
	if(setAttribute(addNode(currentPanel(),"Tray", "TrayButton"),"icon",icon)){
		if(setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"popup",popup)){
			if(setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"border",linuxcommon::convert_num_to_string(border))){
				return addSubNodewithAttributeAndText(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"Button","mask","123",execLine);
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
bool add_new_shortcut(Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Input* tooltip,Fl_Box* icon_name,int border){
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
bool addShortcut(std::string icon,std::string execLine,std::string popup,int border){
	if(execLine.find("exec:")>execLine.length()){execLine="exec:"+execLine;}
	debug_out("void addShortcut(std::string "+icon+",std::string "+execLine+",std::string "+popup+",int border)");
	setAttribute(addNode(currentPanel(),"Tray", "TrayButton"),"icon",icon);
	setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"popup",popup);
	setAttribute(getLastSubNode(currentPanel(),"Tray", "TrayButton"),"border",linuxcommon::convert_num_to_string(border));
	return setNodeText(getLastSubNode(currentPanel(),"Tray", "TrayButton"),execLine);
}
bool style_gone(){
	debug_out("bool style_gone()");
	if(newStyle() ==1){return true;}
	return false;
}
bool toomanypanels(){
	debug_out("bool toomanypanels()");
	if(numPanels()>=4){return true;}
	return false;
}
//Void//////////////////////////////////////////////////////////////////
//////A
void addBattery(){

}
void addClock(){
	debug_out("");
	std::string defaultFormat="%a, %e %b %l:%M %p";
	std::string defaultclock=linuxcommon::term_out("which torios-calendar");
	if(defaultclock.compare("")==0){defaultclock=linuxcommon::term_out("which xclock");}
	//TODO more??
	if(defaultclock.compare("")==0){
		debug_out("FAILED to find clock program...");
		return;
	}
	setAttribute(addNode(currentPanel(),"Tray", "Clock"),"format",defaultFormat);
	addSubNodewithAttributeAndText(getLastSubNode(currentPanel(),"Tray", "Clock"),"Button","mask","123",defaultclock);
}
void addNetworkMonitor(){
	
}
void add_new_menu(){
	debug_out("void add_new_menu()");
}
void addPager(){
	debug_out("void addPager()");
	if(!setAttribute(addNode(currentPanel(),"Tray", "Pager"),"labeled","true")){
		debug_out("Couldn't add the Pager");
	}
}
void addPanel(){

}
void addTaskList(){
	debug_out("void addTaskList()");
	if(!setAttribute(addNode(currentPanel(),"Tray", "TaskList"),"maxwidth","256")){debug_out("Could not add the TaskList");}	
}
void addVolume(){

}
void app_command_CB(Fl_Input* o, Fl_Input* app_command){
	debug_out("void app_command_CB(Fl_Input* o, Fl_Input* app_command)");
	const char* result = o->value();
	if(result!=NULL){
		std::string exec = result;
		unsigned found = exec.rfind("//");
		exec=exec.erase(0,found+1);
		app_command->value(exec.c_str());
	}
}
void autohide(Fl_Check_Button* autohide_check,Fl_Menu_Button* choose_autohide){
	debug_out("void autohide(Fl_Check_Button* autohide_check,Fl_Menu_Button* choose_autohide)");
	std::string a = getElementAttribute("Tray","autohide");
	if(!newStyle()){
		autohide_check->show();
		choose_autohide->hide();
		if(a=="true"){autohide_check->value(1);}
		else{autohide_check->value(0);}
	}
}
void autohide_position(const char* where){
	if(where==NULL){return;}
	debug_out("void autohide_position(const char* where)");
	setElementAttribute(currentPanel(),"Tray","autohide",where);
}
//////C
void changeClock(std::string style){
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
void changePanel(int number){
	debug_out("void changePanel(int number)");
	if(!setJSMItem("panel",linuxcommon::convert_num_to_string(number))){debug_out("FAILED to change panel");}
}
//////D
void deleteBattery(){
	debug_out("void deleteBattery()");
	std::string TORI="torios-battery";
	std::string XFCEB="xfce4-power-manager";
	std::string xfcebatt=linuxcommon::term_out("which "+XFCEB);
	std::string toribatt=linuxcommon::term_out("which "+TORI);
	std::string yad=linuxcommon::term_out("which yad");
	if((yad.compare("")!=0)&&(toribatt.compare("")!=0)){deleteSomeIndicator(TORI);}
	else if(xfcebatt.compare("")!=0){deleteSomeIndicator(XFCEB);}
}
void deleteNetworkMonitor(){
	debug_out("void deleteNetworkMonitor()");
	//std::string TORI="torios-network";
	std::string NM="nm-applet";
	std::string nm=linuxcommon::term_out("which "+NM);
	std::string WICD="wicd-gtk";
	std::string wicd=linuxcommon::term_out("which "+WICD);
	//std::string toribatt=linuxcommon::term_out("which "+TORI);
	//std::string yad=linuxcommon::term_out("which yad");
	if(nm.compare("")!=0){deleteSomeIndicator(NM);}
	else if(wicd.compare("")!=0){deleteSomeIndicator(WICD);}
	//else if(.compare("")!=0){deleteSomeIndicator();}
	
}
void deletePanel(){removeElement(currentPanel(),"Tray");}
void deletePanelItem(std::string item){
	debug_out("void deletePanelItem(std::string "+item+")");
	if(item.compare("")==0){return;}
	unsigned int whichPanel=currentPanel();
	std::string RUNNINGAPPLIST=gettext("Running App List");
	std::string INDICATORS=gettext("Indicators");
	std::string CLOCK=gettext("Clock");
	std::string SWALLOW=gettext("Swallow");
	std::string MENU=gettext("Menu");
	std::string DESKSWITCH=gettext("Desktop Switcher");
	std::string LAUNCHER=gettext("Launcher");
	if(item.compare(RUNNINGAPPLIST)==0){removeElement(whichPanel,"Tray","TaskList");}
	else if(item.compare(DESKSWITCH)==0){removeElement(whichPanel,"Tray","Pager");}
	else if(item.compare(INDICATORS)==0){removeElement(whichPanel,"Tray","Dock");}
	else if(item.compare(CLOCK)==0){removeElement(whichPanel,"Tray","Clock");}
	else if(item.find(SWALLOW)<item.length()){removeElement(whichPanel,"Tray","Swallow");}
	else if(item.find(MENU)<item.length()){
		std::string tempMenu = item;
        tempMenu = tempMenu.erase(0,MENU.length());
        deleteTrayButton(tempMenu);
	}
	else{
		removeElement(whichPanel,"Tray",item);
	}
}
void deleteShortcut(std::string program){
	debug_out("");
}
void deleteSomeIndicator(std::string indicator){
	std::string tmp="pkill "+indicator;
	int retval=system(tmp.c_str());
	if(retval!=0){debug_out("Couldn't stop "+indicator);}
	removeAutostart(indicator);
}
void deleteTrayButton(std::string text_to_find){
	debug_out("void deleteTrayButton(std::string "+text_to_find+")");
	
}
void deleteVolume(){
	debug_out("void deleteVolume()");
	std::string TORI="torios-volume";
	std::string VOL="volumeicon";
	std::string vol=linuxcommon::term_out("which "+VOL);
	std::string torivol=linuxcommon::term_out("which "+TORI);
	std::string yad=linuxcommon::term_out("which yad");
	if((yad.compare("")!=0)&&(torivol.compare("")!=0)){deleteSomeIndicator(TORI);}
	else if(vol.compare("")!=0){deleteSomeIndicator(VOL);}
}
//////G
void getColorFromItem(bool active, std::string element,std::string subelement,Fl_Button* o){
	debug_out("void getColorFromItem(bool active, std::string "+element+",std::string "+subelement+")");
	unsigned int color=0;
	std::string COLOR=getElementText(element,subelement);
	if(active)COLOR=getElementText(element,"Active",subelement);
	o->color(color);
}
void getIndicators(Fl_Browser* o){
	debug_out("");
	o->clear();
	o->redraw();
}
//////H
void hide_menu(Fl_Menu_Item * o, int whichOne){
	debug_out("void hide_menu(Fl_Menu_Item * o, int whichOne)");
	int num = numPanels();
	if (whichOne > num) o->hide();
	else o->show();
}
//////I
void icon_for_desktop(Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Box* icon_name,Fl_Input* tooltip,Fl_Button* app_icon_box){
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
    tooltip->value(name.c_str());
    app_command->redraw();
    //Fl_Browser* shortcut_browser,Fl_Input* app_command,Fl_Input* tooltip,Fl_Box* icon_name,int border
    add_new_shortcut(shortcut_browser,app_command,tooltip,icon_name,0);
}
void input_width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension){
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
void labelMenu(std::string testNum,std::string newLabel){
	debug_out("void labelMenu(unsigned int testNum,std::string newLabel)");
	testNum="root:"+testNum;
	if(!setAttribute(getMenu(testNum),"label",newLabel)){
		debug_out("Didn't set the label "+newLabel+" for the Menu");
	}
}
//////N
void new_panel_items(Fl_Browser *o){
	debug_out("void new_panel_items(Fl_Browser *o)");
	std::string RUNNINGAPPLIST=gettext("Running App List");
	std::string INDICATORS=gettext("Indicators");
	std::string CLOCK=gettext("Clock");
	std::string SWALLOW=gettext("Swallow");
	std::string MENU=gettext("Menu");
	std::string DESKSWITCH=gettext("Desktop Switcher");
	std::string LAUNCHER=gettext("Launcher");
	o->add(MENU.c_str());
	o->add(CLOCK.c_str());
	o->add(DESKSWITCH.c_str());
	o->add(INDICATORS.c_str());
	o->add(RUNNINGAPPLIST.c_str());
	o->add(LAUNCHER.c_str());
	o->add(SWALLOW.c_str());
}
void num_desktop_wh_CB(std::string whichone, int value,Fl_Value_Input* num_desktop_w, Fl_Value_Input* num_desktop_h){
	debug_out("void num_desktop_wh_cb(std::string "+whichone+", int value)");
	std::string VAL=linuxcommon::convert_num_to_string(value);
	setElementAttribute("Desktops",whichone,VAL);
	int w = int((num_desktop_w->value()));
	int h = int((num_desktop_h->value()));
	std::string defaultValue = "1";
	if(w==0){setElementAttribute("Desktops","width",defaultValue);}
	if(h==0){setElementAttribute("Desktops","height",defaultValue);}
}
//////O
void one_color(Fl_Widget *o, std::string whichElement){
	debug_out("void one_color(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){
		setElementFloat(whichElement,colors);
		std::string colorString=getElementText(whichElement);
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
void one_color_active(Fl_Widget *o, std::string whichElement){
	debug_out("void one_color_active(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){ //If color chooser isn't canceled... do stuff
		setElementFloat(whichElement,"Active",colors);
		std::string colorString=getElementText(whichElement,"Active");
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
void one_color_Font(Fl_Widget *o, std::string whichElement){
	debug_out("void one_color_Font(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){ //If color chooser isn't canceled... do stuff
  	///FIXME flPanel function
		setElementFloat(whichElement,"Foreground",colors);
		std::string colorString=getElementText(whichElement,"Foreground");
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
void opacity(Fl_Value_Input *o, Fl_Slider *slider, std::string whichElement){
	debug_out("void opacity(Fl_Value_Input *o, Fl_Slider *slider, std::string "+whichElement+")");
	double opac=slider->value();
	double* opacity =&opac;
	setElementFloat(whichElement,"Opacity",opacity);
	o->value(opac*100);
}
//////P
void panel_label(Fl_Menu_Button *o){
	debug_out("void panel_label(Fl_Menu_Button *o)");
	std::string PANEL=gettext("Panel");
	int num = 1;
	std::string x = convert(num);
	std::string l = PANEL + " " + x;
	o->copy_label(l.c_str());
	o->redraw();
}
void panel_menu_button_label(Fl_Menu_Button* o){
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
void panel_position(std::string position){
	debug_out("void panel_position(std::string "+position+")");
	if((position.compare("top")==0)||(position.compare("bottom")==0)){
		setElementAttribute(currentPanel(),"Tray","halign","fixed");
		setElementAttribute(currentPanel(),"Tray","layout","horizontal");
		setElementAttribute(currentPanel(),"Tray","valign",position);
	}
	else{
		setElementAttribute(currentPanel(),"Tray","layout","vertical");
		setElementAttribute(currentPanel(),"Tray","valign","center");
		setElementAttribute(currentPanel(),"Tray","halign",position);
	}
}
void populateClocks(Fl_Browser* o){
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
void refresh_app_browser(Fl_Browser* app_browser){populateApps(app_browser);}
void remove_app(Fl_Browser* app_browser){
	debug_out("void remove_app(Fl_Browser* app_browser)");
	unsigned int appLine=app_browser->value();
	unsigned int size =app_browser->size();
	if(appLine <= size && appLine !=0){
		std::string whichAPP = app_browser->text(appLine);
		deletePanelItem(whichAPP);
		refresh_app_browser(app_browser);
	}
}
void removeAutostart(std::string exec){
	debug_out("void removeAutostart(std::string "+exec+")");
	removeElement("StartupCommand",exec);
	//TODO xdg remove autostart
}
//////S
void setImageMenu(std::string testNum,std::string icon){
	debug_out("void setImageMenu(unsigned int testNum,std::string "+icon+")");
	if(!setAttribute(getMenu(testNum),"icon",icon)){
		debug_out("Did not set "+icon+" for Menu");
	}
	
}
void setCoordinate(std::string xy, int value){if(!setElementAttribute(currentPanel(),"Tray",xy,convert(value))){debug_out("Couldn't set value of "+xy);}}
void setValue(std::string attribute, std::string value){
	debug_out("void setValue(std::string "+attribute+", std::string "+value+")");
	unsigned int panel = currentPanel();
	setElementAttribute(panel,"Tray",attribute,value);
	saveChangesTemp();
}
void switchButton(std::string OLD,std::string NEW,std::string tooltip,std::string icon,std::string label){
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
void width_height_border(Fl_Slider *slider_o, Fl_Value_Input *input_o, const char* dimension){
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
