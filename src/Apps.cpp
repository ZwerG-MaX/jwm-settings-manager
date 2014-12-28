#include "../include/flPanel.h"

#include "../include/Apps.h"

Apps::Apps()
{
    volumeiconBin = "volumeicon";
    volumeiconExists = testExec(volumeiconBin);
    xfcepowerBin = "xfce4-power-manager";
    xfcepower = testExec(xfcepowerBin);
    nmapplet="nm-applet";
    wicd="wicd-gtk";
    wicdExists= testExec(wicd);
    nmappletExists = testExec(nmapplet);
}

Apps::~Apps()
{
    //dtor
}
//*****************************************  PANEL APPS  **********************************************

//-------------------------- xload  This is the System Monitor -----------------------------------------
/*
    <Swallow name="xload" width="64">
        xload -nolabel -bg black -fg red -hl white
    </Swallow>
    -bg is background color
    -fg is forground
    -hl is highlight
    supports X11 color names
*/
/*TODO: add configuration options for xload colors might be hard*/
bool Apps::isTrayElement(const char* element, std::string text){
    int length = text.length();
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
    for(panelElement = panelElement->FirstChildElement( element );
        panelElement;
        panelElement=panelElement->NextSiblingElement(element)){

        std::string fromDoc = panelElement->GetText();
        fromDoc = fromDoc.erase(length,std::string::npos);
        const char* value  = fromDoc.c_str();
        if(text.compare(value) ==0){
            return true;
        }
    }
    return false;
}

void Apps::addAppXload(){
    ///TODO: get colors for xload some how... probably just guess programatically what will look good...
    //otherwise I may need to use a GUI
    bool test = false;
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
    for(tinyxml2::XMLElement* testNode=panelElement->FirstChildElement( "Swallow" );
    testNode;testNode=testNode->NextSiblingElement("Swallow")){
        test= true;
    }
    tinyxml2::XMLNode *trayNode = panelElement;
    tinyxml2::XMLNode *node = doc.NewElement("Swallow");
    if(test){
        //if there are other swallows, add this after them
        tinyxml2::XMLNode *swallowNode = panelElement->FirstChildElement( "Swallow" );
        trayNode->InsertAfterChild(swallowNode,node);
    }
    else{trayNode->InsertEndChild(node);}
    tinyxml2::XMLText *xloadCommand = doc.NewText("xload -nolabel -bg DimGrey -fg Grey -hl DarkGrey");
    node->LinkEndChild(xloadCommand);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement("Swallow");

    trayElement->SetAttribute("name","xload");
    trayElement->SetAttribute("width","64");
    saveChangesTemp();
}


void Apps::deleteAppXload(){
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );

    //loop through the Swallows and look for the xload to delete
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->
        FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
        node;
        node=node->NextSiblingElement("Swallow")){

        std::string fromDoc = node->GetText();
        fromDoc = fromDoc.erase(5,std::string::npos);
        const char* value  = fromDoc.c_str();
        std::cout<<value<<'\n';
        std::string xload = "xload";
        if(xload.compare(value) ==0){
            panelElement->DeleteChild(node);
        }
    }
    saveChangesTemp();
}
//+++++++++++++++++++++++++++++++++++++++++++++ END xload ++++++++++++++++++++++++++++++++++++++++++++


//---------------------------------------------  clock ----------------------------------------------

void Apps::changeClock(std::string style){
    //Check to make sure there is REALLY a clock... just in case
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return;}
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
    panelElement=panelElement->FirstChildElement("Clock");
    if (style=="Day"){panelElement->SetAttribute("format","%a, %e %b %l:%M %p");}
    else if(style=="12"){panelElement->SetAttribute("format","%l:%M %p");}
    else if(style=="24"){panelElement->SetAttribute("format","%H:%M");}
    else if(style=="Year"){panelElement->SetAttribute("format","%F %H:%M");}
    else{panelElement->SetAttribute("format","%c");}
}
/*

TODO: Add function for choosing which program to use for the clock/calender.
Also, add a better default option.
*/

