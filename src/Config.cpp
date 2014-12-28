#include "../include/Config.h"

Config::Config()
{
    file = ".jwmrc";
    JSMfile = ".jsm";
    home = getenv ("HOME");
    std::string homePathNoFiles = homePathNoFile();
    whichPanel = 1;
    path = getenv("PATH");
    stringPATH = path;
    pathPosition = stringPATH.find_first_of(':');
    numPATHS = howmanyPATHS();
    iconExtention = getIconExtention();
}

Config::~Config()
{
    //dtor
}

std::string Config::getIconExtention(){return ".svg";}

void Config::cancel(){
    load();
    saveChangesTemp();
    recoverJSM();
}

//****************************  Member Variables  ***********************************
void Config::setFileName(std::string &fileName){
file = fileName;
}

//################################ END Member Variables ###########################################



//****************************  LOADING / SAVING  ***********************************


void Config::saveChanges(){
    std::cout<<"File saved\n";
    doc.SaveFile(homePath().c_str());
    if(std::system("jwm -restart")!=0){
        std::cout<<"couldn't restart JWM\n";
    }
}
void Config::saveChangesTemp(){
    doc.SaveFile((homePathTemp()).c_str());
    std::cout<<"Temporary File saved\n";
    if(std::system("jwm -p")!=0){
        std::cout<<"Error checking JWM... please run jwm -p again\n";
    }
}

int Config::loadTemp(){
    std::string fileName = homePathTemp();
    doc.LoadFile( fileName.c_str() );
    if (doc.ErrorID() !=0){
        printf("The file %s was not found.  Trying to fix it now\n", fileName.c_str());
        recover();load();saveChangesTemp();
        return doc.ErrorID();
    }
    return 0;
}

int Config::load(){
    std::string fileName = homePath();
    doc.LoadFile( fileName.c_str() );
    if (doc.ErrorID() !=0){
        printf("The file %s was not found.  Recovering now\n", fileName.c_str());
        if(recover()==0)
        {load();saveChanges();}
        else{std::cout<<"An error occured loading "<<file<<std::endl;}
    }
    return 0;
}
//################################################# END LOADING/SAVING ######################################################


/// JSM //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::saveJSM(){
    std::cout<<"File saved\n";
    jsm.SaveFile(jsmPath().c_str());
}

int Config::loadJSM(){
    std::string fileName = jsmPath();
    jsm.LoadFile( fileName.c_str() );
    if (jsm.ErrorID() !=0){
        std::cout<<"An error occured loading "<< fileName<<std::endl;
        if(recoverJSM()==0){return 0;}
    }
    return jsm.ErrorID();
}
int Config::recoverJSM(){
    recoverJSM(1);
    return 0;
}
void Config::recoverJSM(int panel){
    std::string path = jsmPath();
    std::cout<<path<<std::endl;
    std::string clock = "xclock";
    const char* fname = path.c_str();
    std::string p = convert(panel);
    std::ofstream jsmSTREAM(fname, std::ios::out);
    jsmSTREAM<<"<?xml version=\"1.0\"?>\n\
<num>"<<p<<"</num>\n\
<clock>"<<clock<<"</clock>";
}

