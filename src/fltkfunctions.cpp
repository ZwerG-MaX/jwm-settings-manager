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
	if(!linuxcommon::test_file(icon_file)){  //((found> icon_file.length())||(!linuxcommon::test_file(icon_file))){
		icon_file=linuxcommon::look_for_icon_file(icon_file);
		if(icon_file.compare("")!=0){debug_out("RESULT="+icon_file);}
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
void startup(Fl_Window *o){under_mouse(o);}
void startup(Fl_Window *o ,const char** windowIcon){
  under_mouse(o);
  o->icon(Get_Fl_Icon(windowIcon));
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
