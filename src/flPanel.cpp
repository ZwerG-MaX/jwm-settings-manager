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
#include "../include/flPanel.h"
flPanel::flPanel(){
    tinyxml2::XMLDocument doc;
    whichPanel = 1;
    errorMessage="Error... Don't hack around in the files so much ok? :D";
    torimenu = "torimenu";
    gnomemenu = "gnomeapps";
    sysmenu = "gnomesystem";
    rootMenu = 5;
    systemMenu = 8;
    isNewStyle = newStyle();

}


flPanel::~flPanel(){}

///             TESTER
bool flPanel::test(tinyxml2::XMLElement *element){
    const char *tester = element->GetText();
    if (tester==NULL){
        recover();
        return false;
    }
    else return true;
}

///************************************  MULTIPLE PANELS  *************************************************

            ///ADD PANEL

void flPanel::addPanel(){
//    const char* functionName = "void addPanel()";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->LastChildElement( "Tray" );
    tinyxml2::XMLNode *node = panelElement;
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    tray->InsertAfterChild(node,newTray);
    saveChangesTemp();
    const char* position = smartPosition();
    const char* align = smartAlign(position);
    int vertORhoriz = whichAlign(align);
    //std::cerr<<"position: "<<position<<" vertORhoriz: "<<vertORhoriz<<" align: "<<align<<std::endl;
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    newTray->InsertEndChild(spacer);
    tinyxml2::XMLElement *thisone = newTray->ToElement();
    thisone->SetAttribute("layout",position);
   if(vertORhoriz == 1){
        thisone->SetAttribute("valign",align);
        thisone->SetAttribute("halign","fixed");
        thisone->SetAttribute("width",0);
        thisone->SetAttribute("height",34);
    }
    else if(vertORhoriz == 2){
        thisone->SetAttribute("valign","fixed");
        thisone->SetAttribute("halign",align);
        thisone->SetAttribute("width",55);
        thisone->SetAttribute("height",200);
    }
    else{
        thisone->SetAttribute("valign","center");
        thisone->SetAttribute("halign","center");
        thisone->SetAttribute("width",0);
        thisone->SetAttribute("height",34);
    }
    thisone->SetAttribute("border","false");
    saveChangesTemp();
    updatePanels(numPanels());
}

            ///Delete Panel
void flPanel::deletePanel(){
   // loadTemp();
    int i = 1;
    int panel = currentPanel();
    int num = numPanels();
    if (num ==1 ){return;}
    tinyxml2::XMLElement* Base = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLNode * node = panelElement;
    Base->DeleteChild(node);
    saveChangesTemp();
    saveChanges();
}

const char* flPanel::horizontalORvertical(int horizontalValue, int verticalValue){
    const char* horizontal = "horizontal";
    const char* vertical= "vertical";
    if((horizontalValue == 0)){return horizontal;}
    else if ((horizontalValue ==1)&&(verticalValue == 0)){return horizontal;}
    else if((horizontalValue==2) && (verticalValue == 0)){return vertical;}
    else if(horizontalValue>verticalValue){return vertical;}
    else if((verticalValue>=2) && (horizontalValue == 1)){return horizontal;}
    else if(verticalValue>horizontalValue){return horizontal;}
    else if (verticalValue == horizontalValue){ return vertical;}
    else {return "center";}
}


                        /// SMART ALIGNMENT  ########################################################
const char* flPanel::smartPosition(){
//TODO: check all panels and find ALL alignments to figure things out.
//    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
   // loadTemp();
    const char* smartiePosition ="";
    int horizontl = 1, verticl = 0, errors = 0;
    std::string layout,lay;
    std::list<std::string> layouts;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    while(panelElement->NextSiblingElement("Tray")){
        panelElement=panelElement->NextSiblingElement("Tray");
        if(panelElement->Attribute("layout")){
            lay = panelElement->Attribute("layout");
            layouts.push_back(lay);
        }
    }
    for (std::list<std::string>::iterator it = layouts.begin(); it != layouts.end(); ++it){
        layout = *it;
        if(layout.compare("horizontal")==0){++horizontl;}
        else if(layout.compare("vertical")==0){++verticl;}
        else {errors++;}
    }
    if (errors != 0){std::cerr<<"Something is wrong with smartPosition()"<<std::endl;}
    //std::cout<<"horizontl: "<<horizontl<<" verticl: "<<verticl<<std::endl;
    smartiePosition = horizontalORvertical(horizontl,verticl);
    return smartiePosition;
}

