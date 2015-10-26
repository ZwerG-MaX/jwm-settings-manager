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
#ifdef DEBUG_TRACK
  std::cerr<<"[flPanel]->"<<std::endl;
#endif // DEBUG
    tinyxml2::XMLDocument doc;
    whichPanel = 1;
    errorMessage="Error... Don't hack around in the files so much ok? :D";
    rootMenu = "5";
    systemMenu = "8";
}


flPanel::~flPanel(){
#ifdef DEBUG_TRACK
  std::cerr<<"<-[flPanel]"<<std::endl;
#endif // DEBUG

}

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
    //loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){createPanel();}
    //make the base element
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    //make the Sibling Tray element to put the new one after
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->LastChildElement( "Tray" );
    //make a node(needed for InsertAfterChild) version of our Sibling Tray
    tinyxml2::XMLNode *node = panelElement;
    //create the new Tray we want to add
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    //add the new tray after the old one within our <JWM></JWM> XML code
    tray->InsertAfterChild(node,newTray);

    //save it temporarily so we can modify it more
    saveChangesTemp();

    //guess the position to put this new panel in
    const char* position = smartPosition();

    //make a spacer so there is at least something there
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    newTray->InsertEndChild(spacer);

    //turn the newTray node back into an element so we can modify the attributes
    tinyxml2::XMLElement *thisone = newTray->ToElement();

    //use our guess position above for the layout
    thisone->SetAttribute("layout",position);

    //guess the vertical and horizontal alignments based on our guessed position from above
    std::string valign = smartVertAlign(position);
    std::string halign = smartHorizAlign(position);
    //set our guesses as the valign and halign
    thisone->SetAttribute("valign",valign.c_str());
    thisone->SetAttribute("halign",halign.c_str());

    //1 means horizontal 2 means vertical and 3 means... something else (center/fixed)
    int vert = whichAlign(valign.c_str());
    int horiz = whichAlign(halign.c_str());

    //Now we will start guessing the width and height to use
    int w,h;
    int screenHeight = Fl::h();
    //a nice starter for a vertical panel is screenheight/2.5
    int guessHeight = screenHeight /2.5;
    if (vert==1 && horiz==3){
        //if it is a top or bottom panel
        //0 means the FULL width
        w=0;
        h=34;
    }
    else if(horiz==2 && vert==3){
        //if it is a left or right panel
        //make it 34 wide and screenHeight /2.5 tall
        w = 34;
        h= guessHeight;
    }
    else{
        //if it is something else... just make it visible?
        w =34;
        h=34;
    }
    thisone->SetAttribute("width",w);
    thisone->SetAttribute("height",h);
    thisone->SetAttribute("border","false");//not sure that JWM still uses this tag
    //save it fully
    saveChangesTemp();
    saveChanges();
    //update the .jsm file
    updatePanels(numPanels());
}

            ///Delete Panel
void flPanel::deletePanel(){
   // loadTemp();
    int i = 1;
    int panel = currentPanel();
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        saveChangesTemp();
        saveChanges();
        updatePanels(numPanels());
        return;
    }
    if (numOFpanels ==1 ){return;}
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
    updatePanels(numPanels());
}

const char* flPanel::horizontalORvertical(int horizontalValue, int verticalValue){
    const char* horizontal = "horizontal";
    const char* vertical= "vertical";
    /*
    if there are:

    0 horiz                     make the next horizontal
    1 horiz 0 vert              make the next horizontal
    1 vert 1 horiz              make the next horizontal
    2 vert 1 horiz              make the next horizontal

    2 horiz 0 vert              make the next vertical
    1 vert 2 horiz              make the next vertical
    anything else... just center it

    Basically I want to preferr Horizontal, because people are used to it.
    */
    if((horizontalValue == 0)){return horizontal;}
    else if((horizontalValue ==1)&&(verticalValue == 0)){return horizontal;}
    else if((horizontalValue==2) && (verticalValue == 0)){return vertical;}
    else if((verticalValue==1) && (horizontalValue == 1)){return horizontal;}
    else if((verticalValue==2) && (horizontalValue == 1)){return horizontal;}
    else if((verticalValue==1) && (horizontalValue == 2)){return vertical;}
    else {return "center";}
}


                        /// SMART ALIGNMENT  ########################################################
