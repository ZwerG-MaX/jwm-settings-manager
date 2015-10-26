#include "../include/flPanel.h"

#include "../include/Apps.h"

Apps::Apps(){
#ifdef DEBUG_TRACK
  std::cerr<<"[Apps]->"<<std::endl;
#endif // DEBUG
    gnomeVolume ="gnome-sound-applet";
    gnomeVolumeExists =testExec(gnomeVolume);

    volumeiconBin = "volumeicon";
    volumeiconExists = testExec(volumeiconBin);

    xfcepowerBin = "xfce4-power-manager";
    xfcepower = testExec(xfcepowerBin);

    sdeskPowerPlugin = "proc2imgd";
    sdeskPowerBin = "sdesk -t ~/.sit/BAT0.svg ~/.sit/BAT0.tt";
    sdeskpower = testExec("sdesk");

    nmapplet="nm-applet";
    nmappletExists = testExec(nmapplet);

    wicd="wicd-gtk";
    wicd_tray="wicd-gtk -t";
    wicdExists= testExec(wicd);

    menuROOT="root:p";
    clockROOT="root:c";
    clockCHAR='c';
}

Apps::~Apps(){
#ifdef DEBUG_TRACK
  std::cerr<<"<-[Apps]"<<std::endl;
#endif // DEBUG
}

/**
  \brief isTrayElement looks for an element with text
  this is a general checker to see if the panel element exists with the given text
*/
bool Apps::isTrayElement(const char* element, std::string text){
    loadTemp();
    int length = text.length();
    int i = 1;

    ///make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return false;
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
///*****************************************  PANEL APPS  **********************************************

/**-------------------------- xload  This is the System Monitor -----------------------------------------

    <Swallow name="xload" width="64">
        xload -nolabel -bg black -fg red -hl white
    </Swallow>
    -bg is background color
    -fg is forground
    -hl is highlight
    supports X11 color names
*/
/*TODO: add configuration options for xload colors might be hard, but might be fun :D */

void Apps::addAppXload(){
    ///TODO: get colors for xload some how... probably just guess programatically what will look good...
    //otherwise I may need to use a GUI :)
    loadTemp();
    bool test = false;
    int i = 1;

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){createPanel();}

    int panel = currentPanel();
    std::string xloadLine = "xload -nolabel -bg ";

    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    tinyxml2::XMLElement* testNode=panelElement;
    if(testNode->FirstChildElement( "Swallow" )){
        for(testNode=testNode->FirstChildElement( "Swallow" );
            testNode;
            testNode=testNode->NextSiblingElement("Swallow")){

            test= true;
        }
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

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
    }

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
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement( "Tray" );
    if(!node->FirstChildElement( "Swallow" )){return;}
    //loop through the Swallows and look for the xload to delete
    for(node=node->FirstChildElement( "Swallow" );
        node;
        node=node->NextSiblingElement("Swallow")){

        std::string fromDoc = node->GetText();
        if((fromDoc.compare("")==0)||(fromDoc.length()<5)){return;}
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
    std::string filename = defaultPath + "time";
    std::string line;
    std::ifstream ifs (filename.c_str(), std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            o->add(line.c_str());
        }
    }
}

void Apps::changeClock(std::string style){
    loadTemp();
    if(DEBUG_ME){
        std::cerr<<"style Chosen: "<<style<<std::endl;
    }
    //Check to make sure there is REALLY a clock... just in case
    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){return;}

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
    }

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
    if(!panelElement->FirstChildElement("Clock")){
        if(DEBUG_ME){std::cerr<<"No Clock Element... we need to create it"<<std::endl;}
        createElement("Tray","Clock");
    }
    //panelElement=panelElement->FirstChildElement("Clock");
    if (style.compare("Day")==0){
        panelElement->FirstChildElement("Clock")->SetAttribute("format","%a, %e %b %l:%M %p");
        if(DEBUG_ME){std::cerr<<"Day"<<std::endl;}
    }
    else if(style.compare("12")==0){
        panelElement->FirstChildElement("Clock")->SetAttribute("format","%l:%M %p");
        if(DEBUG_ME){std::cerr<<"12"<<std::endl;}
    }
    else if(style.compare("24")==0){
        panelElement->FirstChildElement("Clock")->SetAttribute("format","%H:%M");
        if(DEBUG_ME){std::cerr<<"24"<<std::endl;}
    }
    else if(style.compare("Year")==0){
        panelElement->FirstChildElement("Clock")->SetAttribute("format","%F %H:%M");
        if(DEBUG_ME){std::cerr<<"Year"<<std::endl;}
    }
    else{
        panelElement->FirstChildElement("Clock")->SetAttribute("format",style.c_str());
        if(DEBUG_ME){std::cerr<<"using: "<<style<<std::endl;}
    }
    saveChangesTemp();
}
/*

TODO: Add function for choosing which program to use for the clock/calender.
Also, add a better default option.
*/
void Apps::setClockProgram(const char* program){
    std::cout<<"TODO"<<program<<std::endl;
}
std::string Apps::getClock(){
    loadTemp();

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "";
    }

    bool exists = isClock();
    //if it doesn't exist... return from this function without doing anything
    if(!exists){
        if(DEBUG_ME){std::cerr<<"No Clock Added yet, adding default"<<std::endl;}
        createElement("Tray","Clock");
        changeClock("Day");
        saveChangesTemp();
        saveChanges();
        return "%a, %e %b %l:%M %p";
    }
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
    if(DEBUG_ME){
        std::cerr<<"Current Clock: "<<result<<std::endl;
    }
    return result;

}
std::string Apps::getClockProgram(){
    loadTemp();

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "";
    }

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
    if(panelElement->FirstChildElement("Clock")){
        panelElement = panelElement->FirstChildElement("Clock");
        std::string result = panelElement->GetText();

        //if nothing exists... make it known
        if(result.compare("")==0){return "";}

        if(newStyle() != -1){
            unsigned int colon = result.find_first_of(':');
            if((colon < result.length())&&(colon!=0)){
                result = result.substr(colon+1,std::string::npos);
                if(DEBUG_ME){std::cerr<<"Current Clock (letters are menus): "<<result<<std::endl;}
            }
        }
        else{
            if(DEBUG_ME){std::cerr<<"Current Clock Program: "<<result<<std::endl;}
            return result;
        }
        if(DEBUG_ME){std::cerr<<"[OLD style JWM] Current Clock Program: "<<result<<std::endl;}
        return result;
    }
    if(DEBUG_ME){std::cerr<<"NO Clock"<<std::endl;}
    return "";
}
void Apps::addClock(){
  if(newStyle()!=-1){addAPP("Clock","format","%a, %e %b %l:%M %p","exec:xclock");}
  else{addAPP("Clock","format","%a, %e %b %l:%M %p","xclock");}
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
void Apps::createClockMenu(std::string thisClockMenu){
/** \brief createClockMenu is for new versions of JWM only
<!-- Clock Menu-->
    <RootMenu height="0" onroot="c">
        <Program icon="time.svg" label="Clock Settings">jwm-settings-manager --clock-settings</Program>
        <Separator/>
        <Program icon="calendar.svg" label="Calendar">zenity --calendar --title="Calendar"</Program>
        <Program icon="time.svg" label="Timezone Settings">xterm -e 'sudo dpkg-reconfigure tzdata'</Program>
    </RootMenu>
*/
    //create the menu
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement("RootMenu");
    element->InsertEndChild(node);
    tinyxml2::XMLElement* clockElement = node->ToElement();
    clockElement->SetAttribute("onroot",thisClockMenu.c_str());
    //tinyxml2::XMLNode* newProgram;

    //set our base to add things to
    //newProgram = clockElement;
    ///<Program icon="time.svg" label="Clock Settings">jwm-settings-manager --clock-settings</Program>
    tinyxml2::XMLNode* progNode = doc.NewElement("Program");
    tinyxml2::XMLElement* progNodeEle;
    clockElement->InsertEndChild(progNode);
    progNodeEle = progNode->ToElement();
    progNodeEle->SetAttribute("icon","time");
    progNodeEle->SetAttribute("label",gettext("Clock Settings"));
    progNodeEle->SetText("jwm-settings-manager --clock-settings");
    ///separator
    tinyxml2::XMLNode* SeparatorNode = doc.NewElement("Separator");
//    tinyxml2::XMLElement* SeparatorNodeEle;
    clockElement->InsertEndChild(SeparatorNode);
    ///<Program icon="calendar.svg" label="Calendar">zenity --calendar --title="Calendar"</Program>
    tinyxml2::XMLNode* progNode2 = doc.NewElement("Program");
    tinyxml2::XMLElement* progNode2Ele;
    clockElement->InsertEndChild(progNode2);
    progNode2Ele = progNode2->ToElement();
    progNode2Ele->SetAttribute("icon","calendar");
    progNode2Ele->SetAttribute("label",gettext("Calendar"));
    progNode2Ele->SetText(getJSMelement("clock"));
    ///<Program icon="time.svg" label="Timezone Settings">xterm -e 'sudo dpkg-reconfigure tzdata'</Program>
    tinyxml2::XMLNode* progNode3 = doc.NewElement("Program");
    tinyxml2::XMLElement* progNode3Ele;
    clockElement->InsertEndChild(progNode3);
    progNode3Ele = progNode3->ToElement();
    progNode3Ele->SetAttribute("icon","time");
    progNode3Ele->SetAttribute("label",gettext("Timezone Settings"));
    progNode3Ele->SetText(getJSMelement("clocktz"));
    saveChangesTemp();
    saveChanges();
}

//++++++++++++++++++++++++++++++++++++++++++++ END Clock +++++++++++++++++++++++++++++++++++++++++++++


/// GENERAL APP FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////
bool Apps::isAPP(const char* app){
    loadTemp();
    int i = 1;

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return false;
    }

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

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
    }

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

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){createPanel();}

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

    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){createPanel();}

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
    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){createPanel();}

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
    if(newStyle()>=1){
        std::string APP = app;
        if (APP.compare("Clock")==0){
            if(DEBUG_ME){std::cerr<<"New Style Clock using: "<<clockROOT<<std::endl;}
            tinyxml2::XMLText *textNode = doc.NewText(clockROOT);
            node->LinkEndChild(textNode);
            saveChangesTemp();
            if(!isRootMenu("c")){
                createClockMenu("c");
            }
            return;
        }
    }
    tinyxml2::XMLText *textNode = doc.NewText(newText);
    node->LinkEndChild(textNode);
    saveChangesTemp();
}