const char* Config::getAttribute(const char* attribute, unsigned int panel){
    loadTemp();
    unsigned int i = 1;
    std::cout<<panel<<std::endl;
    const char* result ="";
    loadTemp();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        std::cout<<attribute<<std::endl;
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->Attribute(attribute)){result = panelElement->Attribute(attribute);}
    else{
        panelElement->SetAttribute(attribute,0);
        saveChangesTemp();
        result = "0";
    }
    return result;
}
std::string Config::jsmPath(){
    using std::string;
    if (home!=NULL){
        //printf ("The current Home Directory is: %s\n",home); //you can turn this on to debug if you like :)
        string fileName = string(home);
        fileName += "/";
        fileName+=JSMfile;
        //std::cout<<"Here is the Path: "<<fileName<<std::endl;//DEBUG
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 2/n";}
}


//################################################# END JSM ######################################################

///ENVIROMENT VARIABLES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//******************************************* $HOME *******************************************

std::string Config::homePathTemp(){
    using std::string;
    if (home!=NULL){
        string fileName = string(home);
        fileName += ("/"+file+"~");
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 1/n";}
}

std::string Config::homePath(){
    using std::string;
    if (home!=NULL){
        //printf ("The current Home Directory is: %s\n",home); //you can turn this on to debug if you like :)
        string fileName = string(home);
        fileName += ("/"+file);
        //std::cout<<"Here is the Path: "<<fileName<<std::endl;//DEBUG
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 2/n";}
}
std::string Config::homePathNoFile(){
    using std::string;
    if (home!=NULL){
        string fileName = string(home);
        fileName += "/";
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 3/n";}
}

//################################################# END HOME ###################################################################



//*************************************************** $PATH ********************************************************************

// /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
unsigned int Config::howmanyPATHS(){
    unsigned int howmany;
    for(howmany=1;(pathPosition!=std::string::npos);howmany++){
        pathPosition=stringPATH.find(':', pathPosition+1);
    }
    return howmany;
}
const char* Config::thisPATH(int whichPath){
    unsigned int lastPath = 0;
    std::string result;
    if (whichPath >=1){lastPath = whichPath - 1;}
    else {lastPath = 0;}
//std::cout<<"last path: "<<lastPath<<std::endl;
    std::string stringPATH = path;
    std::string::size_type firstPosition = stringPATH.find(':');
    std::string::size_type position = stringPATH.find(':');
    for (int i=1;i<=whichPath;i++){position = stringPATH.find(':',position+1);}
    for (int j=1;j<=lastPath;j++){firstPosition = stringPATH.find(':',firstPosition+1);}
    result = stringPATH.substr (firstPosition+1,((position-firstPosition)-1));
    return result.c_str();
}

//################################################# END PATH ###################################################################
///************************************************ END ENVIROMENT VARIABLES ****************************************************


//************************************************* Recovery *******************************************************************

void Config::setRecoveryText(std::string &ConfigFile){
    recoveryText = ConfigFile;
}
int Config::recover(){
    std::string path = homePathNoFile();
    std::string recoveryCommand = "cp -f /usr/share/jwm-settings-manager/themes/Default/Default " + path + ".jwmrc";
    if(system(recoveryCommand.c_str())!=0){
        std::cout<<recoveryCommand<<" did not go well.../n";
        //fl_message("The Default file could not be found.. check the Console");
    }
    else{
        std::cout<<"jwmrc should be recovered now\n";
        saveChangesTemp();
        if(std::system("jwm -restart")!=0){
            errorJWM("Error restarting JWM\n");
        }
        else{return 0;}
    }
    return 1;
}

int Config::checkFiles(){
    std::string fileName = homePath();
    std::string fileName2 = homePathTemp();
    doc.LoadFile(fileName.c_str() );
    if (doc.ErrorID() !=0){
        errorJWM(file+" was not loaded properly...");
        if (loadTemp()!=0){
            doc.LoadFile(fileName2.c_str() );
            if (doc.ErrorID() !=0){
            errorJWM(file+" was not loaded properly...\n");
            recover();
            return 42;
            }
        }
    }
    return 0;
}

//################################################# END Recovery ###################################################################



/// Utility Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::errorJWM(std::string message){
 errorJWM(message.c_str());
}
void Config::errorJWM(const char* message){
 std::cout<< message << " Please Report this bug\n";
}
std::string Config::convert(int num){
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number;
}
const char* Config::convert(double num){
    std::string number;
    std::stringstream out;
    out << num;
    number = out.str();
    return number.c_str();
}
unsigned int Config::convert(const char* num){
    std::stringstream out;
    out << num;
    unsigned int integer;
    out >> integer;
    return integer;
}
/// Autostart ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Config::addAutostart(const char * program){
    loadTemp();
    bool tester = false;
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *startNode = doc.FirstChildElement( "JWM" )->LastChildElement("StartupCommand");
    for(tinyxml2::XMLElement* testNode=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");
    testNode;testNode=testNode->NextSiblingElement("StartupCommand")){
        tester=true;
    }
    tinyxml2::XMLNode *node = doc.NewElement("StartupCommand");
    if(tester){trayNode->InsertAfterChild(startNode,node);}
    else{trayNode->InsertEndChild(node);}
    tinyxml2::XMLText *startup = doc.NewText(program);
    node->LinkEndChild(startup);
    saveChangesTemp();
}
bool Config::isAutostart(const char* program){
    loadTemp();
    std::string autostart = program;
    std::string trim = program;
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        if(autostart.compare(value) ==0){return true;}
    }
    return false;
}

void Config::removeAutostart(const char * program){
    loadTemp();
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        //std::string pkill ="pkill ";
        ///TODO: test exec to kill process?
        const char* value  = fromDoc.c_str();
        std::string fromProgram = program;
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            std::cout<<"deleted "<<program<<std::endl;
            //testExec(value)
            //if (system(pkill.c_str())!=0){
              //  std::cout<<"Couldn't run "<<pkill<<std::endl;
            //}
        }
    }
    saveChangesTemp();
}