const char* flPanel::smartPosition(){
   // loadTemp();
    const char* smartiePosition ="";
    int horizontl = 1, verticl = 0, errors = 0;
    std::string layout,lay;
    std::list<std::string> layouts;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "horizontal";
    }
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    //while there are Tray elements to look through
    do{
        //get each layout
        if(panelElement->Attribute("layout")){
            lay = panelElement->Attribute("layout");
            //add the layout attribute to a string list
            layouts.push_back(lay);
        }
        panelElement=panelElement->NextSiblingElement("Tray");
    }while(panelElement->NextSiblingElement("Tray"));

    //now iterate through the string list of layouts from beginning to end
    for (std::list<std::string>::iterator it = layouts.begin(); it != layouts.end(); ++it){
        layout = *it;
        //if it is horizontal or vertical increment counters
        if(layout.compare("horizontal")==0){++horizontl;}
        else if(layout.compare("vertical")==0){++verticl;}
        else {errors++;}
        //if not... then increment errors
    }
    if (errors != 0){std::cerr<<"Something is wrong with your ~/.jwmrc file"<<std::endl;}
    //std::cout<<"horizontl: "<<horizontl<<" verticl: "<<verticl<<std::endl;

    //call horizontalORvertical to figure out which one to pick.
    smartiePosition = horizontalORvertical(horizontl,verticl);

    return smartiePosition;
}
const char* flPanel::smartHorizAlign(const char* layout){
    std::string layoutSTRING = layout;
    std::string halign,hLayout;
    std::list<std::string> halignLayouts;
    int halignCounter = 0;
    int fixed = 0, center = 0, left = 0, right = 0;
    const char* smartieAlign;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "fixed";
    }
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );

    ///gather all the 'halign' attributes from every tray
    do{
        if(panelElement->Attribute("halign")){
            halign = panelElement->Attribute("halign");
            halignLayouts.push_back(halign);
            halignCounter++;
        }
        panelElement=panelElement->NextSiblingElement("Tray");
    }while(panelElement->NextSiblingElement("Tray"));

    ///figure out how many we have of each one
    for (std::list<std::string>::iterator it = halignLayouts.begin(); it != halignLayouts.end(); ++it){
        hLayout = *it;
        if(hLayout.compare("fixed")==0){fixed++;}
        else if(hLayout.compare("left")==0){left++;}
        else if(hLayout.compare("right")==0){right++;}
        else {center++;}
    }
    ///pick a good alignment based on our guess work... for horizontal we mostly want fixed
    if(layoutSTRING.compare("horizontal")==0){
        //basically we want a fixed Tray.... we don't need it to be anything else
        if (((left+right+center)<=1)&&(fixed<=1)){smartieAlign ="fixed";}
        else if (((left+right)<=1)&&(fixed<1)){smartieAlign ="fixed";}
        else if (((left+center)<=1)&&(fixed<1)){smartieAlign ="fixed";}
        else if (((right+center)<=1)&&(fixed<1)){smartieAlign ="fixed";}
        else{smartieAlign ="center";}
    }
    else{
    //this is our vertical Tray, since it can only be vertical or horizontal
        ///basically we want a LEFT tray first.
        //if not left then Right...
        //otherwise just make it 'fixed'... but they should only have 4 panels anyway... from this program
        if (left==0){smartieAlign ="left";}
        else if ((left==1)&&(fixed+right==0)){smartieAlign ="right";}
        else{smartieAlign ="fixed";}

    }
    return smartieAlign;
}

