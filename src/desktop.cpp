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
/**
 * @file desktop.cpp
 * @author Israel Dahl
 * @date 2015-2017
 *
 * @brief Functions for modifying desktop settings
 *
 */
#include <libintl.h>
#include "../include/desktop.hpp"
///Void//////////////////////////////////////////////////////////////////
void JSM_Desktop::allBGS(Fl_Box* Image, Fl_Box* Color1,Fl_Box* Color2, std::string choice, unsigned int num, Fl_Input *in){
	debug_out("void allBGS(Fl_Box* Image, Fl_Box* Color1,Fl_Box* Color2, std::string "+choice+", unsigned int num, Fl_Input *in)");
	const char* img=in->value();
	if(choice.compare(img)==0){return;}
	background(Image,choice,num);
	background1(Color1,choice,num);
	background2(Color2,choice,num);
	in->value(choice.c_str());
}
//b
/** Set the background image of an Fl_Box*/
void JSM_Desktop::background(Fl_Box*o,std::string thisBG,unsigned int bgnum){
	debug_out("void background(Fl_Box*o,std::string "+thisBG+",unsigned int bgnum)");
	std::string bg;
	/** Check the string and get the background from the jwmrc if it is empty*/
	if (thisBG.compare("")==0){
		bg=getBackground(bgnum);
		thisBG=bg;
	}
	else{bg=thisBG;}
	/** if the string is an image file, make an image of it in the Fl_Box (sizes hard coded here)*/
	if (isImage(bg)){
		makeWidgetIcon(bg,o,354,270);
		if(!o->visible())o->show();
		o->redraw();
	}
	else{
		//if(o->visible())o->hide();
		return;
	}
}
/** Set the Background color of an Fl_Box*/
void JSM_Desktop::background1(Fl_Box*o,std::string thisBG,unsigned int bgnum){
	debug_out("void background1(Fl_Box*o,std::string "+thisBG+",unsigned int bgnum)");
	std::string bg;
	/** Check the string and get the background from the jwmrc if it is empty*/
	if (thisBG.compare("")==0){
		bg =getBackground(bgnum);
		/** split the string from the jwmrc into the first color ONLY*/
		bg=splitColor(1,bg);
		if(bg.length()<=4){return;}
		thisBG=bg;
	}
	else{bg=thisBG;}
	/** Check if it is a color and make the Fl_Box that color*/
	if(isColor(thisBG)){
		unsigned int junk=0;
		unsigned int colorSet = flCOLOR(thisBG,junk);
		if(!o->visible())o->show();
		o->color(colorSet);
	}
	else{
		if(o->visible())o->hide();
		return;
	}
}
/** Set the Background color of an Fl_Box*/
void JSM_Desktop::background2(Fl_Box*o,std::string thisBG,unsigned int bgnum){
	debug_out("void background1(Fl_Box*o,std::string "+thisBG+",unsigned int bgnum)");
	std::string bg;
	/** Check the string and get the background from the jwmrc if it is empty*/
	if (thisBG.compare("")==0){
		bg =getBackground(bgnum);
		/** split the string from the jwmrc into the second color ONLY*/
		bg=splitColor(2,bg);
		if(bg.length()<=4){return;}
		thisBG=bg;
	}
	else{bg=thisBG;}
	/** Check if it is a color and make the Fl_Box that color*/
	if(isColor(thisBG)){
		unsigned int colorSet = 0;
		unsigned int c=flCOLOR(thisBG,colorSet);
		if(c!=0){c=0;}
		if(!o->visible())o->show();
		o->color(colorSet);
	}
	else{
		if(o->visible())o->hide();
		return;
	}
}
/** Open a file dialog to pick an image*/
void JSM_Desktop::bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Output *current_bg,Fl_Box *color_display1,Fl_Box *color_display2,unsigned int bgnum){
	debug_out("void bg_chooser_cb(Fl_Box *background_displayer_thingie,Fl_Box *current_bg,Fl_Box *color_display1,Fl_Box *color_display2,unsigned int bgnum)");
	std::string background = linuxcommon::home_path();
	background +="Pictures/";
	std::string title=gettext("Choose a Background");
	std::string result = nativeFileDialog(title,background,"*.{jpg,JPG,png,PNG}");
	if(result.compare("")!=0){
		if(isImage(result)){
			current_bg->value(result.c_str());
			std::string type="image";
			setBackground(type,result,bgnum);
			makeWidgetIcon(result,background_displayer_thingie,354,270);
			color_display1->hide();
			color_display2->hide();
		}
		else{return;}
	}
}
/**Get the filename OR display text describing the background type*/
void JSM_Desktop::bg_name(Fl_Output *o,std::string thisBG,unsigned int bgnum){
	debug_out("void bg_name(Fl_Output *o,std::string "+thisBG+")");
	std::string bg;
	/** Check the string and get the background from the jwmrc if it is empty*/
	if (thisBG.compare("")==0){
		bg=getBackground(bgnum);
		/** if it is empty or too small clear the output and return*/
		if(bg.length()<=1){
			o->value("");
			return;
		}
	}
	else{bg=thisBG;}
	/** if it is a color decide if it is one or two colors, otherwise just put the value in the output*/
	if(isColor(bg)){
		std::string tester=splitColor(2,bg);
		std::string title;
		if(tester.compare("")==0){title=gettext("Solid Color");}
		else{title=gettext("Color Gradient");}
		o->value(title.c_str());
	}
	else{o->value(bg.c_str());}
}
//n
/** set value for the number of desktops wide or high then make sure it is at least 1 If there are more than 1 each turn on the check button*/
void JSM_Desktop::num_desktop_wh_cb(std::string whichone, int value,Fl_Value_Input* num_desktop_w,Fl_Value_Input* num_desktop_h, Fl_Check_Button* check){
	debug_out("void num_desktop_wh_cb(std::string "+whichone+", int value)");
	/** set the attribute here*/
	setElementAttribute("Desktops",whichone,linuxcommon::convert_num_to_string(value));
	int w = int((num_desktop_w->value()));
	int h = int((num_desktop_h->value()));
	std::string num="1";
	/** check to make sure we have sane values, or fix them*/
	if(w==0){
		setElementAttribute("Desktops","width",num);
		num_desktop_w->value(1);
	}
	if(h==0){
		setElementAttribute("Desktops","height",num);
		num_desktop_h->value(1);
	}
	/** make the check button show a good value*/
	if((w>1)||(h>1)){check->value(1);}
	else{check->value(0);}
}
//o
/** Choose a single color and save it to the file*/
void JSM_Desktop::one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum){
	debug_out("void one_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum)");
	int c;
	/** open the color chooser dialog*/
	double* colors = choose_a_color(c,color_display1);
	if(c!=0){
		/**If color chooser isn't canceled... do stuff*/
		unsigned int unusedColor=0;
		unsigned int colorSet=0;
		setBackground("solid",colorToString(colors),bgnum);
		std::string bg=getBackground(bgnum);
		colorSet=flCOLOR(bg,unusedColor);
		color_display1->color(colorSet);
		color_display1->show();
		color_display2->hide();
		background_displayer_thingie->hide();
		current_bg->value("Color");
		std::string BG=getBackground(bgnum);
		background(background_displayer_thingie,BG,bgnum);
		background1(color_display1,BG,bgnum);
		background2(color_display2,BG,bgnum);
	}
}
//s
/**Set the background of the filemanager to match the jwmrc*/
void JSM_Desktop::setFMBackground(std::string type, std::string wallpaper){
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
    /** figure out what filemanager it is*/
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
	/** figure out what type of background it is*/
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
			svgGradient(wallpaper,1);
			std::string tmpHOME=linuxcommon::home_path();
			terminalCommand=desktopCOMMAND+tmpHOME+"gradient.svg";
			
		}
		else{debug_out("Unsupported Filemanager");}
	}
	else if(type.compare("gradient")==0){
		gradient=true;
		/** if using a gsettings filemanager set it */
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
		/** if using pcmanfm make an svg for the gradient*/
		else if(current.compare("pcmanfm")==0){
			svgGradient(wallpaper,1);
			std::string tmpHOME=linuxcommon::home_path();
			terminalCommand=desktopCOMMAND+tmpHOME+"gradient.svg";
		}
		else{debug_out("Unsupported Filemanager");}
	}
	std::string TMPterminalCommand;
	/** if it is solid color and gsettings set the svg as the BG*/
	if(solid){
		if(gsettings){
			TMPterminalCommand=gsett+"picture-uri file://"+picture;
			if(linuxcommon::run_a_program(TMPterminalCommand)!=0){errorOUT("Couldn't set the wallpaper to blank");}
		}
	}
	/** if it is solid color and gsettings set the gradient as the BG*/
	if(gradient){
		if(gsettings){
			TMPterminalCommand=desktopCOMMAND2;
			if(linuxcommon::run_a_program(TMPterminalCommand)!=0){errorOUT("Couldn't set the secondary color");}
		}
	}
	/** if this is empty return*/
	if(terminalCommand.compare("")==0){
		debug_out("Empty Terminal Command in one_color... might be what is intended");
		return;
	}
	/** set the background by running the command, and show an error if things fail*/
    if(linuxcommon::run_a_program(terminalCommand)!=0){errorOUT("Couldn't set the wallpaper using:"+terminalCommand);}
}
/** create an SVG file of a color/colors and then set it as the background*/
void JSM_Desktop::svgGradient(std::string color,unsigned int bgnum){
	debug_out("void svgGradient(std::string "+color+",unsigned int bgnum)");
/**This just makes an svg file with a rectangle the size of the screen and the color(s) we send it*/
    std::string result;
    /**get the screen width from FLTK for the width*/
	std::string width = convert(Fl::w());
	/**get the screen height from FLTK for the height*/
	std::string height = convert(Fl::h());
	unsigned int found=color.find(":");
    if(found<color.length()){
	  /**TWO COLOR*/
	    std::string color1=splitColor(1,color);
	    std::string color2=splitColor(2,color);;
	    debug_out("Color1="+color1+"\nColor2="+color2);
		std::string svgHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
    <svg>\n\
       <defs>\n\
	    <linearGradient id = \"g1\" x1 = \"50%\" y1 = \"0%\" x2 = \"50%\" y2 = \"100%\">\n\
            <stop stop-color = \"";
            /**colorToString(color) will go here for the first color*/
		std::string svg1 = "\" offset = \"0%\"/>\n\
            <stop stop-color = \"";
            /**colorToString(color2) will go here for the second color*/
		std::string svg2 = "\" offset = \"50%\"/>\n\
        </linearGradient>\n\
    </defs>\n\
    <rect x=\"0\" y=\"0\" width=\"";
		std::string svg3 = "\" height=\"";
		/**fill the rect(angle) with the url of #g1... this is the linear gradient id above in the header*/
		std::string svgFooter="\" fill=\"url(#g1)\" />\n\
    </svg>";
		/**put it all together*/
		result = svgHeader+color1+svg1+color2+svg2+width+svg3+height+svgFooter;
	}
	else {
		/** ONE COLOR*/
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
        setBackground("scale",SVGpath.c_str(),bgnum);
    }
}
//t
/** The two color chooser*/
void JSM_Desktop::two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum){
	debug_out("void two_color(Fl_Box *color_display1,Fl_Box *color_display2,Fl_Box *background_displayer_thingie,Fl_Output *current_bg,unsigned int bgnum)");
	int c=0;
	int c2=0;
	std::string thisColor;
	/** choose the first color in a dialog*/
	double* gradient1 = choose_a_color(c,color_display1);
	if(c!=0){ /**If color chooser isn't canceled... choose the second color in a dialog*/
		double* gradient2 = choose_a_color(c2,color_display1);
		if(c2!=0){ /**If color chooser isn't canceled... set the colors*/
			std::string c1=colorToString(gradient1);
			std::string c2=colorToString(gradient2);
			unsigned int color2=0;
			thisColor=c1+":"+c2;
			unsigned int color1=flCOLOR(thisColor,color2);
			setBackground("gradient",thisColor,bgnum);
			color_display1->color(color1);
			color_display2->color(color2);
			color_display1->show();
			color_display2->show();
			background_displayer_thingie->hide();
			color_display1->redraw();
			color_display2->redraw();
			debug_out("Color gradient:"+thisColor);
			current_bg->value("Color Gradient");
			std::string BG=getBackground(bgnum);
			background(background_displayer_thingie,BG,bgnum);
			background1(color_display1,BG,bgnum);
			background2(color_display2,BG,bgnum);
		}
	}
}
//u
/** Toggle the multiple desktops... if we are using them, make it so we are not
 * If we are not using them, add one to the right*/