/// Color Functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Config::getColor(std::string color, unsigned int &color2){
    const char* input =color.c_str();
    std::string c1, c2;
	unsigned int flColor;
	std::string::size_type position = color.find(':');
	std::string::size_type validator = color.find('#');
	if(validator==0){
		if (color.length()>7){
			if((color.find(':')!=std::string::npos) && (color.find('#',position+1)!=std::string::npos)){
				c1 = color.substr (1,6);
				c2 = color.substr (9,6);
				c1="0x"+c1+"00";
				c2="0x"+c2+"00";
				//std::cout<< "color c1 = "<<c1<<" color2 = "<<c2<<"\n";
				flColor = strtoul(c1.c_str(),0,16);
				color2 = strtoul(c2.c_str(),0,16);
				//std::cout<<"flColor1 = "<<flColor<<" flColor2 = "<<color2<<"\n";
				return flColor;
			}
			else {
				std::cout<< "not a valid color\n";
				return 42;
			}
		}
		else{
			c1 = color.substr (1,6);
			c1="0x"+c1+"00";
			flColor = strtoul(c1.c_str(),0,16);
			//std::cout<<"color = "<<c1<<"\n";
			//std::cout<<"flColor = "<<flColor<<"\n";
			color2 = 0;
			return flColor;
		}
	}
	else{
        std::string value= xColor(input);
        return getColor(value, color2);
    }
}
std::string Config::colorToString(const double *rgb){
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", int(rgb[0]), int(rgb[1]), int(rgb[2]));
        //return
    //std::cout<<tmp<<"\n tmp\n";
    return tmp;
}


bool Config::testElement(tinyxml2::XMLElement* element){
    loadTemp();
    if(element){return true;}
    return false;
}

std::string Config::xColor(const char *colorName){
/* Paul Sladen, 2014-08-13, Public Domain
 * XLookupColor() -> RGB colour value example, per request on
 * http://irclogs.ubuntu.com/2014/08/13/%23ubuntu-devel.html#t19:52
 * grep MistyRose /usr/share/X11/rgb.txt | awk '{printf("%02x%02x%02x\n",$1,$2,$3);}'
 * http://manpages.ubuntu.com/manpages/man3/XQueryColor.3.html
 * gcc xlookupcolour.c -o xlookupcolour -lX11 && ./xlookupcolour red yellow blue

modified for use in this program by Israel <israel@torios.org>
Thanks Sladen for the quick help!!!!
*/
    Display *dpy;
    Colormap map;
    int scr;
    XColor rgb, nearest_rgb;
    const char *fallback_colours[] = {"red", "white", "blue", "pink", NULL};
    dpy = XOpenDisplay(NULL);
    scr = XDefaultScreen(dpy);
    map = DefaultColormap(dpy, scr);
    XLookupColor(dpy, map, colorName, &rgb, &nearest_rgb);
    //printf("%3d %3d %3d %s\n", rgb.red>>8, rgb.green>>8, rgb.blue>>8, colorName);
    int red = (int)rgb.red>>8;
    int green = (int)rgb.green>>8;
    int blue = (int)rgb.blue>>8;
    //std::cout<< "r= "<<red<<"  g= "<<green<<"  b= "<<blue<<'\n';
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", red, green, blue);
    std::string output = tmp;
    return output;
}