const char* flPanel::smartAlign(const char* layout){
   // loadTemp();
    std::string layoutSTRING = layout;
    std::string valign,halign,vLayout,hLayout;
    std::list<std::string> valignLayouts;
    std::list<std::string> halignLayouts;
    int valignCounter = 0;
    int halignCounter = 0;
    int top = 0, bottom = 0, left = 0, right = 0, otherH = 0, otherV = 0;
    const char* smartieAlign;

    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if(layoutSTRING.compare("horizontal")==0){
        while(panelElement->NextSiblingElement("Tray")){
            panelElement=panelElement->NextSiblingElement("Tray");
            if(panelElement->Attribute("valign")){
                valign = panelElement->Attribute("valign");
                valignLayouts.push_back(valign);
                valignCounter++;
            }
        }
        for (std::list<std::string>::iterator it = valignLayouts.begin(); it != valignLayouts.end(); ++it){
            vLayout = *it;
            if(vLayout.compare("top")==0){top++;}
            else if(vLayout.compare("bottom")==0){bottom++;}
            else {otherV++;}
        }
        if (top==1 && bottom == 0){smartieAlign ="bottom";}
        else if (top==0 && bottom == 1){smartieAlign ="top";}
        else if (top==0 && bottom == 0){smartieAlign ="bottom";}
        else{smartieAlign ="top";}
    }
    else{
        while(panelElement->NextSiblingElement("Tray")){
            panelElement=panelElement->NextSiblingElement("Tray");
            if(panelElement->Attribute("halign")){
                halign = panelElement->Attribute("halign");
                halignLayouts.push_back(halign);
                halignCounter++;
            }
        }
        for (std::list<std::string>::iterator it = halignLayouts.begin(); it != halignLayouts.end(); ++it){
            hLayout = *it;
            if(hLayout.compare("right")==0){right++;}
            else if(hLayout.compare("left")==0){left++;}
            else {otherH++;}
        }
        if (left==1 && right == 0){smartieAlign ="right";}
        else if (left==0 && right == 1){smartieAlign ="left";}
        else if (left==0 && right == 0){smartieAlign ="right";}
        else{smartieAlign ="left";}
    }
    //std::cout<<"smartieAlign: "<<smartieAlign<<std::endl;
    return smartieAlign;
}

int flPanel::whichAlign(const char* Align){
    std::string align = Align;
    if(align.compare("top")==0 || align.compare("bottom")==0){return 1;}
    else if(align.compare("left")==0 || align.compare("right")==0){return 2;}
    else {return 3;}
}
//END MULTIPLE PANELS ###########################################



///  ######################################################## JSM
void flPanel::setJSM(const char* element,const char* value){
    loadJSM();
  //  std::cout<<"element: "<<element<<" "<<"value: "<<value<<std::endl;
    tinyxml2::XMLElement* ele = jsm.FirstChildElement(element);
    ele->SetText(value);
    saveJSM();
}
// End JSM

 /*! @} */
/// ########################################################  Autohide
void flPanel::panelAutohide(bool &yesOrNo){
   // loadTemp();
    bool autohide;
    const char* autohideValue;
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if (yesOrNo){autohideValue ="true";}
    else{autohideValue ="false";}
    panelElement->SetAttribute("autohide",autohideValue);
    panelElement->QueryBoolAttribute("autohide", &autohide);
    saveChangesTemp();
}
void flPanel::panelAutohide(const char* where){
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement->SetAttribute("autohide",where);
    saveChangesTemp();
}
///******************************  PANEL SIZE setters and getters  *************************************

int flPanel::getValue(const char* attribute){
//    const char* functionName = "int getValue(const char * attribute)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    int value = 0;
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if (panelElement->Attribute(attribute)){panelElement->QueryIntAttribute(attribute, &value);}
    //std::cerr<<"int getValue: "<<value<<std::endl;
    return value;
}
std::string flPanel::getStringValue(const char* attribute){
//    const char* functionName = "std::string getStringValue(const char * attribute)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    std::string value = "";
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if (panelElement->Attribute(attribute)){value = panelElement->Attribute(attribute);}
    //std::cerr<<"getStringValue: "<<value<<std::endl;
    return value;
}