const char* flPanel::smartVertAlign(const char* layout){
    std::string layoutSTRING = layout;
    std::string valign,vLayout;
    std::list<std::string> valignLayouts;
    int valignCounter = 0;
    int fixed = 0, center = 0, top = 0, bottom = 0;
    const char* smartieAlign;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "bottom";
    }
    //int current = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );

    ///gather all the 'valign' attributes from every tray
    do{
        if(panelElement->Attribute("valign")){
            valign = panelElement->Attribute("valign");
            std::cout<<"valign: "<<valign<<std::endl;
            valignLayouts.push_back(valign);
            valignCounter++;
        }
        panelElement=panelElement->NextSiblingElement("Tray");
    }while(panelElement->NextSiblingElement("Tray"));
    ///figure out how many we have of each one
    for (std::list<std::string>::iterator it = valignLayouts.begin(); it != valignLayouts.end(); ++it){
        vLayout = *it;
        if(vLayout.compare("fixed")==0){fixed++;}
        else if(vLayout.compare("top")==0){top++;}
        else if(vLayout.compare("bottom")==0){bottom++;}
        else {center++;}
    }

    // if there is a top make a bottom!
    // if there is a bottom make a top!
    //otherwise... make it fixed. Not the greatest... but better than center
    if(layoutSTRING.compare("horizontal")==0){
        if ((top==1)&&((bottom+fixed)==0)){smartieAlign ="bottom";}
        else if ((top==0)&&((bottom+fixed)==1)){smartieAlign ="top";}
        else{smartieAlign ="fixed";}
    }
    else if(layoutSTRING.compare("vertical")==0){
    //this is our vertical Tray, since it can only be vertical or horizontal
        //so we pretty much only want fixed....
        if (fixed>=3){smartieAlign ="center";}
        else{smartieAlign ="fixed";}
    }
    else {errorJWM("Not vertical or horizontal??? WHAT!!!!!");smartieAlign="fixed";}
    return smartieAlign;
}
//basically figure out if it is horizontal or vertical
//if it is fixed we should know which one to use, since we are checking halign and valign when we add the panel
int flPanel::whichAlign(const char* Align){
    std::string align = Align;
    if(align.compare("top")==0 || align.compare("bottom")==0){return 1;}
    else if(align.compare("left")==0 || align.compare("right")==0){return 2;}
    else {return 3;}
}
//END MULTIPLE PANELS ###########################################



///  ######################################################## JSM
void flPanel::setJSM(const char* element,const char* value){
    //modify our configuration file... the .jsm file, NOT the .jwmrc file
    loadJSM();
    tinyxml2::XMLElement* ele = jsm.FirstChildElement(element);
    ele->SetText(value);
    saveJSM();
}
// End JSM

 /*! @} */
/// ########################################################  Autohide
void flPanel::panelAutohide(bool &yesOrNo){
    ///this is the OLD style autohide jwm 2.2.2
   // loadTemp();
    bool autohide;
    const char* autohideValue;
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}
    int panel = currentPanel();
    //get our current panel to work on
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //it is true/false only
    if (yesOrNo){autohideValue ="true";}
    else{autohideValue ="false";}
    panelElement->SetAttribute("autohide",autohideValue);
    panelElement->QueryBoolAttribute("autohide", &autohide);
    saveChangesTemp();
}
void flPanel::panelAutohide(const char* where){
    ///this is the newer style jwm(2.3.0++) autohide
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //this can be top,bottom,left,right or off.... it hides the panel in any direction, or turns it off
    panelElement->SetAttribute("autohide",where);
    saveChangesTemp();
}
std::string flPanel::getAutohide(){
    std::string autohide =getStringValue("autohide");
    if(autohide.compare("")==0){return "off";}
    return autohide;
}
///******************************  PANEL SIZE setters and getters  *************************************

///this is my all purpose integer getter
int flPanel::getValue(const char* attribute){
   // loadTemp();
    int value = 0;
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
    }
    int panel = currentPanel();
    //get the current panel
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //if the attribute we want exists, get it
    if (panelElement->Attribute(attribute)){panelElement->QueryIntAttribute(attribute, &value);}
    //return value... either 0 or the value of an existing attribute
    return value;
}

