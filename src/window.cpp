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

#include "../include/window.hpp"
void active_color_loader(Fl_Button *o, unsigned int one_or_two){
  unsigned int color=0;
  unsigned int c = 0;
  std::string colors,newOrOld;
  debug_out("void active_color_loader(Fl_Button *o, unsigned int one_or_two)->");
  if(newStyle() !=-1){
    colors=getElementText("WindowStyle","Active","Background");
  }
  else{
    colors=getElementText("WindowStyle","Active","Title");
  }
  color=splitColor(colors,1);
  c=splitColor(colors,2);
  std::cout<<"one OR two="<<one_or_two<<" Color1="<<c<<" Color2="<<color<<std::endl;
  if(one_or_two ==1){o->color(c);}
  else{o->color(color);}
  debug_out("<-active color loader");
}

void add_option_to_group(Fl_Browser *options_available, Fl_Input* icon_value, Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Browser *add_tracker, Fl_Browser* browser){
	debug_out("void add_option_to_group(Fl_Browser *options_available, Fl_Input* icon_value, Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Browser *add_tracker, Fl_Browser* browser)");
	const char* input=browser->label();
	if(input==NULL)return;
	std::string group=input;
	if(group.compare("")==0)return;
	int line =options_available->value();
	if((line == 0)||(line>options_available->size())){return;}
	else{
		unsigned int found = group.find_first_of(' ');
		group = group.substr(found+1,std::string::npos);
		unsigned int whichGroup = convert(group.c_str());
		std::string val = options_available->text(line);
		std::string thisitem;
		std::string result = val;
		if(result.compare("")==0){return;}
		if(val.compare("icon:")==0){
			thisitem=icon_value->value();
			if(thisitem.compare("")==0){return;}
		}
		else if(val.compare("desktop:")==0){
			thisitem=convert(desktop_num->value());
			result+=thisitem;
			if(thisitem.compare("")==0){return;}
		}
		else if(val.compare("layer:")==0){
			thisitem=layer_value->value();
			result+=thisitem;
			if(thisitem.compare("")==0){return;}
		}
		else if(val.compare("opacity:")==0){
			thisitem = convert(opacity_value->value());
			result+=thisitem;
			if(thisitem.compare("")==0){return;}
		}
		add_tracker->add(result.c_str());
		addGroupItem( whichGroup, group,result);
	}
}

void add_thingie(Fl_Browser *groups_browser,std::string input,std::string Item){
	debug_out("void add_thingie(Fl_Browser *groups_browser,std::string "+input+",std::string "+Item+")");
	if(input.compare("")!=0){
		unsigned int line = groups_browser->value();
		addGroupItem(line,Item,input);
	}
}

void addGroup(){
	//bool ans=addElement("Group");
}

void addGroupItem(unsigned int whichone, std::string subelement,std::string value){
	debug_out("void addGroupItem(unsigned int whichone, std::string "+subelement+",std::string "+value+")");
	bool ans=addSubElementWithText(whichone,"Group",subelement,value);
	if(!ans){debug_out("addSubElementWithText(whichone,Group, "+subelement+"," +value +") FAILED");}
}

void border_color_loader(Fl_Widget *o, int Active1_Inactive2){
	debug_out("void border_color_loader(Fl_Widget *o, int Active1_Inactive2)");
	unsigned int colour=0;
	std::string OUT="Outline";
	if (Active1_Inactive2==1){colour= getElementInt("WindowStyle","Active",OUT);}
	else{colour = getElementInt("WindowStyle",OUT);}
	o->color(colour);
}

void border_modifier(Fl_Slider *o1, Fl_Value_Input *o2, int change_o1_or_o2){
	debug_out("void border_modifier(Fl_Slider *o1, Fl_Value_Input *o2, int change_o1_or_o2)");
	int whichone = 0;
	if(change_o1_or_o2==1){
		int input = o2->value();
		o1->value(input);
		whichone = input;
	}
	else{
		int slider = o1->value();
		o2->value(slider);
		whichone = slider;
	}
	setElementInt("WindowStyle","Width",whichone);
}