///-----------------------------------------------  Shortcuts -------------------------------------------------

std::string Apps::desktopIcon(std::string filename){
    if (filename.compare("")==0){std::cerr<<"No file specified to look for Icon"<<std::endl;return "";}
    const char* IconLine = grep("Icon=",filename.c_str());
    std::string ICON = IconLine;
    if((IconLine == NULL)||(ICON.compare("")==0)){std::cerr<<"No icon found in "<<filename<<std::endl;return " ";}
    //std::cout<<"Icon:::"<<ICON<<std::endl;
    bool useExt = false;
    unsigned int equals = 0, ext = 0;
    equals = ICON.find("=");
    ext = ICON.find(".");
    if (ext > ICON.length()){useExt=true;}
    if (equals < ICON.length()){ICON= ICON.erase(0,equals+1);}

    if (useExt){
        if(newStyle() < 1){
        std::string extention = getExtention();
        ICON+=extention;
        }
        useExt=false;
    }
    if(DEBUG_ME){std::cerr<<"Desktop Icon found: "<<ICON<<std::endl;}
    return ICON;
}

std::string Apps::desktopName(std::string filename){
    if (filename.compare("")==0){return "";}
    const char* myLANG = getenv("LANG");
    std::string name = "Name";
    name+=myLANG;
    name+="=";
    bool LOCAL = true;
    const char* IconLine = grep(name.c_str(),filename.c_str());
    std::string ICON = IconLine;
    if(IconLine == NULL){LOCAL=false;}
    if(ICON.compare("")==0){LOCAL=false;}
    if(!LOCAL){
        IconLine = grep("Name=",filename.c_str());
        ICON = IconLine;
    }
    if(IconLine == NULL){return "";}
    if(ICON.compare("")==0){return "";}
    unsigned int equals = 0;
    equals = ICON.find("=");
    if (equals < ICON.length())ICON= ICON.erase(0,equals+1);
    if(DEBUG_ME){std::cerr<<"Desktop Name found: "<<ICON<<std::endl;}
    return ICON;
}


