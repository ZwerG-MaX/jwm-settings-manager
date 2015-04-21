#include "../include/flPanel.h"

#include "../include/Apps.h"

Apps::Apps()
{
    volumeiconBin = "volumeicon";
    xfcepowerBin = "xfce4-power-manager";
    //TODO find the battery for the user
    sdeskPowerBin = "sdesk -t ~/.sit/BAT0.svg ~/.sit/BAT0.tt";
    sdeskPowerPlugin = "proc2imgd";
    volumeiconExists = testExec(volumeiconBin);
    xfcepower = testExec(xfcepowerBin);
    sdeskpower = testExec(sdeskPowerBin);
    nmapplet="nm-applet";
    wicd="wicd-gtk";
    wicdExists= testExec(wicd);
    nmappletExists = testExec(nmapplet);
}

Apps::~Apps()
{
    //dtor
}
///*****************************************  PANEL APPS  **********************************************

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
    loadTemp();
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
    loadTemp();
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
    loadTemp();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );

    //loop through the Swallows and look for the xload to delete
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->
        FirstChildElement( "Tray" )->FirstChildElement( "Swallow" );
        node;
        node=node->NextSiblingElement("Swallow")){

        std::string fromDoc = node->GetText();
        fromDoc = fromDoc.erase(5,std::string::npos);
        const char* value  = fromDoc.c_str();
        //std::cout<<value<<'\n';
        std::string xload = "xload";
        if(xload.compare(value) ==0){
            panelElement->DeleteChild(node);
        }
    }
    saveChangesTemp();
}
//+++++++++++++++++++++++++++++++++++++++++++++ END xload ++++++++++++++++++++++++++++++++++++++++++++


///  clock ----------------------------------------------
void Apps::populateClocks(Fl_Browser *o){
    const char* filename = "/usr/share/jwm-settings-manager/time";
    std::string line;
    std::ifstream ifs (filename, std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            o->add(line.c_str());
        }
    }
}

void Apps::changeClock(std::string style){
    loadTemp();
    //std::cerr<<"style: "<<style<<std::endl;
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
    //panelElement=panelElement->FirstChildElement("Clock");
    if (style.compare("Day")==0){panelElement->FirstChildElement("Clock")->SetAttribute("format","%a, %e %b %l:%M %p");
    std::cerr<<"Day"<<std::endl;
    }
    else if(style.compare("12")==0){panelElement->FirstChildElement("Clock")->SetAttribute("format","%l:%M %p");
    std::cerr<<"12"<<std::endl;
    }
    else if(style.compare("24")==0){panelElement->FirstChildElement("Clock")->SetAttribute("format","%H:%M");
    std::cerr<<"24"<<std::endl;
    }
    else if(style.compare("Year")==0){panelElement->FirstChildElement("Clock")->SetAttribute("format","%F %H:%M");
    std::cerr<<"Year"<<std::endl;
    }
    else{panelElement->FirstChildElement("Clock")->SetAttribute("format",style.c_str());}
    saveChangesTemp();
}
/*

TODO: Add function for choosing which program to use for the clock/calender.
Also, add a better default option.
*/
std::string Apps::getClock(){
    loadTemp();
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return "No Clock Added yet";}
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
    panelElement = panelElement->FirstChildElement("Clock");
    const char* current = panelElement->Attribute("format");
    std::string result = getClock(current);
    //std::cout<<"Current Clock: "<<result<<std::endl;
    return result;

}
std::string Apps::getClockProgram(){
    loadTemp();
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return "No Clock Added yet";}
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
    panelElement = panelElement->FirstChildElement("Clock");
    std::string result = panelElement->GetText();
    //std::cout<<"Current Clock Program: "<<result<<std::endl;
    return result;

}
std::string Apps::getClock(const char* timeString){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,timeString,timeinfo);
    std::string stringBuffer = buffer;

    return stringBuffer;
}

//++++++++++++++++++++++++++++++++++++++++++++ END Clock +++++++++++++++++++++++++++++++++++++++++++++