void flPanel::setValue(const char* attribute, int value){
   // loadTemp();
    int i = 1;
    std::string VALUE = convert(value);
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement->SetAttribute(attribute,VALUE.c_str());
    saveChangesTemp();
}
const char* flPanel::getValue(std::string attribute){
//    const char* functionName = "const char* getValue(std::string attribute)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    std::string result ="";
    int i = 1;
    const char* attrib = attribute.c_str();
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if (panelElement->Attribute(attrib)){result = panelElement->Attribute(attrib);}
    return result.c_str();
}

void flPanel::setValue(const char* attribute, const char* value){
   // loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}
//END PANEL SIZE

int flPanel::getBorder(){
//    const char* functionName = "int getBorder()";
   //std::cerr<<functionName<<std::endl;
    std::string value = getStringValue("border");
    if (value.compare("false")==0){return 0;}
    int result =  getValue("border");
    //std::cerr<<"result: "<<result<<std::endl;
    return result;
}

///  ######################################################## MENU  ************************************************


//TODO change ALL 5 to som integer in flPanel
void flPanel::menuLabel(const char * label){
   // loadTemp();
    const char* image = getMenuImage().c_str(); // Config::getImageMenu(5)
    labelMenu(image, rootMenu, label); ///Config
}
void flPanel::switchMenu(int whichStyle, const char* MenuName){
    std::string stringMenuName = MenuName;
    if(stringMenuName.compare("")==0){stringMenuName=gettext("Apps");}
    /// these come from Config;
    bool tori=isMenu(torimenu);
    bool gnome=isMenu(gnomemenu);
    bool test = isMenu(rootMenu);
    if(!test){addMenu(rootMenu,stringMenuName.c_str(),"/usr/share/pixmaps/distributor-logo");}
    if(whichStyle==1){
    //traditional
        if (gnome){switchMenuInclude(gnomemenu,torimenu);}
    }
    else if(whichStyle==2){
    //Gnome 2 style
        if(tori){
            if(!isMenu(systemMenu)){addMenu(systemMenu,"System","applications-system");}
            switchMenuInclude(torimenu,gnomemenu);
        }
    }
    else errorJWM("switchMenu requires values of 1 for traditional or 2 for Gnome 2 like menus");
}
void flPanel::switchMenuInclude(std::string changeTHIS, std::string toTHIS){
//    const char* conf = "$HOME/.config/";
    std::string homie = getenv("HOME");
    homie+="/.config/";
    std::string thisError;
    bool changeGnome = false;
    bool changeTori=false;
    if(changeTHIS.compare(gnomemenu)==0){changeGnome=true;}
    if(changeTHIS.compare(torimenu)!=0 ){changeTori=true;}
    bool toGnome = false;
    bool toTori=false;
    if(toTHIS.compare(gnomemenu)==0){toGnome=true;}
    if(toTHIS.compare(torimenu)!=0 ){toTori=true;}
    //make sure something valid was sent in
    if(!changeGnome && !changeTori){
        thisError ="flPanel: changeTHIS must be '"+gnomemenu+"' or '"+torimenu+"'";
        errorJWM(thisError); return;
    }
    if(!toTori && !toGnome){
        thisError ="flPanel: toTHIS must be '"+gnomemenu+"' or '"+torimenu+"'";
        errorJWM(thisError); return;
    }

    ///Switcher ...TODO
    if (changeGnome && toTori){
        std::cerr<<"change Gnome to Tori"<<std::endl;
    }
    else if (changeTori && toGnome){
        std::cerr<<"change Tori to Gnome"<<std::endl;
    }
    else{
        thisError ="Must be switching'"+gnomemenu+"' and '"+torimenu+"'";
        errorJWM(thisError); return;
    }
    //std::string


}


///****************************  PANEL BACKGROUND & Opacity ***********************************

    ///Colors

    //Inactive
void flPanel::setBackground(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( "Background" );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

unsigned int flPanel::getBackground(unsigned int &color2, const char * whichElement){
//    const char* functionName = "unsigned int getBackground(unsigned int &color2, const char * whichElement)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( whichElement )->
                        FirstChildElement( "Background" );
    std::string colour = colorElement->GetText();
    unsigned int bg = getColor(colour, color2);
    return bg;
}
    //Active
void flPanel::setActiveBackground(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(newStyle()){
        colorElement  = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Active" )->
                            FirstChildElement( "Background" );
    }
    else{
        colorElement  = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "ActiveBackground" );
    }
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
unsigned int flPanel::getActiveBackground(unsigned int  &color2, const char * whichElement){
//    const char* functionName = "unsigned int getActiveBackground(unsigned int &color2, const char * whichElement)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(newStyle()){
        colorElement  = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Active" )->
                            FirstChildElement( "Background" );
    }
    else{
        colorElement  = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "ActiveBackground" );
    }
    std::string colour = colorElement->GetText();
    unsigned int bg = getColor(colour, color2);
    return bg;
}