void border_modifier(Fl_Slider *o1, Fl_Value_Output *o2){
	debug_out("void border_modifier(Fl_Slider *o1, Fl_Value_Output *o2)");
	int slider = o1->value();
	o2->value(slider);
	setElementInt("WindowStyle","Width",slider);
}

std::string buttonPath(){
	debug_out("std::string buttonPath()");
	std::string defaultPath=linuxcommon::find_xdg_data_dir_subdir("jwm-settings-manager");
	std::string ButtonPath = defaultPath + "Buttons/";
	debug_out("Button Path="+ButtonPath);
	return ButtonPath;
}

void check_opts(std::string itemValue,Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Input* icon_value, Fl_Menu_Button* layer_chooser){
	debug_out("void check_opts(std::string "+itemValue+",Fl_Value_Input* desktop_num, Fl_Output* layer_value, Fl_Slider* opacity_value, Fl_Input* icon_value, Fl_Menu_Button* layer_chooser)");
	if(itemValue.compare("")==0){return;}
	desktop_num->deactivate();
	layer_value->deactivate();
	opacity_value->deactivate();
	icon_value->deactivate();
	layer_chooser->deactivate();
	if(itemValue.compare("icon:")==0){
		icon_value->activate();
	}
	else if(itemValue.compare("desktop:")==0){
		desktop_num->activate();
	}
	else if(itemValue.compare("layer:")==0){
		layer_value->activate();
		layer_chooser->activate();
	}
	else if(itemValue.compare("opacity:")==0){
		opacity_value->activate();
	}
}

void corner_load(Fl_Slider *o){
	debug_out("void corner_load(Fl_Slider *o)");
	if(newStyle() == -1){o->hide();}
	else{
		unsigned int corner=0;
		std::string C = getElementText("WindowStyle","Corner");
		if(C.compare("")!=0){corner=strtol(C.c_str(),0,10);}
		o->value(corner);
	}
}

void corner_change(Fl_Slider *o){
	debug_out("void corner_change(Fl_Slider *o)");
	if(newStyle() == -1){o->hide();}
	else{
		unsigned int corner =o->value();  
		setElementInt("WindowStyle","Corner",corner);
	}
}

void display(std::string filename, Fl_Widget *o){
	debug_out("void display(std::string "+filename+", Fl_Widget *o)");
	makeWidgetIcon(filename,o,32);
}

void font_color_loader(Fl_Widget *o, int Active1_Inactive2){
	debug_out("void font_color_loader(Fl_Widget *o, int Active1_Inactive2)->");
	std::string colour="";
	std::string colors,newOrOld;
	std::string newORold;
	if(newStyle() !=-1){newORold="Foreground";}
	else{newORold="Text";}
	if (Active1_Inactive2==1){colour=getElementText("WindowStyle","Active",newORold);}
	else{colour = getElementText("WindowStyle",newORold);}
	unsigned int colorint=0;
	if(colour.compare("")!=0){colorint=flCOLOR(colour);}
	o->color(colorint);
	debug_out("<-font color loader");
}

int getBorderHeight(){
	debug_out("int getBorderHeight()");
	return getElementInt("WindowStyle","Height");
}

int getBorderWidth(){
	debug_out("int getBorderWidth()");
	return getElementInt("WindowStyle","Width");
}

void getGroups(Fl_Browser *o){
	debug_out("void getGroups(Fl_Browser *o)");
	int groups=elementCounter("Group");
	for (int i=1;i<=groups;i++){
		std::string tmp =linuxcommon::convert_num_to_string(i);
		o->add(tmp.c_str());
	}
}

int getSnap(){
	debug_out("int getSnap()");
	std::string dist= getElementAttribute("SnapMode","distance");
	debug_out("current Snap="+dist);
	if(dist.compare("")==0) return 0;//TODO default snap
	return convert(dist.c_str());
}

void get_button(Fl_Widget*o, std::string whichElement,Fl_Widget* a_title_color1){
	debug_out("void get_button(Fl_Widget*o, std::string "+whichElement+",Fl_Button* a_title_color1)");
	o->color(a_title_color1->color());
	std::string result=getElementText(whichElement);
	debug_out("Button="+result);
	if(result.compare("")!=0){display(result,o);}
	o->redraw();
	debug_out("<-button loader");
}

