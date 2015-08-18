#include "../include/flWindow.h"

flWindow::flWindow(){
#ifdef DEBUG_TRACK
  std::cerr<<"[flWindow]->"<<std::endl;
#endif // DEBUG
    tinyxml2::XMLDocument doc;
    GROUP="Group";
    CLASS="Class";
    NAME="Name";
    OPTION="Option";
    //isNewStyle = newStyle();
}

flWindow::~flWindow(){
#ifdef DEBUG_TRACK
  std::cerr<<"<-[flWindow]"<<std::endl;
#endif // DEBUG
}
///COLOR FUNCTIONS
//Active
void flWindow::setActiveColor(const char* element, const double* rgb){
   // loadTemp();

   //does this exist??
   if(!testElement("WindowStyle","Active",element)){
        createElement("WindowStyle","Active",element);
    }
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                                            FirstChildElement( "WindowStyle" )->
                                            FirstChildElement( "Active" )->
                                            FirstChildElement( element );
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
void flWindow::setActiveColor(const char* element, const double* rgb, const double* rgb2){
   // loadTemp();
    //does this exist??
   if(!testElement("WindowStyle","Active",element)){
        createElement("WindowStyle","Active",element);
    }
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                                            FirstChildElement( "WindowStyle" )->
                                            FirstChildElement( "Active" )->
                                            FirstChildElement( element );
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
    if(DEBUG_ME){
    const char* functionName = "unsigned int getActiveColor(const char* element)";
    std::cerr << functionName << std::endl;
    }

    unsigned int u=1;
    return getActiveColor(element, u); //the int is arbitrary
}
unsigned int flWindow::getActiveColor(const char* element, unsigned int &color2){

    //does this exist??
   if(!testElement("WindowStyle","Active",element)){
        createElement("WindowStyle","Active",element);
        tinyxml2::XMLElement* fixer = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Active")->
                    FirstChildElement( element );
        fixer->SetText("#000000");
        saveChanges();
        saveChangesTemp();
        return 0;
    }
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->
                                            FirstChildElement( "WindowStyle" )->
                                            FirstChildElement( "Active" )->
                                            FirstChildElement( element );
    std::string colorXML = colorElement->GetText();
    if(DEBUG_ME){std::cerr<<colorXML<<std::endl;}
    unsigned int color;
    color = getColor(colorXML, color2);
    return color;
}
//Inactive
void flWindow::setInactiveColor(const char* element, const double* rgb){
   // loadTemp();
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" );
    if(isNewStyle !=-1){
        if(!testElement("WindowStyle",element)){
            createElement("WindowStyle",element);
        }
        colorElement  = colorElement->FirstChildElement( element );
    }
    else{
        if(!testElement("WindowStyle","Inactive",element)){
            createElement("WindowStyle","Inactive",element);
        }
        colorElement  = colorElement->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
    }
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
void flWindow::setInactiveColor(const char* element, const double* rgb, const double* rgb2){
   // loadTemp();
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" );
    if(isNewStyle !=-1){
        if(!testElement("WindowStyle",element)){
            createElement("WindowStyle",element);
        }
        colorElement  = colorElement->FirstChildElement( element );
    }
    else{
        if(!testElement("WindowStyle","Inactive",element)){
            createElement("WindowStyle","Inactive",element);
        }
        colorElement  = colorElement->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
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
    unsigned int u=1;
    return getInactiveColor(element,u); //the int is arbitrary
}
unsigned int flWindow::getInactiveColor(const char* element, unsigned int &color2){
    #ifdef DEBUG_TRACK
        const char* functionName = "unsigned int getInactiveColor(const char* element, unsigned int &color2)";
        std::cerr << functionName << std::endl;
    #endif // DEBUG
   // loadTemp();
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" );
    if(isNewStyle !=-1){
        if(!testElement("WindowStyle",element)){
            createElement("WindowStyle",element);
            tinyxml2::XMLElement* fixer = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( element );
            fixer->SetText("#000000");
            saveChanges();
            saveChangesTemp();
            return 0;
        }
        colorElement  = colorElement->FirstChildElement( element );
    }
    else{
        if(!testElement("WindowStyle","Inactive",element)){
            createElement("WindowStyle","Inactive",element);
            tinyxml2::XMLElement* fixer = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Inactive")->
                    FirstChildElement( element );
            fixer->SetText("#000000");
            saveChanges();
            saveChangesTemp();
            return 0;
        }
        colorElement  = colorElement->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( element );
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
    if(isNewStyle !=-1){NewOrOldBG="Background";}
    else{NewOrOldBG="Title";}
    setActiveColor(NewOrOldBG,rgb,rgb2);
}
void flWindow::setActiveWindowColor(const double* rgb){
    const char* NewOrOldBG;
    if(isNewStyle !=-1){NewOrOldBG="Background";}
    else{NewOrOldBG="Title";}
    setActiveColor(NewOrOldBG,rgb);
}
//Inactive
void flWindow::setWindowColor(const double* rgb){
    const char* newORold;
    if(isNewStyle !=-1){newORold="Background";}
    else{newORold="Title";}
    setInactiveColor(newORold,rgb);
}
void flWindow::setWindowColor(const double* rgb, const double* rgb2){
    const char* newORold;
    if(isNewStyle !=-1){newORold="Background";}
    else{newORold="Title";}
    setInactiveColor(newORold,rgb,rgb2);
}
/// GET COLOR

//Inactive
unsigned int flWindow::getWindowColor(unsigned int &color2){
//    const char* functionName = "unsigned int getWindowColor(unsigned int &color2)";
    //std::cerr << functionName << std::endl;
    const char* newOrOld;
    if(isNewStyle !=-1){newOrOld="Background";}
    else{newOrOld="Title";}
    return getInactiveColor(newOrOld, color2);
}

//Active
unsigned int flWindow::getActiveWindowColor(unsigned int &color2){
//    const char* functionName = "unsigned int flWindow::getActiveWindowColor(unsigned int &color2)";
    //std::cerr << functionName << std::endl;
    const char* newOrOld;
    if(isNewStyle !=-1){newOrOld="Background";}
    else{newOrOld="Title";}
    if(DEBUG_ME){std::cerr<<newOrOld<<std::endl;}
    return getActiveColor(newOrOld, color2);
}

/// OPACITY
//Active
void flWindow::activeWindowOpacity(float &opacity){
   // loadTemp();
    if(!testElement("WindowStyle","Active","Opacity")){
        createElement("WindowStyle","Active","Opacity");
    }
    tinyxml2::XMLElement* opacityElement  = doc.FirstChildElement("JWM")->
                            FirstChildElement( "WindowStyle")->
                            FirstChildElement( "Active")->
                            FirstChildElement( "Opacity" );
    if(DEBUG_ME){std::cerr<<"SET Active Opacity: "<<opacity<<std::endl;}
    opacityElement->SetText(opacity);
    saveChangesTemp();
}
float flWindow::getActiveOpacity(){
   if(!testElement("WindowStyle","Active","Opacity")){
        createElement("WindowStyle","Active","Opacity");
        tinyxml2::XMLElement* fixer = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Active")->
                    FirstChildElement( "Opacity" );
        fixer->SetText(1.0);
        saveChanges();
        saveChangesTemp();
    }
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Active")->
                    FirstChildElement( "Opacity" );
    std::string opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
    if(DEBUG_ME){std::cerr<<"Active Opacity: "<<opacity<<std::endl;}
    return opacity;
}
//Inactive
void flWindow::windowOpacity(float &opacity){
   // loadTemp();
   tinyxml2::XMLElement* opacityElement;
    if(isNewStyle !=-1){
        if(!testElement("WindowStyle","Opacity")){
            createElement("WindowStyle","Opacity");
        }
        opacityElement  = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" )->FirstChildElement( "Opacity" );
        opacityElement->SetText(opacity);
    }
    else{
        if(!testElement("WindowStyle","Inactive","Opacity")){
            createElement("WindowStyle","Inactive","Opacity");
        }
        opacityElement  = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( "Opacity" );
        opacityElement->SetText(opacity);
    }
    saveChangesTemp();
}
float flWindow::getOpacity(){
    //create our pointer
    tinyxml2::XMLElement* opacityElement;

    //if it is the new version
    if(isNewStyle !=-1){
        //does the element even exist??
        if(!testElement("WindowStyle","Opacity")){
            //hmmm.... nope  we should make it
            createElement("WindowStyle","Opacity");
            //point to it
            tinyxml2::XMLElement* fixer = doc.FirstChildElement("JWM")->
                    FirstChildElement( "WindowStyle")->
                    FirstChildElement( "Opacity" );
            //set to default... i.e completely opaque
            fixer->SetText(1.0);
            //save it
            saveChanges();
            saveChangesTemp();
            //return this
            return 1.0f;
        }

        //if you got here it must exist... lets point to it
        opacityElement  = doc.FirstChildElement( "JWM" )->FirstChildElement( "WindowStyle" )->FirstChildElement( "Opacity" );
    }
    else{
        //not the new style apparently

        //does this element even exist?
        if(!testElement("WindowStyle","Inactive","Opacity")){
            //nopers... we better fix that
            createElement("WindowStyle","Inactive","Opacity");
        }
        //point to it
        opacityElement  = doc.FirstChildElement( "JWM" )->
                        FirstChildElement( "WindowStyle" )->
                        FirstChildElement( "Inactive" )->
                        FirstChildElement( "Opacity" );
    }
    //OK... whatever element we are pointing to better have text!
    if(!opacityElement->GetText()){
        //how can we not have text here??  that should not happen EVER!!!
        //lets make it the default
        opacityElement->SetText(1.0);
        //save it
        saveChangesTemp();
        //return this value
        return 1.0f;
    }
    std::string opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
    if(DEBUG_ME){std::cerr<<"Inactive Opacity: "<<opacity<<std::endl;}
    return opacity;
}
//######################################### END Window TitleBar ##############################################


//***************************************************************  CORNER ***********************************
unsigned int flWindow::getCorner(){

    //do we have a corner?
    if(!testElement("WindowStyle","Corner")){
        //nope, lets make one!
        createElement("WindowStyle","Corner");

        //point to it
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Corner" );
        //set the default value
        fixer->SetText(4);
        //save
        saveChanges();
        saveChangesTemp();
        //return the default
        return 4;
    }
    //it does exist!
    tinyxml2::XMLElement* cornerElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Corner" );
    //get the text version of our number
    const char* border = cornerElement->GetText();
    //convert it to a base 10 integer
    int sizeOfBorder = strtol(border,0,10);
    //return the integer version
    return sizeOfBorder;
}
void flWindow::setCorner(unsigned int pixels){
    //if for some odd reason they want to set a value we can't use...
    //fix it
    if(pixels>5){pixels = 5;}
    //does this really exist?
    if(!testElement("WindowStyle","Corner")){
        //hmmm.. well we should make it
        createElement("WindowStyle","Corner");
    }
    //point to the corner
    tinyxml2::XMLElement* cornerElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Corner" );
    //set the text to our input
    cornerElement->SetText(pixels);
    //save
    saveChangesTemp();
}
//######################################### END CORNER ##############################################


//****************************  Window Borders (including Title bar height) ***********************************

///COLOR
unsigned int flWindow::getBorderColor(){return getInactiveColor("Outline" );}
unsigned int flWindow::getActiveBorderColor(){return getActiveColor( "Outline" );}

void flWindow::setActiveBorderColor(const double* rgb){setActiveColor("Outline",rgb);}
void flWindow::setBorderColor(const double* rgb){setInactiveColor("Outline",rgb);}


///SIZE
int flWindow::getBorderWidth(){
    //does this really exist in the document?
    if(!testElement("WindowStyle","Width")){
        //WHAT?  it doesn't... ok no problem,
        //lets make it
        createElement("WindowStyle","Width");
        //point to it
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
        //set the default value i.e. 4
        fixer->SetText(4);
        //save it
        saveChanges();
        saveChangesTemp();
        //return our value
        return 4;
    }

    //well this must exist so let's point to it, shall we?
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Width" );
    //get the text
    const char* border = borderElement->GetText();

    //convert the const char* into a base 10 number
    int sizeOfBorder = strtol(border,0,10);

    //return the integer version of the text
    return sizeOfBorder;
}

void flWindow::setBorderWidth(int &border){
    //does it really exist?
    if(!testElement("WindowStyle","Width")){
        //nope... well we should make it
        createElement("WindowStyle","Width");
    }

    //point to the element
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Width" );
    //set the text and save
    borderElement->SetText(border);
    saveChangesTemp();
}

int flWindow::getBorderHeight(){
   //does this exist?
   if(!testElement("WindowStyle","Height")){
        //NO!!!! why?!?!?!?
        //lets make it
        createElement("WindowStyle","Height");
        //point to our new thing
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
        //set it to the default value JWM provides
        fixer->SetText(0);
        //save doubly
        saveChanges();
        saveChangesTemp();
        return 0;
    }
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
    const char* border = borderElement->GetText();
    int sizeOfBorder = strtol(border,0,10);
    //std::cout<<sizeOfBorder<<" Title bar size"<<std::endl;
    return sizeOfBorder;
}
void flWindow::setBorderHeight(int &border){
    //does this exist?
    if(!testElement("WindowStyle","Height")){
        //lets make it shall we?
        createElement("WindowStyle","Height");
    }
    //point to it
    tinyxml2::XMLElement* borderElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "WindowStyle" )->
                            FirstChildElement( "Height" );
    //set the text
    borderElement->SetText(border);

    //save it
    saveChangesTemp();
}
//######################################### END Window Borders ##############################################


//****************************  Font Color  ***********************************
void flWindow::setActiveFontColor(const double* rgb){
    // make the correct starting element
    const char* newORold;

    //if it is new use this
    if(isNewStyle !=-1){newORold="Foreground";}
    else{newORold="Text";}//otherwise use this

    //set the color
    setActiveColor(newORold,rgb);
}
void flWindow::setFontColor(const double* rgb){
    // make the correct starting element
    const char* newORold;

    //if it is new use this
    if(isNewStyle !=-1){newORold="Foreground";}
    else{newORold="Text";}//otherwise use this

    //set the color
    setInactiveColor(newORold,rgb);
}
unsigned int flWindow::getActiveFontColor(){

    // make the correct starting element
    const char* newORold;

    //if it is new use this
    if(isNewStyle !=-1){newORold="Foreground";}
    else{newORold="Text";}//otherwise use this

    //return the result of our generic function
    return getActiveColor(newORold);
}
unsigned int flWindow::getFontColor(){

    // make the correct starting element
    const char* newORold;

    //if it is new use this
    if(isNewStyle !=-1){newORold="Foreground";}
    else{newORold="Text";}//otherwise use this

    //return the result of our generic function
    return getInactiveColor(newORold);
}

//######################################### END Font Color ##############################################


//ETC
void flWindow::setThings(const char* thing, const char* mode){

   //does the thing exist?
   if(!testElement(thing)){
        // NO???? lets make it!
        createElement(thing);
    }

    //point to the thing
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(thing);

    //set the text
    element->SetText(mode);

    //save!
    saveChangesTemp();
}
void flWindow::setThings(const char* thing, const char* mode, int &distance){

   //does the thing exist?
   if(!testElement(thing)){
        //well... lets make it so we can set it
        createElement(thing);
    }

    //point to the thing
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(thing);

    //set the text
    element->SetText(mode);

    //set the attribute
    element->SetAttribute("distance",distance);

    //save
    saveChangesTemp();
}

// use the generic function above to set something
void flWindow::setResize(const char *mode){setThings("ResizeMode",mode);}
void flWindow::setMoveMode(const char *mode){setThings("MoveMode",mode);}
void flWindow::setFocusModel(const char *mode){setThings("FocusModel",mode);}
void flWindow::setSnap(const char *mode, int &distance){setThings("SnapMode",mode,distance);}

void flWindow::setSnap(int &distance){
   // loadTemp();
   if(!testElement("SnapMode")){
        createElement("SnapMode");
    }
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement("SnapMode");
    element->SetAttribute("distance",distance);
    saveChangesTemp();
}

int flWindow::getSnap(){
if(!testElement("SnapMode")){
        createElement("SnapMode");

        //we need to put in the default values here
        //this is what the user is used to, so use them
        tinyxml2::XMLElement* fixer = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "SnapMode" );
        fixer->SetText("border");
        fixer->SetAttribute("distance",5);
        saveChanges();
        saveChangesTemp();
        return 5;
    }
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
   // loadTemp();
    const char* result;

   //does it exist??
    if(!testElement(whichElement)){
        return "x";
    }
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    result = element->GetText();
    return result;
}

std::string flWindow::buttonPath(){
    //this is just a function to get the button path....
    std::string ButtonPath = defaultPath + "Buttons/";
    return ButtonPath;
}
void flWindow::setButton(const char * button, const char* whichElement){

    //does it exist??
    if(!testElement(whichElement)){
        createElement(whichElement);
    }

    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    element->SetText(button);
    saveChangesTemp();
}

//######################################### END Button ##############################################




//********************************************** GROUPS **********************************************
///add
void flWindow::addGroup(){
    //point to the base
    tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM");
    //make our new item
    tinyxml2::XMLNode *newItem = doc.NewElement(GROUP);
    //insert
    groupElement->InsertEndChild(newItem);
    //and save
    saveChangesTemp();
}
void flWindow::addGroupTHING( unsigned int whichGroup, const char* itemName, const char* whichElement){

    //if there is no group just return
    if(!testElement(GROUP)){addGroup();}
    unsigned int i = 1;

    //point to the first Group element
    tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM")->FirstChildElement(GROUP);

    //look for the group we want
    if (whichGroup != i){
        while(groupElement->NextSiblingElement(GROUP) && i!=whichGroup){
            groupElement=groupElement->NextSiblingElement(GROUP);
            i++;
        }
    }

    //create a new element called whichElement... this is whatever we passed in from the functions below
    tinyxml2::XMLNode *newItem = doc.NewElement(whichElement);

    //insert it at the end of whichGroup we are in
    groupElement->InsertEndChild(newItem);

    //save it
    saveChangesTemp();

    //set the text
    groupElement->LastChildElement()->SetText(itemName);

    //save it!!
    saveChangesTemp();
}

//specific functions  see the declarations in the constructor (very top) to figure out OPTION, CLASS, NAME
void flWindow::addGroupItem( unsigned int whichGroup,const char* itemName){addGroupTHING(whichGroup,itemName, OPTION);}
void flWindow::addGroupClass( unsigned int whichGroup, const char* className){addGroupTHING(whichGroup,className, CLASS);}
void flWindow::addGroupProgram(unsigned int whichGroup,const char* progName){addGroupTHING(whichGroup,progName, NAME);}

///REMOVE
void flWindow::removeGroup(unsigned int whichGroup){
    unsigned int i = 1;

    //make a base element
    tinyxml2::XMLElement * baseElement = doc.FirstChildElement("JWM");

    //make our basic pointer
    tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM")->FirstChildElement(GROUP);

    //find out whichGroup group
    if (whichGroup != i){
        while(groupElement->NextSiblingElement(GROUP) && i!=whichGroup){
            groupElement=groupElement->NextSiblingElement(GROUP);
            i++;
        }
    }

    //point our node to the whichGroup group
    tinyxml2::XMLNode* node = groupElement;

    //delete
    baseElement->DeleteChild(node);

    //save
    saveChangesTemp();
    saveChanges();
}
//specific functions
void flWindow::removeGroupProgram(unsigned int whichGroup, const char* progName){removeGroupTHING(whichGroup,progName,NAME);}
void flWindow::removeGroupClass(unsigned int whichGroup, const char* className){removeGroupTHING(whichGroup,className,CLASS);}
void flWindow::removeGroupItem(unsigned int whichGroup, const char* itemName){removeGroupTHING(whichGroup,itemName,OPTION);}

void flWindow::removeGroupTHING(unsigned int whichGroup, const char* progName, const char* whichElement){

    //if there are no groups return... this shouldn't happen... but might as well check
    if(!testElement(GROUP)){return;}
    unsigned int i = 1;

    //create our pointer
    tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM")->FirstChildElement(GROUP);

    //loop to find our whichGroup group
    if (whichGroup != i){
        while(groupElement->NextSiblingElement(GROUP) && i!=whichGroup){
            groupElement=groupElement->NextSiblingElement(GROUP);
            i++;
        }
    }
    //make a tester for our GetText below
    std::string tester;

    //loop through whichElements through the end
    for(tinyxml2::XMLNode* node = groupElement->FirstChildElement(whichElement);node;node = node->ToElement()->NextSiblingElement(whichElement)){

        //if there is text (there should ALWAYS be text here)
        if(node->ToElement()->GetText()){

            //set our tester to the text at node
            tester=node->ToElement()->GetText();

            //if our tester text is the same thing we sent in (at our current whichGroup)
            if(tester.compare(progName)==0){

                //delete it
                groupElement->DeleteChild(node);
                if(DEBUG_ME){std::cerr<<"Deleted: "<<whichElement<<" node: "<<progName<<" from: Group "<<whichGroup<<std::endl;}
                //save!!
                saveChanges();
                saveChangesTemp();
            }
        }
    }
}


///GET
int flWindow::getGroups(Fl_Browser *o){

    //clear the browser
    o->clear();

    //this will hold our string to add
    std::string group;

    //the number for our group
    //we start at 1, because users are not programmers and don't count from 0... usually
    int i = 1;

    //if there are no groups... return 1
    if(!testElement(GROUP)){return 1;}

    //loop through our groups
    for(tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM")->FirstChildElement(GROUP);groupElement;groupElement = groupElement->NextSiblingElement(GROUP)){

        //set  our add string to hold "Group"
        group = GROUP;

        // add a space for readability
        group += " ";

        //convert the integer i to a string and add it to group
        group += convert(i);

        //now we add "Group i" to our browser
        o->add(group.c_str());

        //increment our numeral to add to our string
        i++;
    }

    //we are done, lets issue a redraw to the browser
    o->redraw();

    return 0;
}

int flWindow::getGroupTHING(Fl_Browser *o, unsigned int whichGroup, const char* whichElement){

    //clear our browser
    o->clear();

    //if there are no groups return 1
    if(!testElement(GROUP)){return 1;}

    //start at 1 because users will appreciate it
    unsigned int i = 1;

    // point to the first element
    tinyxml2::XMLElement * groupElement = doc.FirstChildElement("JWM")->FirstChildElement(GROUP);

    //look for whichGroup
    if (whichGroup != i){
        while(groupElement->NextSiblingElement(GROUP) && i!=whichGroup){
            groupElement=groupElement->NextSiblingElement(GROUP);
            i++;
        }
    }

    //loop through our group elements
    for(groupElement=groupElement->FirstChildElement(whichElement);groupElement;groupElement = groupElement->NextSiblingElement(whichElement)){

        //if they have text (they ALWAYS should)
        if(groupElement->GetText()){

            //add the text to our browser
            o->add(groupElement->GetText());
        }
    }

    //refresh the browser
    o->redraw();
    return 0;
}

//specific functions
int flWindow::getGroupClasses(Fl_Browser *o, unsigned int whichGroup){return getGroupTHING(o, whichGroup, CLASS);}
int flWindow::getGroupPrograms(Fl_Browser *o, unsigned int whichGroup){return getGroupTHING(o, whichGroup, NAME);}
int flWindow::getGroupItems(Fl_Browser *o, unsigned int whichGroup){return getGroupTHING(o, whichGroup, OPTION);}

///Options
void flWindow::populateOptions(Fl_Browser *o){
    /*I generated this using
    the chart here:
    http://www.joewing.net/projects/jwm/config.shtml#groups

    programming to write a program :P
    there is NO way I'd type this all out, Joe already spent the effort :D

    saving it as a file and running:

    sed -i 's/^/o->add("/' filename
    sed -i 's/$/");/' filename
    sed -i 's# * #");\nb->add("#' filename
    sed  -i s'/\t//' filename
    */
    //this moves b->add to the end of the file for easy copy and paste
    //  sed -i '/^b->add/{H;$!d;s/.*//};$G;s/\n*//' filename

    // I DID delete things after : manually
    //these are all the options
    o->add("border");
    o->add("centered");
    o->add("constrain");
    o->add("desktop:");
    o->add("hmax");
    o->add("icon:");
    o->add("iignore");
    o->add("layer:");
    o->add("maximized");
    o->add("minimized");
    o->add("noborder");
    o->add("nofocus");
    o->add("nolist");
    o->add("nopager");
    o->add("noshade");
    o->add("nomax");
    o->add("nomin");
    o->add("noclose");
    o->add("nomove");
    o->add("noresize");
    o->add("nofullscreen");
    o->add("notitle");
    o->add("noturgent");
    o->add("opacity:");
    o->add("pignore");
    o->add("shaded");
    o->add("sticky");
    o->add("tiled");
    o->add("title");
    o->add("vmax");
}
void flWindow::populateDesc(Fl_Browser *b){
    //see above how I generated this code
    //these are all the descriptions of the options above
    b->add(gettext("Enables the border on windows in this group."));
    b->add(gettext("Center windows in this group upon initial placement instead of using cascaded placement."));
    b->add(gettext("Prevent clients in this group from moving off-screen."));
    b->add(gettext("The desktop on which windows in this group will be started."));
    b->add(gettext("Make windows in this group maximize horizontally by default."));
    b->add(gettext("The icon to be used for windows in this group."));
    b->add(gettext("Ignore the increment size hint when maximizing windows in this group."));
    b->add(gettext("The layer on which windows in this group will be started. Valid options are below, normal, and above."));
    b->add(gettext("Make windows in this group maximized."));
    b->add(gettext("Make windows in this group minimized."));
    b->add(gettext("Disables the border for windows in this group."));
    b->add(gettext("Prevents windows in this group from grabbing the focus when mapped."));
    b->add(gettext("Causes the tray to ignore windows in this group."));
    b->add(gettext("Causes the pager to ignore windows in this group."));
    b->add(gettext("Disallows shading for windows in this group."));
    b->add(gettext("Disallows maximization for windows in this group."));
    b->add(gettext("Disallows minimization for windows in this group."));
    b->add(gettext("Hides the close button for windows in this group."));
    b->add(gettext("Prevents windows in this group from being moved."));
    b->add(gettext("Prevents windows in this group from being resized."));
    b->add(gettext("Prevents windows in this group from being fullscreen."));
    b->add(gettext("Disables the title bar for windows in this group."));
    b->add(gettext("Ignore the urgent hint for windows in this group. Without this option set, JWM will flash the border of urgent windows."));
    b->add(gettext("Set the opacity for windows in this group. The value is a number between 0.0 and 1.0 inclusive."));
    b->add(gettext("Ignore program-specified initial position."));
    b->add(gettext("Make windows in this group shaded."));
    b->add(gettext("Make windows in this group sticky."));
    b->add(gettext("Attempt to tile windows in this group upon initial placement. If tiled placement fails, windows will fall back to cascaded (the default) or centered if specified."));
    b->add(gettext("Enables the title bar for windows in this group."));
    b->add(gettext("Make windows in this group maximize vertically by default."));
}
//######################################### END Groups ##############################################