/// all purpose handy-dandy string value getter
std::string flPanel::getStringValue(const char* attribute){
   // loadTemp();
    std::string value = "";
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
    }
    int panel = currentPanel();
    //load our current panel to work on
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //if the attribute exists get the value of it!
    if (panelElement->Attribute(attribute)){value = panelElement->Attribute(attribute);}
    //return the value from the panel or just return ""
    return value;
}
///this is the const char* version of the getStringValue
const char* flPanel::getValue(std::string attribute){
   // loadTemp();
    std::string result;
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
    }
    const char* attrib = attribute.c_str();
    int panel = currentPanel();
    //load our current panel to work on
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //if the attribute exists get the value of it!
    if (panelElement->Attribute(attrib)){result = panelElement->Attribute(attrib);}
    else{
        std::cerr<<"Tray attribute: "<<attribute<<" doesn't exist"<<std::endl;
        return "";
    }
    //return the value from the panel or just return ""
    return result.c_str();
}

/// all purpose heavy-duty(?) generic value setter for INTEGERS!!!!
void flPanel::setValue(const char* attribute, int value){
   // loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}
    std::string VALUE = convert(value);
    int panel = currentPanel();
    //load our current panel to work on
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //we don't need to worry about the attribute existing
    //tinyxml2 creates it if it doesn't
    panelElement->SetAttribute(attribute,VALUE.c_str());
    saveChangesTemp();
}

/// our handy-handy-dandy-dandy const char* value setter
void flPanel::setValue(const char* attribute, const char* value){
   // loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}
    int panel = currentPanel();
    //load our current panel to work on
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //we don't need to worry about the attribute existing
    //tinyxml2 creates it if it doesn't
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}
//END PANEL SIZE

int flPanel::getBorder(){
    //use our handy getStringValue function
    std::string value = getStringValue("border");
    //if it is false return 0, because this is an integer function :)
    if ((value.compare("false")==0)||(value.compare("")==0)){return 0;}
    //if it is not 'false' then it will be an integer
    int result =  getValue("border");
    //return the integer
    return result;
}


///****************************  PANEL BACKGROUND & Opacity ***********************************

    ///These next few functions are all pupropse setters/getters
    //just tell them whichElement
    //the will set the value or get the value

    //Inactive setter of single colors
void flPanel::setBackground(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    //check to make sure whichElement exists
    if(!colorElement->FirstChildElement( whichElement )){
        createElement(whichElement);
        colorElement=doc.FirstChildElement( "JWM" );
    }
    //check to make sure whichElement->Background exists
    if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( "Background" )){
        createElement(whichElement,"Background");
    }
    colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Background" );

    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

//This will get 2 colors... to get one color make an unused variable for color2
//this will return the first color fine
unsigned int flPanel::getBackground(unsigned int &color2, const char * whichElement){
   // loadTemp();
    unsigned int bg=0;
    //check to make sure whichElement exists
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    if(!colorElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    colorElement = doc.FirstChildElement( "JWM" );
    //check to make sure whichElement->Background exists
    if(!colorElement->FirstChildElement( whichElement )->FirstChildElement( "Background" )){
        createElement(whichElement,"Background");
        colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Background" );
        colorElement->SetText("#000000");
        saveChanges();
        saveChangesTemp();
        return 0;
    }
    colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Background" );
    std::string colour = colorElement->GetText();
    //this is a generic color function in Config
    bg = getColor(colour, color2);
    return bg;
}

    //Active
    //these are a bit trickier, since the new config has changed
    //the new style is more intuitive... but... we need to make sure to do it both ways
void flPanel::setActiveBackground(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* colorElement  = doc.FirstChildElement( "JWM" );
    if (whichElement==NULL){return;}

    //make sure our element exists first
    if(!colorElement->FirstChildElement( whichElement )){createElement(whichElement);}

    //use the handy color2string function in Confg
    //this turns our double value (which comes from the Fl color chooser)
    std::string color1 = colorToString(rgb);

    //OK!  is it newstyle or old??
    //either way let's set up colorElement to point to the right place
    if(newStyle() != -1){
        //does the Active element exist?
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )){
            createElement(whichElement,"Active");
        }
        //make sure the Background Element exists as well
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )->FirstChildElement( "Background" )){
            createElement(whichElement,"Active","Background");
        }
        //point to it
        colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )->FirstChildElement( "Background" );
    }
    else{
        //does Active background exist?
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "ActiveBackground" )){
            createElement(whichElement,"ActiveBackground");
        }
        colorElement  = doc.FirstChildElement( "JWM" )->FirstChildElement( "ActiveBackground" );
    }


    //into our .jwmrc value (HTML style color)

    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}