/// GENERAL APP FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////
bool Apps::isAPP(const char* app){
    loadTemp();
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
    loadTemp();
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
    tinyxml2::XMLNode *node = doc.NewElement(app);
    panelElement->InsertEndChild(node);
    panelElement=panelElement->FirstChildElement(app);
    panelElement->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Apps::addAPP(const char* app){
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
    tinyxml2::XMLNode *node = doc.NewElement(app);
    panelElement->InsertEndChild(node);
    saveChangesTemp();
}

void Apps::addAPP(const char* app, const char* attribute, const char* value, const char* newText){
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
    loadTemp();
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


///-----------------------------------------------  Shortcuts -------------------------------------------------

std::string Apps::desktopIcon(std::string filename){
    const char* IconLine = grep("Icon=",filename.c_str());
    std::string ICON = IconLine;
    if(IconLine == NULL){return " ";}
    if(ICON.compare("")==0){return " ";}
    std::string extention = getExtention();
    bool useExt = false;
    unsigned int equals = 0, ext = 0;
    equals = ICON.find("=");
    ext = ICON.find(".");
    if (ext > ICON.length())useExt=true;
    if (equals < ICON.length())ICON= ICON.erase(0,equals+1);
    if (useExt){ICON+=extention;}
    //std::cerr<<ICON<<std::endl;
    return ICON;
}
std::string Apps::desktopName(std::string filename){
    const char* myLANG = getenv("LANG");
    std::string name = "Name";
    name+=myLANG;
    name+="=";
    bool LOCAL = true;
    const char* IconLine = grep(name.c_str(),filename.c_str());
    std::string ICON = IconLine;
    if(IconLine == NULL){LOCAL=false;}
    if(ICON.compare("")==0){LOCAL=false;}
    if(!LOCAL){IconLine = grep("Name=",filename.c_str());}
    ICON = IconLine;
    if(IconLine == NULL){return "";}
    if(ICON.compare("")==0){return "";}
    unsigned int equals = 0;
    equals = ICON.find("=");
    if (equals < ICON.length())ICON= ICON.erase(0,equals+1);
    //std::cerr<<ICON<<std::endl;
    return ICON;
}
void Apps::populate(Fl_Browser *o){
    o->clear();
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
    for(panelElement = panelElement->FirstChildElement();panelElement;panelElement = panelElement->NextSiblingElement()){
        //Get the documents text
        std::string item =panelElement->Name();
        std::string add_text;
        if(item.compare("TrayButton")==0){
            add_text=panelElement->GetText();
            unsigned found = add_text.find_first_of(":");
            if(isExec(add_text.c_str())){
               add_text = add_text.erase(0,found+1);
            }
            else{
                add_text = add_text.erase(0,found+1);
                int number = convert(add_text.c_str());
                switch(number){
                    case 5:
                        add_text="App Menu";
                        break;
                    case 7:
                        add_text="Places Menu";
                        break;
                    case 9:
                        add_text="Shutdown Menu";
                        break;
                    case 8:
                        add_text="System Menu";
                        break;
                    default:
                        break;

                }
            }
        }
        else if(item.compare("Pager")==0){
            add_text="Desktop Switcher";
        }
        else if(item.compare("TaskList")==0){
            add_text="Running App List";
        }
        else if(item.compare("Dock")==0){
            add_text="Indicators";
        }
        else if(item.compare("Swallow")==0){
            add_text="Swallowed App: ";
            std::string swallow =panelElement->GetText();
            unsigned found = swallow.find_first_of(" ");
            swallow=swallow.erase(found+1,std::string::npos);
            add_text+=swallow;
        }
        else if(item.compare("Clock")==0){
            add_text=item;
        }
        else{
            add_text=item;
        }
        o->add(add_text.c_str());
    }
    o->redraw();
}
void Apps::deletePanelItem(std::string whichItem){
    if(whichItem.compare("App Menu")==0){deleteAppMenu();}
    else if(whichItem.compare("Places Menu")==0){deletePlaces();}
    else if(whichItem.compare("Shutdown Menu")==0){deleteShutdown();}
    else if(whichItem.compare("Desktop Switcher")==0){deletePager();}
    else if(whichItem.compare("Running App List")==0){deleteTaskList();}
    else if(whichItem.compare("Indicators")==0){deleteDock();}
    else if(whichItem.compare("Clock")==0){deleteClock();}
    else if(whichItem.compare("")==0){return;}
    else{
        unsigned found = whichItem.find_first_of(":");
        if(found<=whichItem.length()){
            std::string thisItem = whichItem.erase(0,found+1);
            if(thisItem.compare("Swallowed App")){
                deleteAPP("Swallow");
            }
        }
        else{
          deleteShortcut(whichItem);
        }

    }
}
void Apps::getShortcuts(Fl_Browser *o){
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
    std::string programs;
    panelElement = panelElement->FirstChildElement("TrayButton");
    for(panelElement = panelElement->FirstChildElement("TrayButton");panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        //Get the documents text
        programs = panelElement->GetText();
        if(isExec(programs.c_str())){
            //check for the colon
            unsigned found = programs.find_first_of(":");
            //delete everything before and including the colon (i.e. 'exec:')
            programs = programs.erase(0,found+1);
            //add it to the Fl_Browser
            o->add(programs.c_str());
        }
    }
}
bool Apps::compared(const char* something, const char* text){
    std::string stringText = text;
    unsigned found = stringText.find_first_of(":");
    stringText=stringText.erase(found+1,std::string::npos);
    std::string stringSomething = something;
    if(stringText.compare(stringSomething)==0){return true;}
    return false;
}

bool Apps::isShortcuts(){
    loadTemp();
    std::string programs;
    //Multipanel test
    int i = 1;
    bool checkingEXEC = false;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->GetText()){
            programs = panelElement->GetText();
            checkingEXEC =compared("exec:",programs.c_str());
        }
        if(checkingEXEC){return checkingEXEC;}
    }
    return checkingEXEC;
}

