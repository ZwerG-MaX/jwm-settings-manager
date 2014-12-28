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

//************************************  MULTIPLE PANELS  *************************************************

///ADD PANEL

void flPanel::addPanel(){
    int a = numPanels();
    if(a==4){return;}
    std::cout<<"add Panel"<<std::endl;
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
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
    tinyxml2::XMLNode *node = panelElement;
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    const char* position = smartPosition();
    const char* align = smartAlign(position);
    int vertORhoriz = whichAlign(align);
    std::cout<<"position: "<<position<<" vertORhoriz: "<<vertORhoriz<<std::endl;
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    tray->InsertAfterChild(node,newTray);
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
        thisone->SetAttribute("height",0);
    }
    else{
        thisone->SetAttribute("valign","center");
        thisone->SetAttribute("halign","center");
        thisone->SetAttribute("width",0);
        thisone->SetAttribute("height",34);
    }
    thisone->SetAttribute("border",0);
    saveChangesTemp();
    saveChanges();
    int panels = numPanels();
    updatePanels(panels);
}
void flPanel::deletePanel(){
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

const char* flPanel::smartPosition(){
//TODO: check all panels and find ALL alignments to figure things out.
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
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
    if (errors != 0){std::cout<<"Something is wrong"<<std::endl;}
    std::cout<<"horizontl: "<<horizontl<<" verticl: "<<verticl<<std::endl;
    smartiePosition = horizontalORvertical(horizontl,verticl);
    return smartiePosition;
}

const char* flPanel::smartAlign(const char* layout){
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
    std::cout<<"smartieAlign: "<<smartieAlign<<std::endl;
    return smartieAlign;
}

int flPanel::whichAlign(const char* Align){
    std::string align = Align;
    if(align.compare("top")==0 || align.compare("bottom")==0){return 1;}
    else if(align.compare("left")==0 || align.compare("right")==0){return 2;}
    else {return 3;}
}
void flPanel::setJSM(const char* element,const char* value){
    int loadedJSM = loadJSM();
  //  std::cout<<"element: "<<element<<" "<<"value: "<<value<<std::endl;
    tinyxml2::XMLElement* ele = jsm.FirstChildElement(element);
    ele->SetText(value);
    saveJSM();
}
//########################################### END MULTIPLE PANELS ###########################################


 /*! @} */
//Autohide
void flPanel::panelAutohide(bool &yesOrNo){
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

///******************************  PANEL SIZE setters and getters  *************************************

int flPanel::getValue(const char* attribute){
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
    return value;
}
std::string flPanel::getStringValue(const char* attribute){
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
    if (panelElement->Attribute(attribute)){panelElement->Attribute(attribute);}
    return value;
}
void flPanel::createValue(const char* attribute, const char* value){
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
    tinyxml2::XMLAttribute * newAttribute;
    //newAttribute->Name(attribute);
    //newAttribute->Value(value);
//    panelElement-
}
void flPanel::createValue(const char* attribute, int &value){
    std::string result = convert(value);
    createValue(attribute, result.c_str());
}
void flPanel::setValue(const char* attribute, int &value){
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
    std::string VALUE = convert(value);
    if (panelElement->Attribute(attribute)){panelElement->SetAttribute(attribute,VALUE.c_str());}
    else{createValue(attribute,value);}
    setJSM(attribute, VALUE.c_str());
}
const char* flPanel::getValue(std::string attribute){
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
    if (panelElement->Attribute(attribute)){panelElement->SetAttribute(attribute,value);}
    else{createValue(attribute,value);}
//    setJSM(attribute, VALUE.c_str());
}

//############################################ END PANEL SIZE ########################################################


///Label  MENU  ************************************************

void flPanel::menuLabel(const char * label){
    const char* image = getMenuImage().c_str();
    labelMenu(image, 5, label);
}




//****************************  PANEL BACKGROUND & Opacity ***********************************


///Colors
void flPanel::setBackground(const double* rgb, const char * whichElement){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Background" );
    std::string color1 = colorToString(rgb);
    bgElement->SetText(color1.c_str());
    saveChangesTemp();
}
unsigned int flPanel::getBackground(unsigned int &color2, const char * whichElement){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "Background" );
    ///tester
    std::string background;
    if (test(bgElement)){
            background = bgElement->GetText();
        }
        else {std::cout<<errorMessage; return 42;}
    unsigned int bg = getColor(background, color2);
    return bg;
}
void flPanel::setActiveBackground(const double* rgb, const char * whichElement){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "ActiveBackground" );
    std::string color1 = colorToString(rgb);
    bgElement->SetText(color1.c_str());
    saveChangesTemp();
}

unsigned int flPanel::getActiveBackground(unsigned int &color2, const char * whichElement){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( whichElement )->
                            FirstChildElement( "ActiveBackground" );
    ///tester
    std::string background;
    if (test(bgElement)){
            background = bgElement->GetText();
        }
        else {std::cout<<errorMessage; return 42;}
    unsigned int bg = getColor(background, color2);
    return bg;
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
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    opacityElement->SetText(opacity);
}
float flPanel::getOpacity(const char* whichElement){
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    std::string opacityString;

    if (test(opacityElement)){opacityString = opacityElement->GetText();}
    else {std::cout<<errorMessage; return 42;}

    float opacity = float(strtold(opacityString.c_str(),NULL));
    return opacity;
}