void JSM_Desktop::useMultipleDesktops(Fl_Value_Input *num_desktop_w,Fl_Value_Input *num_desktop_h){
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


///Boolean///////////////////////////////////////////////////////////////
//f
/** check if the default filemanager is running*/
bool JSM_Desktop::filemanagerRunning(){return filemanagerRunning(whichFileManager());}
/** check a specific filemanager to see if it is running*/
bool JSM_Desktop::filemanagerRunning(std::string filemanagerToCheck){
	debug_out("bool filemanagerRunning(std::string "+filemanagerToCheck+")");
	/** if no filemanager came in return false*/
	if(filemanagerToCheck.compare("")==0){return false;}
	/**Check to see if the program is actually running*/
	return linuxcommon::program_is_running(filemanagerToCheck);
	//This stuff used to be the check... but now I use the above...
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
/** open the filemanager's preferences dialog*/
bool JSM_Desktop::filemanagerPreferences(){
	std::string command;
	std::string FM=whichFileManager();
	command=FM;
	/**AFAIK pcmanfm is the only one that has a specific option*/
	if(FM.compare("pcmanfm")==0){command+=" --desktop-pref";}
	/** naulitus is a bit annoying controlling the desktop.. so just in case, lets avoid it*/
	else if(FM.compare("nautilus")==0){command+=" -n";}
	int retval=linuxcommon::run_a_program_in_background(command);
	if (retval!=0)return false;
	return true;
}
//i
/** check to see if a filemanager is running*/
bool JSM_Desktop::icons_on_desktop(){
	debug_out("int icons_on_desktop()");
  /**1 is on 0 is off*/
  std::string fm=whichFileManagerRunning();
  /** make sure we know the filemanager and actually have something*/
  if((fm.compare("unkown")!=0)&&
     (fm.compare("")!=0)){return 1;}
  /** If we don't know OR there is nothing return 0*/
  return 0;
}
/** a better function... just check if the filemanager is running*/
bool JSM_Desktop::isIconsOnDesktop(){
	debug_out("bool isIconsOnDesktop()");
	if(filemanagerRunning()){
		debug_out("File manager IS running");
		return true;
	}
	debug_out("File manager is NOT running");
	return false;
}
//m
/** check to see if multiple desktops exist*/
bool JSM_Desktop::multipleDesktops(){
	debug_out("bool multipleDesktops()");
	/** get the attributes*/
	int width = getIntAttribute("Desktops","width");
	int height = getIntAttribute("Desktops","height");
	/**zero for false and non-zero for true.*/
	if (height==1 && width ==1){return false;}
	else if (!height || !width){return false;}
	return true;
}
//r
/** get rid of the filemanager that is running*/
bool JSM_Desktop::removeIconsOnDesktop(){
	debug_out("bool removeIconsOnDesktop()");
	std::string current = whichFileManagerRunning();
	/** remove the current file manager.. might cause issues if there is some other reason the same filemanager is in startup commands*/
	//TODO possibly affix the ending, or look for both fm and ending using hazy search?
	removeElementHazy("StartupCommand",current);
	/** kill the current file manager*/
	return linuxcommon::pkill(current);
}
//s
/** set the background in the jwmrc, and possibly filemanager*/
bool JSM_Desktop::setBackground(std::string type,std::string result,unsigned int bgnum){
	debug_out("bool setBackground(std::string "+type+",std::string "+result+",unsigned int bgnum)");
	/** get a good decent attribute based on what is sent in*/
	if(isImage(result)){type="image";}
	if(isColor(result)){type="solid";}
	if(linuxcommon::test_exec(result)){type="command";}
	/**This isn't perfect but will at least catch minor mistakes*/
	//TODO more thorough checking to help the user
	debug_out("background type is="+type);
	/** double check here to make sure the jwmrc gets a good color attribute*/
	if(type.compare("gradient")==0){
		if(result.find(":")>result.length()){type="solid";}
	}
	else if(type.compare("solid")==0){
		if(result.find(":")<result.length()){
			type="gradient";
		}
	} 
	debug_out("Type="+type);
	/** ok, set the attribute now*/
	if(!setElementAttributeANDtext(bgnum,"Desktops","Background","type",type,result)){
		debug_out("Setting "+result+" as "+type+" image, FAILED");
		return false;
	}
	/** if a file manager is running set that background too*/
	if(isIconsOnDesktop()){setFMBackground(type,result);}
	return true;
}
/** make the desktop handled by a filemanager*/
bool JSM_Desktop::setIconsOnDesktop(){
	debug_out("bool setIconsOnDesktop()");
    /**find out which filemanager is existant*/
    std::string current = whichFileManager();
    /**get the current wallpaper*/
    std::string currentWallpaper = getBackground();
    /**no need to initialize this with a value, strings do not require this*/
    std::string desktopCOMMAND;
    /**figure out which one it is, and add the right commands to the bash string*/
    if (current.compare("pcmanfm")==0){desktopCOMMAND= "pcmanfm --desktop";}
    else if (current.compare("thunar")==0){desktopCOMMAND= "thunar --daemon";}
    else if (current.compare("nautilus")==0){desktopCOMMAND= "nautilus -n";}
    else if (current.compare("rox-filer")==0){desktopCOMMAND= "rox -p";}
    else{return false;}
    //make sure it isn't running, and start it*/
    if (!filemanagerRunning()){
		/** run the filemanager in the background*/
        int result = linuxcommon::run_a_program_in_background(desktopCOMMAND);
        if(result!=0){
			errorOUT("system call did not return 0");
			return false;
		}
		/** add the filemanager to startup if needed*/
		if(!elementTextExists("StartupCommand",desktopCOMMAND)){
			addElementWithText("StartupCommand",desktopCOMMAND);
		}
    }
    /**set the background for whatever filemanager is running, if it isn't already*/
    setFMBackground("image",currentWallpaper);
    return true;
}
//u
/**Toggle the icons on the desktop*/
bool JSM_Desktop::use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string thisBG){
	debug_out("bool use_icons_on_desktop(Fl_Box *background_displayer_thingie,std::string "+thisBG+")");
	if(!isIconsOnDesktop()){
		if(setIconsOnDesktop()){
			background(background_displayer_thingie,thisBG,1);
		}
		else{errorOUT("Could not set a filemanager to show icons on the desktop");}
	}
	else{
		if(!removeIconsOnDesktop()){errorOUT("Could not kill the filemanager handling Icons");}
	}
	return isIconsOnDesktop();
}


///String////////////////////////////////////////////////////////////////
/** get the desktop background string*/
std::string JSM_Desktop::getBackground(){return getBackground(1);}
std::string JSM_Desktop::getBackground(unsigned int whichOne){
	debug_out("std::string getBackground(unsigned int whichOne)");
	std::string bg,JWMBG;
	/** get the JWM background*/
	JWMBG=getElementText("Desktops",whichOne,"Desktop","Background");
	if(JWMBG.compare("")==0){JWMBG=getElementText("Desktops","Background");}
	debug_out(JWMBG);
	/** if a filemanager is running get that background*/
	if(filemanagerRunning()){
		bg= getFMBackground();
		if(bg.compare("")==0){
			/** oops... filemanager has no background... better set the JWM background to the filemanager*/
			debug_out("No file manager background... using JWM background: "+JWMBG);
			setFMBackground("image",JWMBG);
			return JWMBG;
		}
	}
	/**Check to see if the filemanager has a background*/
	if(bg.compare("")!=0){
		/** if the backgrounds are different set JWM background to the filemanager... since it is already on top*/
		if(JWMBG.compare(bg)!=0){
			debug_out("JWM background is not the same as the running file manager... setting it correctly to:"+bg);
			if(!setBackground("image",bg,whichOne)){debug_out("Didn't correctly set JWM bg to"+bg);}
		}
	}
	else{
		debug_out("JWM is running without a (supported) filemanager to handle the desktop");
		bg=JWMBG;
	}
	/** return whatever we got*/
	debug_out("getBackground() found="+bg);
	return bg;
}
/** Figure out which filemanager is running*/
std::string JSM_Desktop::whichFileManagerRunning(){
	debug_out("std::string whichFileManagerRunning()");
	std::string fm="";
	std::vector<std::string> fileManagers;
	/** get the nice list of existing file managers*/
	fileManagers=ListFileManagers();
    for( std::vector<std::string>::iterator it = fileManagers.begin();
		it!=fileManagers.end();
		++it){
		std::string testFM=*it;
		if(testFM.compare("")!=0){
			/** is the filemanager running? catch it :P */
			if(filemanagerRunning(testFM)){return testFM;}
		}
	}
	return fm;
}
/** find the default filemanager from xdg-mime, or pick the first in the list*/
std::string JSM_Desktop::whichFileManager(){
	debug_out("std::string whichFileManager()");
	std::string XDGMIME = linuxcommon::term_out("xdg-mime query default inode/directory");
	std::string desktopFile=linuxcommon::find_xdg_data_dir_subdir("applications");
	debug_out("desktop dir="+ desktopFile+"\nMime="+ XDGMIME);
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
/** get the filemanager's background*/
std::string JSM_Desktop::getFMBackground(){
	debug_out("std::string getFMBackground()");
	std::string wallpaper,desktopCOMMAND;
	std::string current = whichFileManager();
	/** well... if the filemanager is not running no need to return its background*/
	if(!linuxcommon::program_is_running(current)){return "";}
	std::string gsett="gsettings get org.gnome.desktop.background picture-uri";
	/** filemanager specific 'getter' code*/
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
		/** if we got a file, return it*/
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
    /** if we get something, return it*/
    if(wallpaper.compare("")==0){errorOUT("Couldn't get the wallpaper using:"+desktopCOMMAND);}
    debug_out("gsettings bg="+wallpaper);
    return wallpaper;
}

///Vector////////////////////////////////////////////////////////////////
/** my list of filemanagers I currently support in vector<string> format*/
std::vector<std::string> JSM_Desktop::ListFileManagers(){
	debug_out("std::vector<std::string> ListFileManagers()");
	//TODO: support more filemanagers in the future...
	std::vector<std::string> fileManagers;
	fileManagers.push_back("pcmanfm");
	fileManagers.push_back("thunar");
	fileManagers.push_back("nautilus");
	fileManagers.push_back("rox-filer");
	return fileManagers;
}