void Apps::populate(Fl_Browser *o){
    o->clear();
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
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
    for(panelElement = panelElement->FirstChildElement();panelElement;panelElement = panelElement->NextSiblingElement()){
        //Get the documents text
        std::string item =panelElement->Name();
        std::string add_text;
        std::string rootMenu = "Menu: ";
        if(item.compare("TrayButton")==0){
            if(panelElement->FirstChildElement("Button")){

                if(panelElement->FirstChildElement("Button")->GetText()){add_text=panelElement->FirstChildElement("Button")->GetText();}
            }
            else{
                if(panelElement->GetText()){add_text=panelElement->GetText();}
            }
            unsigned found = add_text.find_first_of(":");
            if(!isExec(add_text.c_str())){
                if(found<add_text.length() && found > 0){add_text = add_text.erase(0,found+1);}
                add_text=rootMenu + add_text;
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
        if(DEBUG_ME){std::cerr<<"populating Panel Apps with: "<<add_text<<std::endl;}
        o->add(add_text.c_str());
    }
    o->redraw();
}
void Apps::deletePanelItem(std::string whichItem){
    std::string rootMenu = "Menu: ";
    unsigned found = whichItem.find(rootMenu);
    if(found<whichItem.length()){
        std::string tempMenu = whichItem;
        tempMenu = tempMenu.erase(0,rootMenu.length());
        //unsigned int menuNumber = convert(tempMenu.c_str());
        deleteMenu(tempMenu.c_str());
        return;
    }

    if(whichItem.compare("Running App List")==0){deleteTaskList();}
    else if(whichItem.compare("Indicators")==0){deleteDock();}
    else if(whichItem.compare("Clock")==0){deleteClock();}
    else if(whichItem.compare("")==0){return;}
    else{
        if(DEBUG_ME){std::cerr<<"deletePanelItem: "<<whichItem<<std::endl;}
        unsigned found = whichItem.find_first_of(":");
        if(found<=whichItem.length()){
            std::string thisItem = whichItem.substr(0,found);
                if(DEBUG_ME){std::cerr<<thisItem<<std::endl;}
            if(thisItem.compare("Swallowed App")==0){
                deleteAPP("Swallow");
            }
            else if(thisItem.compare("exec")==0){
            //std::cout<<"found executable"<<std::endl;
                deleteShortcut(whichItem);
            }
            else{
                    if(DEBUG_ME){std::cerr<<"Found: "<<thisItem<<"\nIn your line: "<<whichItem<<"\nMust contain exec: OR root: OR Swallowed App:"<<std::endl;}
                    return;
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
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
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
    std::string programs;
    if (panelElement->FirstChildElement("TrayButton")){
        for(panelElement = panelElement->FirstChildElement("TrayButton");panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
            //Get the documents text
            if(panelElement->FirstChildElement("Button")){programs = panelElement->FirstChildElement("Button")->GetText();}
            else{programs = panelElement->GetText();}
            if(isExec(programs.c_str())){
                //check for the colon
                unsigned found = programs.find_first_of(":");
                //delete everything before and including the colon (i.e. 'exec:')
                programs = programs.erase(0,found+1);
                //add it to the Fl_Browser
                if(DEBUG_ME){std::cerr<<"adding: "<<programs<<" to the browser"<<std::endl;}
                o->add(programs.c_str());
            }
        }
    }
}

bool Apps::isShortcuts(){
    loadTemp();
    std::string programs;
    //Multipanel test
    int i = 1;
    bool checkingEXEC = false;
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return false;
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
    if(!panelElement->FirstChildElement( "TrayButton" )){return false;}
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->FirstChildElement("Button")){
            if(panelElement->FirstChildElement("Button")->GetText()){
                programs = panelElement->FirstChildElement("Button")->GetText();
                checkingEXEC = comparedColon("exec:",programs.c_str());
                if(checkingEXEC){return checkingEXEC;}
            }
        }
        if(panelElement->GetText()){
            programs = panelElement->GetText();
            checkingEXEC = comparedColon("exec:",programs.c_str());
        }
        if(checkingEXEC){return checkingEXEC;}
    }
    return checkingEXEC;
}

void Apps::deleteShortcut(std::string shortcut){
    loadTemp();
    //make sure Tray exists
    int numOFpanels = numPanels();
    unsigned int found_colon =0;
    std::string programs, substring_programs;
    std::string input = shortcut;
    int i = 1;
    int panel = currentPanel();

    //does the tray element exist???
    if (numOFpanels == -1){
        createPanel();
        return;
    }
    //set root element to 'Tray'
    tinyxml2::XMLElement* rootNode=doc.FirstChildElement("JWM")->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            rootNode=rootNode->NextSiblingElement("Tray");
            i++;
        }
    }

    //do we have any buttons??
    if(!panelElement->FirstChildElement( "TrayButton" )){return;}
    tinyxml2::XMLElement* button;
    //loop through the buttons
    for(panelElement=panelElement->FirstChildElement( "TrayButton" );panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){

        //make sure there is text
        if(panelElement->GetText()){programs = panelElement->GetText();}
        //if not see if there is a button
        if(panelElement->FirstChildElement("Button")){
            if(panelElement->FirstChildElement("Button")->GetText()){
                button = panelElement;
                programs = button->FirstChildElement("Button")->GetText();
                button = button->FirstChildElement("Button");
            }
        }
        if(DEBUG_ME){std::cerr<<"Input: "<<input<<" Current: "<<programs<<std::endl;}
        //make sure the text is not blank
        if(programs.compare("")!=0){found_colon = programs.find_first_of(':');}

        //make sure found_colon is not 0 or greater than the length
        if(found_colon!=0 && found_colon < programs.length()){substring_programs = programs.substr(found_colon+1,(programs.length()-found_colon));

            //find an instance of 'exec:'
            if(isExec(programs.c_str())){

                //if programs has exec:------ and the input(shortcut) has exec:----- and are the same... DELETE!!!
                if(programs.compare(input)==0){
                    rootNode->DeleteChild(panelElement);
                    saveChangesTemp();
                    return;
                }//if input is program in file (delete the program)

                else{
                    // There is no instance of exec: (abnormal) delete the line if the executable is the same
                    if (shortcut.compare(substring_programs)==0){
                        rootNode->DeleteChild(panelElement);
                        saveChangesTemp();
                    }
                }
            }//if 'exec:'
        }
    }//for loop
}
/********************************************//**
 \brief Add Shortcut
        Add a Traybutton with:
        \param icon - filename (or full path) for icon to use
        \param program - executable program
        \param tooltip - text to display on mouse over
        \param border - size of a border to put around the button

 ***********************************************/
void Apps::addShortcut(const char* icon, const char * program, const char* popup, int border){
        //check the inputs
    if (icon==NULL){
        std::string testIcon="application-default-icon";
        testIcon+=getExtention();
        icon = testIcon.c_str();
    }
    if(program==NULL){return;}
    if(popup==NULL){popup=program;}
    if(jwmVersion()>0){addButton(icon,program,popup,border);}/// check the binary version... add the correct button if it is newer
    loadTemp();
    int i = 1;
    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
    }
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
    if(panelElement->FirstChildElement("TrayButton")){
        std::string rootTester;
       // for(panelElement=panelElement->FirstChildElement("TrayButton");panelElement;panelElement->NextSiblingElement("TrayButton")){
         //   rootTester=panelElement->GetText();
          //  std::cout<<rootTester<<std::endl;
       // }
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

/********************************************//**
 \brief Add Button
    Just like Add Shortcut, but only for newer JWM versions.
    Add a Traybutton with:
    \param icon - filename (or full path) for icon to use
    \param program - executable program
    \param tooltip - text to display on mouse over
    \param border - size of a border to put around the button
 ***********************************************/
void Apps::addButton(const char* icon, const char * program, const char* popup, int border){
        //check the inputs
    if (icon==NULL){
        std::string testIcon="application-default-icon";
        testIcon+=getExtention();
        icon = testIcon.c_str();
    }
    if(program==NULL){return;}
    if(popup==NULL){popup=program;}

    loadTemp();
    int i = 1;
    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
    }
    int panel = currentPanel();
    std::string programs, Exec, Root;
    // bool isExec, isRoot; //TODO: check for other buttons and add after them
    std::string exec = "exec:";
    std::string root= "root:";
    std::string shortcut = exec;
    shortcut += program;
    tinyxml2::XMLNode *newNode = doc.NewElement("TrayButton");
    tinyxml2::XMLNode *trayNode;
    tinyxml2::XMLNode *trayNode2;
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
    trayNode2 = newNode;
    tinyxml2::XMLElement *node = newNode->ToElement();
    node->SetAttribute("icon",icon);
    node->SetAttribute("popup",popup);
    if (border == 0) {node->SetAttribute("border","false");}
    else {node->SetAttribute("border",border);}

    tinyxml2::XMLNode *buttonNode= doc.NewElement("Button");
    tinyxml2::XMLNode *buttonNode2= doc.NewElement("Button");
    trayNode2->InsertEndChild(buttonNode);
    trayNode2->InsertEndChild(buttonNode2);
    tinyxml2::XMLElement *BUTTON = buttonNode->ToElement();
    tinyxml2::XMLElement *BUTTON2 = buttonNode2->ToElement();
    BUTTON->SetAttribute("mask",1);
    BUTTON->SetText(program);
    BUTTON2->SetAttribute("mask",23);
    if(DEBUG_ME){std::cerr<<"mask=1 launches:"<<program<<"\nadding "<<menuROOT<<std::endl;}
    BUTTON2->SetText(menuROOT);
    saveChangesTemp();
    return;
}

void Apps::deleteALLshortcuts(){
    loadTemp();
    //make sure Tray exists
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return;
    }
    std::string programs;
    std::string exec = "exec:";
    int i = 1;
    int panel = currentPanel();
    tinyxml2::XMLNode* node;
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            node=panelElement;
            i++;
        }
    }
    tinyxml2::XMLElement* button;
    for(panelElement= panelElement->FirstChildElement("TrayButton");panelElement;panelElement = panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->GetText()){
            programs = panelElement->GetText();
            unsigned found = programs.find_first_of(":");
            programs = programs.erase(found+1,std::string::npos);
            if(programs.compare(exec)==0){
                node->DeleteChild(panelElement);
                return;
            }
        }
        if(panelElement->FirstChildElement("Button")){
            for(button = panelElement->FirstChildElement("Button");button;button->NextSiblingElement("Button")){
                if(button->GetText()){
                    programs = button->GetText();
                    unsigned found = programs.find_first_of(":");
                    programs = programs.erase(found+1,std::string::npos);
                    if(programs.compare(exec)==0){
                        node->DeleteChild(button);
                        return;
                    }

                }
            }

        }
    }
    saveChangesTemp();
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Shortcuts +++++++++++++++++++++++++++++++++++++++++++++++

