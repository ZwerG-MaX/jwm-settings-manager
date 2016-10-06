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
#include "../include/desktop.hpp"
//Void//////////////////////////////////////////////////////////////////
void background(Fl_Box*o,std::string thisBG){
	debug_out("void background(Fl_Box*o,std::string "+thisBG+")");
	std::string bg;
	if (thisBG.compare("")==0){
		bg=getBackground();
		thisBG=bg;
	}
	else{bg=thisBG;}
	if (isImage(bg)){
		makeWidgetIcon(bg,o,354,270);
		o->show();
		o->redraw();
	}
	else{o->hide();}
}
void background1(Fl_Box*o,std::string thisBG){
	debug_out("void background1(Fl_Box*o,std::string "+thisBG+")");
	std::string bg;
	if (thisBG.compare("")==0){
		bg =getBackground();
		if(bg.length()<=4){return;}
		thisBG=bg;
	}
	else{bg=thisBG;}
	if(isColor(thisBG)){
		unsigned int junk=0;
		unsigned int colorSet = flCOLOR(thisBG,junk);
		o->color(colorSet);
	}
	else{
		o->hide();
		return;
	}
}
void background2(Fl_Box*o,std::string thisBG){
	debug_out("void background1(Fl_Box*o,std::string "+thisBG+")");
	std::string bg;
	if (thisBG.compare("")==0){
		bg =getBackground();
		if(bg.length()<=4){return;}
		thisBG=bg;
	}
	else{bg=thisBG;}
	if(isColor(thisBG)){
		unsigned int colorSet = 0;
		unsigned int c=flCOLOR(thisBG,colorSet);
		if(c!=0){c=0;}
		o->color(colorSet);
	}
	else{
		o->hide();
		return;
	}
}
void bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Output *current_bg,Fl_Box *color_display1,Fl_Box *color_display2){
	debug_out("void bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Box *current_bg,Fl_Box *color_display1,Fl_Box *color_display2)");
	std::string background = linuxcommon::home_path();
	background +="Pictures/";
	std::string title=gettext("Choose a Background");
	std::string result = nativeFileDialog(title,background,"*.{jpg,JPG,png,PNG}");
	if(result.compare("")!=0){
		if(isImage(result)){
			current_bg->value(result.c_str());
			std::string type="image";
			setBackground(type,result);
			makeWidgetIcon(result,background_displayer_thingie,354,270);
			color_display1->hide();
			color_display2->hide();
		}
		else{return;}
	}
}
void bg_name(Fl_Output *o,std::string thisBG){
	debug_out("void bg_name(Fl_Output *o,std::string "+thisBG+")");
	std::string bg;
	if (thisBG.compare("")==0){
		bg=getBackground();
		if(bg.length()<=1){
			o->value("");
			return;
		}
	}
	else{bg=thisBG;}
	if(isColor(bg)){
		std::string tester=splitColor(2,bg);
		std::string title;
		if(tester.compare("")==0){title=gettext("Solid Color");}
		else{title=gettext("Color Gradient");}
		o->value(title.c_str());
	}
	else{o->value(bg.c_str());}
}
void num_desktop_wh_cb(std::string whichone, int value,Fl_Value_Input* num_desktop_w,Fl_Value_Input* num_desktop_h, Fl_Check_Button* check){
	debug_out("void num_desktop_wh_cb(std::string "+whichone+", int value)");
	setElementAttribute("Desktops",whichone,linuxcommon::convert_num_to_string(value));
	int w = int((num_desktop_w->value()));
	int h = int((num_desktop_h->value()));
	std::string num="1";
	if(w==0){setElementAttribute("Desktops","width",num);}
	if(h==0){setElementAttribute("Desktops","height",num);}
	if((w>1)||(h>1)){check->value(1);}
	else{check->value(0);}
}
void one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg){
	debug_out("void one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg)");
	int c;
	double* colors = choose_a_color(c,color_display1);
	if(c!=0){ //If color chooser isn't canceled... do stuff
		unsigned int unusedColor=0;
		unsigned int colorSet=0;
		setBackground("solid",colorToString(colors));
		std::string bg=getBackground();
		colorSet=flCOLOR(bg,unusedColor);
		color_display1->color(colorSet);
		color_display1->show();
		color_display2->hide();
		background_displayer_thingie->hide();
		current_bg->value("Color");
		std::string BG=getBackground();
		background(background_displayer_thingie,BG);
		background1(color_display1,BG);
		background2(color_display2,BG);
	}
}
void setFMBackground(std::string type, std::string wallpaper){
	debug_out("void setFMBackground(std::string "+type+", std::string "+wallpaper+")");
	std::string current = whichFileManager();
	std::string desktopCOMMAND,desktopCOMMAND2,picture;
	if(!linuxcommon::program_is_running(current)){return;}
	std::string gsett="gsettings set org.gnome.desktop.background ";
	std::string gset1=gsett;
	std::string gset2=gsett;
	bool gsettings=false;
	bool gradient=false;
	bool solid=false;
    std::string terminalCommand;
    if (current.compare("pcmanfm")==0){
		desktopCOMMAND= "pcmanfm --wallpaper-mode=stretch --set-wallpaper=";
	}
    else if((current.compare("thunar")==0)||(current.compare("nautilus")==0)){
		desktopCOMMAND=gsett;
		gsettings=true;
		
	}
	else{
		//TODO support more eventually??
		return;
	}
	if(type.compare("image")==0){
		//TODO: gsettings picture-options
		//gsettings range org.gnome.desktop.background picture-options
		//ALSO pcmanfm picture options... at some point
		wallpaper=linuxcommon::fix_file_path_for_command_line(wallpaper);
		picture=wallpaper;
		terminalCommand=desktopCOMMAND+picture;
	}
	else if(type.compare("solid")==0){
		solid=true;
		std::string temp=splitColor(1,wallpaper);
		if(gsettings){
			std::string mod;
			if(temp.compare("")!=0){mod="primary-color "+temp;}
			if(mod.compare("")!=0){desktopCOMMAND=gset1+mod;}
			terminalCommand=desktopCOMMAND;
		}
		else if (current.compare("pcmanfm")==0){
			svgGradient(wallpaper);
			std::string tmpHOME=linuxcommon::home_path();
			terminalCommand=desktopCOMMAND+tmpHOME+"gradient.svg";
			
		}
		else{debug_out("Unsupported Filemanager");}
	}
	else if(type.compare("gradient")==0){
		gradient=true;
		if(gsettings){
			std::string temp=splitColor(1,wallpaper);
			std::string mod;
			if(temp.compare("")!=0){mod="primary-color "+temp;}
			if(mod.compare("")!=0){desktopCOMMAND=gset1+mod;}
			mod="";
			temp=splitColor(2,wallpaper);
			if(temp.compare("")!=0){mod="secondary-color "+temp;}
			if(mod.compare("")!=0){desktopCOMMAND2=gset2+mod;}
			terminalCommand=desktopCOMMAND;
		}
		else if(current.compare("pcmanfm")==0){
			svgGradient(wallpaper);
			std::string tmpHOME=linuxcommon::home_path();
			terminalCommand=desktopCOMMAND+tmpHOME+"gradient.svg";
		}
		else{debug_out("Unsupported Filemanager");}
	}
	std::string TMPterminalCommand;
	if(solid){
		if(gsettings){
			TMPterminalCommand=gsett+"picture-uri file://"+picture;
			if(linuxcommon::run_a_program(TMPterminalCommand)!=0){errorOUT("Couldn't set the wallpaper to blank");}
		}
	}
	if(gradient){
		if(gsettings){
			TMPterminalCommand=desktopCOMMAND2;
			if(linuxcommon::run_a_program(TMPterminalCommand)!=0){errorOUT("Couldn't set the secondary color");}
		}
	}
	if(terminalCommand.compare("")==0){
		debug_out("Empty Terminal Command in one_color... might be what is intended");
		return;
	}
    if(linuxcommon::run_a_program(terminalCommand)!=0){errorOUT("Couldn't set the wallpaper using:"+terminalCommand);}
}
void svgGradient(std::string color){
	debug_out("void svgGradient(std::string "+color+")");
//see the other version below for more detailed explanation
//basically it just makes an svg file with a rectangle the size of the screen and the color we send it
    std::string result;
    //get the screen width from FLTK for the width
	std::string width = convert(Fl::w());
	//get the screen height from FLTK for the height
	std::string height = convert(Fl::h());
	unsigned int found=color.find(":");
    if(found<color.length()){
	  //TWO COLOR
	    std::string color1=splitColor(1,color);
	    std::string color2=splitColor(2,color);;
	    debug_out("Color1="+color1+"\nColor2="+color2);
		std::string svgHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
    <svg>\n\
       <defs>\n\
	    <linearGradient id = \"g1\" x1 = \"50%\" y1 = \"0%\" x2 = \"50%\" y2 = \"100%\">\n\
            <stop stop-color = \"";
            //colorToString(color) will go here for the first color
		std::string svg1 = "\" offset = \"0%\"/>\n\
            <stop stop-color = \"";
            //colorToString(color2) will go here for the second color
		std::string svg2 = "\" offset = \"50%\"/>\n\
        </linearGradient>\n\
    </defs>\n\
    <rect x=\"0\" y=\"0\" width=\"";
		std::string svg3 = "\" height=\"";
		//fill the rect(angle) with the url of #g1... this is the linear gradient id above in the header
		std::string svgFooter="\" fill=\"url(#g1)\" />\n\
    </svg>";
		//put it all together
		result = svgHeader+color1+svg1+color2+svg2+width+svg3+height+svgFooter;
	}
	else {
		std::string svgHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
    <svg>\n\
    <rect x=\"0\" y=\"0\" width=\"";
		std::string svg2 = "\" height=\"";
		std::string svg3 = "\" fill=\"";
		std::string svgFooter="\" />\n\
    </svg>";
		result = svgHeader + width+svg2+height+svg3+color+svgFooter;
	}
    std::cout<<result<<std::endl;
    std::string SVGpath = linuxcommon::home_path();
    SVGpath += "gradient.svg";
    std::ofstream out( SVGpath.c_str() );
    if (!out.fail()){
        out<<result;
        setBackground("scale",SVGpath.c_str());
    }
}
void two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg){
	debug_out("void two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg)");
	int c=0;
	int c2=0;
	std::string thisColor;
	double* gradient1 = choose_a_color(c,color_display1);
	if(c!=0){ //If color chooser isn't canceled... do stuff
		double* gradient2 = choose_a_color(c2,color_display1);
		if(c2!=0){ //If color chooser isn't canceled... do stuff
			std::string c1=colorToString(gradient1);
			std::string c2=colorToString(gradient2);
			unsigned int color2=0;
			thisColor=c1+":"+c2;
			unsigned int color1=flCOLOR(thisColor,color2);
			setBackground("gradient",thisColor);
			color_display1->color(color1);
			color_display2->color(color2);
			color_display1->show();
			color_display2->show();
			background_displayer_thingie->hide();
			color_display1->redraw();
			color_display2->redraw();
			debug_out("Color gradient:"+thisColor);
			current_bg->value("Color Gradient");
			std::string BG=getBackground();
			background(background_displayer_thingie,BG);
			background1(color_display1,BG);
			background2(color_display2,BG);
		}
	}
}
void useMultipleDesktops(Fl_Value_Input *num_desktop_w,Fl_Value_Input *num_desktop_h){
	debug_out("void useMultipleDesktops(Fl_Value_Input *num_desktop_w,Fl_Value_Input *num_desktop_h)");
	if(!multipleDesktops()){
		int width = int((num_desktop_w->value()));
		int height = int((num_desktop_h->value()));
		if (width == 1 && height ==1 ){width =2;}
		std::string num=linuxcommon::convert_num_to_string(width);
		setElementAttribute("Desktops","width",num);
		num=linuxcommon::convert_num_to_string(height);
		setElementAttribute("Desktops","height",num);
	}
	else{
		setElementAttribute("Desktops","width","1");
		setElementAttribute("Desktops","height","1");
		num_desktop_w->value(1);
		num_desktop_h->value(1);
	}
}
//Boolean///////////////////////////////////////////////////////////////
bool icons_on_desktop(){
	debug_out("int icons_on_desktop()");
  //1 is on 0 is off
  std::string fm;
//FIXME//
whichFileManagerRunning();
	
  if(fm.compare("unkown")!=0 ){return 1;}
  return 0;
}
bool filemanagerRunning(){return filemanagerRunning(whichFileManager());}
bool filemanagerRunning(std::string filemanagerToCheck){
	debug_out("bool filemanagerRunning(std::string "+filemanagerToCheck+")");
	if(filemanagerToCheck.compare("")==0){return false;}
	return linuxcommon::program_is_running(filemanagerToCheck);
	if(false){
		//this is pointless but I am still saving the code
	}
	else{
		std::string thisThingie;
		std::vector<std::string> StartupCommands;
		StartupCommands=AnythingVector("StartupCommand");
		for( std::vector<std::string>::iterator it2 = StartupCommands.begin();
		it2!=StartupCommands.end();
		++it2){
			thisThingie=*it2;
			if(thisThingie.compare("")!=0){
				unsigned int found=thisThingie.find_first_of(' ');
				if(found<thisThingie.length()){
					std::string tester=thisThingie;
					tester=tester.erase(found,std::string::npos);
					if(tester.compare(filemanagerToCheck)==0){return true;}
				}
				else{
					if(thisThingie.compare(filemanagerToCheck)==0){return true;}
				}
			}
		}
	}
	return false;
}
bool multipleDesktops(){
	debug_out("bool multipleDesktops()");
	int width = getIntAttribute("Desktops","width");
	int height = getIntAttribute("Desktops","height");
	// zero for false and non-zero for true.
	if (height==1 && width ==1){return false;}
	else if (!height || !width){return false;}
	return true;
}
bool setBackground(std::string type,std::string result){
	debug_out("bool setBackground(std::string "+type+",std::string "+result+")");
	if(isImage(result)){type="image";}
	if(isColor(result)){type="solid";}
	if(linuxcommon::test_exec(result)){type="command";}
	//This isn't perfect but will at least catch minor mistakes
	//TODO more thorough checking to help the user
	debug_out("background type is="+type);
	if(type.compare("gradient")==0){
		if(result.find(":")>result.length()){type="solid";}
	}
	else if(type.compare("solid")==0){
		if(result.find(":")<result.length()){
			type="gradient";
		}
	} 
	debug_out("Type="+type);
	if(!setElementAttributeANDtext("Desktops","Background","type",type,result)){
		debug_out("Setting "+result+" as "+type+" image, FAILED");
		return false;
	}
	if(isIconsOnDesktop()){setFMBackground(type,result);}
	return true;
}
bool removeIconsOnDesktop(){
	debug_out("");
	std::string current = whichFileManagerRunning();
	return linuxcommon::pkill(current);
}
bool setIconsOnDesktop(){
	debug_out("bool setIconsOnDesktop()");
    //find out which filemanager is running/autstarted
    std::string current = whichFileManager();
    //get the current wallpaper
    std::string currentWallpaper = getBackground();
    //no need to initialize this with a value, strings do not require this
    std::string desktopCOMMAND;
    //get the bash command started
    std::string execLine = linuxcommon::get_shell_for_C();
    //figure out which one it is, and add the right commands to the bash string
    if (current.compare("pcmanfm")==0){desktopCOMMAND= "pcmanfm --desktop";}
    else if (current.compare("thunar")==0){desktopCOMMAND= "thunar --daemon";}
    else if (current.compare("nautilus")==0){desktopCOMMAND= "nautilus -n";}
    else if (current.compare("rox-filer")==0){desktopCOMMAND= "rox -p";}
    else{return false;}
    //add &disown so we don't wait for it to exit...
    execLine +=desktopCOMMAND;
    execLine +=" &disown'";
    //make sure it isn't running, and start it
    if (!filemanagerRunning()){
        int result = system(execLine.c_str());
        if(result!=0){
			errorOUT("system call did not return 0");
			return false;
		}
        addElementWithText("StartupCommand",desktopCOMMAND);
    }
    //set the background for whatever filemanager is running, if it isn't already
    setFMBackground("image",currentWallpaper);
    return true;
}
bool use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string thisBG){
	debug_out("bool use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string "+thisBG+")");
	if(!isIconsOnDesktop()){
		if(setIconsOnDesktop()){
			background(background_displayer_thingie,thisBG);
		}
		else{errorOUT("Could not set a filemanager to show icons on the desktop");}
	}
	else{
		if(!removeIconsOnDesktop()){errorOUT("Could not kill the filemanager handling Icons");}
	}
	return isIconsOnDesktop();
}
bool isIconsOnDesktop(){
	debug_out("bool isIconsOnDesktop()");
	if(filemanagerRunning()){
		debug_out("File manager IS running");
		return true;
	}
	debug_out("File manager is NOT running");
	return false;
}
//String////////////////////////////////////////////////////////////////
std::string getBackground(){
	debug_out("std::string getBackground()");
	std::string bg,JWMBG;
	JWMBG=getElementText("Desktops","Background");
	if(filemanagerRunning()){
		bg= getFMBackground();
		if(bg.compare("")==0){
			debug_out("No file manager background... using JWM background: "+JWMBG);
			setFMBackground("image",JWMBG);
			return JWMBG;
		}
	}
	if(bg.compare("")!=0){
		if(JWMBG.compare(bg)!=0){
			debug_out("JWM background is not the same as the running file manager... setting it correctly to:"+bg);
			if(!setBackground("image",bg)){debug_out("Didn't correctly set JWM bg to"+bg);}
		}
	}
	else{
		debug_out("JWM is running without a (supported) filemanager to handle the desktop");
		bg=JWMBG;
	}
	debug_out("getBackground() found="+bg);
	return bg;
}
std::string whichFileManagerRunning(){
	debug_out("std::string whichFileManagerRunning()");
	std::string fm="";
	std::vector<std::string> fileManagers;
	fileManagers=ListFileManagers();
    for( std::vector<std::string>::iterator it = fileManagers.begin();
		it!=fileManagers.end();
		++it){
		std::string testFM=*it;
		if(testFM.compare("")!=0){
			if(filemanagerRunning(testFM)){return testFM;}
		}
	}
	return fm;
}
std::string whichFileManager(){
	debug_out("std::string whichFileManager()");
	std::string XDGMIME = linuxcommon::term_out("xdg-mime query default inode/directory");
	std::string desktopFile=linuxcommon::find_xdg_data_dir_subdir("applications");
	debug_out("desktop file="+ desktopFile+"\ndirectory="+ XDGMIME);
	desktopFile+=XDGMIME;
	if(!linuxcommon::test_file(desktopFile)){
		std::vector<std::string> fileManagers;
		fileManagers=ListFileManagers();
		for( std::vector<std::string>::iterator it = fileManagers.begin();
			it!=fileManagers.end();
			++it){
			std::string testFM=*it;
			if(linuxcommon::test_exec(testFM)){
				return testFM;
			}
		}
		return "";
	}
	std::string executable=linuxcommon::get_line_with_equal(desktopFile,"Exec=");
	debug_out("Executable="+executable);
	if(executable.compare("")==0){return "";}
	executable=linuxcommon::remove_percentage(executable);
	debug_out("Executable="+executable);
	if(linuxcommon::test_exec(executable)){return executable;}
	return "";
}
std::string getFMBackground(){
	debug_out("std::string getFMBackground()");
	std::string wallpaper,desktopCOMMAND;
	std::string current = whichFileManager();
	if(!linuxcommon::program_is_running(current)){return "";}
	std::string gsett="gsettings get org.gnome.desktop.background picture-uri";
	if (current.compare("pcmanfm")==0){
		std::string pcmanFMfilename = linuxcommon::home_path();
		pcmanFMfilename += ".config/pcmanfm/default/pcmanfm.conf";
		std::string pcmanFMdesktopfilename = linuxcommon::home_path();
		pcmanFMdesktopfilename += ".config/pcmanfm/default/desktop-items-0.conf";
		wallpaper=linuxcommon::get_line_with_equal(pcmanFMdesktopfilename,"wallpaper=");
		if(wallpaper.compare("")==0){
			wallpaper=linuxcommon::get_line_with_equal(pcmanFMfilename,"wallpaper=");
			if(wallpaper.compare("")==0){return "";}
		}
		if(!linuxcommon::test_file(wallpaper)){errorOUT(wallpaper+" is NOT a File");}
		debug_out("pcmanfm bg="+wallpaper);
		return wallpaper;
	}
    else if((current.compare("thunar")==0)||(current.compare("nautilus")==0)){
		desktopCOMMAND=gsett;
	}
    //else if (current.compare("rox-filer")==0){desktopCOMMAND= "rox -p";}
    else{return "";}
    std::string shell=linuxcommon::get_shell_for_C();
    if(shell.compare("")==0){return "";}
    std::string terminalCommand=shell+desktopCOMMAND+"'";
    wallpaper=linuxcommon::term_out(terminalCommand);
    if(wallpaper.compare("")==0){errorOUT("Couldn't get the wallpaper using:"+desktopCOMMAND);}
    debug_out("gsettings bg="+wallpaper);
    return wallpaper;
}
std::vector<std::string> ListFileManagers(){
	debug_out("std::vector<std::string> ListFileManagers()");
	//TODO: support more filemanagers in the future...
	std::vector<std::string> fileManagers;
	fileManagers.push_back("pcmanfm");
	fileManagers.push_back("thunar");
	fileManagers.push_back("nautilus");
	fileManagers.push_back("rox-filer");
	return fileManagers;
}
