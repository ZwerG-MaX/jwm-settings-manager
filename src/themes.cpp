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
void Theme::change_theme(std::string whichTheme, bool overwrite){
	debug_out("void change_theme(std::string "+whichTheme+", bool overwrite");
	if(whichTheme.compare("")==0){
		errorOUT("Empty theme sent in!");
		return;
	}
	if(overwrite){theme_copier(whichTheme);}
	else if(!overwrite){modCurrentTheme(whichTheme);}
	saveChanges();
} 
void Theme::save_theme(Fl_Browser *usr_theme){
	debug_out("void save_theme(Fl_Browser *usr_theme)");
	std::string save_name = choose_directory(gettext("Save File"));
	if(save_name.compare("")==0){return;}
	int result = saveAs(save_name);
	if(result!=0){
		errorOUT("Problem saving: "+save_name);
		return;
	}
	populateUserThemes(usr_theme);
}
void Theme::theme_copier(std::string theme){
	debug_out("void theme_copier(std::string "+theme+")");
	if(theme.compare("")==0){
		errorOUT("Theme was empty");
		return;
	}
    bool existant=checkForTheme(theme);
    std::string path=linuxcommon::home_path();
    std::string error=gettext("ERROR");
    if(existant){
        std::string copyTheme = "cp "+ theme + " " + path +".jwmrc";
        //userTheme();
        int retval =linuxcommon::run_a_program(copyTheme);
        if(retval!=0){
            errorOUT(copyTheme+" "+error);
        }
        copyTheme = "cp "+ theme + " " + path +".jwmrc~";
        retval =linuxcommon::run_a_program(copyTheme);
        if(retval!=0){
            errorOUT(copyTheme+" "+error);
        }
    }
    else {errorOUT(error+"Theme doesn't exist, cannot copy\n");}
}
void Theme::setButton(std::string filename,std::string element){
	debug_out("void setButton(std::string "+filename+",std::string "+element+")");
	if(!load(filename,false)){return;}
	std::string temp=getElementText(element);
	if(temp.compare("")==0){
		errorOUT("Did NOT get Button from "+filename);
		return;
	}
	if(!load()){
		errorOUT("LOADING base document FAILED");
		return;
	}
	if(!setElementText(element,temp)){errorOUT("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void Theme::setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement){
	debug_out("void setThemeElementTextwithSub(std::string "+filename+",std::string "+element+",std::string "+subelement+")");
	if(!load(filename,false)){
		errorOUT("Could not load "+filename);
		return;
	}
	std::string temp=getElementText(element,subelement);
	if(temp.compare("")==0){
		errorOUT("Did NOT get Button from "+filename);
		return;
	}
	if(!load())errorOUT("LOADING base document FAILED");
	if(!setElementText(element,subelement,temp)){errorOUT("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void Theme::setThemeElementTextwithSub(std::string filename,std::string element,std::string subelement,std::string SUBsubelement){
	debug_out("void setThemeElementTextwithSub(std::string "+filename+",std::string "+element+",std::string "+subelement+",std::string "+SUBsubelement+")");
	if(!load(filename,false)){return;}
	std::string temp=getElementText(element,subelement,SUBsubelement);
	if(temp.compare("")==0){
		errorOUT("Did NOT get Button from "+filename);
		return;
	}
	if(!load())debug_out("LOADING base document FAILED");
	if(!setElementText(element,subelement,SUBsubelement,temp)){errorOUT("FAILED setting "+element+" with "+temp+" in the main DOC");}
	else{saveNoRestart();}
}
void Theme::modCurrentTheme(std::string filename){
	debug_out("void modCurrentTheme(std::string "+filename+")");
    if(!load(filename,false)){return;}
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
void Theme::updateTheme( Fl_Browser *o,
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
	/** Window buttons */
    std::string maxButton = getButton("ButtonMax",filename);
    std::string minButton = getButton("ButtonMin",filename);
    std::string closeButton = getButton("ButtonClose",filename);
	std::string WindowStyle="WindowStyle";
	std::string TrayStyle="TrayStyle";
	//debug_out("*************************************************\nMin="+minButton+"\nMax="+maxButton+"\nClose="+closeButton+"\n*************************************************\n");
    /**These should never be empty, unless it is NOT a file, or the tags do not exist*/
    if(minButton.compare("")!=0){
        if(!load(filename,false)){return;}
        makeWidgetIcon(minButton,active_min_button,25);
        active_min_button->redraw();
        if(!load(filename,false)){return;}
        makeWidgetIcon(minButton,inactive_min_button,25);
        inactive_min_button->redraw();
    }
    if(maxButton.compare("")!=0){
		if(!load(filename,false)){return;}
        makeWidgetIcon(maxButton,active_max_button,25);
        active_max_button->redraw();
        if(!load(filename,false)){return;}
        makeWidgetIcon(maxButton,inactive_max_button,25);
        inactive_max_button->redraw();
    }
    if(closeButton.compare("")!=0){
		if(!load(filename,false)){return;}
        makeWidgetIcon(closeButton,active_close_button,25);
        active_close_button->redraw();
        if(!load(filename,false)){return;}
        makeWidgetIcon(closeButton,inactive_close_button,25);
        inactive_close_button->redraw();
    }
/** Window styles */
    unsigned int active_color2=0;
    unsigned int activeWindowColorText = 0;
    unsigned int activeWindowColor = 0;
    std::string activeWC;
	std::string activeWCT;
	if(!load(filename,false)){return;}
    activeWC = getElementText(WindowStyle,"Active","Background");
    if(activeWC.compare("")==0){
		if(!load(filename,false)){return;}
		activeWC = getElementText(WindowStyle,"Active","Title");
	}
    if(!load(filename,false)){return;}
	activeWCT = getElementText(WindowStyle,"Active","Foreground");
	if(activeWCT.compare("")==0){
		if(!load(filename,false)){return;}
		activeWCT = getElementText(WindowStyle,"Active","Text");
	}
    /** modify the UI if needed */
    if(activeWC.compare("")!=0){
		activeWindowColor = flCOLOR(activeWC,active_color2);
		activeW->color(activeWindowColor);
		activeW2->color(active_color2);
		activeW->redraw();
		activeW2->redraw();
	}
	if(activeWCT.compare("")!=0){
		activeWindowColorText=flCOLOR(activeWCT);
		activeW_text->labelcolor(activeWindowColorText);
		activeW_text->redraw();
	}
    unsigned int inactive_color2=0;
    unsigned int windowColor = 0;
    unsigned int windowColorText = 0;
    if(!load(filename,false)){return;}
    std::string WC=getElementText(WindowStyle,"Background");
    if(WC.compare("")==0){
		if(!load(filename,false)){return;}
		WC=getElementText(WindowStyle,"Title");
	}
    if(!load(filename,false)){return;}
    std::string WCT=getElementText(WindowStyle,"Foreground");
    if(WCT.compare("")==0){
		if(!load(filename,false)){return;}
		WCT=getElementText(WindowStyle,"Text");
	}
    /** modify the UI if needed */
    if(WC.compare("")!=0){
		windowColor=flCOLOR(WC,inactive_color2);
		inactiveW->color(windowColor);
		inactiveW2->color(inactive_color2);
		inactiveW->redraw();
		inactiveW2->redraw();
	}
	if(WCT.compare("")!=0){
		windowColorText = flCOLOR(WCT);
		inactiveW_text->labelcolor(windowColorText);
		inactiveW_text->redraw();
	}
/** Panel */
	if(!load(filename,false)){return;}
    std::string label =getElementAttribute("Tray","TrayButton","label");
    unsigned int panelColor = 0;
    if(!load(filename,false)){return;}
    std::string PC = getElementText(TrayStyle,"Background");
    /** modify the UI if needed */
    if(PC.compare("")!=0){
		panelColor = flCOLOR(PC);
		tray->color(panelColor);
	}
    unsigned int panelColorText = 0;
    if(!load(filename,false)){return;}
    std::string PCT = getElementText(TrayStyle,"Foreground");
    if(PCT.compare("")!=0){
		panelColorText = flCOLOR(PCT);
		tray->labelcolor(panelColorText);
	}
    debug_out("LABEL: "+label+"\npanelColor: "+PC+"\npanelColorText: "+PCT);
	tray->redraw();
    //panel Button */
    unsigned int panelButtonColorText=panelColorText;
    unsigned int panelButtonColor=panelColor;
    
    /** New version */
    if(themeNewStyle(filename)<1){
		if(!load(filename,false)){return;}
		std::string tmp=getElementText("TrayButtonStyle","Background");
		if(tmp.compare("")!=0)
			panelButtonColor = flCOLOR(tmp);
		if(!load(filename,false)){return;}
		tmp = getElementText("TrayButtonStyle","Foreground");
		if(tmp.compare("")!=0)
			panelButtonColorText = flCOLOR(tmp);
    }/**END Dont do this IF new version*/
    else{
        panelButtonColor=panelColor;
        panelButtonColorText = panelColorText;
    }
    if(label.compare("")!=0)
		button->copy_label(label.c_str());
	
    button->color(panelButtonColor);
    button->labelcolor(panelButtonColorText);
    button_icon->color(panelButtonColor);
    if(!load(filename,false)){return;}
    std::string icon_file = getPanelButtonIcon();
    makeWidgetIcon(icon_file,button_icon,30);
    button->redraw();
    button_icon->redraw();
}
//String////////////////////////////////////////////////////////////////
std::string Theme::choose_directory(std::string whichChoice){
	debug_out("std::string choose_directory(std::string "+whichChoice+")");
	std::string directory_path =userThemeDir();
	std::string label=gettext("Choose");
	label += " ";
	label+=whichChoice;
	return choose_a_directory_to_save(directory_path,label);
}
std::string Theme::choose_file(){return choose_a_file();}
std::string Theme::getTheme(std::string whichTheme){
	debug_out("std::string getTheme(std::string "+whichTheme+")");
    std::string stringTheme = whichTheme;
    std::string themeTest;
    std::string theme;
    std::string themePATH=sysThemeDir();
    std::string OLDthemePATH=themePATH+"2.3.0/";
    std::string themePATH230=themePATH+"old/";
    int isOLDjwmrc = newStyle();
    bool existant = false;
    switch(isOLDjwmrc){
		case -1:
			existant = oldThemesExist();
			theme = OLDthemePATH + stringTheme + "/" + stringTheme;
			themeTest = OLDthemePATH + stringTheme + "/";
			break;
		case 0:
			existant = oldThemesExist();
			theme = themePATH230 + stringTheme + "/" + stringTheme;
			themeTest = themePATH230 + stringTheme + "/";
			break;
		default:
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
std::string Theme::sysThemeDir(){
	debug_out("std::string sysThemeDir()");
	std::string result=linuxcommon::find_xdg_data_dir_subdir("jwm-settings-manager");
	result+="themes/";
	if(!linuxcommon::test_dir(result)){
		errorOUT("Could not find "+result);
		return "";
	}
	return result;
}
std::string Theme::userThemeDir(){
	debug_out("std::string userThemeDir()");
	std::string result=linuxcommon::home_path();
	result+=".themes/";
	if(!linuxcommon::test_dir(result)){
		errorOUT("Could not find "+result);
		return "";
	}
	return result;
}
std::string Theme::theme_cb(Fl_Browser* browser,bool systemTheme, Fl_Input* current_theme){
	debug_out("std::string theme_cb(Fl_Browser* browser,bool systemTheme, Fl_Widget* current_theme)");
	int line = browser->value();
	const char* TEXT= browser->text(line);
	if(TEXT==NULL){
		errorOUT("Nothing selected");
		return "";
	}
	std::string text = TEXT;
	if(text.compare("..")==0){
		const char* temp=current_theme->value();
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
	current_theme->value(returnpath.c_str());
	current_theme->redraw();
	return returnpath;
}
std::string Theme::getButton(std::string element,std::string themefile){
	debug_out("std::string getButton(std::string "+element+")");
	if(!load(themefile,false)){return "";}
	std::string filename=getElementText(element);
	if(linuxcommon::test_file(filename)){
		debug_out(filename+" is a file");
		return filename;
	}
	debug_out(filename+" is NOT a file still going to try to make it happen...");
	if(!load(themefile,false)){return "";}
	std::vector<std::string> icon_paths=IconPaths();
	return linuxcommon::test_file_in_vector_path(filename,icon_paths);
}
//Int///////////////////////////////////////////////////////////////////
int Theme::saveAs(std::string save_name){
	debug_out("int saveAs(std::string "+save_name+")");
	if(!saveChanges(save_name,false,false)){return 1;}
	return 0;
}
int Theme::populateANYThemes(Fl_Browser *o,std::string checkHERE,bool backone){
	debug_out("int populateANYThemes(Fl_Browser *o,std::string "+checkHERE+",bool backone)");
	if(backone){o->add("..");}
	DIR *dir=NULL;
    std::string itemName;
    struct dirent *ent=NULL;
    if ((dir = opendir (checkHERE.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            itemName=ent->d_name;
			std::string fullpath=ent->d_name;
            itemName=itemName.substr(0,(itemName.length()));
            if (!(itemName.compare(".")==0)&&!(itemName.compare("..")==0)&&!(itemName.compare("old")==0)&&!(itemName.compare("2.3.0")==0)){
				//Don't add our random stuff
				if( (!linuxcommon::has_file_extention_at_end(itemName,".in")) && !linuxcommon::has_file_extention_at_end(itemName,".txt") ){
					pugi::xml_document tmp;
					if(checkHERE.rfind('/')!=checkHERE.length()-1){checkHERE+="/";}
					std::string subber = checkHERE+fullpath;
					fullpath=checkHERE+fullpath+"/"+fullpath;
					debug_out(fullpath);
					if( (tmp.load_file(fullpath.c_str())) || (tmp.load_file( subber.c_str())) ){
						o->add(itemName.c_str());
					}
				}
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
int Theme::populateThemes(Fl_Browser *o){return populateANYThemes(o,sysThemeDir(),false);}
int Theme::populateUserThemes(Fl_Browser *o){return populateANYThemes(o,userThemeDir(),false);}
int Theme::loadTheme(std::string themePath){
    if(!linuxcommon::test_file(themePath)){return 42;}
    if (!load(themePath.c_str(),false)){
        errorOUT("An error occured loading "+themePath);
        return 1;
    }
    else{debug_out("Theme loaded: "+themePath);}
    return 0;
}
int Theme::themeNewStyle(std::string themefile){
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
    //int NEWEST = 2; //Added traybutton taskliststyles
    debug_out("loading theme");
    int retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TBS=isElement("TrayButtonStyle");
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TLS=isElement("TaskListStyle");
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool CS=isElement("ClockStyle");
    if(!TBS && !TLS && !CS ){
		std::string temp=linuxcommon::convert_num_to_string(two3later);
		debug_out("this is an NEW (>2.3.2) but not newest(2.3.6) theme, returning:"+temp+"\n<--themeNewStyle()");
        return two3later;
    }
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TAB=isElement(tray,aback);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TSAB=isElement(task,aback);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool PAB=isElement(pager,aback);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool BAB=isElement(button,aback);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TAF=isElement(tray,afore);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool TSAF=isElement(task,afore);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool PAF=isElement(pager,afore);
    retval=loadTheme(themefile);
    if(retval!=0){return 42;}
    bool BAF=isElement(button,afore);
    /**OLD STYLE*/
	if(TAB||TSAB||PAB||BAB||TAF||TSAF||PAF||BAF){
		std::string temp=linuxcommon::convert_num_to_string(not23);
		debug_out("this is an OLD theme, returning:"+temp+"\n<--themeNewStyle()");
		return not23;
	}
	std::string temp=linuxcommon::convert_num_to_string(two30);
	debug_out("this is an NEW (2.3.0 || 2.3.1||2.3.6) theme, returning:"+temp+"\n<--themeNewStyle()");
    return two30;
}

//Boolean///////////////////////////////////////////////////////////////
bool Theme::checkForTheme(std::string theme){
	debug_out("bool checkForTheme(std::string "+theme+")");
	return linuxcommon::test_file(theme);
}
bool Theme::checkThemeVersion(){
	debug_out("bool checkThemeVersion()");
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
bool Theme::oldThemesExist(){
	debug_out("bool oldThemesExist()");
    std::string userHomePath = sysThemeDir();
    userHomePath+="old/";
    return linuxcommon::test_dir(userHomePath.c_str());
}
bool Theme::themesExist(){
	debug_out("bool themesExist()");
    std::string userHomePath = sysThemeDir();
    return linuxcommon::test_dir(userHomePath.c_str());
}