void get_button_inactive(Fl_Widget*o, std::string whichElement,Fl_Button* inactive_color,Fl_Button* inactive_font_color){
	debug_out("void get_button_inactive(Fl_Widget*o, std::string "+whichElement+",Fl_Button* inactive_color,Fl_Button* inactive_font_color)");
	o->color(inactive_color->color());
	o->labelcolor(inactive_font_color->color());
	std::string result=getElementText(whichElement);
	debug_out("Button="+result);
	if(result.compare("")!=0){display(result,o);}
	o->redraw();
}

void inactive_color_loader(Fl_Button *o, int one_or_two){
	debug_out("void inactive_color_loader(Fl_Button *o, int one_or_two)");
	unsigned int color=0;
	unsigned int c = 0;
	std::string colors;
	if(newStyle() !=-1){colors=getElementText("WindowStyle","Background");}
	else{colors=getElementText("WindowStyle","Inactive","Title");}
	color=splitColor(colors,0);
	c=splitColor(colors,1);
	if(one_or_two ==1){o->color(c);}
	else{o->color(color);}
}

void opacity_loader(Fl_Slider *o, int Active1_Inactive2){
	debug_out("void opacity_loader(Fl_Slider *o, int Active1_Inactive2)");
	float opacity;
	if (Active1_Inactive2==1){opacity=getElementFloat("WindowStyle","Active","Opacity");}
	else{opacity=getElementFloat("WindowStyle","Opacity");}
	o->value(opacity);
}

void populate_groups(Fl_Browser *groups_browser,Fl_Browser *opt_browser,Fl_Browser *class_browser,Fl_Browser *name_browser){
	debug_out("void populate_groups(Fl_Browser *groups_browser,Fl_Browser *opt_browser,Fl_Browser *class_browser,Fl_Browser *name_browser)");
	int line = groups_browser->value();
	opt_browser->clear();
	class_browser->clear();
	name_browser->clear();
	if ((line == 0) || (line > groups_browser->size())){return;}
	else{
		populateFLBrowser(class_browser,"Group","Class",line);
		populateFLBrowser(opt_browser,"Group","Option",line);
		populateFLBrowser(name_browser,"Group","Name",line);
	}
}

void set_border_color(Fl_Widget *o, int Active1_Inactive2){
	debug_out("void set_border_color(Fl_Widget *o, int Active1_Inactive2)");
	int c;
	double* colors = choose_a_color(c,o);
	std::string current;
	unsigned int theANS=0;
	std::string OUT="Outline";
	std::string thisCOLOR=colorToString(colors);
	if(c!=0){
		if (Active1_Inactive2==1){
			setElementText("WindowStyle","Active",OUT,thisCOLOR);
			current = getElementText("WindowStyle","Active",OUT);
		}
		else{
			setElementText("WindowStyle",OUT,thisCOLOR);
			current = getElementText("WindowStyle",OUT);
		}
		theANS=flCOLOR(current);
		o->color(theANS);
		o->redraw();
	}
}

