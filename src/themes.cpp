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
#include "../include/themes.hpp"
void change_theme(std::string whichTheme, bool overwrite){
  if(overwrite){theme_copier(whichTheme);}
  else if(!overwrite){modCurrentTheme(whichTheme);}
  saveChanges();
}
void save_theme(Fl_Browser *usr_theme) {
  std::string save_name = choose_directory(gettext("Save File"));
  if (save_name.compare("")==0){return;}
  int result = saveAs(save_name);
  if(result!=0){fl_alert("Problem saving: %s",save_name.c_str()); return;}
  populateUserThemes(usr_theme);
}
void theme_copier(std::string theme){
	if(!linuxcommon::test_file(theme)){
		std::cerr<<theme<<" is not a file"<<std::endl;
		return;
	}
    bool existant=checkForTheme(theme);
    std::string bash=bash = "/bin/bash -c '";
    std::string path=linuxcommon::home_path();
    std::string error=" ERROR!!";
    if (existant){
        std::string copyTheme = bash;
        copyTheme = copyTheme + "cp "+ theme + " " + path +".jwmrc'";
        //userTheme();
        if(system(copyTheme.c_str())!=0){
            std::cerr<<copyTheme<<error;
        }
        copyTheme = bash+"cp "+ theme + " " + path +".jwmrc~'";
        if(system(copyTheme.c_str())!=0){
            std::cerr<<copyTheme<<error;
        }
    }
    else {errorOUT("Theme doesn't exist, cannot copy\n");}
}
void setButton(std::string filename,std::string element){
	if(!load(filename)){return;}
	std::string temp=getElementText(element);
	if(temp.compare("")==0){
		debug_out("Did NOT get Button from "+filename);
		return;
	}
	if(!load())debug_out("LOADING base document FAILED");
	if(!setElementText(element,temp)){debug_out("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement){
	if(!load(filename)){return;}
	std::string temp=getElementText(element,subelement);
	if(temp.compare("")==0){
		debug_out("Did NOT get Button from "+filename);
		return;
	}
	if(!load())debug_out("LOADING base document FAILED");
	if(!setElementText(element,subelement,temp)){debug_out("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement,std::string SUBsubelement){
	if(!load(filename)){return;}
	std::string temp=getElementText(element,subelement,SUBsubelement);
	if(temp.compare("")==0){
		debug_out("Did NOT get Button from "+filename);
		return;
	}
	if(!load())debug_out("LOADING base document FAILED");
	if(!setElementText(element,subelement,SUBsubelement,temp)){debug_out("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void modCurrentTheme(std::string filename){
	debug_out("void modCurrentTheme(std::string "+filename+")");
    if(!load(filename)){return;}
    setButton(filename,"ButtonMin");
	setButton(filename,"ButtonMax");
    setButton(filename,"ButtonMaxActive");
    setButton(filename,"ButtonClose");
    std::string WindowStyle="WindowStyle";
    std::string Active="Active";
    std::string Background="Background";
    std::string Foreground="Foreground";
    std::string ActiveBackground="ActiveBackground";
    std::string ActiveForeground="ActiveForeground";
    std::string TrayStyle="TrayStyle";
    std::string  TrayButtonStyle="TrayButtonStyle";
    std::string  TaskListStyle="TaskListStyle";
    std::string  MenuStyle="MenuStyle";
    if(themeNewStyle(filename)<0){
		setThemeElementTextwithSub(filename,WindowStyle,ActiveBackground);
		setThemeElementTextwithSub(filename,WindowStyle,ActiveForeground);
	}
	else{
		setThemeElementTextwithSub(filename,WindowStyle,Active,Background);
		setThemeElementTextwithSub(filename,WindowStyle,Active,Foreground);
	}
	setThemeElementTextwithSub(filename,WindowStyle,Background);
	setThemeElementTextwithSub(filename,WindowStyle,Foreground);
    setThemeElementTextwithSub(filename,TrayStyle,Background);
    if(themeNewStyle(filename)<0){setThemeElementTextwithSub(filename,TrayStyle,"Text");}
	else{setThemeElementTextwithSub(filename,TrayStyle,Foreground);}

/// /////Don't do this if we are using the newest version.. because it doesn't exist
	if(themeNewStyle(filename)<1){
		///panel Button     modCurrentTheme
		setThemeElementTextwithSub(filename,TrayButtonStyle,Background);
		setThemeElementTextwithSub(filename,TrayButtonStyle,Foreground);
		///tasklist     modCurrentTheme
		setThemeElementTextwithSub(filename,TaskListStyle,Background);
		setThemeElementTextwithSub(filename,TaskListStyle,Foreground);
		setThemeElementTextwithSub(filename,TaskListStyle,Active,Background);
		setThemeElementTextwithSub(filename,TaskListStyle,Active,Foreground);
	}
///menus    modCurrentTheme
    setThemeElementTextwithSub(filename,MenuStyle,Background);
    setThemeElementTextwithSub(filename,MenuStyle,Foreground);
    setThemeElementTextwithSub(filename,MenuStyle,Active,Background);
    setThemeElementTextwithSub(filename,MenuStyle,Active,Foreground);
}
void updateTheme( Fl_Browser *o,
					Fl_Box * button,
					Fl_Box * button_icon,
					Fl_Box *tray,
					Fl_Box *activeW,
					Fl_Box *activeW2,
					Fl_Box *activeW_text,
					Fl_Box *inactiveW,
					Fl_Box *inactiveW2,
					Fl_Box *inactiveW_text,
					Fl_Box *active_min_button,
					Fl_Box *active_max_button,
					Fl_Box *active_close_button,
					Fl_Box *inactive_min_button,
					Fl_Box *inactive_max_button,
					Fl_Box *inactive_close_button,
					std::string filename,
					bool user){
	debug_out("void updateTheme(..."+filename+"...)");
	if(linuxcommon::test_dir(filename)){
		o->clear();
		populateANYThemes(o,filename,true);
		return;
	}
	const char* notNULL=o->text(o->value());
	if(notNULL!=NULL){
		std::string tempitem=notNULL;
		if(tempitem.compare("..")==0){
			//
			o->clear();
			if(user){populateUserThemes(o);}
			else{populateThemes(o);}
		}
	}
    if(!load(filename)){return;}
//menu buttons
    std::string maxButton = getButton("ButtonMax");
    std::string minButton = getButton("ButtonMin");
    std::string closeButton = getButton("ButtonClose");
	std::string WindowStyle="WindowStyle";
	std::string TrayStyle="TrayStyle";
    //These should never be empty, unless it is NOT a file.
    if( (minButton.compare("")!=0) && (!isSVG(minButton)) ){
        ///make image and copy
        Fl_Image * MIN;
        MIN = new Fl_PNG_Image(minButton.c_str());

        //copy makes the image not get all quirky
        Fl_Image * MIN2 = MIN->copy(25,25);
        active_min_button->image(MIN2);
        inactive_min_button->image(MIN2);

        //redraw the button to show the icon
        active_min_button->redraw();
        inactive_min_button->redraw();
    }
    if( (maxButton.compare("")!=0) && (!isSVG(maxButton)) ){
        Fl_Image * MAX;
        MAX = new Fl_PNG_Image(maxButton.c_str());
        Fl_Image * MAX2 = MAX->copy(25,25);
        active_max_button->image(MAX2);
        inactive_max_button->image(MAX2);
        active_max_button->redraw();
        inactive_max_button->redraw();
    }
    if( (closeButton.compare("")!=0) && (!isSVG(closeButton)) ){
        Fl_Image * CLOSE;
        CLOSE = new Fl_PNG_Image(closeButton.c_str());
        Fl_Image * CLOSE2 = CLOSE->copy(25,25);
        active_close_button->image(CLOSE2);
        inactive_close_button->image(CLOSE2);
        active_close_button->redraw();
        inactive_close_button->redraw();
    }
//windows
    unsigned int active_color2=0;
    unsigned int activeWindowColor = flCOLOR(getElementText(WindowStyle,"Active","Background"),active_color2);
    unsigned int activeWindowColorText = flCOLOR(getElementText(WindowStyle,"Active","Foreground"));

    //modify the UI
    activeW->color(activeWindowColor);
    activeW2->color(active_color2);
    activeW_text->labelcolor(activeWindowColorText);
    activeW->redraw();
    activeW2->redraw();
    activeW_text->redraw();

    unsigned int inactive_color2=0;
    unsigned int windowColor = flCOLOR(getElementText(WindowStyle),inactive_color2);
    unsigned int windowColorText = flCOLOR(getElementText(WindowStyle,"Foreground"));

    //modify the UI
    inactiveW->color(windowColor);
    inactiveW2->color(inactive_color2);
    inactiveW_text->labelcolor(windowColorText);
    inactiveW->redraw();
    inactiveW2->redraw();
    inactiveW_text->redraw();

//Panel
    std::string label;// = getPanelLabel(); //TODO
    unsigned int panelColor = flCOLOR(getElementText(TrayStyle,"Background"));
    unsigned int panelColorText = flCOLOR(getElementText(TrayStyle,"Foreground"));
    #ifdef DEBUG
    std::cerr<<"LABEL: "+label<<"\npanelColor: "<<panelColor<<"\npanelColorText: "<<panelColorText<<std::endl;
    #endif
    //modify the UI
    tray->color(panelColor);//labelcolor
    tray->labelcolor(panelColorText);
    tray->redraw();

    //panel Button
    unsigned int panelButtonColorText=panelColorText;
    unsigned int panelButtonColor=panelColor;
    //New version
    if(themeNewStyle(filename)<1){
        panelButtonColor = flCOLOR(getElementText("TrayButtonStyle","Background"));
        panelButtonColorText = flCOLOR(getElementText("TrayButtonStyle","Foreground"));
    }//END Dont do this IF new version
    else{
        panelButtonColor=panelColor;
        panelButtonColorText = panelColorText;
    }
    button->copy_label(label.c_str());
    button->color(panelButtonColor);
    button->labelcolor(panelButtonColorText);
    button_icon->color(panelButtonColor);
    std::string icon_file = getPanelButtonIcon();
    makeWidgetIcon(icon_file,button_icon,30);
    button->redraw();
    button_icon->redraw();
}
//String////////////////////////////////////////////////////////////////
std::string choose_directory(std::string whichChoice){
  std::string directory_path =userThemeDir();
  std::string label=gettext("Choose");
  label += " ";
  label+=whichChoice;
  return choose_a_directory_to_save(directory_path,label);
}
std::string choose_file(){return choose_a_file();}
std::string getTheme(std::string whichTheme){
    std::string stringTheme = whichTheme;
    std::string themeTest;
    std::string theme;
    std::string themePATH=sysThemeDir();
    std::string OLDthemePATH=themePATH+"2.3.0/";
    std::string themePATH230=themePATH+"old/";
    int isOLDjwmrc = newStyle();
    bool existant = false;
    if(isOLDjwmrc == -1){
        existant = oldThemesExist();
        theme = OLDthemePATH + stringTheme + "/" + stringTheme;
        themeTest = OLDthemePATH + stringTheme + "/";
    }
    else if (isOLDjwmrc == 0){
        existant = oldThemesExist();
        theme = themePATH230 + stringTheme + "/" + stringTheme;
        themeTest = themePATH230 + stringTheme + "/";
    }
    else{
        existant = themesExist();
        theme = themePATH + stringTheme + "/" + stringTheme;
        themeTest = themePATH + stringTheme + "/";
    }
    if (existant){
        existant = checkForTheme(themeTest);
        if (!existant){
            errorOUT("Theme doesn't exist, cannot get it\n");
            return "ERROR";
        }
        return (themeTest.c_str());

    }
    else {errorOUT("Theme directory doesn't exist, cannot GET THE THEME\n");}
    return "Themes don't exist";
}
std::string sysThemeDir(){
	std::string result=linuxcommon::find_xdg_data_dir_subdir("jwm-settings-manager");
	result+="themes/";
	return result;
}
std::string userThemeDir(){
	std::string result=linuxcommon::home_path();
	result+=".themes/";
	return result;
}
std::string theme_cb(Fl_Browser* browser,bool systemTheme, Fl_Widget* current_theme){
	int line = browser->value();
	std::string text = browser->text(line);
	if(text.compare("..")==0){
		const char* temp=current_theme->label();
		if(temp!=NULL){
			std::string dir=temp;
			return dir;
		}
		else{return "";}
	}
	
	std::string path ="";
	if(systemTheme){
		path = sysThemeDir();
		path= path + text+"/";
	}
	else{path = userThemeDir();}
	if(path.compare("")==0){return "";}
	std::string returnpath=path+text;
	if(!linuxcommon::test_file(returnpath)){ return path;}
	//std::cout<<"filename: "<<path<<std::endl;
	current_theme->copy_label(returnpath.c_str());
	return returnpath;
}
std::string getButton(std::string element){
	debug_out("std::string getButton(std::string "+element+")");
	std::string filename=getElementText(element);
	if(linuxcommon::test_file(filename)){
		debug_out(filename+" is a file");
		return filename;
	}
	debug_out(filename+" is NOT a file");
	std::vector<std::string> icon_paths=IconPaths();
	return linuxcommon::test_file_in_vector_path(filename,icon_paths);
}
//Int///////////////////////////////////////////////////////////////////
int saveAs(std::string save_name){
	if(!saveChanges(save_name,false,false)){return 1;}
	return 0;
}
int populateANYThemes(Fl_Browser *o,std::string checkHERE,bool backone){
	if(backone){o->add("..");}
	DIR *dir=NULL;
    std::string itemName;
    struct dirent *ent=NULL;
    if ((dir = opendir (checkHERE.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            itemName=ent->d_name;
            itemName=itemName.substr(0,(itemName.length()));
            if (!(itemName.compare(".")==0)&&!(itemName.compare("..")==0)&&!(itemName.compare("old")==0)&&!(itemName.compare("2.3.0")==0)){
				o->add(itemName.c_str());
			}
        }
        if(dir!=NULL){closedir (dir);}
    }
    else {
        perror ("");
        return EXIT_FAILURE;
    }
    return 0;
 }
int populateThemes(Fl_Browser *o){return populateANYThemes(o,sysThemeDir(),false);}
int populateUserThemes(Fl_Browser *o){return populateANYThemes(o,userThemeDir(),false);}
int loadTheme(std::string themePath){
    if(!linuxcommon::test_file(themePath)){return 42;}
    if (!load(themePath.c_str())){
        std::cerr<<"An error occured loading "<<themePath<<std::endl;
        return 1;
    }
    else{debug_out("Theme loaded: "+themePath);}
    return 0;
}
int themeNewStyle(std::string themefile){
	debug_out("int themeNewStyle(std::string "+themefile+")");
    std::string button = "TrayButtonStyle";
    std::string tray = "TrayStyle";
    std::string task = "TaskListStyle";
    std::string pager = "PagerStyle";
//    std::string win = "WindowStyle";
//    std::string menu = "MenuStyle";
    std::string afore ="ActiveForeground";
    std::string aback = "ActiveBackground";
    int not23 = -1; //OLD
    int two30 = 0; // version before removing traybutton/tasklist styles
    int two3later = 1; //2.3.2 ++
    #ifdef DEBUG
    std::cerr<<"loading theme"<<std::endl;
    #endif
    int retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    if( !(isElement("TrayButtonStyle")) &&
        !(isElement("TaskListStyle")) &&
        !(isElement("ClockStyle")) ){
		#ifdef DEBUG
		std::cerr<<"this is an NEW (2.3.2++) theme, returning:"<<two3later<<"\n<--themeNewStyle()"<<std::endl;
		#endif
        return two3later;
    }
    //OLD STYLE
	if((isElement(tray,aback)) ||
	(isElement(task,aback)) ||
	(isElement(pager,aback)) ||
	(isElement(button,aback)) ||
	(isElement(tray,afore)) ||
	(isElement(task,afore)) ||
	(isElement(pager,afore)) ||
	(isElement(button,afore))
	){
       #ifdef DEBUG
       std::cerr<<"this is an OLD theme, returning:"<<not23<<"\n<--themeNewStyle()"<<std::endl;
       #endif
       return not23;
    }
    #ifdef DEBUG
    std::cerr<<"this is an NEW (2.3.0 || 2.3.1) theme, returning:"<<two30<<"\n<--themeNewStyle()"<<std::endl;
    #endif
    return two30;
}

//Boolean///////////////////////////////////////////////////////////////
bool checkForTheme(std::string theme){return linuxcommon::test_file(theme);}
bool checkThemeVersion(){
    bool text = false;
    bool title =false;
    bool inactive =false;
    bool isNewTheme=false;
    if (isElement("WindowStyle","Active","Text")){text=true;}
    if (isElement("WindowStyle","Active","Title")){title=true;}
    if (isElement("WindowStyle","Inactive")){inactive=true;}
    if(text || title || inactive){ isNewTheme=false;}
    else{isNewTheme=true;}
    return isNewTheme;
}
bool oldThemesExist(){
    std::string userHomePath = sysThemeDir();
    userHomePath+="old/";
    return linuxcommon::test_dir(userHomePath.c_str());
}
bool themesExist(){
    std::string userHomePath = sysThemeDir();
    return linuxcommon::test_dir(userHomePath.c_str());
}
