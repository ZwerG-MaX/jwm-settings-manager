#include "../include/flWindow.h"

flWindow::flWindow()
{
    tinyxml2::XMLDocument doc;
    //isNewStyle = newStyle();
}

flWindow::~flWindow()
{
    //dtor
}
///COLOR FUNCTIONS
//Active
void flWindow::setActiveColor(const char* element, const double* rgb){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Active" )->
                        FirstChildElement( element ))
    colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Active" )->
                        FirstChildElement( element );
    else return;///TODO make FLTK error box show up
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
void flWindow::setActiveColor(const char* element, const double* rgb, const double* rgb2){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Active" )->
                        FirstChildElement( element ))
    colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Active" )->
                        FirstChildElement( element );
    else return;///TODO make FLTK error box show up
    std::string color1 = colorToString(rgb);
    if(rgb2!=NULL){
        std::string color2 = colorToString(rgb2);
        std::string color = color1 + ":" + color2;
        colorElement->SetText(color.c_str());
        saveChangesTemp();
    }
    else{
        colorElement->SetText(color1.c_str());
        saveChangesTemp();
    }
}
unsigned int flWindow::getActiveColor(const char* element){
 //   const char* functionName = "unsigned int getActiveColor(const char* element)";
//    std::cerr << functionName << std::endl;
    unsigned int u=1;
    return getActiveColor(element, u); //the int is arbitrary
}
unsigned int flWindow::getActiveColor(const char* element, unsigned int &color2){
   // loadTemp();
//    const char* functionName = "unsigned int getActiveColor(const char* element, unsigned int &color2)";
//    std::cerr << functionName << std::endl;
    tinyxml2::XMLElement* colorElement;
    if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Active" )->
                        FirstChildElement( element ))
    colorElement = doc.FirstChildElement("JWM")->
                            FirstChildElement( "WindowStyle")->
                            FirstChildElement( "Active")->
                            FirstChildElement( element );
    else return 0; //ADD FLTK ERROR
    std::string colorXML = colorElement->GetText();
//    std::cerr<<colorXML<<std::endl;
    unsigned int color;
    color = getColor(colorXML, color2);
    return color;
}
//Inactive
void flWindow::setInactiveColor(const char* element, const double* rgb){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(isNewStyle){
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element );
        else return; ///create
    }
    else{
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
        else return; ///ERROR
    }
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
void flWindow::setInactiveColor(const char* element, const double* rgb, const double* rgb2){
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(isNewStyle){
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element );
        else return; ///ERROR
    }
    else{
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
        else return; ///ERROR
    }
    std::string color1 = colorToString(rgb);
    if(rgb2!=NULL){
        std::string color2 = colorToString(rgb2);
        std::string color = color1 + ":" + color2;
        colorElement->SetText(color.c_str());
        saveChangesTemp();
    }
    else{
        colorElement->SetText(color1.c_str());
        saveChangesTemp();
    }
}

unsigned int flWindow::getInactiveColor(const char* element){
 //   const char* functionName = "unsigned int getInactiveColor(const char* element)";
    //std::cerr << functionName << std::endl;
    unsigned int u=1;
    return getInactiveColor(element,u); //the int is arbitrary
}
unsigned int flWindow::getInactiveColor(const char* element, unsigned int &color2){
//    const char* functionName = "unsigned int getInactiveColor(const char* element, unsigned int &color2)";
    //std::cerr << functionName << std::endl;
   // loadTemp();
    tinyxml2::XMLElement* colorElement;
    if(isNewStyle){
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( element );
        else return 0; ///ERROR
    }
    else{
        if(doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element ))
        colorElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
        else return 0; ///ERROR
    }
    std::string colorXML = colorElement->GetText();
    ///this one is important
    unsigned int color;
    color = getColor(colorXML, color2);
    return color;
}
//****************************  Window Title Bar Color and Opacity  ***********************************

/// WINDOW COLOR