void Apps::getIndicators(Fl_Browser *o){
    //this is used in the UI
    const char* net = gettext("Network");
    const char* batt = gettext("Battery");
    const char* vol = gettext("Volume");
    o->clear();

    //check them and add them to the UI
    if(isNetworkMonitor()){o->add(net);}
    if (isBattery()){o->add(batt);}
    if (isVolume()){o->add(vol);}
    o->redraw();
    //TODO: bluetooth, others????
}
//----------------------------------------------- Network Monitor -----------------------------------------------
bool Apps::isNetworkMonitor(){
    //TODO: find other network applets people use
    //nmapplet and wicd_tray are in the Constructor
    bool n = isAutostart(nmapplet);
    bool w = isAutostart(wicd_tray);
    bool dock = isDock();
    if (n && dock){return true;}
    else if (w && dock){return true;}
    return false;
}

void Apps::addNetworkMonitor(){
    // we need to make sure they can see it...
    //make sure the Dock exists first
    if (!isDock()){addDock();}
    //if it is already there, don't add another :)
    if (isNetworkMonitor()) return;

    //figure out what they have installed
    //prefer nm-applet because most people do
    //anyone who cares enough will be able to change it

    //nmapplet and wicd_tray are in the Constructor
    if (nmappletExists){addAutostart(nmapplet);}
    else if (wicdExists){addAutostart(wicd_tray);}
    else{
            ///TODO: check other network things
        std::string noNetwork=wicd; noNetwork += " and "; noNetwork += nmapplet; noNetwork += " not found";
        errorJWM(noNetwork);
    }
    saveChangesTemp();
}

void Apps::deleteNetworkMonitor(){
    //nmapplet and wicd_tray are in the Constructor
    removeAutostart(wicd_tray);
    removeAutostart(nmapplet);
}

