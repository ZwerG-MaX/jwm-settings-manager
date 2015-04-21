/**       @file Joe's Window Manager Configuration - Panel
 *
 *         @author Israel <israel@torios.org>
 *         @section Copyright (C) 2014
 *         @section LICENSE
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
 * @section DESCRITPTION
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 * This program configures JWM using tinyxml2 and FLTK
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#include "../include/flThemes.h"

flThemes::flThemes(){
    themePATH = "/usr/share/jwm-settings-manager/themes/";
    OLDthemePATH = "/usr/share/jwm-settings-manager/themes/old/";
    path = homePathNoFile(); ///Config function
    userThemePATH =path+".jwm/themes/";
    userThemeName = "/bin/bash -c 'cp -f " + path + ".usertheme " + path + ".jwmrc'";
    bash = "/bin/bash -c '";
    error =" failed please report this bug \n";
    isOLDjwmrc = !newVersionJWM();///Config function
    isNewTheme = false;
}

flThemes::~flThemes()
{
    //dtor
}
std::string flThemes::sysThemeDir(){
    if (isOLDjwmrc){return OLDthemePATH;}
    return themePATH;
}
int flThemes::populateUserThemes(Fl_Browser *o){
    DIR *dir;
    std::string itemName;
    std::string checkHERE;
    struct dirent *ent;
    if ((dir = opendir (userThemePATH.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            itemName=ent->d_name;
            if ((itemName.compare(".")==0)||(itemName.compare("..")==0)){/*DO NOTHING*/}
            else{o->add(itemName.c_str());}
        }
        closedir (dir);
    }
    else {
        perror ("");
        return EXIT_FAILURE;
    }
    return 0;
}
int flThemes::populateThemes(Fl_Browser *o){
    DIR *dir;
    std::string itemName;
    std::string checkHERE;
    if(isOLDjwmrc){
        checkHERE = OLDthemePATH;
    }
    else{
        checkHERE=themePATH;
    }
    struct dirent *ent;
    if ((dir = opendir (checkHERE.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            itemName=ent->d_name;
            itemName=itemName.substr(0,(itemName.length()));
            if ((itemName.compare(".")==0)||(itemName.compare("..")==0)||(itemName.compare("old")==0)){
                //DO NOTHING
            }
            else{o->add(itemName.c_str());}
        }
        closedir (dir);
    }
    else {
        perror ("");
        return EXIT_FAILURE;
    }
    return 0;
}
std::string flThemes::getPanelLabel(){
    tinyxml2::XMLElement* panelElement = themeDoc.FirstChildElement( "JWM" )->FirstChildElement("Tray");
    std::string Label = "Apps";
    //std::string root = "root";
    //unsigned int found;
    std::string txt ="";
    //std::string text ="";
    for(panelElement = panelElement->FirstChildElement( "TrayButton" );
        panelElement;
        panelElement = panelElement->NextSiblingElement("TrayButton" )){
            txt = panelElement->GetText();
            //found = txt.find_first_of(":");
            //text=txt.substr(0,found);
            //std::cout<<txt<<std::endl;
            if(txt.compare("root:5")==0){
                if(panelElement->Attribute("label")){Label=panelElement->Attribute("label");}
                else{Label="";}
            }
    }
    return Label;
}
std::string flThemes::getPanelButtonIcon(){
    tinyxml2::XMLElement* panelElement = themeDoc.FirstChildElement( "JWM" )->FirstChildElement("Tray");
    std::string Icon = "/usr/share/pixmaps/distributor-logo.png";
    //std::string root = "root";
    //unsigned int found;
    std::string txt ="";
    //std::string text ="";
    for(panelElement = panelElement->FirstChildElement( "TrayButton" );
        panelElement;
        panelElement = panelElement->NextSiblingElement("TrayButton" )){
            txt = panelElement->GetText();
            //found = txt.find_first_of(":");
            //text=txt.substr(0,found);
            //std::cout<<text<<std::endl;
            if(txt.compare("root:5")==0){
                if(panelElement->Attribute("label")){Icon=panelElement->Attribute("icon");}
                else{Icon="/usr/share/pixmaps/distributor-logo.png";}
            }
    }
    return Icon;
}

int flThemes::loadTheme(std::string themePath){
    themeDoc.LoadFile( themePath.c_str() );
    if (themeDoc.ErrorID() !=0){std::cerr<<"An error occured loading "<<themePath<<std::endl; return 42;}
    else{std::cout<<"loaded: "<<themePath<<std::endl;}
    return 0;
}
void flThemes::checkThemeVersion(){
    bool text = false;
    bool title =false;
    bool inactive =false;
    tinyxml2::XMLElement* element = themeDoc.FirstChildElement( "JWM" );
    if ((element)->FirstChildElement("WindowStyle")->FirstChildElement("Active")->FirstChildElement("Text")){text=true;}
    if ((element)->FirstChildElement("WindowStyle")->FirstChildElement("Active")->FirstChildElement("Title")){title=true;}
    if ((element)->FirstChildElement("WindowStyle")->FirstChildElement("Inactive")){inactive=true;}
    if(text || title || inactive){ isNewTheme=false;}
    else{isNewTheme=true;}
}
void flThemes::updateTheme(Fl_Box * button, Fl_Box * button_icon, Fl_Box *tray, Fl_Box *activeW,Fl_Box *activeW2,Fl_Box *activeW_text, Fl_Box *inactiveW, Fl_Box *inactiveW2,Fl_Box *inactiveW_text,Fl_Box *active_min_button, Fl_Box *active_max_button, Fl_Box *active_close_button, Fl_Box *inactive_min_button, Fl_Box *inactive_max_button, Fl_Box *inactive_close_button,std::string filename){
    int testLoad = loadTheme(filename);
    if (testLoad !=0){return;}
    checkThemeVersion();

//menu buttons
    std::string maxButton = getMaxButton();
    std::string minButton = getMinButton();
    std::string closeButton = getCloseButton();

    //These should never be empty
    // but let's check anyhow.
    if (minButton.compare("")!=0){
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
    if (maxButton.compare("")!=0){
        Fl_Image * MAX;
        MAX = new Fl_PNG_Image(maxButton.c_str());
        Fl_Image * MAX2 = MAX->copy(25,25);
        active_max_button->image(MAX2);
        inactive_max_button->image(MAX2);
        active_max_button->redraw();
        inactive_max_button->redraw();
    }
    if (closeButton.compare("")!=0){
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
    unsigned int activeWindowColor = getActiveWindow(active_color2);
    unsigned int activeWindowColorText = getActiveWindowText();
    activeW->color(activeWindowColor);
    activeW2->color(active_color2);
    activeW_text->labelcolor(activeWindowColorText);
    activeW->redraw();
    activeW2->redraw();
    activeW_text->redraw();
    unsigned int inactive_color2=0;
    unsigned int windowColor = getWindow(inactive_color2);
    unsigned int windowColorText = getWindowText();
    inactiveW->color(windowColor);
    inactiveW2->color(inactive_color2);
    inactiveW_text->labelcolor(windowColorText);
    inactiveW->redraw();
    inactiveW2->redraw();
    inactiveW_text->redraw();

//Panel
    std::string label = getPanelLabel();
    //std::cout<<label<<std::endl;
    unsigned int panelColor = getPanel();
    unsigned int panelColorText = getPanelText();
    tray->color(panelColor);//labelcolor
    tray->labelcolor(panelColorText);
    tray->redraw();
//panel Button
    unsigned int panelButtonColor = getPanelButton();
    unsigned int panelButtonColorText = getPanelButtonText();
    button->copy_label(label.c_str());
    button->color(panelButtonColor);
    button->labelcolor(panelButtonColorText);
    button->redraw();
    std::string icon_file = getPanelButtonIcon();
    Fl_Image * icon;
    icon = new Fl_PNG_Image(icon_file.c_str());
	Fl_Image * icon2 = icon->copy(30,30);
	button_icon->image(icon2);
    button_icon->color(panelButtonColor);
    button_icon->redraw();
}
///get text from an Element
std::string flThemes::getThemeItemText(const char* whichOne){
    tinyxml2::XMLElement* Element;
    Element  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichOne );
    if(Element){return Element->GetText();}
    return "";
}
/// 2 Color getter
unsigned int flThemes::getThemeItemInt(const char * whichElement, const char* whatToGet,unsigned int &color2){
    tinyxml2::XMLElement* colorElement;
    colorElement  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    unsigned int bg = getColor(colour, color2);
    return bg;
}

/// 1 Color for Panel and new Inactive winodws
unsigned int flThemes::getThemeItemInt(const char * whichElement, const char* whatToGet){
    tinyxml2::XMLElement* colorElement;
    colorElement  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    unsigned int color2 = 0;
    unsigned int bg = getColor(colour, color2);
    return bg;
}

/// 2 Colors for Active windows and old style
unsigned int flThemes::getTheme2ItemInt(const char * whichElement, const char * whichElement2, const char* whatToGet,unsigned int &color2){
    tinyxml2::XMLElement* colorElement;
    colorElement  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( whichElement2 )->
                        FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    unsigned int bg = getColor(colour, color2);
    return bg;
}

///Panel getters
unsigned int flThemes::getPanel(){return getThemeItemInt("TrayStyle","Background");}
unsigned int flThemes::getPanelButton(){return getThemeItemInt("TrayButtonStyle","Background");}
unsigned int flThemes::getPanelText(){return getThemeItemInt("TrayStyle","Foreground");}
unsigned int flThemes::getPanelButtonText(){return getThemeItemInt("TrayButtonStyle","Foreground");}

///Window getters
unsigned int flThemes::getWindow(unsigned int &color2){
    unsigned int result = 0;
    if(isNewTheme){result = getThemeItemInt("WindowStyle","Background", color2);}
    else{result = getTheme2ItemInt("WindowStyle","Inactive","Title", color2);}
    return result;
}

unsigned int flThemes::getActiveWindow(unsigned int &color2){
    unsigned int result= 0;
    if(isNewTheme){result = getTheme2ItemInt("WindowStyle","Active","Background", color2);}
    else{result = getTheme2ItemInt("WindowStyle","Active","Title", color2);}
    return result;
}

unsigned int flThemes::getWindowText(){
    unsigned int color=0;
    unsigned int result = 0;
    if(isNewTheme){result = getThemeItemInt("WindowStyle","Foreground",color);}
    else{result = getTheme2ItemInt("WindowStyle","Inactive","Text",color);}
    return result;
}

unsigned int flThemes::getActiveWindowText(){
    unsigned int color=0;
    unsigned int result= 0;
    if(isNewTheme){result = getTheme2ItemInt("WindowStyle","Active","Foreground",color);}
    else{result = getTheme2ItemInt("WindowStyle","Active","Text",color);}
    return result;
}

bool flThemes::themesExist(){
    struct stat sb;
    std::string userHomePath = homePathNoFile();
    const char* themeDir = themePATH.c_str();
    if (stat(themeDir, &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    else {return false;}
}
bool flThemes::oldThemesExist(){
    struct stat sb;

    std::string userHomePath = homePathNoFile();
    const char* themeDir = OLDthemePATH.c_str();
    if (stat(themeDir, &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    else {return false;}
}
bool flThemes::checkForTheme(std::string theme){return testFile(theme.c_str());}

void flThemes::copier(std::string theme){
    bool existant = themesExist();
    if (existant){
        existant=checkForTheme(theme);
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
    else {errorJWM("Theme directory doesn't exist, cannot copy\n");}
}
void flThemes::other(const char* themeName){
    std::string theme = std::string(themeName);
    copier(theme);
}
void flThemes::change(const char* themeName){
    std::string stringTheme = std::string(themeName);
    std::string themeTest;
    std::string theme;
    bool existant = false;
    if(isOLDjwmrc){
        existant = oldThemesExist();
        theme = OLDthemePATH + stringTheme + "/" + stringTheme;
        themeTest = OLDthemePATH + stringTheme + "/";
    }
    else{
        existant = themesExist();
        theme = themePATH + stringTheme + "/" + stringTheme;
        themeTest = themePATH + stringTheme + "/";
    }
    if (existant){
        existant = checkForTheme(themeTest);
        if (!existant){
            errorJWM("Theme doesn't exist, cannot get it\n");
            return;
        }
        copier(theme);
    }
    else {errorJWM("Theme directory doesn't exist, cannot change theme\n");}
}
int flThemes::saveAs(const char* filename){
    bool existant = themesExist();
    std::string theme = filename;
    if (existant){
        if(theme.compare("")!=0){
            std::string copyTheme = bash+"cp "+ path +".jwmrc "+ filename+"'";
            if(system(copyTheme.c_str())!=0){
                std::string message =copyTheme +" failed please use a correct path";
                errorJWM(message);
                return 12;
            }
            std::cout<<copyTheme<<'\n';
            return 0;
        }
    }
    else {errorJWM("Incorrect filename cannot copy theme");}
    return 1;
}
void flThemes::userTheme(){
    if(system(userThemeName.c_str())!=0){
        std::cout<<userThemeName<<error;
    }
}

const char* flThemes::getTheme(const char* whichTheme){
    std::string stringTheme = std::string(whichTheme);
    std::string themeTest;
    std::string theme;
    bool existant = false;
    if(isOLDjwmrc){
        existant = oldThemesExist();
        theme = OLDthemePATH + stringTheme + "/" + stringTheme;
        themeTest = OLDthemePATH + stringTheme + "/";
    }
    else{
        existant = themesExist();
        theme = themePATH + stringTheme + "/" + stringTheme;
        themeTest = themePATH + stringTheme + "/";
    }
    if (existant){
        existant = checkForTheme(themeTest);
        if (!existant){
            errorJWM("Theme doesn't exist, cannot get it\n");
            return "ERROR";
        }
        return (themeTest.c_str());

    }
    else {errorJWM("Theme directory doesn't exist, cannot GET THE THEME\n");}
    return "Themes don't exist";
}