unsigned int flPanel::getActiveBackground(unsigned int  &color2, const char * whichElement){
   // loadTemp();
    unsigned int bg =0;
    tinyxml2::XMLElement* colorElement  = doc.FirstChildElement( "JWM" );
    //make sure our element exists first
    if(!colorElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    //OK!  is it newstyle or old??
    //either way let's set up colorElement to point to the right place
    if(newStyle() != -1){
        //does the Active element exist?
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )){
            createElement(whichElement,"Active");
        }
        //make sure the Background Element exists as well
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )->FirstChildElement( "Background" )){
            createElement(whichElement,"Active","Background");
            colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )->FirstChildElement( "Background" );
            colorElement->SetText("#000000");
            saveChanges();
            saveChangesTemp();
            return 0;
        }
        //point to it
        colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Active" )->FirstChildElement( "Background" );
    }
    else{
        //does Active background exist?
        if(!doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "ActiveBackground" )){
            createElement(whichElement,"ActiveBackground");
            colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "ActiveBackground" );
            colorElement->SetText("#000000");
            saveChanges();
            if(DEBUG_ME){std::cerr<<"Created ActiveBackground, since it didn't exist"<<std::endl;}
            return 0;
        }
        colorElement  = doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "ActiveBackground" );
    }
    std::string colour = colorElement->GetText();
    //use the handy getColor function from Config
    bg = getColor(colour, color2);
    return bg;
}