//++++++++++++++++++++++++++++++++++++++++++++++ END Network Monitor +++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------- Volume Control -----------------------------------------------
///TODO: other volume applets
    bool Apps::isVolume(){
        //volumeiconBin as well as gnomeVolume is in the Constructor
        if (isAutostart(volumeiconBin) || isAutostart(gnomeVolume)){
            //make sure the Dock exists, or they wont see this
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
        //if not try the gnome one
        if(volumeiconExists){addAutostart(volumeiconBin);}
        else if (gnomeVolumeExists){addAutostart(gnomeVolume);}
        else{errorJWM("No volume icon...");}
    }
    void Apps::deleteVolume(){
        //get rid of ALL of them :)
        removeAutostart(volumeiconBin);
        removeAutostart(gnomeVolume);
    }
//++++++++++++++++++++++++++++++++++++++++++++++ END Volume Control +++++++++++++++++++++++++++++++++++++++++++++++

//----------------------------------------------- Battery -----------------------------------------------
    bool Apps::isBattery(){
        // if there is something in autostart find it
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



//----------------------------------------------- Menu -----------------------------------------------

void Apps::removeMenuItem(Fl_Browser *elementName, Fl_Browser *elementText){
    const char* root ="RootMenu";
    int LINEposition = elementName->value();
    std::string NAME = elementName->text(LINEposition);
    std::string TEXT = elementText->text(LINEposition);
//    tinyxml2::XMLElement * menuElement;
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(NAME.compare(TEXT)==0){
            std::cerr<<NAME<<" has no text"<<std::endl;
        }
    }

}

//This function configures menus
void Apps::ConfigMenuItem(Fl_Browser *elementName,
                        Fl_Browser *elementText,
                        Fl_Input * itemLabel,
                        Fl_Input * itemIcon,
                        Fl_Input * itemProgram,
                        Fl_Check_Button *itemCheck){
    const char* root ="RootMenu"; //just so I don't have typos
    //this will hold the attribute value to compare with onroot
    std::string attributeValue;

    //this will have the document text to compare with TEXT (below)
    std::string docText;

    // this gets the line position for both things.. since they are set the same
    unsigned int LINEposition = elementName->value();
    if(LINEposition<elementName->size()){return;}
    //this gets the text at the line position
    const char* elename = elementName->text(LINEposition);
    if(elename==NULL){return;}
    std::string NAME = elename;

    //this gets the text at the line position
    const char* eletext = elementText->text(LINEposition);
    if(eletext==NULL){return;}
    std::string TEXT =eletext;

    //this is the root menu number...  I have hidden the label, since my menu const char* wont make sense to the user
    //but it is a nice way to store the data easily
    const char* rootmenu = elementText->label();
    if(rootmenu==NULL){return;}
    // this will be the element we check later
    tinyxml2::XMLElement * menuElement;

    //these will hold our values from the dialog window
    const char* iteml = itemIcon->value();
    if(iteml==NULL){return;}
    const char* itemI = itemLabel->value();
    if(itemI==NULL){return;}
    const char* itemP=NULL;
    if(itemProgram->visible()){
        itemP = itemProgram->value();
    }
    else{itemP="None";}
    if(itemP==NULL){return;}
    std::string label = iteml;
    std::string icon = itemI;
    std::string program = itemP;
    int confirm = itemCheck->value();
    const char* labelAttrib = "label";
    const char* iconAttrib = "icon";
    std::cout<<"configuring"<<label<<":"<<program<<":"<<label<<std::endl;
    //find the menu we want using our hidden rootmenu and the attribute onroot
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one in the hidden label
            if (attributeValue.compare(rootmenu)==0){
                //Yes it does... loop through the elements of that menu
                for(menuElement = menu->FirstChildElement();menuElement;menuElement = menuElement->NextSiblingElement()){
                    //does it match the Name of the item the user clicked?
                    if(menuElement->Name()){
                    if(DEBUG_ME)std::cout<<NAME<<std::endl;
                    if(NAME.compare(menuElement->Name())==0){
                        //lets see if there is text
                        if(menuElement->GetText()){
                            docText=menuElement->GetText();
                            //this must be a proram
                            //is it the one we want??
                            if(TEXT.compare(docText)==0){
                                //Program (label,icon) [program]
                                if(DEBUG_ME){std::cerr<<NAME<<" name"<<std::endl;}
                                int a = setMenuAttribute(NAME.c_str(),labelAttrib,label,rootmenu);
                                int b = setMenuAttribute(NAME.c_str(),iconAttrib,icon,rootmenu);

                                // which element?      new text        which menu    old text
                                int c = setMenuText(NAME.c_str(), program.c_str(), rootmenu, docText.c_str());

                                if((a==0) && (b==0) && (c==0)){saveChanges();}
                                else{std::cerr<<"There was a problem configuring: "<<NAME<<std::endl;}
                                return;
                            }
                        }
                        //no text it must be a
                        /*
                            Restart (label,icon)
                            Exit (label,icon,confirm)
                            Separator
                            (or something I don't support yet)

                            So we will ignore prog_input for sure
                        */
                        else{
                            if(NAME.compare("Separator")==0){
                                std::cerr<<"Can not configure: "<<NAME<<"... there is nothing to configure"<<std::endl;
                            }
                            else if(NAME.compare("Exit")==0){
                                //we need (label,icon,confirm)
                                //confirm:
                                // 1 is on
                                // 0 is off
                                int a = setMenuAttribute(NAME.c_str(),labelAttrib,label,rootmenu);
                                int b = setMenuAttribute(NAME.c_str(),iconAttrib,icon,rootmenu);
                                //we convert the int to a c string
                                int c = setMenuAttribute(NAME.c_str(),"confirm",(convert(confirm).c_str()),rootmenu);
                                if((a==0) && (b==0) && (c==0)){saveChanges();}
                                else{std::cerr<<"There was a problem configuring: "<<NAME<<std::endl;}
                                return;
                            }
                            else if(NAME.compare("Restart")==0){
                                //we need (label,icon)
                                int a = setMenuAttribute(NAME.c_str(),labelAttrib,label,rootmenu);
                                int b = setMenuAttribute(NAME.c_str(),iconAttrib,icon,rootmenu);
                                if((a==0) && (b==0)){saveChanges();}
                                else{std::cerr<<"There was a problem configuring: "<<NAME<<std::endl;}
                                return;
                            }
                            else if(NAME.compare("Include")==0){
                                // which element?      new text        which menu    old text
                                if(setMenuText(NAME.c_str(), program.c_str(), rootmenu, docText.c_str())==0){saveChanges();}
                                else{std::cerr<<"There was a problem configuring: "<<NAME<<std::endl;}
                                return;
                            }
                            else{
                                //this supports everything fully except Menu
                                /*
                                Desktops (label,icon)
                                SendTo (label,icon)
                                Stick (label,icon)
                                Maximize (label,icon)
                                Minimize (label,icon)
                                Shade (label,icon)
                                Move (label,icon)
                                Resize (label,icon)
                                Kill (label,icon)
                                Close (label,icon)

                                // missing labeled which defaults to false
                                // height defaults to parent menu
                                //so these are not absolutely needed
                                Menu (height,label,icon,labeled)
                                */
                                int a = setMenuAttribute(NAME.c_str(),labelAttrib,label,rootmenu);
                                int b = setMenuAttribute(NAME.c_str(),iconAttrib,icon,rootmenu);
                                if((a==0) && (b==0)){saveChanges();}
                                else{std::cerr<<"There was a problem configuring: "<<NAME<<std::endl;}
                                return;
                            }
                        }
                    }
                    }
                }
            }
        }
    }
}

///Add an item to the menu
int Apps::addMenuItem(Fl_Browser *menuElementText,
                    Fl_Browser *menuElement,
                    Fl_Input *add_label,
                    Fl_Input *add_icon,
                    Fl_Input *add_input,
                    Fl_Check_Button *add_button,
                    std::string whichElement){

    //get the user input
    std::string label;
    const char* my_label = add_label->value();
    if(my_label!=NULL){label=my_label;}
    else{errorJWM("No label");}
    std::string icon;
    const char* this_icon = add_icon->value();
    if(this_icon!=NULL){icon=this_icon;}
    else{errorJWM("No Icon");}
    std::string program;
    const char* a_program = add_input->value();
    if(a_program!=NULL){program=a_program;}
    else{errorJWM("No program");}
    int confirm = add_button->value();

    //prevent typos for attributes by using code completion variable names :D
    const char* labelAttrib = "label";
    const char* iconAttrib = "icon";

    //the hidden menu variable
    std::string whichMENU;
    const char* tempmenu = menuElementText->label();
    if (tempmenu!=NULL){whichMENU=tempmenu;}
    else{errorJWM("No menuElementText");}

    //this will hold the checking variable for finding our desired menu
    std::string attributeValue;

    const char* root ="RootMenu"; //just so I don't have typos

    //find the menu we want using our hidden rootmenu and the attribute onroot
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one in the hidden label
            if (attributeValue.compare(whichMENU)==0){

                if(whichElement.compare("Program")){
                    int c = createMenuItem(whichElement,whichMENU,menuElement,menuElementText,program);
                    // (label,icon) [program]
                    int a = setMenuAttribute(whichElement.c_str(),labelAttrib,label,whichMENU.c_str());
                    int b = setMenuAttribute(whichElement.c_str(),iconAttrib,icon,whichMENU.c_str());
                    if((a==0) && (b==0) && (c==0)){saveChanges();}
                    else{
                        std::cerr<<"There was a problem creating: "<<whichElement<<std::endl;
                        return 1;
                    }
                    return 0;

                }
                else if(whichElement.compare("Include")){return createMenuItem(whichElement,whichMENU,menuElement,menuElementText,program);}
                else{
                    createMenuItem(whichElement,whichMENU,menuElement,menuElementText);
                    if(whichElement.compare("Exit")){
                        //(label,icon,confirm)
                        std::string result;
                        //confirm:
                        // 1 is on
                        // 0 is off
                        if(confirm==0){
                            result = "false";
                        }
                        else{
                            result = "true";
                        }
                        //label
                        int a = setMenuAttribute(whichElement.c_str(),labelAttrib,label,whichMENU.c_str());
                        //icon
                        int b = setMenuAttribute(whichElement.c_str(),iconAttrib,icon,whichMENU.c_str());
                        //confirm
                        int c = setMenuAttribute(whichElement.c_str(),"confirm",result,whichMENU.c_str());
                        //did those work?? save it!
                        if((a==0) && (b==0) && (c==0)){saveChanges();}
                        else{
                            //didn't work... error out
                            std::cerr<<"There was a problem creating: "<<whichElement<<std::endl;
                            return 1;
                        }
                        return 0;
                    }
                    //Separators don't need any configuring
                    else if(whichElement.compare("Separator")){return 0;}
                    else if(whichElement.compare("Menu")){
                        //Menu (height,label,icon,labeled)
                        // we don't add height or labeled yet... I suppose the confirm could double as labeled...
                        std::cerr<<"This feature is not yet fully supported"<<std::endl;
                        //label
                        int a = setMenuAttribute(whichElement.c_str(),labelAttrib,label,whichMENU.c_str());
                        //icon
                        int b = setMenuAttribute(whichElement.c_str(),iconAttrib,icon,whichMENU.c_str());
                        //did those work?? save it!
                        if((a==0) && (b==0)){saveChanges();}
                        else{
                            //didn't work... error out
                            std::cerr<<"There was a problem creating: "<<whichElement<<std::endl;
                            return 1;
                        }
                    return 0;
                    }
                    else{
                    /*
                    This is EVERYTHING ELSE

                    Desktops (label,icon)
                    //Window operations
                    SendTo (label,icon)
                    Stick (label,icon)
                    Maximize (label,icon)
                    Minimize (label,icon)
                    Shade (label,icon)
                    Move (label,icon)
                    Resize (label,icon)
                    Kill (label,icon)
                    Close (label,icon)
                    */
                        //label
                        int a = setMenuAttribute(whichElement.c_str(),labelAttrib,label,whichMENU.c_str());
                        //icon
                        int b = setMenuAttribute(whichElement.c_str(),iconAttrib,icon,whichMENU.c_str());
                        if((a==0) && (b==0)){saveChanges();}
                        else{
                            std::cerr<<"There was a problem creating: "<<whichElement<<std::endl;
                            return 1;
                        }
                        return 0;
                    }

                }
            }
        }
    }
    return 1;
}