std::string Apps::getClock(){
    //Check to make sure there is REALLY a clock... just in case
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return "Error no clock";}
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
    std::string clock = panelElement->Attribute("format");
    if (clock == "%a, %e %b %l:%M %p"){return "Saturday, June 21 7:02 PM";}
    else if(clock =="%l:%M %p"){return "7:02 PM";}
    else if(clock =="%H:%M"){return "19:02";}
    else if(clock =="%F %H:%M"){return "2014-06-21 19:02";}
    else{return clock;}
}

//++++++++++++++++++++++++++++++++++++++++++++ END Clock +++++++++++++++++++++++++++++++++++++++++++++


/// GENERAL APP FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////
bool Apps::isAPP(const char* app){
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            ++i;
            std::cout << i;
        }
    }
    if(panelElement->FirstChildElement( app )){return true;}
    else {return false;}
}
void Apps::deleteAPP(const char* app){
    bool checkAPP = isAPP(app);
    if(checkAPP){
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
        tinyxml2::XMLNode* node= panelElement->FirstChildElement( app );
        panelElement->DeleteChild(node);
    }
    saveChangesTemp();
}
void Apps::addAPP(const char* app, const char* attribute, const char* value){
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
    tinyxml2::XMLNode *node = doc.NewElement(app);
    panelElement->InsertEndChild(node);
    panelElement=panelElement->FirstChildElement(app);
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Apps::addAPP(const char* app){
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
    tinyxml2::XMLNode *node = doc.NewElement(app);
    panelElement->InsertEndChild(node);
    saveChangesTemp();
}

void Apps::addAPP(const char* app, const char* attribute, const char* value, const char* newText){
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
    tinyxml2::XMLNode *node = doc.NewElement(app);
    panelElement->InsertEndChild(node);
    tinyxml2::XMLText *textNode = doc.NewText(newText);
    node->LinkEndChild(textNode);
    panelElement=panelElement->FirstChildElement(app);
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}


//---------------------------------------------  Shutdown Menu ----------------------------------------------

void Apps::addShutdown(){
    bool test = isShutdown();
    if(!test){
    const char* menu = gettext("Shutdown");
    addMenu(9,menu,"system-shutdown");
    }
}

void Apps::deleteShutdown(){
    bool test = isShutdown();
    if(test){deleteMenu(9);}
}

void Apps::setShutdownImage(const char* icon){
    for(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement()){
        if(panelElement->Attribute("label","Shutdown")){//TODO: check for root:9 eventually to make text optional
            panelElement->SetAttribute("icon",icon);
            saveChangesTemp();
        }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++ END Shutdown Menu +++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------  App Menu ----------------------------------------------
void Apps::addAppMenu(){
    bool test = isAppMenu();
    if(!test){
        const char* MenuName = gettext("Apps");
        addMenu(5,MenuName,"/usr/share/pixmaps/distributor-logo");
    }
}

void Apps::deleteAppMenu(){
    bool test = isAppMenu();
    if(test){deleteMenu(5);}
}

//---------------------------------------------  Places Menu ----------------------------------------------
void Apps::addPlaces(){
    bool test = isPlaces();
    if(!test){
        const char* MenuName = gettext("Places");
        addMenu(7,MenuName,"folder");
    }
}

void Apps::deletePlaces(){
    bool test = isPlaces();
    if(test){deleteMenu(7);}
}
//++++++++++++++++++++++++++++++++++++++++++++ END Places Menu +++++++++++++++++++++++++++++++++++++++++++++


//-----------------------------------------------  Shortcuts -------------------------------------------------
void Apps::getShortcuts(Fl_Browser *o){
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
    panelElement = panelElement->FirstChildElement("TrayButton");
    for(panelElement;panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        //Get the documents text
        std::string programs = panelElement->GetText();
        std::string exec = "exec:";
        //find the colon
        unsigned found = programs.find_first_of(":");
        //copy this so we don't overwrite it :)
        std::string progTester = programs;
        //delete the program name
        progTester = progTester.erase(found+1,std::string::npos);
        //find out if what is left is 'exec:'
        if(progTester.compare(exec)==0){
            //check for the colon
            unsigned found2 = programs.find_first_of(":");
            //delete everything before and including the colon (i.e. 'exec:')
            programs = programs.erase(0,found+1);
            //add it to the Fl_Browser
            ///TODO add checking here
            o->add(programs.c_str());
        }
    }
}
bool Apps::isShortcuts(){
    std::string programs;
    std::string exec = "exec:";
    //Multipanel test
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
    panelElement =panelElement->FirstChildElement( "TrayButton" );
    if(panelElement){
        for(panelElement;panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
            if(panelElement->GetText()){programs = panelElement->GetText();
                unsigned found = programs.find_first_of(":");
                programs = programs.erase(found+1,std::string::npos);
                if(programs.compare(exec)==0){return true;}
            }
        }
    }
    return false;
}

void Apps::deleteShortcut(const char* shortcut){
    ///set root element to 'Tray'
    tinyxml2::XMLElement* rootNode=doc.FirstChildElement("JWM")->
                                        FirstChildElement( "Tray" );
    std::string programs;
    std::string input = shortcut;
    std::string exec = "exec:";
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
    panelElement=panelElement->FirstChildElement( "TrayButton" );
    if(panelElement){
        for(panelElement;panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        ///make sure there is text
            if(panelElement->GetText()){
                programs = panelElement->GetText();
                unsigned found = programs.find_first_of(":");
                programs = programs.erase(found+1,std::string::npos);
            ///find an instance of 'exec:'
                if(programs.compare(exec)==0){
                    programs = panelElement->GetText();
                    if(programs.compare(input)){
                        rootNode->DeleteChild(panelElement);
                        saveChangesTemp();
                    }//if input is program in file (delete the program)
                }//if 'exec:'
            }//if GetText()
        }//for loop
    }
}

///Can I delete this one now that I have multipanel?
void Apps::insertShortcut(const char* icon, const char * program, const char* popup, int border, tinyxml2::XMLElement* element){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->FirstChildElement("Tray");
    tinyxml2::XMLNode *buttonNode = element;
    tinyxml2::XMLNode *newNode = doc.NewElement("TrayButton");
    trayNode->InsertAfterChild(buttonNode,newNode);
    tinyxml2::XMLText *programText = doc.NewText(program);
    newNode->LinkEndChild(programText);
    tinyxml2::XMLElement *node = newNode->ToElement();
    node->SetAttribute("icon",icon);
    node->SetAttribute("popup",popup);
    node->SetAttribute("border",border);
    saveChangesTemp();
}

void Apps::insertShortcut(const char* icon, const char * program, const char* popup, int border){
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
    tinyxml2::XMLNode *newNode = doc.NewElement("TrayButton");
    panelElement->InsertEndChild(newNode);
    tinyxml2::XMLText *programText = doc.NewText(program);
    newNode->LinkEndChild(programText);
    tinyxml2::XMLElement *node = newNode->ToElement();
    node->SetAttribute("icon",icon);
    node->SetAttribute("popup",popup);
    node->SetAttribute("border",border);
    saveChangesTemp();
}

void Apps::addShortcut(const char* icon, const char * program, const char* popup, int border){
    std::string programs;
    std::string exec = "exec:";
    std::string root= "root:";
    std::string shortcut = exec;
    shortcut += program;
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
    panelElement=panelElement->FirstChildElement( "TrayButton" );
    if(panelElement){
        for(panelElement;panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
            programs = panelElement->GetText();
            unsigned int found = programs.find_first_of(":");

            ///TODO add checking here
            std::string isExec = programs.erase(found+1,std::string::npos);
            std::string isMenu = programs.erase(0,found+1);

        if(panelElement->GetText()&&isExec.compare(exec)==0){
                shortcut+=program;
                std::cout<<"There is an exec:\n";
                insertShortcut(icon, shortcut.c_str(), popup, border, panelElement);
                return;
                }
            ///find an instance of 'root:'
            else if(isExec.compare(root)==0){

                std::cout<<"There is a root:\n";
                insertShortcut(icon, shortcut.c_str(), popup, border, panelElement);
            }
        }
    }
    else{insertShortcut(icon, shortcut.c_str(), popup, border);}

    ///TODO: search for other exec: buttons... if existing, add a sibiling right after it.
    /* if other exec don't exist... look for places menu. add after that.
     * and if that(places) does not exist add it after the main menu
     * and if that(main) does not exist... add it as the First element...
     *  OR figure out how to let user re-arrange everything, and just add it at the end :)
     */
}

void Apps::deleteALLshortcuts(){
    std::string programs;
    std::string exec = "exec:";
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    panelElement = panelElement->FirstChildElement("TrayButton");
    ///TODO multipanel checking here too...
    tinyxml2::XMLNode* node = doc.FirstChildElement( "JWM" )->
                                    FirstChildElement( "Tray" );
    for(panelElement;panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->GetText()){programs = panelElement->GetText();
            unsigned found = programs.find_first_of(":");
            programs = programs.erase(found+1,std::string::npos);
            if(programs.compare(exec)==0){node->DeleteChild(panelElement);}
        }
    }
    saveChangesTemp();
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Shortcuts +++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------- Network Monitor -----------------------------------------------
bool Apps::isNetworkMonitor(){
    bool n = isAutostart("nm-applet");
    bool w = isAutostart("wicd-gtk -t");
    bool dock = isDock();
    if (n && dock){return true;}
    else if (w && dock){return true;}
    return false;
}

void Apps::addNetworkMonitor(){
    if (!isDock()){addDock();}
    if (isNetworkMonitor()) return;
    if (nmappletExists){
        //std::cout << "using " << nmapplet << " for Network\n";
        addAutostart("nm-applet");
    }
    else if (wicdExists){
        //std::cout << "using " << wicd << " for Network\n";
        addAutostart("wicd-gtk -t");
    }
    else{
            ///TODO: check other places?
            //add fl error dialog to explain this
        std::string noNetwork=wicd; noNetwork += " and "; noNetwork += nmapplet; noNetwork += " not found";
        std::cout << noNetwork << std::endl;
    }
    saveChangesTemp();
}

void Apps::deleteNetworkMonitor(){
    if (isDock()){deleteDock();}
    removeAutostart("wicd-gtk -t");
    removeAutostart("nm-applet");
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Network Monitor +++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------- Volume Control -----------------------------------------------
///TODO: other volume applets
    bool Apps::isVolume(){
        bool dock = isDock();
        bool volume = isAutostart("volumeicon");
        if (dock && volume){
            return true;
        }
        return false;
    }
    void Apps::addVolume(){
        if (!isDock()){addDock();}
        if (isVolume()) return;
        if(volumeiconExists){addAutostart("volumeicon");}
    }
    void Apps::deleteVolume(){
        if (isDock()){deleteDock();}
        removeAutostart("volumeicon");
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Volume Control +++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------------- Battery -----------------------------------------------
    bool Apps::isBattery(){
        bool dock = isDock();
        bool xf = isAutostart("xfce4-power-manager");
        bool gnome = false;
        bool sdesk = false;
        if (xf && dock ){return true;}
        //else if (gnome){return true;}
        return false;
    }

    void Apps::addBattery(){
        if (!isDock()){addDock();}
        if (isBattery()) return;
        if(xfcepower){
            addAutostart("xfce4-power-manager");
        }
        else{
            errorJWM("No power manager");
        }
        saveChangesTemp();
    }

    void Apps::deleteBattery(){
        if (isDock()){deleteDock();}
        if(xfcepower){
            removeAutostart("xfce4-power-manager");
        }
        else{
            errorJWM("No power manager");
        }
        saveChangesTemp();
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Battery +++++++++++++++++++++++++++++++++++++++++++++++



//##########################################  END APPS ###########################################################
