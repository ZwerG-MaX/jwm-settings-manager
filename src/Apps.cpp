#include "../include/flPanel.h"

#include "../include/Apps.h"

Apps::Apps()
{
    volumeiconBin = "/usr/bin/volumeicon";
    volumeiconExists = testExec(volumeiconBin);
    xfcepowerBin = "/usr/bin/xfce4-power-manager";
    xfcepower = testExec(xfcepowerBin);
    nmapplet="/usr/bin/nm-applet";
    wicd="/usr/bin/wicd-gtk";
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
void Apps::addAppXload(){
    //Check to see if there are other swallows... make test=true if there are
    bool test = false;
    for(tinyxml2::XMLElement* testNode=doc.FirstChildElement("JWM")->
    FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
    testNode;testNode=testNode->NextSiblingElement("Swallow")){
        test= true;
    }
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("Swallow");
    if(test){
        //if there are other swallows, add this after them
        tinyxml2::XMLNode *swallowNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
        trayNode->InsertAfterChild(swallowNode,node);
    }
    else{trayNode->InsertEndChild(node);}
    tinyxml2::XMLText *xloadCommand = doc.NewText("xload -nolabel -bg black -fg red -hl white");
    node->LinkEndChild(xloadCommand);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement("Swallow");

    trayElement->SetAttribute("name","xload");
    trayElement->SetAttribute("width","64");
    saveChangesTemp();
}
bool Apps::xloadLoaded(){
    bool test = false;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->
        FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
        node;node=node->NextSiblingElement("Swallow")){
     test= true;
    }
    if(test){
        for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->
        FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
        node;node=node->NextSiblingElement("Swallow")){
            std::string fromDoc = node->GetText();
            fromDoc = fromDoc.erase(5,std::string::npos);
            const char* value  = fromDoc.c_str();
            //std::cout<<value<<'\n';//debug looking for xload to show up :)
            std::string xload = "xload";
            if(xload.compare(value) ==0){
                return true;
            }
        }
    }
//outside the for loop...
return false;
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

    if (style=="Day"){
        tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

        trayElement->SetAttribute("format","%a, %e %b %l:%M %p");
    }
    else if(style=="12"){
        tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

        trayElement->SetAttribute("format","%l:%M %p");
    }
    else if(style=="24"){
        tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

        trayElement->SetAttribute("format","%H:%M");
    }
    else if(style=="Year"){
        tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

        trayElement->SetAttribute("format","%F %H:%M");
    }
    else{tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

    trayElement->SetAttribute("format","%c");}
}
/*

TODO: Add function for choosing which program to use for the clock/calender.
Also, add a better default option.
*/
void Apps::addClock(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("Clock");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLText *clockCommand = doc.NewText("xclock");
    node->LinkEndChild(clockCommand);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );

    trayElement->SetAttribute("format","%a, %e %b %l:%M %p");
    saveChangesTemp();
}

void Apps::deleteClock(){
    //Check to make sure there is REALLY a clock... just in case
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return;}
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode* node= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );
    panelElement->DeleteChild(node);
    //std::cout<<"Removed Clock\n";
    saveChangesTemp();
}

bool Apps::isClock(){
    if(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" )){return true;}
    else {return false;}
}
std::string Apps::getClock(){
    //Check to make sure there is REALLY a clock... just in case
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return "Error no clock";}
    tinyxml2::XMLElement* panelElement= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Clock" );
    std::string clock = panelElement->Attribute("format");
    if (clock == "%a, %e %b %l:%M %p"){return "Saturday, June 21 7:02 PM";}
    else if(clock =="%l:%M %p"){return "7:02 PM";}
    else if(clock =="%H:%M"){return "19:02";}
    else if(clock =="%F %H:%M"){return "2014-06-21 19:02";}
    else{return clock;}
}
//++++++++++++++++++++++++++++++++++++++++++++ END Clock +++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------  TaskList (Running App list) ----------------------------------------------