/// FONT color
void flPanel::setFontColor(const double* rgb, const char * whichElement){
   // loadTemp();
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    if (!colorElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    colorElement = doc.FirstChildElement( "JWM" );
    if (!colorElement->FirstChildElement( whichElement )->FirstChildElement( "Foreground" )){
        createElement(whichElement,"Foreground");
    }
    colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Foreground" );

    //use the handy color2string function in Confg
    //this turns our double value (which comes from the Fl color chooser)
    //into our .jwmrc value (HTML style color)
    std::string color1 = colorToString(rgb);
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

//to use this for one color make an unused color2 variable when you call this
unsigned int flPanel::getFontColor(unsigned int &color2, const char * whichElement){
   // loadTemp();
    unsigned int bg = 0;
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    if (!colorElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    colorElement = doc.FirstChildElement( "JWM" );
    if (!colorElement->FirstChildElement( whichElement )->FirstChildElement( "Foreground" )){
        createElement(whichElement,"Foreground");
        setFontColor(0,whichElement);
        saveChanges();
        saveChangesTemp();
        return 0;
    }
    colorElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Foreground" );
    std::string background;
    //get the string for the color
    background = colorElement->GetText();
    //use the Config function to get the colors
    bg = getColor(background, color2);
    return bg;
}

void flPanel::setActiveFontColor(const double* rgb, const char * whichElement){
   // loadTemp();
    const char* ActiveOrInactive;
    //check if it is new or old
    if(newStyle()!=-1){ActiveOrInactive="Active";}
    else{ActiveOrInactive="ActiveForeground";}
    // set the color using this function from Config
    setFGColor(whichElement,ActiveOrInactive,rgb);
    saveChangesTemp();
}

//color2 is not really used
unsigned int flPanel::getActiveFontColor(unsigned int &color2, const char * whichElement){
   // loadTemp();
    const char* ActiveOrInactive;
    //check for new or old style
    if(newStyle()!=-1){ActiveOrInactive="Active";}
    else{ActiveOrInactive="ActiveForeground";}
    //use this function from config to return 1 color
    return getFGColor(whichElement, ActiveOrInactive, color2);
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
    tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM");
    if(!opacityElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    opacityElement = doc.FirstChildElement( "JWM" );
    if(!opacityElement->FirstChildElement( whichElement )->FirstChildElement( "Opacity" )){
        createElement(whichElement,"Opacity");
    }
    opacityElement=doc.FirstChildElement( "JWM" )->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    opacityElement->SetText(opacity);
    saveChangesTemp();
}

float flPanel::getOpacity(const char* whichElement){
   // loadTemp();
   tinyxml2::XMLElement* opacityElement = doc.FirstChildElement("JWM");
    if(!opacityElement->FirstChildElement( whichElement )){
        createElement(whichElement);
    }
    opacityElement = doc.FirstChildElement( "JWM" );
    if(!opacityElement->FirstChildElement( whichElement )->FirstChildElement( "Opacity" )){
        createElement(whichElement,"Opacity");
        opacityElement=opacityElement->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
        opacityElement->SetText(1.0);
        saveChanges();
        saveChangesTemp();
        std::string thisError = "Opacity didin't exist for ";
        thisError+=whichElement;
        thisError+= " it is set for 1.0";
        errorJWM(thisError);
        return 1.0;
    }
    opacityElement=doc.FirstChildElement("JWM")->FirstChildElement( whichElement )->FirstChildElement( "Opacity" );
    std::string opacityString;
    opacityString = opacityElement->GetText();
    float opacity = float(strtold(opacityString.c_str(),NULL));
    return opacity;
}
// End Panel Color


///MOVE panel items around
int flPanel::deleteOldElement(std::string nameofElement){
    std::cerr<<"flPanel::deleteOldElement("<<nameofElement<<")"<<std::endl;
    int i = 1;
    int panel = currentPanel();
    std::string text;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * baseElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode* deleteNode;
    tinyxml2::XMLElement* button;
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            baseElement=baseElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement("TrayButton");panelElement;panelElement=panelElement->NextSiblingElement("TrayButton")){
        if (panelElement->GetText()){
            text=panelElement->GetText();
            if(text.compare(nameofElement)==0){
                deleteNode=panelElement;
                baseElement->DeleteChild(deleteNode);
                saveChangesTemp();
                saveChanges();
                return 0;
            }
        }
        else{
            if(panelElement->FirstChildElement("Button")){
                std::cerr<<"Contains Button Element"<<std::endl;
                for(button=panelElement->FirstChildElement("Button"); button;button=button->NextSiblingElement("Button")){
                    std::cerr<<"parsing Buttons"<<std::endl;
                    if(button->GetText()){
                        text=button->GetText();
                        std::cerr<<text<<std::endl;
                        if(text.compare(nameofElement)==0){
                            deleteNode=panelElement;
                            baseElement->DeleteChild(deleteNode);
                            saveChangesTemp();
                            saveChanges();
                            return 0;
                        }
                    }
                }
            }

        }
    }
    if(DEBUG_ME){ std::cerr<<"[deleteOldElement("<<nameofElement<<")] This was not found... there must be an error..."<<std::endl;}
    return 1;
}


///This is too complicated... make this work and make it simple
int flPanel::moveMenuDown(std::string menu){
    std::cerr<<"flPanel::moveMenuDown("<<menu<<")"<<std::endl;
    loadTemp();
    std::string namesaver,text;
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement * baseElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode* previous;
    tinyxml2::XMLElement* button;
    tinyxml2::XMLNode *panelEle;

    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            baseElement=baseElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement("TrayButton");panelElement;panelElement=panelElement->NextSiblingElement("TrayButton")){
        if(!panelElement->GetText()){
            if(panelElement->FirstChildElement("Button")){
                std::cerr<<"moveMenuDown::Contains Button Element"<<std::endl;
                for(button=panelElement->FirstChildElement("Button"); button;button=button->NextSiblingElement("Button")){
                    std::cerr<<"moveMenuDown::parsing Buttons"<<std::endl;
                    if(button->GetText()){
                        text=button->GetText();
                        std::cerr<<text<<std::endl;
                        if(text.compare(menu)==0){
                            std::cerr<<"moveMenuDown::  "<<menu<< " compares to: "<<text<<std::endl;
                            panelEle= panelElement->ShallowClone(NULL);
                            previous = panelElement->PreviousSiblingElement();
                            if(previous->ToElement()->FirstChildElement()->GetText()){
                                std::cerr<<"previous->ToElement()->FirstChildElement()->GetText()"<<std::endl;
                                namesaver=previous->ToElement()->FirstChildElement()->GetText();
                                panelElement->InsertAfterChild(previous,panelEle);
                                saveChangesTemp();
                                deleteOldElement(namesaver);
                                return 0;
                            }
                            else{
                            std::cerr<<"NO::::::previous->ToElement()->FirstChildElement()->GetText()"<<std::endl;
                                if(namesaver.compare("")!=0){
                                panelEle= panelElement->ShallowClone(NULL);
                                previous = panelElement->PreviousSibling();
                                    if(previous->ToElement()->GetText()){
                                        namesaver=previous->ToElement()->GetText();
                                        panelElement->InsertAfterChild(previous,panelEle);
                                        saveChangesTemp();
                                        deleteOldElement(namesaver);
                                        return 0;
                                    }
                                }
                                else{errorJWM("moveMenuDown::previous Element does not contain text");return 1;}
                            }
                            return 1;
                        }
                        namesaver=text;
                    }
                }
            }

        }
        else{
            text=panelElement->GetText();
            std::cerr<<"moveMenuDown::   found:" << text<<"in panel element"<<std::endl;
                if(text.compare(menu)==0){
                std::cerr<<"moveMenuDown::   "<<menu<< " compares to: "<<text<<std::endl;
                panelEle= panelElement->ShallowClone(NULL);
                previous = panelElement->PreviousSibling();
                if(previous->ToElement()->GetText()){
                    namesaver=previous->ToElement()->GetText();
                    panelElement->InsertAfterChild(previous,panelEle);
                    saveChangesTemp();
                    deleteOldElement(namesaver);
                    return 0;
                }
                else{errorJWM("moveMenuDown::previous Element does not contain text");return 1;}
            }
        }
    }
    if(DEBUG_ME){ std::cerr<<"[moveMenuDown("<<menu<<")] You reached an impossible situation, please report this."<<std::endl;}
    return 1;
}
// this does not work yet :(
void flPanel::moveUp(std::string item){
    loadTemp();
    std::string namesaver;
    std::string text=item.erase(item.length()-1,std::string::npos);
    if(text.compare("root:")==0){
        moveMenuDown(item);
        return;
    }
    if(item.compare("App Menu")==0){
        moveMenuDown("root:5");
    }
    else if(item.compare("Places Menu")==0){
        moveMenuDown("root:7");
    }
    else if(item.compare("Shutdown Menu")==0){
        moveMenuDown("root:9");
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
///MOVE panel items around
// this does not work yet :(
void flPanel::moveDown(std::string item){
    if(DEBUG_ME){std::cerr<<"flPanel::moveDown("<<item<<")"<<std::endl;}
    loadTemp();
    std::string namesaver;
    if(item.compare("App Menu")==0){
        moveMenuDown("root:5");
    }
    else if(item.compare("Places Menu")==0){
        moveMenuDown("root:7");
    }
    else if(item.compare("Shutdown Menu")==0){
        moveMenuDown("root:9");
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
            std::string thisItem = item.erase(found+1,std::string::npos);
            if(thisItem.compare("Swallowed App")){

            }
            else if(thisItem.compare("root")==0){
                moveMenuDown(item);
                return;
            }
        }
        else{

        }

    }
}

//this is a handy general function to get sub element's text
//such as:
//JWM->Tray->TrayButton etc..
const char* flPanel::getSubElementText(const char* whichElement){
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so getSubElementText() will exit after creating one");
        createPanel();
        return "";
    }
    int panel = currentPanel();
    //get the current panel to work on
    const char* result ="";
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(!panelElement->FirstChildElement(whichElement)){
        createElement("Tray",whichElement);

    }
    else{
        panelElement=panelElement->FirstChildElement(whichElement);
        result = panelElement->GetText();
    }
    return result;
}

void flPanel::setSubElementText(const char* whichElement, const char* value){
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        createPanel();
    }
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //lets make sure the sub element exists
    if(!panelElement->FirstChildElement(whichElement)){
        createElement("Tray",whichElement);
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    //set the text
    panelElement->SetText(value);
    saveChangesTemp();
}

const char* flPanel::getSubElementAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so getSubElementAttribute() will exit after creating one");
        createPanel();
        return "";
    }
    int panel = currentPanel();
    const char* result ="";
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //lets make sure the sub element exists
    if(!panelElement->FirstChildElement(whichElement)){
        createElement("Tray",whichElement);
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    //get the attribute if there is one
    result = panelElement->Attribute(attribute);
    return result;
}
void flPanel::setSubElementAttribute(const char* whichElement,const char* attribute, const char* value){
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so setSubElementAttribute() will create one");
        createPanel();
    }
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
    //lets make sure the sub element exists
    if(!panelElement->FirstChildElement(whichElement)){
        createElement("Tray",whichElement);
    }
    panelElement=panelElement->FirstChildElement(whichElement);
    //set the attribute.  this will make it if it doesn't exist
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}