///Create a menu item
int Apps::createMenuItem(std::string whichElement, std::string whichMenu, Fl_Browser *menuElement, Fl_Browser *menuElementText){
    const char* root ="RootMenu";
    std::string attributeValue;
    //the new XMLElement we are making (create it as a node first)
    tinyxml2::XMLNode *newItem = doc.NewElement(whichElement.c_str());
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one in the hidden label
            if (attributeValue.compare(whichMenu)==0){
                menu->InsertEndChild(newItem);
                saveChangesTemp();
                saveChanges();
                getMenuItems(menuElement,whichMenu.c_str(),menuElementText);
                return 0;
            }
        }
    }
    return 1;
}
///Create a menu item
int Apps::createMenuItem(std::string whichElement, std::string whichMenu, Fl_Browser *menuElement, Fl_Browser *menuElementText, std::string text){
    const char* root ="RootMenu";
    std::string attributeValue;
    //the new XMLElement we are making (create it as a node first)
    tinyxml2::XMLNode *newItem = doc.NewElement(whichElement.c_str());
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one in the hidden label
            if (attributeValue.compare(whichMenu)==0){
                menu->InsertEndChild(newItem);
                newItem->ToElement()->SetText(text.c_str());
                saveChangesTemp();
                saveChanges();
                getMenuItems(menuElement,whichMenu.c_str(),menuElementText);
                return 0;
            }
        }
    }
    return 1;
}

///Create a menu
int Apps::createMenu(const char* whichMenu, Fl_Browser *menuElement, Fl_Browser *menuElementText){
    const char* root ="RootMenu";
    std::string attributeValue;
    //the new XMLElement we are making (create it as a node first)
    tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM");
    for(menu=menu->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one sent in
            if (attributeValue.compare(whichMenu)==0){
                return 1;
            }
        }
    }
    tinyxml2::XMLNode *newItem = doc.NewElement(root);
    menu->InsertEndChild(newItem);
    newItem->ToElement()->Attribute("onroot",whichMenu);
    saveChanges();
    saveChangesTemp();
    return 0;
}
///Create a menu
int Apps::removeMenu(const char* whichMenu){
    const char* root ="RootMenu";
    std::string attributeValue;
    //the base XMLElement
    tinyxml2::XMLElement *rootElement = doc.FirstChildElement("JWM");
    for(tinyxml2::XMLElement *menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement()){
        if(menu->Attribute("onroot")){
            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");
            //std::cout<<attributeValue<<" "<<rootmenu<<std::endl;
            // see if it matches the one we sent in
            if (attributeValue.compare(whichMenu)==0){
                //remove the menu
                 tinyxml2::XMLNode* node= menu;
                rootElement->DeleteChild(node);
                saveChanges();
                saveChangesTemp();
                //refresh menus
                return 0;
            }
        }
    }
    return 1;
}
///Get all items in a menu
void Apps::getMenuItems(Fl_Browser *elementName, const char* rootmenu, Fl_Browser *elementText){
    const char* root ="RootMenu";
    if(rootmenu==NULL){return;}
    std::string attributeValue;
    if(!testElement(root)){
        errorJWM("No menus found.. this is odd");
        return;
    }
    else{
    tinyxml2::XMLElement * menuElement;
    //Test for:
        //Program (label,icon) [program]
        //Restart (label,icon)
        //Exit (label,icon,confirm)
        //Separator
        /*
        Menu (height,label,icon,labeled)
        Include //this is for included menu files  if it is exec: then the output of exec is used
        Desktops (label,icon)

        //Window operations
        SendTo (label,icon)
        Stick (label,icon)
        Maximize (label,icon)
        Minimize (label,icon)
        Shade (label,icon)
        Move (label,icon)
        Resize (label,icon)
        Kill (label,icon)
        Close (label,icon)
        */
        elementText->clear();
        elementName->clear();
        //Loop through the Root menu elements
        for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement(root)){
            //look for onroot attribute
            if(menu->Attribute("onroot")){
                //if it exists put it in our string to compare
                attributeValue=menu->Attribute("onroot");
                // see if it matches the one given to the function
                if (attributeValue.compare(rootmenu)==0){
                    //Yes it does
                    for(menuElement = menu->FirstChildElement();menuElement;menuElement = menuElement->NextSiblingElement()){
                        //add the Name... we don't need to check for this to exist, as the for loop does this already
                        if(menuElement->Name()){
                            const char* menuName = menuElement->Name();
                            if(menuName!=NULL){elementName->add(menuName);}
                        }
                        //add the text if it exists
                        if(menuElement->GetText()){
                            const char* menuText = menuElement->GetText();
                            if(menuText!=NULL){elementText->add(menuText);}
                        }
                        else if (menuElement->Name()){
                            const char* menuName = menuElement->Name();
                            if(menuName!=NULL){elementText->add(menuName);}
                            else{elementText->add("Nothing");}
                        }
                        else{elementText->add("Nothing");}
                    }
                }
            }
        }
    }
    elementText->redraw();
    elementName->redraw();
}

