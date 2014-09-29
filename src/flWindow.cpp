#include "../include/flWindow.h"

flWindow::flWindow()
{
    tinyxml2::XMLDocument doc;
}

flWindow::~flWindow()
{
    //dtor
}

//****************************  Window Title Bar Color and Opacity  ***********************************

/// WINDOW COLOR

/// SET COLOR
void flWindow::setWindowColor(const double* rgb, const double* rgb2, const char* whichWindow){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( whichWindow )->
                            FirstChildElement( "Title" );
    std::string color1 = colorToString(rgb);
    if(rgb2!=NULL){
        std::string color2 = colorToString(rgb2);
        std::string color = color1 + ":" + color2;
        colorElement->SetText(color.c_str());
        saveChangesTemp();
    }
    else
        {colorElement->SetText(color1.c_str());
        saveChangesTemp();
    }
}
void flWindow::setWindowColor(const double* rgb, const char* whichWindow){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( whichWindow )->
                            FirstChildElement( "Title" );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

/// GET COLOR
unsigned int flWindow::getWindowColor(unsigned int &color2,const char* whichWindow){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( whichWindow )->
                            FirstChildElement( "Title" );
    std::string colorXML = colorElement->GetText();
    unsigned int color = getColor(colorXML, color2);
    return color;
}

/// OPACITY
void flWindow::windowOpacity(float &opacity,const char* whichWindow){
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( "WindowStyle")->FirstChildElement( whichWindow)->FirstChildElement( "Opacity" );
    opacityElement->SetText(opacity);
}
float flWindow::getOpacity(const char* whichWindow){
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->FirstChildElement( "WindowStyle")->FirstChildElement( whichWindow)->FirstChildElement( "Opacity" );
    std::string opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
    return opacity;
}
//######################################### END Window TitleBar ##############################################


//****************************  Window Borders (including Title bar height) ***********************************

///COLOR
unsigned int flWindow::getBorderColor(const char *element){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( element )->
                            FirstChildElement( "Outline" );;
    std::string colorXML = colorElement->GetText();
    //this unsigned int isn't used here, because there is only 1 color...
    //TODO: overload the getColor function :)
    unsigned int u = 1;
    ///this one is important
    unsigned int color;
    color = getColor(colorXML, u);
    return color;
}


void flWindow::setBorderColor(const double* rgb, const char* element){
    tinyxml2::XMLElement* borderColorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( element)->
                            FirstChildElement( "Outline" );
    std::string color1 = colorToString(rgb);
    borderColorElement->SetText(color1.c_str());
    saveChangesTemp();
}


///SIZE
int flWindow::getBorderWidth(){
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Width" );
    const char* border = borderElement->GetText();
    int sizeOfBorder = strtol(border,0,10);
    //std::cout<<sizeOfBorder<<" border size\n";
    return sizeOfBorder;
}

void flWindow::setBorderWidth(int &border){
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Width" );
    borderElement->SetText(border);
    saveChangesTemp();
}

int flWindow::getBorderHeight(){
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
    const char* border = borderElement->GetText();
    int sizeOfBorder = strtol(border,0,10);
    //std::cout<<sizeOfBorder<<" Title bar size\n";
    return sizeOfBorder;
}
void flWindow::setBorderHeight(int &border){
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
    borderElement->SetText(border);
    saveChangesTemp();
}
//######################################### END Window Borders ##############################################


//****************************  Font Color  ***********************************
void flWindow::setFontColor(const double* rgb,const char* whichWindow){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( whichWindow )->
                            FirstChildElement( "Text" );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

unsigned int flWindow::getFontColor(const char *element){
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( element )->
                            FirstChildElement( "Text" );
    std::string colorXML = colorElement->GetText();
    //this unsigned int isn't used here, because there is only 1 color...
    //TODO: overload the getColor function :)
    unsigned int u = 1;
    ///this one is important
    unsigned int color;
    color = getColor(colorXML, u);
    return color;
}

//######################################### END Font Color ##############################################


//ETC
void flWindow::setResize(const char *mode){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("ResizeMode");
    element->SetText(mode);
    saveChangesTemp();
}
void flWindow::setMoveMode(const char *mode){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("MoveMode");
    element->SetText(mode);
    saveChangesTemp();
}
void flWindow::setFocusModel(const char *mode){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("FocusModel");
    element->SetText(mode);
    saveChangesTemp();
}
void flWindow::setSnap(const char *mode, int &distance){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("SnapMode");
    element->SetText(mode);
    element->SetAttribute("distance",distance);
    saveChangesTemp();
}
void flWindow::setSnap(int &distance){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("SnapMode");
    element->SetAttribute("distance",distance);
    saveChangesTemp();
}

int flWindow::getSnap(){
    int value;
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("SnapMode");
    element->QueryIntAttribute("distance",&value);
    /*if(value !=NULL){
        saveChangesTemp();
        return value;
    }
    return 0;*/
    return value;
}

//*****************************************  Button  **********************************************
const char* flWindow::getButton(const char* whichElement){
    const char* result;
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    if(element){
        result = element->GetText();
    }
    else{
        result = "x";
    }
    return result;
}
std::string flWindow::buttonPath(){
    std::string ButtonPath ="/usr/share/jwm-settings-manager/Buttons/";
    return ButtonPath;
}
void flWindow::setButton(const char * button, const char* whichElement){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    if(element){
        element->SetText(button);
    }
    else{
        tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" );
        tinyxml2::XMLNode *insertNode = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" );
        tinyxml2::XMLNode *node = doc.NewElement(whichElement);
        trayNode->InsertAfterChild(insertNode,node);
        tinyxml2::XMLText *image = doc.NewText(button);
        node->LinkEndChild(image);
    }
    saveChangesTemp();
}

//######################################### END Button ##############################################