void set_font_color(Fl_Widget *o, int Active1_Inactive2){
	debug_out("void set_font_color(Fl_Widget *o, int Active1_Inactive2)");
	int c;
	double* colors = choose_a_color(c,o);
	unsigned int theANS=0;
	std::string current;
	bool ans=false;
	if(c!=0){
		std::string newORold;
		if(newStyle() !=-1){newORold="Foreground";}
		else{newORold="Text";}
		if(Active1_Inactive2==1){
			std::string tmp=colorToString(colors);
			ans=setElementText("WindowStyle","Active",newORold,tmp);
			current = getElementText("WindowStyle","Active",newORold);
		}
		else{
			std::string tmp=colorToString(colors);
			ans=setElementText("WindowStyle",newORold,tmp);
			current = getElementText("WindowStyle",newORold);
			
		}
	}
	if(!ans){
		debug_out("set font color FAILED");
		return;
	}
	theANS=flCOLOR(current);
	o->color(theANS);
	o->redraw();
}
unsigned int set_title_color(Fl_Widget *o, int Active1_Inactive2,int First1_or_Second2){
	debug_out("");
	bool ans=false;
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){
		debug_out("Color chooser failed?!?!");
		//return;
	}
	std::string colorSet,ORGcolor,ORGcolorFULLString,stringColor;
	if(Active1_Inactive2 ==1){
		if(newStyle() !=-1){ORGcolorFULLString = getElementText("WindowStyle","Active","Background");}
		else{ORGcolorFULLString = getElementText("WindowStyle","ActiveBackground");}
	}
	else{ORGcolorFULLString = getElementText("WindowStyle","Background");}
	ORGcolor=splitColor(First1_or_Second2,ORGcolorFULLString);
	stringColor=linuxcommon::color_double_to_string(colors);
	std::string RESULT=linuxcommon::remove_cruft(ORGcolorFULLString,ORGcolor);
	if(RESULT.compare("")!=0){
		std::string colon;
		unsigned int finCOLON=RESULT.find(":");
		if(finCOLON>RESULT.length()){colon=":";}
		if(First1_or_Second2==1){RESULT=stringColor+colon+RESULT;}
		else{RESULT=RESULT+colon+stringColor;}
	}
	else{RESULT=stringColor;}
	debug_out("OLD:"+ORGcolorFULLString+"\nNEW:"+RESULT);
	if(Active1_Inactive2 ==1){
		if(newStyle() !=-1){
			ans=setElementText("WindowStyle","Active","Background",RESULT);
			colorSet = getElementText("WindowStyle","Active","Background");
		}
		else{
			ans=setElementText("WindowStyle","ActiveBackground",RESULT);
			colorSet = getElementText("WindowStyle","ActiveBackground");
		}
	}
	else{
		ans=setElementText("WindowStyle","Background",RESULT);
		colorSet = getElementText("WindowStyle","Background");
	}
	if(!ans){debug_out("Did not save the changes!!!!");}
	return splitColor(colorSet,First1_or_Second2);
}
void set_one_title_color(Fl_Widget *o,  int Active1_Inactive2){
	debug_out("void set_one_title_color(Fl_Widget *o,  int Active1_Inactive2)");
	unsigned int c=set_title_color(o,Active1_Inactive2,1);
	o->color(c);
	o->redraw();
}
void set_one_title_color(Fl_Widget *o, int Active1_Inactive2, Fl_Widget* max_a_image, Fl_Widget* max_image, Fl_Widget* min_image, Fl_Widget* close_image){
	debug_out("void set_one_title_color(Fl_Widget *o, int Active1_Inactive2, Fl_Widget* max_a_image, Fl_Widget* max_image, Fl_Widget* min_image, Fl_Widget* close_image)");
	unsigned int c=set_title_color(o,Active1_Inactive2,1);
	get_button(max_a_image,"ButtonMaxActive",o);
	get_button(max_image,"ButtonMax",o);
	get_button(min_image,"ButtonMin",o);
	get_button(close_image,"ButtonClose",o);
	o->color(c);
	o->redraw();
}

void set_opacity(Fl_Slider *o, Fl_Value_Input *o2, int Active1_or_Inactive2){
	debug_out("void set_opacity(Fl_Slider *o, Fl_Value_Input *o2, int Active1_or_Inactive2)");
	double opac=o->value();
	double* opacity=&opac;
	if (Active1_or_Inactive2==1){setElementFloat("WindowStyle","Active","Opacity",opacity);}
	else{setElementFloat("WindowStyle","Opacity",opacity);}
	o2->value(opac*100);
}

void set_two_title_colors(Fl_Widget *o, int Active1_Inactive2){
	debug_out("void set_two_title_colors(Fl_Widget *o, int Active1_Inactive2)");
	unsigned int c=set_title_color(o,Active1_Inactive2,2);
	o->color(c);
	o->redraw();
}

void setThing(std::string thing,std::string mode){
	debug_out("void setThing(std::string "+thing+",std::string "+mode+")");
	setElementText(thing,mode);
}

void setThings(std::string thing,std::string mode,int &distance){
	debug_out("void setThings(std::string "+thing+",std::string "+mode+",int &distance)");
	setElementText(thing,mode);
	setSnap(distance);
}