///  MULTIPLE PANELS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Config::getLabelMenu(int menu){
    loadTemp();
    if (!isMenu(menu)){return "";}
    const char* TEXT = "";
    const char * label = "";
    std::string labelString , labeled;
    labelString = "";
    std::string root ="root:";
    root +=convert(menu);
   // std::cout<<root<<std::endl;
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
    if(panelElement->FirstChildElement( "TrayButton" )){
        panelElement=panelElement->FirstChildElement( "TrayButton" );
        labeled = panelElement->GetText();
        if (labeled.compare(root)!=0){
            while(panelElement->NextSiblingElement( "TrayButton" ) && labeled.compare(root)!=0){
                if(panelElement->GetText()){
                    labeled = panelElement->GetText();
                }
            }
        }
        label = panelElement->Attribute("label");
        labelString = label;
    }
    //std::cout<<labelString<<"\n";
    return labelString;
}
 std::string Config::getImageMenu(int menu){
    loadTemp();
    int i = 1;
    if (!isMenu(menu)){return "";}
    std::string root ="root:";
    std::string labeled;
    root +=convert(menu);
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->FirstChildElement( "TrayButton" )){
        panelElement=panelElement->FirstChildElement( "TrayButton" );
        labeled = panelElement->GetText();
        if (labeled.compare(root)!=0){
            while(panelElement->NextSiblingElement( "TrayButton" ) && labeled.compare(root)!=0){
                if(panelElement->GetText()){
                    labeled = panelElement->GetText();
                }
            }
        }
        if (panelElement->Attribute("icon")){
            std::string icon = panelElement->Attribute("icon");
            return icon;
        }
    }
 }

 void Config::setImageMenu(const char* icon, int menu){
    loadTemp();
    int i = 1;
    std::string root ="root:";
    std::string labeled;
    root +=convert(menu);
    int panel = currentPanel();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if(panelElement->FirstChildElement( "TrayButton" )){
        panelElement=panelElement->FirstChildElement( "TrayButton" );
        labeled = panelElement->GetText();
        if (labeled.compare(root)!=0){
            while(panelElement->NextSiblingElement( "TrayButton" ) && labeled.compare(root)!=0){
                if(panelElement->GetText()){
                    labeled = panelElement->GetText();
                }
            }
        }
        if (panelElement->Attribute("icon")){
            panelElement->SetAttribute("icon",icon);
        }
        else std::cout << "no image set";
    }
    saveChangesTemp();
}