int Apps::setMenuAttribute(const char* whichElement, const char* attribute, std::string value, const char* rootmenu){
    loadTemp();
    const char* root ="RootMenu";
    std::string nameTester, attributeValue, textTester;
    //make sure element exists first
    //if (!isElement(root,whichElement)){return 1;}
    if(DEBUG_ME){std::cerr<<"is Element"<<std::endl;}
    //point to it
    tinyxml2::XMLElement * menuElement;
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement(root)){

        //look for onroot attribute
        if(menu->Attribute("onroot")){

            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");

            // see if it matches the one given to the function
            if (attributeValue.compare(rootmenu)==0){
                //Yes it does
                std::cout<<attributeValue<<" menu"<<std::endl;
                for(menuElement = menu->FirstChildElement();menuElement;menuElement = menuElement->NextSiblingElement()){
                    nameTester=menuElement->Name();

                    //does this element match the one we want to change???
                    if(nameTester.compare(whichElement)==0){
                        menuElement->SetAttribute(attribute,value.c_str());
                        saveChangesTemp();
                        saveChanges();
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
int Apps::setMenuText(const char* whichElement, const char* text, const char* rootmenu, const char* oldtext){
    loadTemp();
    const char* root ="RootMenu";
    if(DEBUG_ME){std::cerr<<"Set Menu Text:\nElement: "<<whichElement<<" text to set: "<<text<<" root menu: "<<rootmenu<<" look for: "<<oldtext<<std::endl;}
    tinyxml2::XMLElement * menuElement;
    std::string nameTester, textTester;
    //this will hold the attribute value to compare with onroot
    std::string attributeValue;
    //make sure the element exists
    //if (!isElement(root,whichElement)){return 1;}

    //loop through RootMenu elements
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement(root)){

        //look for onroot attribute
        if(menu->Attribute("onroot")){

            //if it exists put it in our string to compare
            attributeValue=menu->Attribute("onroot");

            // see if it is the root menu we are looking for
            if (attributeValue.compare(rootmenu)==0){
                //Yes it does
                if(DEBUG_ME){std::cerr<<attributeValue<<" menu"<<std::endl;}

                //loop through sub elements of RootMenu
                for(menuElement = menu->FirstChildElement();menuElement;menuElement = menuElement->NextSiblingElement()){
                    nameTester=menuElement->Name();

                    //does this element match the one we want to change???
                    if(nameTester.compare(whichElement)==0){
                        if(DEBUG_ME){std::cerr<<nameTester<<" "<<whichElement<<std::endl;}

                        //does it have text?
                        if(NULL !=  menuElement->GetText()){
                            textTester=menuElement->GetText();
                            if(DEBUG_ME){std::cerr<<textTester<<" "<<oldtext<<std::endl;}
                            if(NULL != oldtext){
                                //is it the one we want to change??
                                if(textTester.compare(oldtext)==0){
                                    //change it
                                    menuElement->SetText(text);
                                    saveChangesTemp();
                                    saveChanges();
                                    return 0;
                                }
                            }
                        }//get text
                    }//test compare nameTester & whichElement
                    else{std::cerr<<nameTester<<" "<<whichElement<<std::endl;}

                }//loop through sub elements of RootMenu

            }// if it is the root menu we are looking for

        }//onroot attribute

    }//loop through RootMenu elements
    return 1;
}

/// Get a list of all menus that exist
int Apps::getMenus(Fl_Browser *menuBrowser){
    std::string attributeValue;
    const char* root ="RootMenu";
    for(tinyxml2::XMLElement * menu = doc.FirstChildElement("JWM")->FirstChildElement(root);menu;menu = menu->NextSiblingElement(root)){
        //look for onroot attribute
        if(menu->Attribute("onroot")){
            //if it exists put it in our menuBrowser
            attributeValue=menu->Attribute("onroot");
            menuBrowser->add(attributeValue.c_str());
            menuBrowser->redraw();
        }
    }
    return 0;
}

void Apps::listMenus(Fl_Browser *list_browser){
    list_browser->clear();
    const char* root ="RootMenu";

    std::string tempString,convertString,tempString2,convertString2,attributeValue,test1,test2;
    if(newStyle() == -1){
        for (int i = 0; i<=9;i++){
            convertString = convert(i);
            if(!isRootMenu(convertString)){
                if(DEBUG_ME)std::cout<<"Adding: "<<convertString<<std::endl;
                list_browser->add(convertString.c_str());
            }
        }
    }
    if(newStyle() >=0){
        if(DEBUG_ME)std::cout<<"New Style Menu"<<std::endl;
        for (char i = '0';i<='z';i++){
            convertString=i;
            if((i < ':')||(i > '`')){
                if(!isRootMenu(convertString)){
                    if(DEBUG_ME)std::cout<<"Adding: "<<convertString<<std::endl;
                    list_browser->add(convertString.c_str());
                }
            }
        }
    }
    list_browser->redraw();
}
std::string Apps::getItemAttribute(const char* program, const char* menu, const char* attribute){
    if(program==NULL){return "";}
    if(attribute==NULL){return "";}
    if(menu==NULL){return "";}
    std::string thisRoot;
    std::string mylabel =gettext("None");
    std::string none=mylabel;
    std::string thisMenu = "root:";
    thisMenu += menu;
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so getLabel() will exit after creating one");
        createPanel();
        return none;
    }
    int panel = currentPanel();
    //get the current panel to work on
    const char* result =mylabel.c_str();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement* ButtonElement;
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement("TrayButton");
        panelElement;
        panelElement=panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->Attribute(attribute)){mylabel = panelElement->Attribute(attribute);}

        if(panelElement->FirstChildElement("Button")){
            ButtonElement=panelElement;
            for(ButtonElement=ButtonElement->FirstChildElement("Button");
            ButtonElement;
            ButtonElement=ButtonElement->NextSiblingElement("Button")){
                if(ButtonElement->GetText()){
                    thisRoot=ButtonElement->GetText();
                    //if(DEBUG_ME)
                    std::cout<<"[Button Style] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                    if(thisMenu.compare(thisRoot)==0){
                    //if(DEBUG_ME)
                    std::cout<<"Found: "<<thisRoot<<std::endl;
                    return mylabel;
                    }
                }
            }
        }
        else{
            if(panelElement->GetText()){
                thisRoot=panelElement->GetText();
                //if(DEBUG_ME)
                std::cerr<<"[OLD STYLE] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                    if(thisMenu.compare(thisRoot)==0){
                        //if(DEBUG_ME)
                        std::cerr<<"Found: "<<thisRoot<<std::endl;
                        return mylabel;
                    }
            }
        }
    }
    //if(DEBUG_ME)
    std::cout<<"Didn't find the menu..."<<std::endl;
    return none;
}
std::string Apps::getItemAttribute(std::string menuElement, const char* thismenu, std::string attribute){
    if(menuElement.compare("")==0){return "";}
    if(attribute.compare("")==0){return "";}
    if(thismenu==NULL){return "";}
    std::string none =gettext("None");
    std::string mylabel=none;
    std::string attributeValue=thismenu;
    loadTemp();
    const char* root ="RootMenu";
    const char* result =mylabel.c_str();
     for(tinyxml2::XMLElement * base_menu = doc.FirstChildElement("JWM")->FirstChildElement(root);base_menu;base_menu = base_menu->NextSiblingElement(root)){
        if(base_menu->Attribute("onroot")){
            const char* root = base_menu->Attribute("onroot");
            std::cout<<"looking for: "<<attributeValue<<" found: "<<root<<std::endl;
            if(attributeValue.compare(root)==0){
                for(tinyxml2::XMLElement * menu = base_menu->FirstChildElement();menu;menu = menu->NextSiblingElement()){
                    if(menu->Name()){
                        const char* item = menu->Name();
                        if(item!=NULL){
                            std::string ITEM=item;
                            std::cout<<"looking for: "<<menuElement<<" found: "<<ITEM<<std::endl;
                            if(ITEM.compare(menuElement.c_str())==0){
                                mylabel = menu->Attribute(attribute.c_str());
                                return mylabel;
                            }
                        }
                    }
                }
                return none;
            }
        }
    }
    //if(DEBUG_ME)
    std::cout<<"Didn't find the menu..."<<std::endl;
    return none;
}
void Apps::changeMenuInclude(std::string newInclude, std::string oldInclude, std::string thismenu){
    std::string attributeValue=thismenu;
    newInclude="exec:"+newInclude;
    oldInclude="exec:"+oldInclude;
    const char* root ="RootMenu";
    for(tinyxml2::XMLElement * base_menu = doc.FirstChildElement("JWM")->FirstChildElement(root);base_menu;base_menu = base_menu->NextSiblingElement(root)){
        if(base_menu->Attribute("onroot")){
            const char* root = base_menu->Attribute("onroot");
            std::cout<<"looking for: "<<attributeValue<<" found: "<<root<<std::endl;
            if(attributeValue.compare(root)==0){
                for(tinyxml2::XMLElement * menu = base_menu->FirstChildElement();menu;menu = menu->NextSiblingElement()){
                    if(menu->Name()){
                        const char* item = menu->Name();
                        if(item!=NULL){
                            std::string ITEM=item;
                            std::cout<<"looking for: Include found: "<<ITEM<<std::endl;
                            if(ITEM.compare("Include")==0){
                                if(menu->GetText()){
                                    const char* text=menu->GetText();
                                    if(text!=NULL){
                                        std::cout<<"looking for: "<<oldInclude<<" found: "<<text<<std::endl;
                                        if(oldInclude.compare(text)==0){
                                            std::cout<<"FOUND IT!!!!!!!!!!!!"<<std::endl;
                                            menu->SetText(newInclude.c_str());
                                            saveChangesTemp();
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return;
            }
        }
    }
}
void Apps::getSubmenuItems(std::string menu, Fl_Browser *o){
    std::string attributeValue=menu;
    std::string none=gettext("None");
    const char* root ="RootMenu";
    for(tinyxml2::XMLElement * base_menu = doc.FirstChildElement("JWM")->FirstChildElement(root);base_menu;base_menu = base_menu->NextSiblingElement(root)){
        if(base_menu->Attribute("onroot")){
            const char* root = base_menu->Attribute("onroot");
            std::cout<<"looking for: "<<attributeValue<<" found: "<<root<<std::endl;
            if(attributeValue.compare(root)==0){
                tinyxml2::XMLElement * submenu = base_menu;
                if(submenu->FirstChildElement("Menu")){
                    if(submenu->FirstChildElement("Menu")->FirstChildElement()){
                        for(submenu = submenu->FirstChildElement("Menu")->FirstChildElement();submenu;submenu = submenu->NextSiblingElement("Menu")->NextSiblingElement()){
                            std::string output;
                            if(submenu->Name()){output=submenu->Name();}
                            else{output=none;}
                            output+='\t';
                            if(submenu->GetText()){output+=submenu->GetText();}
                            else{
                                if(submenu->Name()){output+=submenu->Name();}
                                else{output+=none;}
                            }
                            o->add(output.c_str());
                        }
                    }
                }
                return;
            }
        }
    }
}

void Apps::getLabel(Fl_Output* menulabel,const char* menu){
    if(menu==NULL){return;}
//loadTemp();
    std::string thisRoot;
    std::string mylabel =gettext("None");
    std::string none=mylabel;
    std::string thisMenu = "root:";
    thisMenu += menu;
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so getLabel() will exit after creating one");
        createPanel();
        return;
    }
    int panel = currentPanel();
    //get the current panel to work on
    const char* result =mylabel.c_str();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement* ButtonElement;
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement("TrayButton");
        panelElement;
        panelElement=panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->Attribute("label")){mylabel = panelElement->Attribute("label");}

        if(panelElement->FirstChildElement("Button")){
            ButtonElement=panelElement;
            for(ButtonElement=ButtonElement->FirstChildElement("Button");
            ButtonElement;
            ButtonElement=ButtonElement->NextSiblingElement("Button")){
                if(ButtonElement->GetText()){
                    thisRoot=ButtonElement->GetText();
                    //if(DEBUG_ME)
                    std::cout<<"[Button Style] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                    if(thisMenu.compare(thisRoot)==0){
                    //if(DEBUG_ME)
                    std::cout<<"Found: "<<thisRoot<<std::endl;
                    menulabel->value(mylabel.c_str());
                    return;
                    }
                }
            }
        }
        else{
            if(panelElement->GetText()){
                thisRoot=panelElement->GetText();
                //if(DEBUG_ME)
                std::cerr<<"[OLD STYLE] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                    if(thisMenu.compare(thisRoot)==0){
                        //if(DEBUG_ME)
                        std::cerr<<"Found: "<<thisRoot<<std::endl;
                        menulabel->value(mylabel.c_str());
                        return;
                    }
            }
        }
    }
    //if(DEBUG_ME)
    std::cout<<"Didn't find the menu..."<<std::endl;
    menulabel->value(none.c_str());
    return;
}
std::string Apps::getLabel(std::string menu){
    std::string mylabel =gettext("None");
    std::string none=mylabel;
    if(menu.compare("")==0){return mylabel;}
    std::string thisRoot;
    std::string thisMenu = "root:";
    thisMenu += menu;
    loadTemp();
    int i = 1;
    int numOFpanels = numPanels();
    if (numOFpanels == 0 ){
        errorJWM("You do not have any Tray elements, so getLabel() will exit after creating one");
        createPanel();
        return mylabel;
    }
    int panel = currentPanel();
    //get the current panel to work on
    const char* result =mylabel.c_str();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    tinyxml2::XMLElement* ButtonElement;
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    for(panelElement=panelElement->FirstChildElement("TrayButton");
        panelElement;
        panelElement=panelElement->NextSiblingElement("TrayButton")){
        if(panelElement->Attribute("label")){mylabel = panelElement->Attribute("label");}

        if(panelElement->FirstChildElement("Button")){
            ButtonElement=panelElement;
            for(ButtonElement=ButtonElement->FirstChildElement("Button");
            ButtonElement;
            ButtonElement=ButtonElement->NextSiblingElement("Button")){
                if(ButtonElement->GetText()){
                    thisRoot=ButtonElement->GetText();
                    //if(DEBUG_ME)
                    std::cout<<"[Button Style] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                    if(thisMenu.compare(thisRoot)==0){
                        //if(DEBUG_ME)
                        std::cout<<"Found: "<<thisRoot<<std::endl;
                        return mylabel;
                    }
                }
            }
        }
        else{
            if(panelElement->GetText()){
                thisRoot=panelElement->GetText();
                //if(DEBUG_ME)
                std::cerr<<"[OLD STYLE] This root: "<<thisRoot<<" the one we want: "<<thisMenu<<std::endl;
                if(thisMenu.compare(thisRoot)==0){
                    //if(DEBUG_ME)
                    std::cerr<<"Found: "<<thisRoot<<std::endl;
                    return mylabel;
                }
            }
        }
    }
    if(DEBUG_ME){std::cerr<<"Didn't find the menu..."<<std::endl;}
    return none;

}
//++++++++++++++++++++++++++++++++++++++++++++++ END Menu +++++++++++++++++++++++++++++++++++++++++++++++


//##########################################  END APPS ###########################################################