void flPanel::switchButton(std::string OLD,std::string NEW,std::string tooltip,std::string icon){
    //this is used by configure manually window...
    //we get the OLD exec: line, the NEW exec: line
    unsigned int found = NEW.find_first_of(":");
    std::string testing123;
    if(NEW.length()>found){
        testing123 = NEW.substr(0,found);
        if((testing123.compare("exec")==0)||(testing123.compare("root")==0)){std::cout<<"yay"<<std::endl;}
        else{
            std::cerr<<"Found: "<<testing123<<"\nIn your line: "<<NEW<<"\nMust contain exec: OR root:"<<std::endl;
            return;
        }
    }
    else{
        testing123 ="exec:"+NEW;
        std::cerr<<"Missing exec:... fixing..."<<testing123<<std::endl;
        NEW=testing123;
    }
    loadTemp();
    if(DEBUG_ME){std::cerr<<"OLD: "<<OLD<<" NEW: "<<NEW<<" tooltip: "<<tooltip<<" icon: "<<icon<<std::endl;}
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so setSubElementAttribute() will create one");
        createPanel();
    }
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    //this should be impossible to happen... but just in case :P
    if(!panelElement->FirstChildElement("TrayButton")){return;}
    std::string rootTester;
    for(panelElement=panelElement->FirstChildElement("TrayButton");
        panelElement;
        panelElement=panelElement->NextSiblingElement("TrayButton")){
        rootTester=panelElement->GetText();
        if(rootTester.compare(OLD)==0){
            if(DEBUG_ME){std::cerr<<rootTester<<std::endl;}
            if(NEW.compare("")!=0){panelElement->SetText(NEW.c_str());}
            if(tooltip.compare("")!=0){panelElement->SetAttribute("popup",tooltip.c_str());}
            if(icon.compare("")!=0){panelElement->SetAttribute("icon",icon.c_str());}
            saveChangesTemp();
            return;
        }
    }
}