void Config::labelMenu(const char * icon, int num,const char* label){
    loadTemp();
    int i = 1;
    int panel = currentPanel();
    std::string compNum;
    std::string number = "root:";
    number+=convert(num);
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        while(panelElement->NextSiblingElement("Tray") && i!=panel){
            panelElement=panelElement->NextSiblingElement("Tray");
            i++;
        }
    }
    if (isMenu(num)){
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){
            compNum = panelElement->GetText();
            if(compNum.compare(number)==0){
                panelElement->SetAttribute("label",label);
                saveChangesTemp();
                return;
            }
        }
    }
    addMenu(num, label, icon);
}
///Parse the document and count how many "Tray" elements there are.  return this number
bool Config::isMenu(int rootNumber){
    loadTemp();
    std::string root = "root:";
    root += convert(rootNumber);
    const char* num = root.c_str();
    std::string compNum;
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
    if(panelElement->FirstChildElement( "TrayButton" )){
        for(panelElement = panelElement->FirstChildElement( "TrayButton" );
            panelElement;
            panelElement = panelElement->NextSiblingElement("TrayButton" )){
            compNum = panelElement->GetText();
            if(compNum.compare(num)==0){return true;}
        }
    }
return false;
}
void Config::addMenu(int rootnumber, const char* label, const char* icon){
    loadTemp();
    std::string r = "root:";
    std::string stringICON = icon;
    stringICON += iconExtention;
    r += convert(rootnumber);
    const char* root = r.c_str();
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
    tinyxml2::XMLNode *node = doc.NewElement("TrayButton");
    panelElement->InsertEndChild(node);
    tinyxml2::XMLText *places = doc.NewText(root);
    node->LinkEndChild(places);
    panelElement = panelElement->LastChildElement( "TrayButton" );
    panelElement->SetAttribute("label",label);
    panelElement->SetAttribute("border","false");
    panelElement->SetAttribute("icon",stringICON.c_str());
    saveChangesTemp();
}
void Config::deleteMenu(int menu){
    std::string menuString = "root:" + convert(menu);
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
    tinyxml2::XMLElement* node = panelElement;
    for(node=node->FirstChildElement( "TrayButton" );node;node=node->NextSiblingElement("TrayButton")){
        std::string root = node->GetText();
        if(root.compare(menuString)==0){
            panelElement->DeleteChild(node);
            saveChangesTemp();
        }
    }
}
//simply check if there are multiple panels
bool Config::multipanel(){
    bool test = false;
    int loader = load();
    int counter2 = 0;
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    for(node;node;node=node->NextSiblingElement("Tray")){counter2++;}
    if (counter2>1){test = true;}
    return test;
}
int Config::numPanels(){
    int loader = load();
    int counter2 = 0;
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    for(node;node;node=node->NextSiblingElement("Tray")){counter2++;}
    //std::cout<<counter2<<std::endl;
    //if the multipanel function fails there should only be 1 panel and return 0 so the numPanels (below) that calls this wont make a new entry for it.
    return counter2;
}

int Config::currentPanel(){
    loadJSM();
    int value =1;
    tinyxml2::XMLElement* num = jsm.FirstChildElement("num");
    bool exists = testElement(num);
    if (exists){
        const char* number = num->GetText();
        value = convert(number);
    }
    else{
    recoverJSM(1);
    }
    return value;
}
void Config::changePanel(int panel){
    std::string p = convert(panel);
    loadJSM();
    tinyxml2::XMLElement* num = jsm.FirstChildElement("num");
    num->SetText(p.c_str());

}
const char* Config::checkLayout(){
    int layout = currentPanel();
    return checkLayout(layout);
}

const char* Config::checkLayout(unsigned int panel){
    loadTemp();
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    int i=1;
    if(test && panel != i ){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            i++;
        }
    }
    else{
        tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    }
    const char* layout = tray->Attribute("layout");
    return layout;
}

const char* Config::getCurrentPanelLayout(){
    loadJSM();
    tinyxml2::XMLElement* layout = jsm.FirstChildElement("layout");
    const char* thisLayout = layout->GetText();
    return thisLayout;
}
const char* Config::getJSMelement(const char* element){
    loadJSM();
    tinyxml2::XMLElement* node = jsm.FirstChildElement(element);
    const char* result = node->GetText();
    return result;
}
const char* Config::getCurrentHalign(){
    loadJSM();
    tinyxml2::XMLElement* halign = jsm.FirstChildElement("halign");
    const char* thisHalign = halign->GetText();
    return thisHalign;
}
const char* Config::getCurrentValign(){
    loadJSM();
    tinyxml2::XMLElement* valign = jsm.FirstChildElement("valign");
    const char* thisValign = valign->GetText();
    return thisValign;
}
const char* Config::getPanelLayout(){
    int layout = currentPanel();
    return getPanelLayout(layout);
}
const char* Config::getPanelLayout(unsigned int panel){
    loadTemp();
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    std::string layout;
    unsigned int i=1;
    std::cout<<"panel: "<<panel<<std::endl;
    if(panel != i && test){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            ++i;
        }
    }
    std::cout<<(tray->Attribute("layout"));
    layout = "";//tray->Attribute("layout");
    //if horizontal check valign
    //should be left or right
    if(layout.compare("horizontal")==0){
        const char* valign = tray->Attribute("valign");
        //std::cout<<valign<<std::endl;
        return valign;
    }
    //if vertical check halign
    //should be top or bottom
    else if(layout.compare("vertical")==0){
        const char* halign = tray->Attribute("halign");
        //std::cout<<halign<<std::endl;
        return halign;
    }
    const char* error = "This shouldn't happen";
    std::cout<<error<<std::endl;
    return error;
}
const char* Config::Panel_Info(Fl_Output *o){
    /*const char* temp = o2->label();
    valign = temp;*/
    return o->label();
}

