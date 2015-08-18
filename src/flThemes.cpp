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
#ifdef DEBUG_TRACK
  std::cerr<<"[flThemes]->"<<std::endl;
#endif // DEBUG
//TODO: XDG_DATA_DIRS to get initial /usr/share (or whatever)
    mydefaultPath= getDefaultFilepath();
    themePATH = mydefaultPath + "themes/";
    themePATH230 = mydefaultPath + "themes/2.3.0/";
    OLDthemePATH = mydefaultPath + "themes/old/";
    path = homePathNoFile(); ///Config function
    userThemePATH =path+".jwm/themes/";
    userThemeName = "/bin/bash -c 'cp -f " + path + ".usertheme " + path + ".jwmrc'";
    bash = "/bin/bash -c '";
    error =" failed please report this bug \n";
    isOLDjwmrc = newStyle();///Config function
    isNewTheme = false;
}

flThemes::~flThemes(){
#ifdef DEBUG_TRACK
  std::cerr<<"<-[flThemes]"<<std::endl;
#endif // DEBUG
}
bool flThemes::isSVG(std::string filename){
    std::string extention;
    extention = filename.substr((strlen(filename.c_str())-4),4);
    std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
    std::string svg =".svg";
    if(extention.compare(svg) ==0){
        if(DEBUG_ME){std::cerr<<"SVG image"<<std::endl;}
        return true;
    }
    if(DEBUG_ME){std::cerr<<filename << " is not SVG"<<std::endl;}
    return false;
}
std::string flThemes::sysThemeDir(){
    if (isOLDjwmrc == -1){return OLDthemePATH;}
    else if (isOLDjwmrc == 0){return themePATH230;}
    return themePATH;
}
int flThemes::populateUserThemes(Fl_Browser *o){

    DIR *dir = NULL;
    std::string itemName;
    std::string checkHERE;
    struct dirent *ent= NULL;
    if ((dir = opendir (userThemePATH.c_str())) != NULL) {
        o->clear();
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
    o->redraw();
    return 0;
}
int flThemes::populateThemes(Fl_Browser *o){
    DIR *dir=NULL;
    std::string itemName;
    std::string checkHERE;
    if (isOLDjwmrc == -1){checkHERE = OLDthemePATH;}
    else if (isOLDjwmrc == 0){ checkHERE = themePATH230;}
    else{
        checkHERE=themePATH;
    }
    struct dirent *ent=NULL;
    if ((dir = opendir (checkHERE.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            itemName=ent->d_name;
            itemName=itemName.substr(0,(itemName.length()));
            if ((itemName.compare(".")==0)||(itemName.compare("..")==0)||(itemName.compare("old")==0)){
                //DO NOTHING
            }
            else{
                if(DEBUG_ME){std::cerr<<itemName<<" added"<<std::endl;}
                o->add(itemName.c_str());
            }
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
    std::string Label = gettext("Apps");
    //std::string root = "root";
    //unsigned int found;
    std::string txt ="";
    //std::string text ="";
    for(panelElement = panelElement->FirstChildElement( "TrayButton" );
        panelElement;
        panelElement = panelElement->NextSiblingElement("TrayButton" )){
            if(panelElement->FirstChildElement("Button")){
                if(panelElement->FirstChildElement("Button")->GetText()){txt = panelElement->FirstChildElement("Button")->GetText();}
            }
            else{
                if(panelElement->GetText()){txt = panelElement->GetText();}
            }


            //found = txt.find_first_of(":");
            //text=txt.substr(0,found);
            if(DEBUG_ME){std::cerr<<"found text: "<<txt<<std::endl;}
            if(txt.compare("root:5")==0){
                if(panelElement->Attribute("label")){
                    Label=panelElement->Attribute("label");
                    if(DEBUG_ME){std::cerr<<txt<<" matches!!!"<<std::endl;}
                    return Label;
                }
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
            if(panelElement->FirstChildElement("Button")){
                if(panelElement->FirstChildElement("Button")->GetText()){txt = panelElement->FirstChildElement("Button")->GetText();}
            }
            else{
                if(panelElement->GetText()){txt = panelElement->GetText();}
            }
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
    else{
        if(DEBUG_ME){std::cerr<<"Theme loaded: "<<themePath<<std::endl;}
    }
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
int flThemes::themeNewStyle(){
#ifdef DEBUG_TRACK
std::cerr << "themeNewStyle()-->"<<std::endl;
#endif // DEBUG_TRACK
    const char* button = "TrayButtonStyle";
    const char* tray = "TrayStyle";
    const char* task = "TaskListStyle";
    const char* pager = "PagerStyle";
//    const char* win = "WindowStyle";
//    const char* menu = "MenuStyle";
    const char* afore ="ActiveForeground";
    const char* aback = "ActiveBackground";
    int not23 = -1; //OLD
    int two30 = 0; // version before removing traybutton/tasklist styles
    int two3later = 1; //2.3.2 ++
    if(DEBUG_ME){std::cerr<<"loading theme"<<std::endl;}
    tinyxml2::XMLElement* element = themeDoc.FirstChildElement( "JWM" );
    if(DEBUG_ME){std::cerr<<"testing theme"<<std::endl;}
    if( !(element->FirstChildElement("TrayButtonStyle")) &&
        !(element->FirstChildElement("TaskListStyle")) &&
        !(element->FirstChildElement("ClockStyle")) ){
        if(DEBUG_ME){std::cerr<<"this is an NEW (2.3.2++) theme, returning:"<<two3later<<"\n<--themeNewStyle()"<<std::endl;}
        return two3later;
    }
    //OLD STYLE
    if (    (element->FirstChildElement(tray)->FirstChildElement(aback)) ||
            (element->FirstChildElement(task)->FirstChildElement(aback)) ||
            (element->FirstChildElement(pager)->FirstChildElement(aback)) ||
            (element->FirstChildElement(button)->FirstChildElement(aback)) ||
            (element->FirstChildElement(tray)->FirstChildElement(afore)) ||
            (element->FirstChildElement(task)->FirstChildElement(afore)) ||
            (element->FirstChildElement(pager)->FirstChildElement(afore)) ||
            (element->FirstChildElement(button)->FirstChildElement(afore))
       ){
       if(DEBUG_ME){
       std::cerr<<"this is an OLD theme, returning:"<<not23<<"\n<--themeNewStyle()"<<std::endl;
       }
       return not23;
    }
    if(DEBUG_ME){std::cerr<<"this is an NEW (2.3.0 || 2.3.1) theme, returning:"<<two30<<"\n<--themeNewStyle()"<<std::endl;}
    return two30;
}
///This function modified the current .jwmrc to use the colors (etc) from the theme file
void flThemes::modCurrentTheme( Fl_Box * button,
                                Fl_Box * button_icon,
                                Fl_Box *tray,
                                Fl_Box *activeW,
                                Fl_Box *activeW2,
                                Fl_Box *activeW_text,
                                Fl_Box *inactiveW,
                                Fl_Box *inactiveW2,
                                Fl_Box *inactiveW_text,
                                std::string filename ){
    int testLoad = loadTheme(filename);
    if (testLoad !=0){return;}
    checkThemeVersion();

    flWindow win;
///window buttons   modCurrentTheme
    //get the theme's values
    std::string maxButton = getMaxButton();
    std::string minButton = getMinButton();
    std::string closeButton = getCloseButton();
    std::string maxActiveButton = getMaxActiveButton();

    //set the jwmrc to have the theme's values
    if ( (minButton.compare("")!=0) ){win.setButton(minButton.c_str(),"ButtonMin");}
    if ( (maxButton.compare("")!=0) ){win.setButton(maxButton.c_str(),"ButtonMax");}
    if ( (maxActiveButton.compare("")!=0) ){win.setButton(maxActiveButton.c_str(),"ButtonMaxActive");}
    if ( (closeButton.compare("")!=0) ){win.setButton(closeButton.c_str(),"ButtonClose");}

///windows    modCurrentTheme
    //get the theme's values
    const double* active_color2=getItemColor(activeW2);
    const double* activeWindowColor = getItemColor(activeW);
    const double* activeWindowColorText = getItemColor(activeW_text);
    const double* inactive_color2=getItemColor(inactiveW2);
    const double* windowColor = getItemColor(inactiveW);
    const double* windowColorText = getItemColor(inactiveW_text);

    //set the jwmrc to have the theme's values
    if(DEBUG_ME){
    std::cerr<<"ACTIVE window color= "<<colorToString(activeWindowColor)<<":"<<colorToString(active_color2)
    <<"\nACTIVE font color= "<<colorToString(activeWindowColorText)
    <<"\ninactive window color= "<<colorToString(windowColor)<<":"<<colorToString(inactive_color2)
    <<"\ninactive font color= "<<colorToString(windowColorText)<<std::endl;
    }
    win.setActiveWindowColor(activeWindowColor,active_color2);
    win.setActiveFontColor(activeWindowColorText);
    win.setWindowColor(windowColor,inactive_color2);
    win.setFontColor(windowColorText);

    flPanel panel;
    loadTemp();
///Panel    modCurrentTheme
    //std::string label = getPanelLabel();
    //get the theme's values
    const double* panelColor = getItemColor(tray);
    unsigned int panel_themeTextColor = getPanelText();
    const double* panelColorText = convertINTcolor2Double(panel_themeTextColor);

    //set the jwmrc to have the theme's values
    panel.setBackground(panelColor,"TrayStyle");
    panel.setFontColor(panelColorText,"TrayStyle");

/// /////Don't do this if we are using the newest version.. because it doesn't exist
if(themeNewStyle()<1){
///panel Button     modCurrentTheme
    //get the theme's values
    const double* panelButtonColor = getItemColor(button);
    unsigned int panel_themeButtonColor = getPanelButtonText();
    const double* panelButtonColorText = convertINTcolor2Double(panel_themeButtonColor);
    //std::string icon_file = getPanelButtonIcon();

    //set the jwmrc to have the theme's values
    panel.setBackground(panelButtonColor,"TrayButtonStyle");
    panel.setFontColor(panelButtonColorText,"TrayButtonStyle");
    //panel.setMenuImage(icon_file.c_str());

///tasklist     modCurrentTheme
    //get the theme's values
    unsigned int task_fg = getTaskFG();
    unsigned int task_bg = getTaskBG();
    unsigned int task_active_fg = getTaskActiveFG();
    unsigned int task_active_bg = getTaskActiveBG();

    //set the jwmrc to have the theme's values
    panel.setBackground(convertINTcolor2Double(task_bg),"TaskListStyle");
    panel.setActiveBackground(convertINTcolor2Double(task_active_bg),"TaskListStyle");
    panel.setActiveFontColor(convertINTcolor2Double(task_active_fg),"TaskListStyle");
    panel.setFontColor(convertINTcolor2Double(task_fg),"TaskListStyle");
}/// /////END Don't do this



///menus    modCurrentTheme
    //get the theme's valuesq
    unsigned int menu_fg = getMenuFG();
    unsigned int menu_bg = getMenuBG();
    unsigned int menu_active_fg = getMenuActiveFG();
    unsigned int menu_active_bg = getMenuActiveBG();

    //set the jwmrc to have the theme's values
    panel.setBackground(convertINTcolor2Double(menu_bg),"MenuStyle");
    panel.setActiveBackground(convertINTcolor2Double(menu_active_bg),"MenuStyle");
    panel.setActiveFontColor(convertINTcolor2Double(menu_active_fg),"MenuStyle");
    panel.setFontColor(convertINTcolor2Double(menu_fg),"MenuStyle");

///SAVE THE MODIFICATIONS TO THE .jwmrc FILE
    saveChanges();
}//END  //modCurrentTheme(std::string filename)




/// this  function updates the FLTK UI to reflect the colors of the theme file that is chosen
void flThemes::updateTheme( Fl_Box * button,
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
                            std::string filename){

    int testLoad = loadTheme(filename);
    if (testLoad !=0){return;}
    //checkThemeVersion();

//menu buttons
    std::string maxButton = getMaxButton();
    std::string minButton = getMinButton();
    std::string closeButton = getCloseButton();

    //These should never be empty
    // but let's check anyhow.
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
    unsigned int active_color2 = getActiveWindow2();
    unsigned int activeWindowColor = getActiveWindow();
    unsigned int activeWindowColorText = getActiveWindowText();

    //modify the UI
    activeW->color(activeWindowColor);
    activeW2->color(active_color2);
    activeW_text->labelcolor(activeWindowColorText);
    activeW->redraw();
    activeW2->redraw();
    activeW_text->redraw();

    unsigned int inactive_color2=0;
    unsigned int windowColor = getWindow(inactive_color2);
    unsigned int windowColorText = getWindowText();

    //modify the UI
    inactiveW->color(windowColor);
    inactiveW2->color(inactive_color2);
    inactiveW_text->labelcolor(windowColorText);
    inactiveW->redraw();
    inactiveW2->redraw();
    inactiveW_text->redraw();

//Panel
    std::string label = getPanelLabel();
    if(DEBUG_ME){std::cerr<<"LABEL: "<<label<<std::endl;}
    unsigned int panelColor = getPanel();
    if(DEBUG_ME){std::cerr<<"panelColor: "<<panelColor<<std::endl;}
    unsigned int panelColorText = getPanelText();
    if(DEBUG_ME){std::cerr<<"panelColorText: "<<panelColorText<<std::endl;}
    //modify the UI
    tray->color(panelColor);//labelcolor
    tray->labelcolor(panelColorText);
    tray->redraw();

    //panel Button
    unsigned int panelButtonColorText;
    unsigned int panelButtonColor;
    //New version
    if(themeNewStyle()<1){
        panelButtonColor = getPanelButton();
        panelButtonColorText = getPanelButtonText();
    }//END Dont do this IF new version
    else{
        panelButtonColor=panelColor;
        panelButtonColorText = panelColorText;
    }
    //if(Config::DEBUG_ME){std::cerr<<"panelButtonColor: "<<panelButtonColor<<"\npanelButtonColorText: "<<panelButtonColorText<<std::endl;}DEBUG
//modify the UI
    button->copy_label(label.c_str());
    button->color(panelButtonColor);
    button->labelcolor(panelButtonColorText);
    button_icon->color(panelButtonColor);
    button->redraw();

    std::string icon_file = getPanelButtonIcon();
    //if(Config::DEBUG_ME){std::cerr<<"icon_file: "<<icon_file<<std::endl;}
    if(!isSVG(icon_file)){
        Fl_Image * icon;
        icon = new Fl_PNG_Image(icon_file.c_str());
        Fl_Image * icon2 = icon->copy(30,30);
        //modify the UI
        button_icon->image(icon2);
    }
    button_icon->redraw();
}

//used in update and modification of theme window, and theme files to convert an INT to a CONST DOUBLE *
const double* flThemes::convertINTcolor2Double(unsigned int colorToConvert){
    uchar r;
    uchar g;
    uchar b;
    Fl::get_color(colorToConvert,r,g,b);
    double* colors = new double[4];
    colors[0] = int(r);
    colors[1] = int(g);
    colors[2] = int(b);
    colors[3] = 0;
    return colors;
}
const double* flThemes::getItemColor(Fl_Box*o){
    unsigned int thisColor = Fl::get_color(o->color());
    return convertINTcolor2Double(thisColor);
}


///USED in TaskList Menu and Panel getters
unsigned int flThemes::getActiveFG(const char* whichElement){
    unsigned int result= 0;
    if(isNewTheme){result = getTheme2ItemInt(whichElement,"Active","Foreground");}
    else{result = getThemeItemInt(whichElement,"ActiveForeground");}
    return result;
}
unsigned int flThemes::getActiveBG(const char* whichElement){
    unsigned int result= 0;
    if(isNewTheme){result = getTheme2ItemInt(whichElement,"Active","Background");}
    else{result = getThemeItemInt(whichElement,"ActiveBackground");}
    return result;
}
///get text from an Element
std::string flThemes::getThemeItemText(const char* whichOne){
    tinyxml2::XMLElement* Element;
    Element  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichOne );
    if(Element){
        std::string value= Element->GetText();
        if (value.compare("")!=0){
            return value.c_str();
        }
    }
    return "";
}
/// 2 Color getter
unsigned int flThemes::getThemeItemInt(const char * whichElement, const char* whatToGet,unsigned int &color2){
    unsigned int bg =0;
    tinyxml2::XMLElement* colorElement= themeDoc.FirstChildElement( "JWM" );
    if(colorElement->FirstChildElement( whichElement )){
        if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( whatToGet )){return 0;}
    }
    else {return 0;}
    colorElement =colorElement->FirstChildElement( whichElement )->FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    if (colour.compare("")!=0){
        bg = getColor(colour, color2);
        return bg;
    }
    return bg;
}

/// 1 Color for Panel and new Inactive winodws
unsigned int flThemes::getThemeItemInt(const char * whichElement, const char* whatToGet){
    unsigned int bg =0;
    tinyxml2::XMLElement* colorElement= themeDoc.FirstChildElement( "JWM" );
    if(colorElement->FirstChildElement( whichElement )){
        if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( whatToGet )){return 0;}
    }
    else {return 0;}
    colorElement =colorElement->FirstChildElement( whichElement )->FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    if (colour.compare("")!=0){
        unsigned int color2 = 0;
        bg = getColor(colour, color2);
    }
    return bg;
}

/// 2 Colors for Active windows and old style
unsigned int flThemes::getTheme2ItemInt(const char * whichElement, const char * whichElement2, const char* whatToGet){
    unsigned int bg =0;
    tinyxml2::XMLElement* colorElement= themeDoc.FirstChildElement( "JWM" );

    //make sure Element exists, otherwise return 0;
    if(colorElement->FirstChildElement( whichElement )){
        if(colorElement->FirstChildElement( whichElement )->FirstChildElement( whichElement2 )){
            if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( whichElement2 )->FirstChildElement( whatToGet )){
                if(DEBUG_ME){std::cerr<<"getTheme2ItemInt()\n\n<"<<whichElement<<">\n\t<"<<whichElement2<<">\n\t<\\"<<whichElement2<<">\n<\\"<<whichElement<<">\ndoesn't exist"<<std::endl;}
                return 0;
            }
        }
        else {return 0;}
    }
    else {return 0;}

    colorElement  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( whichElement2 )->
                        FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    if (colour.compare("")!=0){
        unsigned int color2 = 0;
        bg = getColor(colour, color2);
    }
    return bg;
}
unsigned int flThemes::getTheme2ItemInt_secondColor(const char * whichElement, const char * whichElement2, const char* whatToGet){
    unsigned int bg = 0;
    tinyxml2::XMLElement* colorElement= themeDoc.FirstChildElement( "JWM" );

    //make sure Element exists, otherwise return 0;
    if(colorElement->FirstChildElement( whichElement )){
        if(colorElement->FirstChildElement( whichElement )->FirstChildElement( whichElement2 )){
            if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( whichElement2 )->FirstChildElement( whatToGet )){
                if(DEBUG_ME){std::cerr<<"getTheme2ItemInt_secondColor()\n\n<"<<whichElement<<">\n\t<"<<whichElement2<<">\n\t<\\"<<whichElement2<<">\n<\\"<<whichElement<<">\ndoesn't exist"<<std::endl;}
                return bg;
            }
        }
        else {return bg;}
    }
    else {return bg;}

    colorElement  = themeDoc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( whichElement2 )->
                        FirstChildElement( whatToGet );
    std::string colour = colorElement->GetText();
    unsigned int color2 = 1;
    if (colour.compare("")!=0){
        unsigned int color2 = 0;
        bg = getColor(colour, color2);
        return color2;
    }
    return color2;
}
///Window getters
unsigned int flThemes::getWindow(unsigned int &color2){
    unsigned int result = 0;
    if(themeNewStyle()!=-1){result = getThemeItemInt("WindowStyle","Background", color2);}
    else{result = getTheme2ItemInt("WindowStyle","Inactive","Title");}
    return result;
}
unsigned int flThemes::getWindow_secondColor(){
    unsigned int result = 0,color2=0;
    if(themeNewStyle()!=-1){result = getThemeItemInt("WindowStyle","Background", color2);}
    else{result = getTheme2ItemInt_secondColor("WindowStyle","Inactive","Title");}
    return result;
}

unsigned int flThemes::getActiveWindow(){
    unsigned int result= 0;
    if(themeNewStyle()!=-1){result = getTheme2ItemInt("WindowStyle","Active","Background");}
    else{result = getTheme2ItemInt("WindowStyle","Active","Title");}
    return result;
}
unsigned int flThemes::getActiveWindow2(){
#ifdef DEBUG_TRACK
std::cerr<<"getActiveWindow2()-->"<<std::endl;
#endif // DEBUG
    unsigned int result= 0;
    if(themeNewStyle()!=-1){result = getTheme2ItemInt_secondColor("WindowStyle","Active","Background");}
    else{result = getTheme2ItemInt_secondColor("WindowStyle","Active","Title");}
#ifdef DEBUG_TRACK
std::cerr<<"<--getActiveWindow2() returns: "<<result<<std::endl;
#endif // DEBUG
    return result;
}
unsigned int flThemes::getWindowText(){
    unsigned int color=0;
    unsigned int result = 0;
    if(themeNewStyle()!=-1){result = getThemeItemInt("WindowStyle","Foreground",color);}
    else{result = getTheme2ItemInt("WindowStyle","Inactive","Text");}
    return result;
}

unsigned int flThemes::getActiveWindowText(){
    unsigned int result= 0;
    if(themeNewStyle()!=-1){result = getTheme2ItemInt("WindowStyle","Active","Foreground");}
    else{result = getTheme2ItemInt("WindowStyle","Active","Text");}
    return result;
}

/// make sure the THEME directory exists
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

//test the theme file to make sure it exists
bool flThemes::checkForTheme(std::string theme){return testFile(theme.c_str());}

//overwrite the current jwmrc with the theme file
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

//save the current modified theme to a user theme
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
//DO I NEED THIS STILL???
void flThemes::other(const char* themeName){
    std::string theme = std::string(themeName);
    copier(theme);
}
void flThemes::change(const char* themeName){
    std::string stringTheme = std::string(themeName);
    std::string themeTest;
    std::string theme;
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
            errorJWM("Theme doesn't exist, cannot get it\n");
            return;
        }
        copier(theme);
    }
    else {errorJWM("Theme directory doesn't exist, cannot change theme\n");}
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
            errorJWM("Theme doesn't exist, cannot get it\n");
            return "ERROR";
        }
        return (themeTest.c_str());

    }
    else {errorJWM("Theme directory doesn't exist, cannot GET THE THEME\n");}
    return "Themes don't exist";
}