/// SET COLOR
//Active
void flWindow::setActiveWindowColor(const double* rgb, const double* rgb2){
    const char* NewOrOldBG;
    if(isNewStyle){NewOrOldBG="Background";}
    else{NewOrOldBG="Title";}
    setActiveColor(NewOrOldBG,rgb,rgb2);
}
void flWindow::setActiveWindowColor(const double* rgb){
    const char* NewOrOldBG;
    if(isNewStyle){NewOrOldBG="Background";}
    else{NewOrOldBG="Title";}
    setActiveColor(NewOrOldBG,rgb);
}
//Inactive
void flWindow::setWindowColor(const double* rgb){
    const char* newORold;
    if(isNewStyle){newORold="Background";}
    else{newORold="Title";}
    setInactiveColor(newORold,rgb);
}
void flWindow::setWindowColor(const double* rgb, const double* rgb2){
    const char* newORold;
    if(isNewStyle){newORold="Background";}
    else{newORold="Title";}
    setInactiveColor(newORold,rgb,rgb2);
}
/// GET COLOR

//Inactive
unsigned int flWindow::getWindowColor(unsigned int &color2){
//    const char* functionName = "unsigned int getWindowColor(unsigned int &color2)";
    //std::cerr << functionName << std::endl;
    const char* newOrOld;
    if(isNewStyle){newOrOld="Background";}
    else{newOrOld="Title";}
    return getInactiveColor(newOrOld, color2);
}

//Active
unsigned int flWindow::getActiveWindowColor(unsigned int &color2){
//    const char* functionName = "unsigned int flWindow::getActiveWindowColor(unsigned int &color2)";
    //std::cerr << functionName << std::endl;
    const char* newOrOld;
    if(isNewStyle){newOrOld="Background";}
    else{newOrOld="Title";}
    //std::cerr<<newOrOld<<std::endl;
    return getActiveColor(newOrOld, color2);
}

/// OPACITY
//Active
void flWindow::activeWindowOpacity(float &opacity){
   // loadTemp();
    tinyxml2::XMLElement* opacityElement  = doc.FirstChildElement("JWM")->
                            FirstChildElement( "WindowStyle")->
                            FirstChildElement( "Active")->
                            FirstChildElement( "Opacity" );
    std::cerr<<"SET Active Opacity: "<<opacity<<std::endl;
    opacityElement->SetText(opacity);
    saveChangesTemp();
}
float flWindow::getActiveOpacity(){
   // loadTemp();
 //   const char* functionName = "float flWindow::getActiveOpacity()";
    //std::cerr << functionName << std::endl;
    tinyxml2::XMLElement* opacityElement;
    opacityElement = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Active")->
                    FirstChildElement( "Opacity" );
    std::string opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
    //std::cerr<<"Active Opacity: "<<opacity<<std::endl;
    return opacity;
}
//Inactive
void flWindow::windowOpacity(float &opacity){
   // loadTemp();
    tinyxml2::XMLElement* opacityElement;
    if(isNewStyle){
        opacityElement = doc.FirstChildElement("JWM")->
                        FirstChildElement( "WindowStyle")->
                        FirstChildElement( "Opacity" );
                        opacityElement->SetText(opacity);
    }
    else{
        opacityElement = doc.FirstChildElement("JWM")->
            FirstChildElement( "WindowStyle")->
            FirstChildElement( "Inactive")->
            FirstChildElement( "Opacity" );
            opacityElement->SetText(opacity);
    }
 //   std::cerr<<"SET Inactive Opacity: "<<opacity<<std::endl;
    saveChangesTemp();
}
float flWindow::getOpacity(){
   // loadTemp();
 //   const char* functionName = "getOpactiy()";
//    std::cerr << functionName << std::endl;
    tinyxml2::XMLElement* opacityElement;
    if(isNewStyle){
        opacityElement = doc.FirstChildElement("JWM")->
                            FirstChildElement( "WindowStyle")->
                            FirstChildElement( "Opacity" );
    }
    else{
        opacityElement = doc.FirstChildElement("JWM")->
                            FirstChildElement( "WindowStyle")->
                            FirstChildElement( "Inactive")->
                            FirstChildElement( "Opacity" );
    }
    std::string opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
//    std::cerr<<"Inactive Opacity: "<<opacity<<std::endl;
    return opacity;
}
//######################################### END Window TitleBar ##############################################