//########################################### END MULTIPLE PANELS ###########################################

///  EXECUTABLES AND PATHS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Config::testExec(const char* exec){
    struct stat sb;
    std::string stringEXEC = exec;
 // /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
    std:: string testPATH, testExec;
    for (int i = 1; i <= numPATHS; i++){
		stringEXEC = exec;
		//std::cout<<"exec: "<<exec<<std::endl;
        testPATH = thisPATH(i);
        stringEXEC = testPATH + "/" + stringEXEC;
        testExec = stringEXEC.c_str();
        if (stat(testExec.c_str(), &sb) == 0){
            //std::cout<<"###########################################\nFound "<<exec<<"\n###########################################\n";
            return true;
        }
            //else{std::cout<<"Couldn't find "<<exec<<"\n";}
    }
    return false;
}
bool Config::testFile(const char* fileWithFullPATH){
    struct stat sb;
    if (stat(fileWithFullPATH, &sb) == 0){
        // std::cout<<"Found "<<exec<<"\n";
        return true;
    }
    std::cout<<"Couldn't find "<<fileWithFullPATH<<"\n";
    return false;
}

//########################################### END EXECUTABLES AND PATHS ###########################################

///  BASH-LIKE  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* Config::grep(const char* args, const char* filename){
    std::string line;
    std::string length = args;
    int len = length.length();
    std::string sub;
    std::ifstream ifs (filename, std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            sub=line.substr(0,len);
            if(sub == args){
               // std::cout<<args<<" "<<sub<<std::endl;
                return line.c_str();
            }
        }
    }
}
///Array for grep
std::vector<std::string> Config::egrep(const char* args, const char* filename){
    std::vector<std::string> result;
    std::string line;
    std::string length = args;
    int len = length.length();
    int i = 0; //iterator
    std::string sub;
    std::ifstream ifs (filename, std::ifstream::in);
    if(ifs.is_open()){
        while (getline(ifs,line)){
            i++;
            sub=line.substr(0,len);
            if(sub == args){
               // std::cout<<args<<" "<<sub<<std::endl;
                result[i]=line;
            }
        }
    }
    return result;
}
//########################################### END BASH-LIKE ###########################################
///MULTIUSE///////////////////////////////////////////////////////////////////////////
void Config::setAttribute(const char* whichElement, const char* attribute, const char* value){
    loadTemp();
    if (!isElement(whichElement)){createElement(whichElement);}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    element->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text){
    loadTemp();
    if (!isElement(whichElement)){createElement(whichElement);}
    tinyxml2::XMLElement* base = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    base->InsertAfterChild(node,node);
    tinyxml2::XMLText *action = doc.NewText(text);
    node->LinkEndChild(action);
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement(whichElement);
    element->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, double value){
    loadTemp();
    const char* result = convert(value);
    setAttribute(whichElement,attribute,result);
}
void Config::createElement(const char* whichElement){
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    element->InsertEndChild(node);
    saveChangesTemp();
}

bool Config::isElement(const char* whichElement){
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if ((element)->FirstChildElement(whichElement)){return true;}
    return false;
}
int Config::getIntAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    const char* result = getElementAttribute(whichElement, attribute);
    int value = strtoul(result,0,10);
    return value;
}

const char* Config::getElementAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    if (!isElement(whichElement)){return "0";}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    return element->Attribute(attribute);
}