/// FONT color
void flPanel::setFontColor(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Foreground" );
    std::string color1 = colorToString(rgb);
    bgElement->SetText(color1.c_str());
    saveChangesTemp();
}
unsigned int flPanel::getFontColor(unsigned int &color2, const char * whichElement){
//    const char* functionName = "unsigned int getFontColor(unsigned int &color2, const char * whichElement)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Foreground" );
    //tester
    std::string background;
    if (test(bgElement)){
            background = bgElement->GetText();
        }
        else {errorJWM(errorMessage); return 42;}
    unsigned int bg = getColor(background, color2);
    return bg;
}

void flPanel::setActiveFontColor(const double* rgb, const char * whichElement){
   // loadTemp();
    const char* ActiveOrInactive;
    if(newStyle()){ActiveOrInactive="Active";}
    else{ActiveOrInactive="ActiveForeground";}
    setFGColor(whichElement,ActiveOrInactive,rgb); //from Config
    saveChangesTemp();
}

unsigned int flPanel::getActiveFontColor(unsigned int &color2, const char * whichElement){
//    const char* functionName = "unsigned int getActiveFontColor(unsigned int &color2, const char * whichElement)";
   //std::cerr<<functionName<<std::endl;
   // loadTemp();
    const char* ActiveOrInactive;
    if(newStyle()){ActiveOrInactive="Active";}
    else{ActiveOrInactive="ActiveForeground";}
    return getFGColor(whichElement, ActiveOrInactive, color2); //from Config
}

/*
//This is here in case I need it later... 2 color setter!
void flPanel::setPanelBackground(const double* rgb,const  double* rgb2){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "TrayStyle" )->
                            FirstChildElement( "Background" );
    std::string color1 = colorToString(rgb);
    if(rgb2!=NULL){
        std::string color2 = colorToString(rgb2);
        std::string color = color1 + ":" + color2;
        bgElement->SetText(color.c_str());
        saveChangesTemp();
    }
    else
        {bgElement->SetText(color1.c_str());
        saveChangesTemp();
    }
}
*/

/// Opacity
void flPanel::setOpacity(float &opacity, const char* whichElement){
   // loadTemp();
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    opacityElement->SetText(opacity);
    saveChangesTemp();
}
float flPanel::getOpacity(const char* whichElement){
//    const char* functionName = "float getOpacity(const char* whichElement)";
    //std::cerr<<functionName<<std::endl;
   // loadTemp();
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    std::string opacityString;
    std::string thisError = "Opacity doesn't exist for ";
    thisError+=whichElement;
    if (test(opacityElement)){opacityString = opacityElement->GetText();}
    else {errorJWM(thisError); return 42;} //TODO create it, and give it a default value

    float opacity = float(strtold(opacityString.c_str(),NULL));
    return opacity;
}
// End Panel Color