bool Apps::isTaskList(){
    if(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TaskList" )){return true;}
    else {return false;}
}

void Apps::addTaskList(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("TaskList");
    trayNode->InsertEndChild(node);
    //set up the Tasklist
    ///TODO: allow user to configure this eventually
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TaskList" );

    trayElement->SetAttribute("maxwidth","256");
    saveChangesTemp();
}

void Apps::deleteTaskList(){
    bool test = isTaskList();
    if (test){
        tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
        tinyxml2::XMLNode* node= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TaskList" );
        panelElement->DeleteChild(node);
        saveChangesTemp();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++ END TaskList +++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------  Pager (Desktop Switcher)----------------------------------------------

bool Apps::isPager(){
    if(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Pager" )){return true;}
    else {return false;}
}

void Apps::addPager(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("Pager");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Pager" );

    trayElement->SetAttribute("labeled","true");
    saveChangesTemp();
}

void Apps::deletePager(){
    bool test = isPager();
    if (test){
        tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
        tinyxml2::XMLNode* node= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Pager" );
        panelElement->DeleteChild(node);
        saveChangesTemp();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++ END Pager +++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------  Dock (Indicators) ----------------------------------------------

bool Apps::isDock(){
    if(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Dock" )){return true;}
    else {return false;}
}

void Apps::addDock(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("Dock");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Dock" );

    trayElement->SetAttribute("labeled","true");
    saveChangesTemp();
}

void Apps::deleteDock(){
    bool test = isDock();
    if(test){
        tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
        tinyxml2::XMLNode* node= doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "Dock" );
        panelElement->DeleteChild(node);
        saveChangesTemp();
    }
}
//++++++++++++++++++++++++++++++++++++++++++++ END Dock +++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------  Shutdown Menu ----------------------------------------------

bool Apps::isShutdown(){
    for(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement()){
        if(panelElement->Attribute("label","Shutdown")){return true;}
    }
    return false;
}
void Apps::addShutdown(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("TrayButton");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLText *shutdown = doc.NewText("root:9");
    node->LinkEndChild(shutdown);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        LastChildElement( "TrayButton" );

    trayElement->SetAttribute("label","Shutdown");
    ///TODO: add in ability for user to set the icon name
    trayElement->SetAttribute("icon","system-shutdown.png");
    saveChangesTemp();
}
void Apps::deleteShutdown(){
    bool test = isShutdown();
    if(!test){return;}

    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *shutdownNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton");

    tinyxml2::XMLElement *element = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        LastChildElement("TrayButton");
    std::string shutdown = element->GetText();
    std::string value ="root:9";
    if(shutdown.compare(value) ==0){
        shutdownNode->DeleteChild(element);
        saveChangesTemp();
    }
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


//---------------------------------------------  Places Menu ----------------------------------------------

void Apps::addPlaces(){
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLNode *node = doc.NewElement("TrayButton");
    trayNode->InsertEndChild(node);
    tinyxml2::XMLText *places = doc.NewText("root:7");
    node->LinkEndChild(places);
    tinyxml2::XMLElement *trayElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        LastChildElement( "TrayButton" );

    trayElement->SetAttribute("label","Places");
    trayElement->SetAttribute("icon","folder.png");
    saveChangesTemp();
}

void Apps::deletePlaces(){
    tinyxml2::XMLElement* rootNode=doc.FirstChildElement("JWM")->
                                        FirstChildElement( "Tray" );
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    node;
    node=node->NextSiblingElement()){
        std::string root = node->GetText();
        std::string places ="root:7";
        if(root.compare(places)==0){
            rootNode->DeleteChild(node);
            saveChangesTemp();
        }
    }
}

bool Apps::isPlaces(){
    for(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement()){
        if(panelElement->Attribute("label","Places")){return true;}
    }
    return false;
}
//++++++++++++++++++++++++++++++++++++++++++++ END Places Menu +++++++++++++++++++++++++++++++++++++++++++++


//-----------------------------------------------  Shortcuts -------------------------------------------------
void Apps::getShortcuts(Fl_Browser *o){
    //Multipanel test
   //int panel = checkWhichPanel();
    int i = 1;
    ///WHAT AM I DOING WRONG HERE??
    //tinyxml2::XMLElement* panelElement = ;
/*    bool test = multipanel();
    if(test){
        for(panelElement;i<=panel;i++){
            panelElement = panelElement->NextSiblingElement("Tray");
        }
    }
    //end MultiPanel
*/
    /*for(tinyxml2::XMLElement* panelElement=doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" )->FirstChildElement( "TrayButton" );
    panelElement->Name() != "TrayButton";
    panelElement = panelElement->NextSiblingElement()){

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
            unsigned found = programs.find_first_of(":");
            //delete everything before and including the colon (i.e. 'exec:')
            programs = programs.erase(0,found+1);
            //add it to the Fl_Browser
            ///TODO add checking here
            o->add(programs.c_str());
        }
    }
*/
}
bool Apps::isShortcuts(){
    std::string programs;
    std::string exec = "exec:";
    //Multipanel test
//    int panel = checkWhichPanel();
    int i = 0;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    bool test = multipanel();
  /*  if(test){
        for(panelElement;i<=panel;i++){
            panelElement = panelElement->NextSiblingElement("Tray");
        }
    }*/
    //end MultiPanel
    tinyxml2::XMLElement *check =panelElement->FirstChildElement( "TrayButton" );
    if(check){
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement("TrayButton")){
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
    //Multipanel test
   //int panel = checkWhichPanel();
    int i = 0;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    bool test = multipanel();
    /*if(test){
        for(panelElement;i<=panel;i++){
            panelElement = panelElement->NextSiblingElement("Tray");
        }
    }*/
    //end MultiPanel
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement("TrayButton")){
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
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" )->FirstChildElement("Tray");
    tinyxml2::XMLNode *newNode = doc.NewElement("TrayButton");
    trayNode->InsertEndChild(newNode);
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
    //Multipanel test
//    int panel = checkWhichPanel();
    int i = 0;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    bool test = multipanel();
  /*  if(test){
        for(panelElement;i<=panel;i++){
            panelElement = panelElement->NextSiblingElement("Tray");
        }
    }*/
    //end MultiPanel
    tinyxml2::XMLElement *check =panelElement->FirstChildElement( "TrayButton" );
    if(check){
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement("TrayButton")){
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
              //  insertShortcut(icon, program, popup, border, panelElement);
            }
        }
    }
    else{
        insertShortcut(icon, shortcut.c_str(), popup, border);
    }

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
    tinyxml2::XMLNode* node = doc.FirstChildElement( "JWM" )->
                                    FirstChildElement( "Tray" );

    for(tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" )->
                                        FirstChildElement( "TrayButton" );
    panelElement;
    panelElement = panelElement->NextSiblingElement("TrayButton")){
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
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        std::string wicd = "wicd-gtk -t";
        std::string nmapplet = "nm-applet";
        if(wicd.compare(value) ==0){
            return true;
        }
        else if(nmapplet.compare(value) ==0){
            return true;
        }
            ///TODO any other network applets?
    }
         //this is outside the loop so if those aren't found...
    return false;
}

void Apps::addNetworkMonitor(){
    const char* nmapplet="/usr/bin/nm-applet";
    const char* wicd="/usr/bin/wicd-gtk";
    bool wicdExists= testExec(wicd);
    bool nmappletExists = testExec(nmapplet);
    if (nmappletExists){
        std::cout << "using " << nmapplet << " for Network\n";
        addAutostart("nm-applet");
    }
    else if (wicdExists){
        std::cout << "using " << wicd << " for Network\n";
        addAutostart("wicd-gtk -t");
    }
    else{
            ///TODO: check other places?
            //add fl error dialog to explain this
        std::string noNetwork=wicd;
        noNetwork += " and ";
        noNetwork += nmapplet;
        noNetwork += " not found";
        std::cout << noNetwork << std::endl;
    }
}

void Apps::deleteNetworkMonitor(){
    removeAutostart("wicd-gtk -t");
    removeAutostart("nm-applet");
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Network Monitor +++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------- Volume Control -----------------------------------------------
    bool Apps::isVolume(){
        std::string volume;
        if(volumeiconExists){
            volume = "volumeicon";
        }
        else {
            //todo other volume icons, do they work?
            return false;
        }
        for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
            std::string fromDoc = node->GetText();
            const char* value  = fromDoc.c_str();
            if(volume.compare(value) ==0){
                return true;
            }
        }
        //this is outside the for loop so if the compare fails...
        return false;
    }

    void Apps::addVolume(){
        if(volumeiconExists){
            addAutostart("volumeicon");
        }
    }

    void Apps::deleteVolume(){
        removeAutostart("volumeicon");
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Volume Control +++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------------- Battery -----------------------------------------------
    bool Apps::isBattery(){
        std::string powermanager;
        const char* gnome = "/usr/bin/???";
        //other power managers?
        for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
            std::string fromDoc = node->GetText();
            const char* value  = fromDoc.c_str();
            if(xfcepower){
                powermanager = "xfce4-power-manager";
            }
            if(powermanager.compare(value) ==0){
                return true;
            }
        }
        //this is outside the for loop so if the compare fails...
        return false;
    }

    void Apps::addBattery(){
        if(xfcepower){
            addAutostart("xfce4-power-manager");
        }
        else{
            errorJWM("No power manager");
        }
    }

    void Apps::deleteBattery(){
        if(xfcepower){
            removeAutostart("xfce4-power-manager");
        }
        else{
            errorJWM("No power manager");
        }
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Battery +++++++++++++++++++++++++++++++++++++++++++++++



//##########################################  END APPS ###########################################################