//****************************  Window Borders (including Title bar height) ***********************************

///COLOR
unsigned int flWindow::getBorderColor(){return getInactiveColor("Outline" );}
unsigned int flWindow::getActiveBorderColor(){return getActiveColor( "Outline" );}

void flWindow::setActiveBorderColor(const double* rgb){setActiveColor("Outline",rgb);}
void flWindow::setBorderColor(const double* rgb){setInactiveColor("Outline",rgb);}


///SIZE
int flWindow::getBorderWidth(){
//    const char* functionName = "int flWindow::getBorderWidth()";
    //std::cerr << functionName << std::endl;
   // loadTemp();
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Width" );
    const char* border = borderElement->GetText();
    int sizeOfBorder = strtol(border,0,10);
    //std::cout<<sizeOfBorder<<" border size"<<std::endl;
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
   // loadTemp();
//    const char* functionName = "int flWindow::getBorderHeight()";
    //std::cerr << functionName << std::endl;
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
    const char* border = borderElement->GetText();
    int sizeOfBorder = strtol(border,0,10);
    //std::cout<<sizeOfBorder<<" Title bar size"<<std::endl;
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
void flWindow::setActiveFontColor(const double* rgb){
    const char* newORold;
    if(isNewStyle){newORold="Foreground";}
    else{newORold="Text";}
    setActiveColor(newORold,rgb);
}
void flWindow::setFontColor(const double* rgb){
    const char* newORold;
    if(isNewStyle){newORold="Foreground";}
    else{newORold="Text";}
    setInactiveColor(newORold,rgb);
}
unsigned int flWindow::getActiveFontColor(){
//    const char* functionName = "unsigned int flWindow::getActiveFontColor()";
    //std::cerr << functionName << std::endl;
    const char* newORold;
    if(isNewStyle){newORold="Foreground";}
    else{newORold="Text";}
    return getActiveColor(newORold);
}
unsigned int flWindow::getFontColor(){
//    const char* functionName = "unsigned int flWindow::getFontColor()";
    //std::cerr << functionName << std::endl;
    const char* newORold;
    if(isNewStyle){newORold="Foreground";}
    else{newORold="Text";}
    return getInactiveColor(newORold);
}

//######################################### END Font Color ##############################################


//ETC
void flWindow::setThings(const char* thing, const char* mode){
   // loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(thing);
    element->SetText(mode);
    saveChangesTemp();
}
void flWindow::setThings(const char* thing, const char* mode, int &distance){
   // loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(thing);
    element->SetText(mode);
    element->SetAttribute("distance",distance);
    saveChangesTemp();
}
void flWindow::setResize(const char *mode){setThings("ResizeMode",mode);}
void flWindow::setMoveMode(const char *mode){setThings("MoveMode",mode);}
void flWindow::setFocusModel(const char *mode){setThings("FocusModel",mode);}
void flWindow::setSnap(const char *mode, int &distance){setThings("SnapMode",mode,distance);}

void flWindow::setSnap(int &distance){
   // loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("SnapMode");
    element->SetAttribute("distance",distance);
    saveChangesTemp();
}

int flWindow::getSnap(){
//    const char* functionName = "int flWindow::getSnap()";
    //std::cerr << functionName << std::endl;
   // loadTemp();
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
//    const char* functionName = "const char* flWindow::getButton(const char* whichElement)";
//    std::cerr << functionName << std::endl;
   // loadTemp();
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
//    const char* functionName = "void flWindow::setButton(const char * button, const char* whichElement)";
    //std::cerr << functionName << std::endl;
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