void flPanel::moveUp(std::string item){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * baseElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            baseElement=baseElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLNode * previous;
    if(item.compare("App Menu")==0){
        for(panelElement=panelElement->FirstChildElement("TrayButton");panelElement;panelElement->NextSiblingElement("TrayButton")){
            std::string text = panelElement->GetText();
            if(text.compare("root:5")==0){
                tinyxml2::XMLNode *panelEle= panelElement->ShallowClone(NULL);
                previous = panelElement->ShallowClone(NULL);
                previous = previous->PreviousSibling();
                panelElement->InsertAfterChild(previous,panelEle);
                baseElement->DeleteChild(panelElement);

            }
        }
    }
    else if(item.compare("Places Menu")==0){

    }
    else if(item.compare("Shutdown Menu")==0){

    }
    else if(item.compare("Desktop Switcher")==0){

    }
    else if(item.compare("Running App List")==0){

    }
    else if(item.compare("Indicators")==0){

    }
    else if(item.compare("Clock")==0){

    }
    else if(item.compare("")==0){return;}
    else{
        unsigned found = item.find_first_of(":");
        if(found<=item.length()){
            std::string thisItem = item.erase(0,found+1);
            if(thisItem.compare("Swallowed App")){

            }
        }
        else{

        }

    }
}
void flPanel::moveDown(std::string item){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    std::string compareText ="";
    std::string compareName ="";
    if(item.compare("")==0){return;}
    else if(item.compare("App Menu")==0){
        compareText="root:5";
        compareName="TrayButton";
    }
    else if(item.compare("Places Menu")==0){
        compareText="root:7";
        compareName="TrayButton";
    }
    else if(item.compare("Shutdown Menu")==0){
        compareText="root:9";
        compareName="TrayButton";
    }
    else if(item.compare("Running App List")==0){
        compareName="TaskList";
        compareText="NO";
    }
    else if(item.compare("Desktop Switcher")==0){
        compareName="Pager";
        compareText="NO";
    }
    else if(item.compare("Indicators")==0){
        compareName="Dock";
        compareText="NO";
    }
    else if(item.compare("Clock")==0){
        compareName="Clock";
        compareText="NO";
    }
    else{
        unsigned found = item.find_first_of(":");
        if(found<=item.length()){
            std::string thisItem = item.erase(0,found+1);
            if(thisItem.compare("Swallowed App")){
                compareName="Swallow";
                compareText="NO";
            }
            else{
                compareName="TrayButton";
                compareText="NO";
            }
        }
    }
    std::cout<<"compareName: "<<compareName<<std::endl;
    std::cout<<"compareText: "<<compareText<<std::endl;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * baseElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * nextElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            baseElement=baseElement->NextSiblingElement("Tray");
            nextElement=nextElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLNode * next;
    tinyxml2::XMLElement * testeroo;
    nextElement = nextElement->FirstChildElement();
    for(panelElement=panelElement->FirstChildElement();panelElement;panelElement=panelElement->NextSiblingElement()){
        //text to check and Element name to check
        std::string text = panelElement->GetText();
        std::string name = panelElement->Name();
        std::cout<<"name: "<<name<<std::endl;
        std::cout<<"text: "<<text<<std::endl;

        if ((text.compare(compareText)!=0)&&(compareText.compare("NO")==0)){
            ///Check for next element...  if it exists set it, otherwise move the other one back
            if(nextElement->NextSiblingElement()){nextElement = nextElement->NextSiblingElement();std::cout<<"nextElement exists"<<std::endl;}
            std::cout<<"NO compared!!!"<<std::endl;
            std::cout<<"name: "<<name<<std::endl;
            std::cout<<"compareName: "<<compareName<<std::endl;
            if((name.compare(compareName)==0)){
                std::cout<<"name: "<<name<<std::endl;
                std::cout<<"Next element: "<<nextElement->GetText()<<std::endl;
                tinyxml2::XMLNode *newElement= panelElement->ShallowClone(NULL);
                testeroo = newElement->ToElement();
                next = nextElement;//->NextSiblingElement();
                baseElement->InsertAfterChild(next,newElement);
                std::cout<<"New element: "<<testeroo->GetText()<<std::endl;
                doc.DeleteNode(panelElement);
                saveChangesTemp();
                return;
            }
        }
        else if((text.compare(compareText)==0)&&(name.compare(compareName)==0)){
            ///Check for next element...  if it exists set it, otherwise move the other one back
            if(nextElement->NextSiblingElement()){nextElement = nextElement->NextSiblingElement();std::cout<<"nextElement exists"<<std::endl;}
            std::cout<<"text: "<<text<<std::endl;
            std::cout<<"Next element text: "<<nextElement->GetText()<<std::endl;
            tinyxml2::XMLNode *newElement= panelElement->ShallowClone(NULL);
            next = nextElement;//->NextSiblingElement();
            baseElement->InsertAfterChild(next,newElement);
            testeroo = newElement->ToElement();
            std::cout<<"New element: "<<testeroo->GetText()<<std::endl;
            doc.DeleteNode(panelElement);
            saveChangesTemp();
            return;
        }
    }
}
const char* flPanel::getSubElementText(const char* whichElement){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    const char* result = panelElement->GetText();
    return result;
}
void flPanel::setSubElementText(const char* whichElement, const char* value){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    panelElement->SetText(value);
    saveChangesTemp();
}
const char* flPanel::getSubElementAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    const char* result = panelElement->Attribute(attribute);
    return result;
}
void flPanel::setSubElementAttribute(const char* whichElement,const char* attribute, const char* value){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * baseElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            baseElement=baseElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}