void Apps::deleteShortcut(std::string shortcut){
    loadTemp();
    unsigned int found_colon;
    ///set root element to 'Tray'
    tinyxml2::XMLElement* rootNode=doc.FirstChildElement("JWM")->
                                        FirstChildElement( "Tray" );
    std::string programs, substring_programs;
    std::string input = shortcut;
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            rootNode=rootNode->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        ///make sure there is text
        programs = panelElement->GetText();
        found_colon = programs.find_first_of(':');
        substring_programs = programs.substr(found_colon+1,(programs.length()-found_colon));
        //std::cout<<":"<<shortcut<<":-:"<<programs<<":"<<std::endl;
        ///find an instance of 'exec:'
        if(isExec(programs.c_str())){
            if(programs.compare(input)==0){
                rootNode->DeleteChild(panelElement);
                saveChangesTemp();
            }//if input is program in file (delete the program)
        else{
            /// There is no instance of exec: (normal) delete the line if the executable is the same
            //std::cout<<substring_programs<<std::endl;
            if (shortcut.compare(substring_programs)==0){
                rootNode->DeleteChild(panelElement);
                saveChangesTemp();
            }
        }
        }//if 'exec:'
    }//for loop
}

void Apps::addShortcut(const char* icon, const char * program, const char* popup, int border){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    std::string programs, Exec, Root;
    // bool isExec, isRoot; //TODO: check for other buttons and add after them
    std::string exec = "exec:";
    std::string root= "root:";
    std::string shortcut = exec;
    shortcut += program;
    tinyxml2::XMLNode *newNode = doc.NewElement("TrayButton");
//    tinyxml2::XMLNode *buttonNode;
    tinyxml2::XMLNode *trayNode;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    trayNode=panelElement;
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            trayNode=panelElement;
            i++;
        }
    }
    trayNode->InsertEndChild(newNode);
    tinyxml2::XMLElement *node = newNode->ToElement();
    node->SetAttribute("icon",icon);
    node->SetAttribute("popup",popup);
    node->SetText(program);
    if (border == 0) {node->SetAttribute("border","false");}
    else {node->SetAttribute("border",border);}
    saveChangesTemp();
}

void Apps::deleteALLshortcuts(){
    loadTemp();
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
    //panelElement
    ///TODO multipanel checking here too...
    tinyxml2::XMLNode* node = doc.FirstChildElement( "JWM" )->
                                    FirstChildElement( "Tray" );
    for(panelElement= panelElement->FirstChildElement("TrayButton");panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->GetText()){programs = panelElement->GetText();
            unsigned found = programs.find_first_of(":");
            programs = programs.erase(found+1,std::string::npos);
            if(programs.compare(exec)==0){node->DeleteChild(panelElement);}
        }
    }
    saveChangesTemp();
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Shortcuts +++++++++++++++++++++++++++++++++++++++++++++++

void Apps::getIndicators(Fl_Browser *o){
    o->clear();
    if(isNetworkMonitor()){o->add("Network");}
    if (isBattery()){o->add("Battery");}
    if (isVolume()){o->add("Volume");}
    o->redraw();
    //TODO: bluetooth, others????
}
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
    removeAutostart("wicd-gtk -t");
    removeAutostart("nm-applet");
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Network Monitor +++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------- Volume Control -----------------------------------------------
///TODO: other volume applets
    bool Apps::isVolume(){
        if (isAutostart(volumeiconBin)){
            if (!isDock()){addDock();}
            return true;
        }
        return false;
    }

    void Apps::addVolume(){
        if (!isDock()){addDock();}
        //if it exists already exit :)
        if (isVolume()){return;}
        //if the binary for the volume icon exists add it!
        if(volumeiconExists){addAutostart(volumeiconBin);}
        else{errorJWM("No volumeicon...");}
    }
    void Apps::deleteVolume(){
        removeAutostart(volumeiconBin);
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Volume Control +++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------------- Battery -----------------------------------------------
    bool Apps::isBattery(){
        if (isAutostart(xfcepowerBin) || isAutostart(sdeskPowerBin)){
            if (!isDock()){addDock();}
            return true;
        }
        return false;
    }

    void Apps::addBattery(){
        if (!isDock()){addDock();}
        if (isBattery()) return;
        if(xfcepower){addAutostart(xfcepowerBin);}
        else if(sdeskpower){
            addAutostart(sdeskPowerBin);
            addAutostart(sdeskPowerPlugin);
        }
        else{errorJWM("No power manager");}
    }

    void Apps::deleteBattery(){
        if(xfcepower){
            removeAutostart(xfcepowerBin);
        }
        else if(sdeskpower){
            removeAutostart(sdeskPowerBin);
            removeAutostart(sdeskPowerPlugin);
        }
        else{
            errorJWM("No power manager");
        }
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Battery +++++++++++++++++++++++++++++++++++++++++++++++



//##########################################  END APPS ###########################################################