bool setSnap(int &distance){
	debug_out("bool setSnap(int &distance)");
	const char* conversion=convert(distance);
	if(conversion==NULL){return false;}
	return setElementAttribute("SnapMode","distance",conversion);
}

void title_bar_modifier(Fl_Slider *o1, Fl_Value_Output *o2){
	debug_out("void title_bar_modifier(Fl_Slider *o1, Fl_Value_Output *o2)");
	int slider = o1->value();
	o2->value(slider);
	bool ans=setElementInt("WindowStyle","Height",slider);
	if(!ans){debug_out("title bar modifier FAILED");}
}

void title_bar_modifier(Fl_Slider *o1, Fl_Value_Input *o2, int change_o1_or_o2){
	int whichone = 0;
	if(change_o1_or_o2==1){
		int input = o2->value();
		o1->value(input);
		whichone = input;
	}
	else{
		int slider = o1->value();
		o2->value(slider);
		whichone = slider;
	}
	bool ans=setElementInt("WindowStyle","Height",whichone);
	if(!ans){debug_out("title bar modifier FAILED");}
}

void removeGroup(int hidethis){
	removeElement(hidethis,"Group");
}

void removeGroupTHING(int hidethis, std::string value,std::string THING){
	removeElement(hidethis,"Group",THING,value);
}

void XminusG(Fl_Browser *groups_browser){
	int hidethis = groups_browser->value();
	if ((hidethis == 0) || (hidethis > groups_browser->size())){return;}
	else{
		removeGroup(hidethis);
		getGroups(groups_browser);
	}
}

void XplusG(Fl_Browser *groups_browser){
	addGroup();
	getGroups(groups_browser);
}

bool Xminus(Fl_Browser *groups_browser, Fl_Browser *opt_browser, std::string THING){
	if(THING.compare("")==0){return false;}
	int hidethis = groups_browser->value();
	if ((hidethis == 0) || (hidethis > groups_browser->size())){return false;}
	else{
		int testthis = opt_browser->value();
		if ((testthis == 0) ||
		(testthis > opt_browser->size())){return false;}
		else{
			const char* value = opt_browser->text(testthis);
			if(value==NULL){return false;}
			std::string test=value;
			if(test.compare("")==0){return false;}
			removeGroupTHING(hidethis,value,THING);
			return true;
		}
	}
	return false;
}

bool Xplus(Fl_Browser *groups_browser){
  int hidethis = groups_browser->value();
  if ((hidethis == 0) || (hidethis > groups_browser->size())){return false;}
  return true;
}

std::string XplusO(Fl_Browser *groups_browser){
	int hidethis = groups_browser->value();
	if ((hidethis == 0) || (hidethis > groups_browser->size())){return "";}
	else{
		const char* value = groups_browser->text(hidethis);
		if(value==NULL){return "";}
		std::string test=value;
		if(test.compare("")==0){return "";}
		return test;
	}
	return "";
}
void choose_button(std::string whichButton){
	debug_out("void choose_button(std::string "+whichButton+")");
	std::string label = "Choose ";
	label += whichButton;
	std::string tempPath = buttonPath();
	if(tempPath.compare("")==0){
		std::cerr<<"Button Path not found... must exit!!"<<std::endl;
		return;
	}
	std::string ICON=choose_an_icon(tempPath);
	if(ICON.compare("")!=0){setElementText(whichButton, ICON);}
}
void add_prog(Fl_Browser *groups_browser,std::string input){return add_thingie(groups_browser,input,"Name");}
void add_class(Fl_Browser *groups_browser,std::string input){return add_thingie(groups_browser,input,"Class");}
bool XminusO(Fl_Browser *groups_browser, Fl_Browser *opt_browser){return Xminus(groups_browser,opt_browser,"Option");}
bool XminusN(Fl_Browser *groups_browser,Fl_Browser *opt_browser){return Xminus(groups_browser,opt_browser,"Name");}
bool XminusC(Fl_Browser *groups_browser,Fl_Browser *opt_browser){return Xminus(groups_browser,opt_browser,"Class");}
bool XplusN(Fl_Browser *groups_browser){return Xplus(groups_browser);}
bool XplusC(Fl_Browser *groups_browser){return Xplus(groups_browser);}
