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
#include "../include/fltkfunctions.hpp"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#define NANOSVG_ALL_COLOR_KEYWORDS  // Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION      // Expands implementation
#include "../include/nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "../include/nanosvgrast.h"
//String////////////////////////////////////////////////////////////////
std::string choose_a_directory(std::string directory, std::string label){
	if(directory.compare("")==0){directory=linuxcommon::home_path();}
	if(label.compare("")==0){label = gettext("Choose Directory");}
	Fl_Native_File_Chooser fnfc;
	fnfc.title(label.c_str());
	fnfc.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
	fnfc.directory(directory.c_str());
	std::string String;
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			debug_out("Error in directory chooser");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				String = result;
				return String;
			}
	}
	return "";
}
std::string choose_a_directory_to_save(std::string directory, std::string label){
	if(directory.compare("")==0){directory=linuxcommon::home_path();}
	if(label.compare("")==0){label = gettext("Choose Directory");}
	Fl_Native_File_Chooser fnfc;
	fnfc.title(label.c_str());
	fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	fnfc.directory(directory.c_str());
	std::string String;
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			debug_out("Error in directory chooser");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				String = result;
			}
	}
	if(String.compare("")!=0){
		std::string message = gettext("Save as ");
		message +=String;
		int choice = fl_choice("Save As","No","Yes","Cancel");//message.c_str(),gettext("No"),gettext("Yes"),gettext("Cancel"));
		if (choice!=1){return "";}
	}
	return String;
}
std::string choose_a_file(){
	std::string directory=linuxcommon::home_path();
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,"*");
	return String;
}
std::string choose_a_file(std::string directory){
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,"*");
	return String;
}
std::string choose_a_file(std::string directory,std::string pattern){
	std::string chooseName=gettext("Choose a File");
	std::string String=nativeFileDialog(chooseName,directory,pattern);
	return String;
}
std::string choose_a_program(){
	debug_out("std::string choose_a_program()");
	std::string chooseName=gettext("Choose a program");
	std::string result=nativeFileDialog(chooseName,"/usr/share/applications","*.desktop");
	if(result.compare("")==0){return "";}
    bool isDESKTOP = false;
    std::string returnable = result;
    std::string base = result;
    unsigned found2 = returnable.find(".desktop");
    if(found2<=result.length()){
		returnable=returnable.erase(found2,std::string::npos);
		isDESKTOP=true;
	}
    if(isDESKTOP){
		std::string execline= linuxcommon::get_line_with_equal(base,"TryExec=");
		if(execline.compare("")==0){execline= linuxcommon::get_line_with_equal(base,"Exec=");}
		execline=linuxcommon::remove_percentage(execline);
		return execline;
	}
	else{
		unsigned int found;
		found=returnable.rfind("/");
		if(found<returnable.length()){returnable=returnable.erase(0,found+1);}
    }
	return returnable;
}
std::string choose_an_icon(){
	std::string directory=linuxcommon::find_xdg_data_dir_subdir("icon");
	return choose_an_icon(directory);
}
std::string choose_an_icon(std::string directory){
	debug_out("std::string choose_an_icon(std::string "+directory+")");
	std::string chooseName=gettext("Choose an Icon");
	if(directory.compare("")==0){directory=linuxcommon::find_xdg_data_dir_subdir("icon");}
	std::string String=nativeFileDialog(chooseName,directory,"*.{xbm,XBM,png,PNG,svg,SVG}");
	return String;
}
std::string nativeFileDialog(std::string title,std::string path,std::string filters){
	debug_out("std::string nativeFileDialog(std::string "+title+",std::string "+path+",std::string "+filters+")");
	if(title.compare("")==0){title=gettext("Choose");}
	if(path.compare("")==0){path=linuxcommon::home_path();}
	if(filters.compare("")==0){filters="*";}
	const char * f=path.c_str();
	const char * m=title.c_str();
	const char * p=filters.c_str();
	Fl_Native_File_Chooser fnfc;
	fnfc.title(m);
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.options(Fl_Native_File_Chooser::PREVIEW);
	fnfc.filter(p);
	fnfc.directory(f); // default directory to use
	// Show native chooser
	switch ( fnfc.show() ){
		case -1:
			debug_out("ERROR");
			break; // ERROR
		case 1:
			break; // CANCEL
		default:
			const char *result =fnfc.filename();
			if(result!=NULL){
				std::string String = result;
				return String;
			}
			break; // FILE CHOSEN
	}
	return "";
}
//Char*/////////////////////////////////////////////////////////////////
char* Get_Fl_Icon(const char** pIcon){
	debug_out("char* Get_Fl_Icon(const char** pIcon)");
    /* Set icon for Linux:
     * This function must be initialised once by assigning an icon with parameter pIcon.
     * For sequential setting of icon to subwindows, this function can be called several
     * times without assigning an icon every time.
     *
     * Code from Vincent on FLTK forums 2015 Feb 10
     */
     //std::cout<< "sent in: "<<pIcon<<" to Get_Fl_Icon"<<std::endl;
	// Set icon for Linux:
    // This function must be initialised once by assigning an icon with parameter pIcon.
    // For sequential setting of icon to subwindows, this function can be called several
    // times without assigning an icon every time.
	static Pixmap p= 0;                // static store of assigned icon
	static Pixmap mask;
	if (!p && pIcon){
		// assign icon once
		fl_open_display();
		XpmCreatePixmapFromData(fl_display, DefaultRootWindow(fl_display),
		(char**) pIcon, &p, &mask, 0);
	}
	return (char*) p;
}
//Double////////////////////////////////////////////////////////////////
double* choose_a_color(int &c,Fl_Widget *o){
	uchar r;
	uchar g;
	uchar b;
	Fl::get_color((o->color()),r,g,b);
	const char * label =gettext("Choose a Color");
	c= fl_color_chooser(label,r,g,b,2);
	double* colors = new double[4];
	colors[0] = int(r); 
	colors[1] = int(g);
	colors[2] = int(b);
	colors[3] = 0;
	return colors;
}
//Void//////////////////////////////////////////////////////////////////
//C
void choose_a_program(Fl_Input *o){
	debug_out("void choose_a_program(Fl_Input *o)");
	std::string chooseName=gettext("Choose a program");
	std::string result=nativeFileDialog(chooseName,"/usr/share/applications","*.desktop");
	if(result.compare("")==0){return;}
	unsigned period = result.rfind(".");
    bool isDESKTOP = false;
    std::string returnable = result;
    std::string base = result;
    if(result.compare("")!=0){
        if(period<result.length()){
            std::string testDesktop = result.substr(period+1,std::string::npos);
            if(testDesktop.compare("desktop")==0){isDESKTOP = true;}
        }
        unsigned found = result.rfind("//");
        if((found+1)<result.length()){returnable=result.erase(0,found+1);}
        unsigned found2 = returnable.rfind(".");
        if(found2<result.length()){returnable=returnable.erase(found2,std::string::npos);}
        if(isDESKTOP){
			std::string execline= linuxcommon::get_line_with_equal(base,"TryExec=");
			if(execline.compare("")==0){execline= linuxcommon::get_line_with_equal(base,"Exec=");}
			execline=linuxcommon::remove_percentage(execline);
            o->value(execline.c_str());
            return;
        }
    }
	o->value(returnable.c_str());
}
void clearOutput(Fl_Output* o){
	debug_out("void clearOutput(Fl_Output* o)");
	int retval=o->value(NULL);
	if(retval!=0){debug_out("Different value set");}
}
void color_two(Fl_Widget * o, std::string whichElement,std::string subelement){
	debug_out("void color_two(Fl_Widget * o, std::string "+whichElement+",std::string "+subelement+")");
	int c,c1;
	std::string colorString=getElementText(whichElement,subelement);
	if(colorString.compare("")==0){
		double* colors1 = choose_a_color(c1,o);
		if(c1==0){return;}
		colorString=colorToString(colors1);
	}
	std::string color1=splitColor(1,colorString);
	double* colors = choose_a_color(c,o);
	if(c!=0){//If color chooser isn't canceled... do stuff
		std::string color2=colorToString(colors);
		std::string finalColor=color1+":"+color2;
		setElementText(whichElement,subelement,finalColor);
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
//G
void getDecorations(Fl_Output *o,std::string element){
	if(JWMversion()<232){
		o->hide();
		return;
	}
	std::string tmp=getElementAttribute(element,"decorations");
	if(tmp.compare("")!=0){
		o->value(tmp.c_str());
	}
	else{o->value("flat");}
	o->redraw();
}
//M
void makeWidgetIcon(std::string icon_file, Fl_Widget * widget,int wh){
	makeWidgetIcon(icon_file,widget,wh,wh);
}
void makeWidgetIcon(std::string icon_file, Fl_Widget * widget, int w, int h){
	debug_out("void makeWidgetIcon(std::string "+icon_file+", Fl_Widget * widget, int w, int h)");
	//std::string oldfile=icon_file;
	if(icon_file.compare("")==0){
		errorOUT("Icon file is empty");
		return;
	}
	//unsigned int found=icon_file.find("/");
	if(!linuxcommon::test_file(icon_file)){  
		std::vector<std::string> tmpV=IconPaths();
		std::string tmp=icon_file;
		unsigned int ext=icon_file.rfind(".");
		if(ext>icon_file.length()){
			tmp=icon_file+".svg";
			tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);
			if(tmp.compare("")==0){
				tmp=icon_file+".png";
				tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);
			}
		}
		else{tmp=linuxcommon::test_file_in_vector_path(tmp,tmpV);}
		if(tmp.compare("")==0){tmp=linuxcommon::look_for_icon_file(icon_file);}
		if(tmp.compare("")!=0){
			icon_file=tmp;
			debug_out("RESULT="+tmp);
		}
	}
	else{debug_out(icon_file+" is an Image!");}
	if(icon_file.compare("")==0){
		errorOUT("Icon file is empty");
		return;
	}
	Fl_Image* image2=NULL;
	if(linuxcommon::has_file_extention_at_end(icon_file,".png")){
        Fl_Image* image = new Fl_PNG_Image(icon_file.c_str());
        image2 = image->copy(w,h);
    }
    else if(linuxcommon::has_file_extention_at_end(icon_file,".xpm")){
    	Fl_Image* image = new Fl_XPM_Image(icon_file.c_str());
    	image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".xbm")){
    	Fl_Image* image = new Fl_XBM_Image(icon_file.c_str());
    	image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".svg")){
		NSVGimage *svg_image = NULL;
		NSVGrasterizer *rast = NULL;
		unsigned char* img_data = NULL;
		int width;
		int height;
		const int depth = 4;
		svg_image = nsvgParseFromFile(icon_file.c_str(), "px", 96.0f);
		if (svg_image == NULL) {
			std::cerr<<"Could not open SVG image:"<<icon_file<<std::endl;
			return;
		}
    	width = (int)svg_image->width;
		height = (int)svg_image->height;
		rast = nsvgCreateRasterizer();
		if (rast == NULL) {
			errorOUT("Could not init rasterizer.");
			return;
		}
		img_data = (unsigned char*)malloc(width * height * depth);
		if (img_data == NULL) {
			errorOUT("Could not alloc image buffer.\n");
			return;
		}
		nsvgRasterize(rast, svg_image, 0, 0, 1, img_data, width, height, (width * depth));
		Fl_Image* image  = new Fl_RGB_Image(img_data, width, height, depth);
		image2 = image->copy(w,h);
		nsvgDeleteRasterizer(rast);
		nsvgDelete(svg_image);
	}
	else if((linuxcommon::has_file_extention_at_end(icon_file,".jpg"))||(linuxcommon::has_file_extention_at_end(icon_file,".jpeg"))){
		Fl_Image* image = new Fl_JPEG_Image(icon_file.c_str());
		image2 = image->copy(w,h);
	}
	else if(linuxcommon::has_file_extention_at_end(icon_file,".gif")){
		Fl_Image* image = new Fl_GIF_Image(icon_file.c_str());
		image2 = image->copy(w,h);
	}
	else{return;}
	widget->image(image2);
}
//O
void one_color(Fl_Widget *o, std::string whichElement){
	debug_out("void one_color(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){
		if(!setElementFloat(whichElement,colors)){errorOUT("Could not set the color");}
		std::string colorString=getElementText(whichElement,"Background");
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
	if(c!=0){//If color chooser isn't canceled... do stuff
		std::string colorString;
		if(JWMversion()<230){
			setElementFloat(whichElement,"ActiveBackground",colors);
			colorString=getElementText(whichElement,"ActiveBackground");
		}
		else{
			setElementFloat(whichElement,"Active","Background",colors);
			colorString=getElementText(whichElement,"Active","Background");
		}
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
void one_color_Font_active(Fl_Widget *o, std::string whichElement){
	debug_out("void one_color_Font_active(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){
		std::string colorString;
		if(JWMversion()>230){
			setElementFloat(whichElement,"Active","Foreground",colors);
			colorString=getElementText(whichElement,"Active","Foreground");
		}
		else{
			setElementFloat(whichElement,"ActiveForeground",colors);
			colorString=getElementText(whichElement,"ActiveForeground");
		}
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
void outline_color(Fl_Widget *o, std::string whichElement){
	debug_out("void outline_color(Fl_Widget *o, std::string "+whichElement+")");
	int c;
	double* colors = choose_a_color(c,o);
	if(c!=0){
		std::string colorString;
		setElementFloat(whichElement,"Outline",colors);
		colorString=getElementText(whichElement,"Outline");
		unsigned int unusedColor;
		unsigned int colorSet = flCOLOR(colorString,unusedColor);
		o->color(colorSet);
		o->redraw();
	}
}
void outline_two_color(Fl_Widget *a, Fl_Widget *b, std::string whichElement){two_colors(a,b,whichElement,"Outline");}
void opacity(Fl_Value_Input *o, Fl_Slider *slider, std::string whichElement){
	debug_out("void opacity(Fl_Value_Input *o, Fl_Slider *slider, std::string "+whichElement+")");
	double opac=slider->value();
	double* opacity =&opac;
	setElementFloat(whichElement,"Opacity",opacity);
	o->value(opac*100);
}
void outline1(Fl_Widget *a, std::string element){
	debug_out("void outline2(Fl_Widget *a, std::string "+element+")");
	std::string val=getFirstColor(element,"OutLine");
	if(val.compare("")==0)return;
	a->color(flCOLOR(val));
	a->redraw();
}
void outline2(Fl_Widget *a, Fl_Output *b,std::string element){
	debug_out("void outline2(Fl_Widget *a, Fl_Output *b, std::string "+element+")");
	const char* value=b->value();
	if(value==NULL){
		return;
	}
	std::string thing = value;
	if(thing.compare("motif")!=0){
		a->hide();
		return;
	}
	std::string val=getSecondColor(element,"OutLine");
	if(val.compare("")==0)return;
	a->color(flCOLOR(val));
	a->redraw();
}
//P
void populateBrowserWithTextFile(Fl_Browser *o, std::string filename){
	if(filename.compare("")==0)return;
	std::vector<std::string> myfile=linuxcommon::file_to_vector(filename);
	for( std::vector<std::string>::iterator it = myfile.begin();
		it!=myfile.end();
		++it){
		std::string tmp=*it;
		o->add(tmp.c_str());
	}
}
void populateBrowserWithString(Fl_Browser *o, std::string STRING){
	debug_out("void populateBrowserWithString(Fl_Browser *o, std::string "+STRING+")");
	if(STRING.compare("")==0)return;
	std::string sep="\n";
	unsigned int finder=STRING.find(sep);
	unsigned int length=STRING.length();
	if(finder>length){
		debug_out("No Newline found");
		o->add(STRING.c_str());
		return;
	}
	while(finder<length){
		finder=STRING.find(sep);
		length=STRING.length();
		std::string tmp1=STRING;
		if(finder<length+1){
			std::string tmp2=tmp1.erase(finder,std::string::npos);	
			o->add(tmp2.c_str());
			tmp1=STRING;
			finder=tmp1.find(sep);
			STRING=tmp1.substr(finder+1,std::string::npos);
		}
	}
}
//S
void setDecorations(Fl_Output *o,std::string element,std::string value){
	debug_out("void setDecorations(Fl_Output *o,std::string "+element+",std::string "+value+")");
	if(JWMversion()<232){
		return;
	}
	if(value.compare("")==0){value="flat";}
	if(!setElementAttribute(element,"decorations",value)){errorOUT("could not add decoration to "+element);}
	o->value(value.c_str());
	o->redraw();
}
void startup(Fl_Window *o){under_mouse(o);}
void startup(Fl_Window *o ,const char** windowIcon){
  under_mouse(o);
  o->icon(Get_Fl_Icon(windowIcon));
}
//T
void two_colors(Fl_Widget *a, Fl_Widget *b, std::string whichElement,std::string subelement){
	debug_out("void two_colors(Fl_Widget *a, Fl_Widget *b, std::string "+whichElement+",std::string "+subelement+")");
	int c,c2;
	double* colors = choose_a_color(c,a);
	if(c!=0){
		std::string colorString=colorToString(colors);
		double* colors2 = choose_a_color(c2,a);
		if(c2!=0){
			std::string colorString2=colorToString(colors2);
			std::string res=colorString+":"+colorString2;
			if(setElementText(whichElement,subelement,res)){
				res=getElementText(whichElement,subelement);
				unsigned int Color;
				unsigned int colorSet = flCOLOR(res,Color);
				a->color(colorSet);
				a->redraw();
				b->color(colorSet);
				b->redraw();
			}
			else{errorOUT("failed to set 2 colors");}
		}
	}
}
//Boolean///////////////////////////////////////////////////////////////
bool OutputIsEmpty(Fl_Output* o){
	debug_out("bool OutputIsEmpty(Fl_Output* o)");
	if(o->value()==NULL){return true;}
	const char* value=o->value();
	if(value==NULL){
		debug_out("Empty");
		return true;
	}
	std::string val=value;
	if(val.compare("")==0){
		debug_out("Empty");
		return true;
	}
	debug_out("Not empty");
	return false;
}
