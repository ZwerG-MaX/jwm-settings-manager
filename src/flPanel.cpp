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

void flPanel::addPanel(Fl_Menu_Button* o){
    const char* out;
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    tinyxml2::XMLNode *node = doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    tray->InsertAfterChild(node,newTray);
    newTray->InsertEndChild(spacer);
    std::string label = "Panel ";
    saveChangesTemp();
    unsigned int panels = numPanels();
    std::string num = convert(panels);
    label+=num;
    out = label.c_str();
    o->add(out,0,0,0,0);
   // setWhichPanel(panels);
}
//########################################### END MULTIPLE PANELS ###########################################

//************************************  PANEL POSITIONING & AUTOHIDE *************************************************

/** ! @addtogroup PanelPositioning
 * @{
 */

/**!
 *
 * @brief Vertical positioning function.
 * @param position can be "top","bottom","fixed" or "center"
 */
void flPanel::panelPositionVert(const char* position){
    bool test = multipanel();
    tinyxml2::XMLElement* positionElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    if(!test){
        positionElement->SetAttribute("valign",position);
    }
    else{
        //const char* layout = loadWhichPanel();

    }
}
/**!
 *
 * @brief Gets the current positioning of the 'Tray' (panel)
 */
 std::string flPanel::getVertPosition(){
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    std::string valign = panelElement->Attribute("valign");
    //std::cout<<valign<<"\n";//Debug
    return valign;
}

 //Horizontal
void flPanel::panelPositionHoriz(const char* position){
    tinyxml2::XMLElement* positionElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    positionElement->SetAttribute("halign",position);
}

//Layout
void flPanel::panelLayout(const char* layout){
    tinyxml2::XMLElement* layoutElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    layoutElement->SetAttribute("layout",layout);
}

//Layer
void flPanel::panelLayer(const char* layer){
    tinyxml2::XMLElement* layerElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    layerElement->SetAttribute("layer",layer);
}

 /*! @} */
//Autohide
void flPanel::panelAutohide(bool &yesOrNo){
    bool autohide;
    const char* autohideValue;
    tinyxml2::XMLElement* autohideElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    autohideElement->QueryBoolAttribute("autohide", &autohide);
    if (yesOrNo){
        autohideValue ="true";
        //std::cout<<"Autohide is set to true\n";
    }
    else{
        autohideValue ="false";
        //std::cout<<"Autohide is set to false\n";
    }
    autohideElement->SetAttribute("autohide",autohideValue);
    autohideElement->QueryBoolAttribute("autohide", &autohide);
    saveChangesTemp();
}

 std::string flPanel::getAutohide(){
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    std::string autohide = panelElement->Attribute("autohide");
    //std::cout<<autohide<<"\n";//Debug
    return autohide;
 }
//########################################### PANEL POSITIONING & AUTOHIDE ########################################################



//******************************  PANEL SIZE setters and getters  *************************************

//Height
void flPanel::panelHeight(int &panelSize){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("height", &sizeOfPanel);
    sizeElement->SetAttribute("height",panelSize);
}

int flPanel::getHeight(){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("height", &sizeOfPanel);
    return sizeOfPanel;
}
int flPanel::getCoordinate(const char * xy){
    int coordinate = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute(xy, &coordinate);
    return coordinate;
}
void flPanel::setCoordinate(const char * xy, int value){
    int coordinate = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute(xy, &coordinate);
    sizeElement->SetAttribute(xy, value);
}

//Width
void flPanel::panelWidth(int &panelSize){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("width", &sizeOfPanel);
    sizeElement->SetAttribute("width",panelSize);
}
int flPanel::getWidth(){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("width", &sizeOfPanel);
    return sizeOfPanel;
}

//Border
void flPanel::borderWidth(int &panelSize){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("border", &sizeOfPanel);
    sizeElement->SetAttribute("border",panelSize);
}
int flPanel::getBorder(){
    int sizeOfPanel = 0;
    tinyxml2::XMLElement* sizeElement = doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    sizeElement->QueryIntAttribute("border", &sizeOfPanel);
    return sizeOfPanel;
}

//############################################ END PANEL SIZE ########################################################


//*******************************************  MENU  ************************************************

///Label
void flPanel::menuLabel(const char * label){
    /*tinyxml2::XMLElement* current;
    currentPanel(current);
    tinyxml2::XMLElement* panelElement = current->*/
    tinyxml2::XMLElement* panelElement =doc.FirstChildElement("JWM")->FirstChildElement("Tray")->FirstChildElement( "TrayButton" );
    if(panelElement){
        panelElement->SetAttribute("label",label);
        saveChangesTemp();
    }
}

std::string flPanel::getMenuLabel(){
   /* tinyxml2::XMLElement *check;
    currentPanel(check);
    tinyxml2::XMLElement * current = check;*/
    bool test = false;
    const char * label;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        //current->
                                        FirstChildElement( "TrayButton" );
    for(tinyxml2::XMLElement* node=doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" )->FirstChildElement( "TrayButton" );
    node;
    node=node->NextSiblingElement("TrayButton")){
        test=true;
    }
    if(!test){return "error";}
    //This will save the Attribute from label="whatever" to a string label
    //i.e. const char* label ="whatever"
    label = panelElement->Attribute("label");
    std::string labelString;
    if (label!=NULL){
        labelString = label;
    }
    else{labelString = "";}
   // std::cout<<label<<"\n";
    return labelString;
}

///Image
 std::string flPanel::getMenuImage(){
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    std::string icon = panelElement->Attribute("icon");
    std::string text = panelElement->GetText();
    ///TODO: check if menu exists

    ///TODO: how do I return a usable value for FLTK??
    /*This, by default, returns "distributor-logo.png"
     * rather than "/path/to/icon/distributor-logo.png"
     * Should I change it to a hardcoded path every single time the image is changed???
     *  Yeah... that is what I should do.
     */
    return icon;
 }
 void flPanel::setMenuImage(const char* icon){
     tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    panelElement->SetAttribute("icon",icon);
    saveChangesTemp();
 }

//########################################### END MENU #########################################################



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
    if (test(opacityElement)){
            opacityString = opacityElement->GetText();
        }
    else {std::cout<<errorMessage; return 42;}
    float opacity = float(strtold(opacityString.c_str(),NULL));
    return opacity;
}
//######################################### END PANEL BACKGROUND ##############################################
