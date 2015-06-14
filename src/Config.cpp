#include "../include/Config.h"

Config::Config()
{
    file = ".jwmrc";
    JSMfile = ".jsm";
    home = getenv ("HOME");
    homePathNoFiles = homePathNoFile();
    whichPanel = 1;
    path = getenv("PATH");
    stringPATH = path;
    pathPosition = stringPATH.find_first_of(':');
    numPATHS = howmanyPATHS();
    configEnvHOME = "$HOME/.config/";
    homeConfig = home;
    homeConfig+="/.config/";
    torimenu = "torimenu";
    placesmenu = "placesmenu";
    gnomemenu = "gnomeapps";
    sysmenu = "gnomesystem";
    isNewStyle = newStyle();
    defaultFilePath = "/usr/share/jwm-settings-manager/themes/Default/Default";
    defaultOLDFilePath ="/usr/share/jwm-settings-manager/themes/old/Default/Default";
}

Config::~Config()
{
    //dtor
}

//End construction/destruction

///****************************   ***********************************
void Config::setFileName(std::string &fileName){
file = fileName;
}
void Config::under_mouse(Fl_Window *o){
  int screenHeight = Fl::h()/2;
  int screenWidth = Fl::w()/2;
  int window_w = o->decorated_w ();
  int window_h = o->decorated_h();
  window_h = window_h/2;
  window_w = window_w/2;
  o->position((screenWidth-window_w),(screenHeight-window_h));
}
//End Member Variables

bool Config::newVersionJWM(){
    const char* jwmVersion = "jwm -v | grep JWM |sed 's/ by.*//' |sed 's/JWM v//'";
	std::string version = returnTerminalOutput(jwmVersion,"r");
	std::string newTagVersion = "2.3.0";
    if(version.compare(newTagVersion)==0){return true;}
    int newTagVersionMajor = 2, newTagVersionMinor = 3;
    int dot1 = version.find_first_of('.');
    int dot2 = version.find_last_of('.');
    std::string major = version.substr(0,dot1);
    std::string minor = version.substr(dot1+1,dot2);
    int majorVersion = convert(major.c_str());
    int minorVersion = convert(minor.c_str());
    if (majorVersion > newTagVersionMajor){return true;}
    if ((majorVersion == newTagVersionMajor)&&(minorVersion >= newTagVersionMinor)){return true;}
    return false;
}
bool Config::newStyle(){
    const char* tray = "TrayButtonStyle";
    const char* task = "TaskListStyle";
    const char* pager = "PagerStyle";
    const char* win = "WindowStyle";
    const char* menu = "MenuStyle";
    std::vector<std::string> styles;
    styles.push_back(menu);//0
    styles.push_back(win);//1
    styles.push_back(pager);//2
    styles.push_back(task);//3
    styles.push_back(tray);//4
    int lengthofStyle = 4;//# of entries above
    int i =0;
    loadTemp();
    //check current if JWM version is >=2.3.0
    bool newVersion = newVersionJWM();

    bool active = false;
    bool inActive =false;
    for (bool testActive =isElement(styles[0].c_str(),"Active"); i<=lengthofStyle;i++){
        testActive=isElement(styles[i].c_str(),"Active");
        if(testActive){active=true;}
        //std::cerr<<"Active"<<styles[i]<<" is "<<testActive<<std::endl;
    }
    i =0;
    for (bool testInactive =isElement(styles[0].c_str(),"Inactive"); i<=lengthofStyle;i++){
        testInactive=isElement(styles[i].c_str(),"Inactive");
        if(testInactive){inActive=true;}
        //std::cerr<<styles[i]<<" is "<<testInactive<<std::endl;
    }
    if(active && !inActive){
        if(!newVersion){
            //do something to let the user know || fix it...
            recover();
        }
        //std::cerr<<"New Version Support"<<std::endl;
        return true;
    }
    //std::cerr<<"OLD Version Support"<<std::endl;
    return false;
}
///++++++++++++++++++++++++++++++++++++++++++++++++++++++ Recovery ++++++++++++++++++++++++++++++++++++++++++++++++++++

void Config::setRecoveryText(std::string &ConfigFile){
    recoveryText = ConfigFile;
}
int Config::recover(){
    //TODO: rework to use ifstream
    std::string pathToJWMRC = homePath();
    std::string tempFile= homePathTemp();
    std::string recoveryCommand = "cp -f ";
    recoveryCommand+=defaultFilePath;
    if (!newVersionJWM()){
        recoveryCommand = "cp -f ";
        recoveryCommand += defaultOLDFilePath;
    }
    recoveryCommand += " ";
    recoveryCommand += pathToJWMRC;
    if(system(recoveryCommand.c_str())!=0){
        std::cerr<<recoveryCommand<<" did not go well..."<<std::endl;
        std::string errorMSG = "Running: ";
        errorMSG += recoveryCommand;
        errorMSG += "failed, The Default file could not be found. Please reinstall.";
        errorJWM(errorMSG);
    }
    else{
        std::cout<<"jwmrc should be recovered now"<<std::endl;
        load();
        saveChangesTemp();
        if(std::system("jwm -restart")!=0){
            errorJWM("Error restarting JWM");
        }
        else{return 0;}
    }
    return 1;
}

int Config::checkFiles(){
    std::string fileName = homePath();
    std::string fileName2 = homePathTemp();
    if(!testFile(fileName2.c_str())){
        if(testFile(fileName.c_str())){
            load();
            saveChangesTemp();
            return 0;
        }
        recover();
        return 12;
    }
    doc.LoadFile(fileName.c_str() );
    if (doc.ErrorID() !=0){
        errorJWM(file+" was not loaded properly...");
        if (loadTemp()!=0){
            doc.LoadFile(fileName2.c_str() );
            if (doc.ErrorID() !=0){
                errorJWM(file+" was not loaded properly...");
                recover();
                return 42;
            }
        }
    }
    return 0;
}

//End Recovery


///****************************  LOADING / SAVING  ***********************************
void Config::saveJWMRC(Fl_Double_Window *o){
    saveJWMRC();
    o->hide();
    //UI ux;
    //ux.showSettings();
}

void Config::saveJWMRC(){
    doc.LoadFile((homePathTemp()).c_str() );
    if (doc.ErrorID() !=0){
        std::cerr<<"The file"<< (homePathTemp().c_str())<<"was not found.  Trying to fix it now"<<std::endl;
        recover();
    }
    doc.SaveFile(homePath().c_str());
    doc.SaveFile((homePathTemp()).c_str());
    if(std::system("jwm -restart")!=0){
        std::cerr<<"Error checking JWM... please fix errors in ~/.jwmrc"<<std::endl;;
    }
}
void Config::saveChanges(){
    std::cout<<"File saved\n";
    doc.SaveFile(homePath().c_str());
    if(std::system("jwm -restart")!=0){
        std::cerr<<"couldn't restart JWM"<<std::endl;
    }
}
void Config::saveChangesTemp(){
    doc.SaveFile((homePathTemp()).c_str());
    //std::cout<<"Temporary File saved\n";
    if(std::system("jwm -p")!=0){
        std::cerr<<"Error checking JWM... please run jwm -p again"<<std::endl;
    }
}

int Config::loadTemp(){
    std::string fileName = homePathTemp();
    doc.LoadFile( fileName.c_str() );
    if (doc.ErrorID() !=0){
        std::cerr<<"The file: "<< (fileName.c_str())<<" was not found.  Trying to fix it now"<<std::endl;
        recover();load();saveChangesTemp();
        return doc.ErrorID();
    }
    return 0;
}

int Config::load(){
    std::string fileName = homePath();
    doc.LoadFile( fileName.c_str() );
    if (doc.ErrorID() !=0){
        std::cerr<<"The file: "<< (fileName.c_str())<<" was not found.  Trying to fix it now"<<std::endl;
        if(recover()==0)
        {load();saveChanges();}
        else{std::cerr<<"An error occured loading "<<file<<std::endl;}
    }
    return 0;
}
///This function cancels any temporary changes to the jwmrc file.
void Config::cancel(){
    load();
    saveChangesTemp();
    recoverJSM();
}
///This one also hides the window and shows the settings window
void Config::cancel(Fl_Double_Window *o){
    cancel();
    o->hide();
    //SettingsUI uiSettings;
    //uiSettings.make_window()->show();
}
//End LOADING/SAVING


/// JSM <></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></><></>
void Config::saveJSM(){
    //std::cout<<"File saved\n";
    jsm.SaveFile(jsmPath().c_str());
}

int Config::loadJSM(){
    std::string fileName = jsmPath();
    jsm.LoadFile( fileName.c_str() );
    if (jsm.ErrorID() !=0){
        std::cerr<<"An error occured loading: "<< fileName<<std::endl;
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
    //std::cout<<path<<std::endl;
    std::string clock;
    if( newStyle()){clock = "root:c";}
    else{clock = "xclock";}
    int places = 7;
    int root = 5;
    int gsys = 8;
    const char* fname = path.c_str();
    std::string p = convert(panel);
    std::ofstream jsmSTREAM(fname, std::ios::out);
    jsmSTREAM<<"<?xml version=\"1.0\"?>\n\
<num>"<<p<<"</num>\n\
<clock>"<<clock<<"</clock>\n\
<places root=\""<<places<<"\">"<<configEnvHOME<<placesmenu<<"</places>\n\
<apps root=\""<<root<<"\">"<<configEnvHOME<<torimenu<<"</apps>\n\
<gnapps root=\""<<root<<"\">"<<configEnvHOME<<sysmenu<<"</gnapps>\n\
<gnsys root=\""<<gsys<<"\">"<<configEnvHOME<<gnomemenu<<"</gnsys>\n\
<ext>"<<"svg"<<"</ext>";
}

const char* Config::getJSMelement(const char* element){
    loadJSM();
    tinyxml2::XMLElement* node = jsm.FirstChildElement(element);
    const char* result = node->GetText();
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
	else{errorJWM("ERROR not valid path"); return "HomePath Error 2\n";}
}


//End JSM <></><></><></><></><></><></><></>




///ENVIROMENT VARIABLES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// $HOME ~/~/~/~/

std::string Config::homePathTemp(){
//this returns $HOME/.jwmrc~
    using std::string;
    if (home!=NULL){
        string fileName = string(home);
        fileName += ("/"+file+"~");
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 1\n";}
}

std::string Config::homePath(){
//this returns $HOME/.jwmrc
    using std::string;
    if (home!=NULL){
        //printf ("The current Home Directory is: %s\n",home); //you can turn this on to debug if you like :)
        string fileName = string(home);
        fileName += ("/"+file);
        //std::cout<<"Here is the Path: "<<fileName<<std::endl;//DEBUG
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 2\n";}
}
std::string Config::homePathNoFile(){
//this returns $HOME/
    using std::string;
    if (home!=NULL){
        string fileName = string(home);
        fileName += "/";
        return fileName;
	}
	else{errorJWM("ERROR not valid path"); return "HomePath Error 3\n";}
}

//End $HOME ~/~/~/


                    /// $PATH /:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:

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
    for (unsigned int j=1;j<=lastPath;j++){firstPosition = stringPATH.find(':',firstPosition+1);}
    result = stringPATH.substr (firstPosition+1,((position-firstPosition)-1));
    return result.c_str();
}

//End $PATH /:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:/:

//End ENVIROMENT VARIABLES


/// Utility Functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::errorJWM(std::string message){
 errorJWM(message.c_str());
}
void Config::errorJWM(const char* message){
    ///TODO: make this an flmessage that shows up also...
    //fl_message(message);
 std::cerr<< message << "\n Please Report this bug"<<std::endl;
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
std::string Config::fixName(const char* filename){
    //std::cout<<"fixName:\n";
    std::string Filename = filename;
    std::string escape = "\\ ";
    size_t start_pos = 0;
    while((start_pos = Filename.find(' ', start_pos)) != std::string::npos) {
        Filename.replace(start_pos, 1, escape);
        start_pos += escape.length(); // Handles case where 'to' is a substring of 'from'
        //std::cout<<Filename<<std::endl;
    }
    return Filename;
}

//End Utility




/// Autostart ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Config::addAutostart(std::string program){
    loadTemp();
    ///Check to see if it is already there...
    if(isAutostart(program)){return;}
    bool tester = false;
    //base XML element
    tinyxml2::XMLNode *trayNode = doc.FirstChildElement( "JWM" );

    //Base startup Node
    //does it even exist???
    tinyxml2::XMLNode *startNode = doc.FirstChildElement( "JWM" );
    if(isElement("StartupCommand")){
        startNode = startNode->LastChildElement("StartupCommand");
        //Are there some nodes?
        for(tinyxml2::XMLElement* testNode=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");
        testNode;
        testNode=testNode->NextSiblingElement("StartupCommand")){

                tester=true;
        }
    }
    tinyxml2::XMLNode *node = doc.NewElement("StartupCommand");
    //if startup nodes exist add after them
    if(tester){trayNode->InsertAfterChild(startNode,node);}
    //otherwise just add at the end
    else{trayNode->InsertEndChild(node);}
    //add the text to our new node
    tinyxml2::XMLText *startup = doc.NewText(program.c_str());
    node->LinkEndChild(startup);

    ///These are used to check for running instances
    //use the pidof command to check if the program is running
    std::string PID = "pidof ";
    int sys = 0;
    ///Check if the program is running.  If not start it!
    PID += program;
    std::cout<<PID<<std::endl;
    std::string pidOF = returnTerminalOutput(PID,"r");
        if(pidOF.compare("")==0){
            std::cout<<program<<" is not running"<<std::endl;
            sys= run(program.c_str());
            if (sys !=0){
                std::string errorMSG = "system call for ";
                errorMSG +=program;
                errorMSG +=" did not return 0";
                errorJWM(errorMSG);
            }
        }
        std::cout<<"added autostart"<<std::endl;
    saveChangesTemp();
}
bool Config::isAutostart(std::string program){
    loadTemp();
    std::string autostart = program;
    std::string trim = program;
    if(!isElement("StartupCommand")){return false;}
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        if(autostart.compare(value) ==0){return true;}
    }
    return false;
}

void Config::removeAutostart(std::string program){
    loadTemp();
    if(!isElement("StartupCommand")){return;}
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        //std::string pkill ="pkill ";
        ///TODO: test exec to kill process?
        const char* value  = fromDoc.c_str();
        std::string fromProgram = program;
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            //std::cout<<"deleted "<<program<<std::endl;
            //testExec(value)
            //if (system(pkill.c_str())!=0){
              //  std::cout<<"Couldn't run "<<pkill<<std::endl;
            //}
        }
    }
    saveChangesTemp();
}
//End Autostart

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
				std::cerr<< "not a valid color"<<std::endl;
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
bool Config::testElement(const char* whichElement){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (!element->FirstChildElement( whichElement )){return false;}
    else{return true;}
    return false;

}
bool Config::testElement(const char* whichElement, const char* whichSubElement){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (!element->FirstChildElement( whichElement )){return false;}
    else{
        if (!element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )){return false;}
        else{return true;}
    }
    return false;
}
bool Config::testElement(const char* whichElement,const char* whichSubElement, const char* whichSUBsubElement){
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (!element->FirstChildElement( whichElement )){return false;}
    else{
        if (!element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )){return false;}
        else{
            if (!element->FirstChildElement( whichElement )->FirstChildElement( whichSubElement )->FirstChildElement( whichSUBsubElement ) ){return false;}
            else{return true;}
        }
    }
    //probably it should never get here.... but return false by default anyhow.
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
//    const char *fallback_colours[] = {"red", "white", "blue", "pink", NULL};
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
std::string Config::returnXColor(unsigned int color){
    #if 0
    Display *dpy;
    Colormap map;
    int scr;
    XColor rgb, nearest_rgb;
    int red = (int)rgb.red>>8;
    int green = (int)rgb.green>>8;
    int blue = (int)rgb.blue>>8;
    const char* colorName;
//    const char *fallback_colours[] = {"red", "white", "blue", "pink", NULL};
    dpy = XOpenDisplay(NULL);
    scr = XDefaultScreen(dpy);
    map = DefaultColormap(dpy, scr);
    XLookupColor(dpy, map, &colorName, rgb, &nearest_rgb);
    //printf("%3d %3d %3d %s\n", rgb.red>>8, rgb.green>>8, rgb.blue>>8, colorName);
    //std::cout<< "r= "<<red<<"  g= "<<green<<"  b= "<<blue<<'\n';
    char tmp[8];
    std::snprintf(tmp, sizeof(tmp), "#%02x%02x%02x", red, green, blue);
    #endif // 0
    color++;
    std::string output = "tmp";
    return output;
}
//End Color



///MENU ///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
std::string Config::getLabelMenu(int menu){
    loadTemp();
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "";
    }
    if (!isMenu(menu)){return "";}
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

    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return "";
    }
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
    return "";
 }

 void Config::setImageMenu(const char* icon, int menu){
    loadTemp();
    int i = 1;
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}

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
        else errorJWM("no Menu image set");
    }
    saveChangesTemp();
}

void Config::labelMenu(const char * icon, int num,const char* label){
    loadTemp();
    int i = 1;
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){createPanel();}

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



bool Config::isMenu(const char* whichStyle){  ///   <----------------------  isMenu called from flPanel::switchMenu
    std::string style = whichStyle;
    loadTemp();
    if (style.compare(gnomemenu)==0){
        bool gnome =  isMenu(configEnvHOME+gnomemenu);
        if (!gnome){return isMenu(homeConfig+gnomemenu);}
        else return true;
    }
    else if (style.compare(torimenu)==0){
        bool tori = isMenu(configEnvHOME+torimenu);
        if (!tori){return isMenu(homeConfig+torimenu);}
        else return true;
    }
    else if (style.compare(sysmenu)==0){
        bool sys = isMenu(configEnvHOME+sysmenu);
        if (!sys){sys= isMenu(homeConfig+sysmenu);}
        else return true;
    }
    return false;
}

///          isMenu

bool Config::isMenu(std::string includeLine){  // called below
    return isElementText("Include",includeLine);
}

bool Config::isMenu(int rootNumber){
    loadTemp();
    //make sure we have a Tray element first
    int numOFpanels = numPanels();
    if (numOFpanels == -1 ){
        createPanel();
        return false;
    }

    std::string root = "root:";
    root += convert(rootNumber);
    const char* num = root.c_str();
    std::string compNum;
    int i = 1;
    bool tori = isMenu(configEnvHOME+torimenu);
    if (!tori){tori = isMenu(homeConfig+torimenu);}
    bool sys = isMenu(configEnvHOME+sysmenu);
    if (!sys){sys= isMenu(homeConfig+sysmenu);}
    bool gnome =  isMenu(configEnvHOME+gnomemenu);
    if (!gnome){gnome =  isMenu(homeConfig+gnomemenu);}
    bool place = isMenu(configEnvHOME+placesmenu);
    if (!place){place = isMenu(homeConfig+placesmenu);}
    bool usingGNOME = false;
    if (gnome && sys){usingGNOME = true;}
    ///Is the menu included??
    if (rootNumber == 5 && !usingGNOME && !tori){return false;}
    if (rootNumber == 7 && !place){return false;}

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
    stringICON += getExtention();
    r += convert(rootnumber);
    const char* root = r.c_str();
    int i = 1;

    //make sure we have a Tray element first
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

    //check to see if the tray exists
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
    tinyxml2::XMLElement* node = panelElement;
    for(node=node->FirstChildElement( "TrayButton" );node;node=node->NextSiblingElement("TrayButton")){
        std::string root = node->GetText();
        if(root.compare(menuString)==0){
            panelElement->DeleteChild(node);
            saveChangesTemp();
        }
    }
}
//End Menus



///  MULTIPLE PANELS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Config::createPanel(){
    //make a node(needed for InsertEndChild) version of our Sibling Tray
    tinyxml2::XMLNode *tray = doc.FirstChildElement("JWM");
    //create the new Tray we want to add
    tinyxml2::XMLNode *newTray = doc.NewElement("Tray");
    //add the new tray
    tray->InsertEndChild(newTray);

    //save it so we can modify it more
    saveChangesTemp();
    saveChanges();

    //make a spacer so there is at least something there
    tinyxml2::XMLNode *spacer = doc.NewElement("Spacer");
    newTray->InsertEndChild(spacer);

    //turn the newTray node back into an element so we can modify the attributes
    tinyxml2::XMLElement *thisone = newTray->ToElement();

    //basic default panel setup
    thisone->SetAttribute("layout","horizontal");
    thisone->SetAttribute("valign","top");
    thisone->SetAttribute("halign","fixed");
    thisone->SetAttribute("height","34");
    thisone->SetAttribute("width","0");
    thisone->SetAttribute("x","0");
    thisone->SetAttribute("y","-1");

    //save it fully
    saveChanges();
    saveChangesTemp();
    //update the .jsm file
    updatePanels(1);
}



const char* Config::getAttribute(const char* attribute, unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "";
    }
    unsigned int i = 1;
    //std::cout<<panel<<std::endl;
    const char* result ="";
    loadTemp();
    tinyxml2::XMLElement* panelElement = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Tray" );
    if (panel != i){
        //std::cout<<attribute<<std::endl;
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

//simply check if there are multiple panels
bool Config::multipanel(){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return false;
    }
    bool test = false;
    load();
    int counter2 = 0;
    tinyxml2::XMLElement* node;
    for(node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");node;node=node->NextSiblingElement("Tray")){counter2++;}
    if (counter2>1){test = true;}
    return test;
}
int Config::numPanels(){
    loadTemp();
    int counter2 = 0;
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    if(!node->FirstChildElement("Tray")){return -1;}
    for(node=node->FirstChildElement("Tray");node;node=node->NextSiblingElement("Tray")){counter2++;}
    //std::cout<<"Found "<<counter2<< " panel(s)"<<std::endl;
    return counter2;
}
void Config::changePanel(int panel){
    std::string p = convert(panel);
    loadJSM();
    tinyxml2::XMLElement* num = jsm.FirstChildElement("num");
    num->SetText(p.c_str());
    saveJSM();

}

                            ///->->->->->->->->->->->->->->->->->-> current
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


                            ///->->->->->->->->->->->->->->->->->-> layout
const char* Config::checkLayout(){
    int layout = currentPanel();
    return checkLayout(layout);
}

const char* Config::checkLayout(unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        return "horizontal";
    }
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    unsigned int i=1;
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

const char* Config::getPanelLayout(){
    int layout = currentPanel();
    return getPanelLayout(layout);
}
const char* Config::getPanelLayout(unsigned int panel){
    loadTemp();
    int numOFpanels = numPanels();
    if (numOFpanels == -1){
        createPanel();
        //not sure what I need to return here...
        return "top";
    }
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    std::string layout;
    unsigned int i=1;
    //std::cout<<"panel: "<<panel<<std::endl;
    if((panel != i) && (test)){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            ++i;
            layout = tray->Attribute("layout");
        }
    }
    ///Why does this crash everything??

    ///if horizontal check valign
    ///should be left or right
    if(layout.compare("horizontal")==0){
        const char* valign = tray->Attribute("valign");
        //std::cout<<valign<<std::endl;
        return valign;
    }
    ///if vertical check halign
    ///should be top or bottom
    else if(layout.compare("vertical")==0){
        const char* halign = tray->Attribute("halign");
        //std::cout<<halign<<std::endl;
        return halign;
    }
    const char* error = "This shouldn't happen... no layout in getPanelLayout(unsigned int panel)";
    errorJWM(error);
    return error;
}

//End MultiPanels


///  EXECUTABLES AND PATHS  /././././././././././././././././././../././.././././././././././././././././..././././././././.././.././././/..././././././

bool Config::testExec(const char* exec){
    struct stat sb;
    std::string stringEXEC = exec;
 /// my cheat sheet
 // /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
    std:: string testPATH, testExec;
    for (int i = 1; i <= numPATHS; i++){
		stringEXEC = exec;
		//std::cout<<"exec: "<<exec<<std::endl;
        testPATH = thisPATH(i);
        stringEXEC = testPATH + "/" + stringEXEC;
        testExec = stringEXEC.c_str();
        if (stat(testExec.c_str(), &sb) == 0){return true;}//else{std::cerr<<"Couldn't find "<<exec<<"\n";}
    }
    return false;
}
bool Config::testFile(const char* fileWithFullPATH){
  struct stat buffer;
  return (stat (fileWithFullPATH, &buffer) == 0);
}
//End Executables && $PATH

///########################################### ICONS ###########################################//////////////...............................................

std::vector<std::string> Config::iconList(){
    std::string value;
    std::vector<std::string> thisList;
    loadTemp();
    for(const tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        value  = node->GetText();
        if(value.c_str() !=NULL){
            if (value.compare("/usr/share/pixmaps")!=0 && value.compare("/usr/share/icons")!=0 ){
                thisList.push_back(value);
            }
        }
    }
    return thisList;
}
int Config::EXTENTION(std::string filename){
 ///represent the image extention in integer numerals
    const char* svg = "svg";
    const char* png = "png";
    const char* xpm = "xpm";
    std::string extentionReturn = ".";
    unsigned int found = filename.find_last_of(".");
    filename = filename.erase(0,found+1);
    if(filename.compare(svg)==0){
        return 0;//0 means svg
    }
    else if(filename.compare(png)==0){
        return 1;//1 means png
    }
    else if(filename.compare(xpm)==0){
        return 2;//2 means xpm
    }
    else return 42;//42 means you'll have to go fish
}
std::string Config::getExtention(){
///This function returns the most used image extention from <IconPath> tags

    //counters for image format as well as a gofishcounter for non images...
    int svgCounter = 0, pngCounter = 0, xpmCounter = 0, gofishcounter = 0;

    //make an unsigned int to store the vector size
    unsigned int listCounter= 0;
    //get a list of the IconPath directory entries as a vector
    std::vector<std::string> IconList = iconList();

    std::string value, filename, tempDir;

    // make our filename extentions to compare with
    const char* SVG = "svg";
    const char* PNG = "png";
    const char* XPM = "xpm";

    //initialize our extention as a dot
    //we add the extention to it later
    std::string extentionReturn = ".";

    // this is used as a temporary container for the result of EXTENTION function above
    int tracker;
    /* 0 means svg
     * 1 means png
     * 2 means xpm
     * 42 means you'll have to go fish... it is not what we want
     */

    // get the size of our list of directories
    listCounter = IconList.size();

    //if there is nothing use pixmaps because we ignored it
    if (listCounter<=1){IconList.push_back("/usr/share/pixmaps");}

    //make our pointer to the directory
    DIR *dirPointer = NULL;

    //make our pointer to our entry in the directory (stuff like files and folders)
    struct dirent *dirEntryPointer = NULL;

    // loop through the whole list starting at 0 and ending at the vector length
    for (unsigned int i = 0; i < listCounter; i++){

        // this will be our directory to open
        // the i-th directory in our list
        tempDir = (IconList[i]).c_str();

        //if it is empty... don't do anything.
        if (tempDir.compare("")!=0){

            // make the directory pointer the tempDir string (i.e. /usr/share/pixmaps)
            dirPointer=opendir(tempDir.c_str());

            // read it until it returns NULL
            // (this would be an error, or the end of the directory)
            while ((dirEntryPointer=readdir(dirPointer)) != NULL){

                // the filename will be whatever the directory entry's name is
                filename = dirEntryPointer->d_name;
                // use the EXTENTION function to get the numerical representation of
                // the file's extention
                tracker = EXTENTION(filename);
                /// see EXTENTION function above
                    /* 0 means svg
                     * 1 means png
                     * 2 means xpm
                     * 42(else) means it is not what we want
                     */
                if(tracker == 0){svgCounter++;}
                else if(tracker == 1){pngCounter++;}
                else if(tracker == 2){xpmCounter++;}
                else{gofishcounter++;}
            }
            // close the directory
            closedir(dirPointer);
        }
    }
    // if png has more than svg and xpm extentionReturn = .png
    // we want to preferr this, as PNG looks nice and works
    // on most compiled JWM setups
    if (pngCounter>svgCounter && pngCounter > xpmCounter){extentionReturn += PNG;}

    // this is very lightweight, so it will be our second check
    // if xpm has more than svg and png extentionReturn = .xpm
    else if (xpmCounter>svgCounter && xpmCounter > pngCounter){extentionReturn += XPM;}

    // if svg has more than png and xpm extentionReturn = .svg
    // svg looks the best, but some versions of JWM are compiled without support for it..
    else if (svgCounter>pngCounter && svgCounter > xpmCounter){extentionReturn += SVG;}
    // I like SVG a lot... so just return it
    else{extentionReturn+="svg";}
    // this can be uncommented to see what you are getting
    //std::cerr<<extentionReturn<<std::endl;

    // return the extention
    return extentionReturn.c_str();
}

//End Icons

///  BASH-LIKE  /!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#/!#

const char* Config::grep(const char* args, const char* filename){
///Return the FIRST match of the 'args' from a file
// this is like  line=`grep $args $filename` that only returns one line
    std::string line;
//    const char* result;
    std::string lengthTEST = args;
    int lengthofARGS = lengthTEST.length();
    std::string subString;
    std::ifstream inputFileStrem (filename, std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line)){
            subString=line.substr(0,lengthofARGS);
            if(subString == args){
                //std::cerr<<args<<" "<<sub<<std::endl;
                return line.c_str();
            }
/* TODO: test this to see if it works better:
            result=strstr(line.c_str(),args);
            if(result!=NULL){
                return line.c_str();
            }
*/
        }
    }
    return "";
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
std::string Config::returnTerminalOutput(std::string terminal_Command_You_Want_Output_From, const char* type){
    std::string result="";
    const int max_buffer = 1024;
    char buffer[max_buffer];
    /*
    Thanks to Jeremy Morgan's article!
    my original code was not using feof, this works now :)
    */
    FILE *command_p = popen(terminal_Command_You_Want_Output_From.c_str(), type);
	if (command_p){
        while(!feof(command_p)){
            if( fgets(buffer, sizeof(buffer), command_p) !=NULL){
                result.append(buffer);
            }
        }
        pclose(command_p);
    }
    else{ return "[returnTerminalOutput] Error from command run";}
	return result;
}
int Config::run(const char* command){
    std::string exec = "/bin/bash -c '";
    exec+=command;
    exec+=" &disown'";
    return system(exec.c_str());
}
//End BASH

///MULTIUSE///////////////////////////////////////////////////////////////////////////
/*
 * These are all Multiuse general functions for the FirstChild Element of 'JWM'
 *
 *
 We are looking for whichElement... this is whatever element you want to find
 I use it for IconPath sepcifically in

 <JWM>
    <whichElement>
    </whichElement>
 </JWM>
 *
 * XML attributes are
 *
 <JWM>
    <whichElement attribute="value">
    </whichElement>
 </JWM>
 *
 */

void Config::setAttribute(const char* whichElement, const char* attribute, const char* value){
    loadTemp();
    //make sure element exists first
    if (!isElement(whichElement)){createElement(whichElement);}
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    //set the attribute
    element->SetAttribute(attribute,value);
    //save :)
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, const char* value, const char* text){
    loadTemp();
    //make sure the element exists
    if (!isElement(whichElement)){createElement(whichElement);}
    //create a pointer to the base element <JWM>
    tinyxml2::XMLElement* base = doc.FirstChildElement( "JWM" );
    //
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    base->InsertAfterChild(node,node);
    tinyxml2::XMLText *action = doc.NewText(text);
    node->LinkEndChild(action);
    tinyxml2::XMLElement* element=doc.FirstChildElement("JWM")->LastChildElement(whichElement);
    element->SetAttribute(attribute,value);
    saveChangesTemp();
}
void Config::setAttribute(const char* whichElement, const char* attribute, double &value){
    loadTemp();
    // this overloads to take a double.. it simply converts to a const char* to run the base function
    const char* result = convert(value);
    setAttribute(whichElement,attribute,result);
}
void Config::setAttribute(const char* whichElement, const char* attribute, int &value){
    loadTemp();
    // this overloads to take an int.. it simply converts to a const char* to run the base function
    std::string result = convert(value);
    setAttribute(whichElement,attribute,result.c_str());
}
void Config::createElement(const char* whichElement){
    /* simply creates a Child element of <JWM>
    <JWM>
       <whichElementToCreate/>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *node = doc.NewElement(whichElement);
    element->InsertEndChild(node);
    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichMainElement, const char* whichElementToCreate){
    loadTemp();
    /*this over-loaded version will make a sub-element of whichMainElement
    <JWM>
        <whichMainElement>
            <whichElementToCreate/>
        </whichMainElement>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */

    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    //make sure whichMainElement exists before we go further
    if (!element->FirstChildElement(whichMainElement)){
        createElement(whichMainElement);
    }
    //make it!
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement);
    tinyxml2::XMLNode *node = doc.NewElement(whichElementToCreate);
    //put it at the very end
    element->InsertEndChild(node);
    //save
    saveChangesTemp();
    saveChanges();
}
void Config::createElement(const char* whichMainElement, const char* whichSubElement, const char* whichElementToCreate){
  /*this over-loaded version will make a sub-element of the sub element whichSubElement
    <JWM>
        <whichMainElement>
            <whichSubElement>
                <whichElementToCreate/>
            </whichSubElement>
        </whichMainElement>
    </JWM>
    * since there is no text, it will make the single element rather than the pair
    */
    loadTemp();
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    //make sure the first element exists
    if (!element->FirstChildElement(whichMainElement)){
        createElement(whichMainElement);
        //loadTemp();
    }
    //point to the first one
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement);
//make sure the second exists
    if (!element->FirstChildElement(whichMainElement)->FirstChildElement(whichSubElement)){
        createElement(whichMainElement,whichSubElement);
        //loadTemp();
    }
//point to the second
    element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichMainElement)->FirstChildElement(whichSubElement);
    //make it!
    tinyxml2::XMLNode *node = doc.NewElement(whichElementToCreate);
    element->InsertEndChild(node);
    //save it!!
    saveChangesTemp();
    saveChanges();
}

bool Config::isElement(const char* whichElement){
    loadTemp();
    //check if it is an element or not
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if ((element)->FirstChildElement(whichElement)){return true;}
    return false;
}
bool Config::isElement(const char* whichElement, const char* whichSUBElement){
    loadTemp();
    //check sub elements
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if (element->FirstChildElement(whichElement)){
        if(doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement)->FirstChildElement(whichSUBElement)){return true;}
    }
    return false;
}

bool Config::isElementText(const char* whichElement, std::string textTOcompare){
    loadTemp();
    //this is to compare text in an element with std::string text
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    std::string testText;
    //does it exist
    if ((element)->FirstChildElement(whichElement)){
        for (element = element->FirstChildElement(whichElement);element;element = element->NextSiblingElement(whichElement)){
            testText = element->GetText();
            //std::cerr<<testText<<std::endl;
            if (textTOcompare.compare(testText.c_str())==0){return true;}
        }
    }
    //if it never gets to return true then we always return false
    return false;
}

int Config::getIntAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    //use the function below
    const char* result = getElementAttribute(whichElement, attribute);
    //convert string to unsigned long int
    // str   to ul
    //oh... and use 10... we want a base 10 number not something else
    int value = strtoul(result,0,10);
    return value;
}

const char* Config::getElementAttribute(const char* whichElement,const char* attribute){
    loadTemp();
    if (!isElement(whichElement)){return "0";}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    return element->Attribute(attribute);
}
const char* Config::getElementAttribute(const char* whichElement,const char* whichSubElement,const char* attribute){
    loadTemp();
    if (!isElement(whichElement)){return "0";}
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement(whichElement);
    //make sure sub element exists... if not then return 0
    if(!element->FirstChildElement(whichSubElement)){return 0;}
    element=element->FirstChildElement(whichSubElement);
    return element->Attribute(attribute);
}

unsigned int Config::getELEMENTColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2, const char* FGorBG){
    loadTemp();
    unsigned int bg = 0;
    tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    //make sure the base element exists
    if (!colorElement->FirstChildElement( whichStyle )){
        createElement(whichStyle);
    }
    colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( whichStyle );
    std::string style = whichStyle;
    if(isNewStyle){
        std::string check = ActiveORinactive;
        if (check.compare("Active")==0){
            //Active so we have 3 deep we need to check for existence more
            if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}
            //make sure the sub element exists first
            if (!colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG )){createElement(whichStyle,ActiveORinactive,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG );
        }
        else{
            //make sure it exists first
            if (!colorElement->FirstChildElement( FGorBG )){createElement(whichStyle,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( FGorBG );
        }
    }
    else{
        //make sure it exists first
        if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}

        //point to it
        colorElement  = colorElement->FirstChildElement( ActiveORinactive );
    }
    //get the text
    std::string colour = colorElement->GetText();
    bg = getColor(colour, color2);
    return bg;
}

unsigned int Config::getFGColor(const char* whichStyle, const char* ActiveORinactive, unsigned int &color2){
    return getELEMENTColor(whichStyle, ActiveORinactive, color2, "Foreground");
}
void Config::setELEMENTColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb, const char* FGorBG){
    loadTemp();
        tinyxml2::XMLElement* colorElement = doc.FirstChildElement( "JWM" );
    //make sure the base element exists
    if (!colorElement->FirstChildElement( whichStyle )){
        createElement(whichStyle);
    }
    colorElement = doc.FirstChildElement( "JWM" )->FirstChildElement( whichStyle );
    std::string style = whichStyle;
    if(isNewStyle){
        std::string check = ActiveORinactive;
        if (check.compare("Active")==0){
            //Active so we have 3 deep we need to check for existence more
            if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}
            //make sure the sub element exists first
            if (!colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG )){createElement(whichStyle,ActiveORinactive,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( ActiveORinactive )->FirstChildElement( FGorBG );
        }
        else{
            //make sure it exists first
            if (!colorElement->FirstChildElement( FGorBG )){createElement(whichStyle,FGorBG);}

            //point to it
            colorElement  = colorElement->FirstChildElement( FGorBG );
        }
    }
    else{
        //make sure it exists first
        if (!colorElement->FirstChildElement( ActiveORinactive )){createElement(whichStyle,ActiveORinactive);}

        //point to it
        colorElement  = colorElement->FirstChildElement( ActiveORinactive );
    }
    //convert the double rgb to a string
    std::string color1 = colorToString(rgb);
    //set it!
    colorElement->SetText(color1.c_str());
    saveChangesTemp();
}

void Config::setFGColor(const char* whichStyle, const char* ActiveORinactive, const double* rgb){
    setELEMENTColor(whichStyle, ActiveORinactive, rgb, "Foreground");
}

std::string Config::desktopFILE(){
    const char * f = "/usr/share/applications";
    const char * m="Choose a program";
    const char *p="*";
    int r = 0;
    std::string result = fl_file_chooser(m,p,f,r);
    std::string returnable = result;
    std::string base = result;
    unsigned period = result.find_last_of(".");
    bool isDESKTOP = false;
    if(result.compare("")!=0){
        if(period<result.length()){
            std::string testDesktop = result.substr(period+1,std::string::npos);
            if(testDesktop.compare("desktop")==0){isDESKTOP = true;}
        }
        unsigned found = result.find_last_of("//");
        if(found<result.length()){returnable=result.erase(0,found+1);}
        unsigned found2 = returnable.find_last_of(".");
        if(found2<result.length()){returnable=returnable.erase(found2,std::string::npos);}
        if(isDESKTOP){
            std::string desktop = desktopExec(base);
            return desktop;
        }
    }
    return returnable;
}
std::string Config::desktopExec(std::string filename){
    const char* ExecLine = grep("Exec=",filename.c_str());
    std::string EXEC = ExecLine;
    unsigned int args = 0, equals = 0;
    args = EXEC.find("%");
    equals = EXEC.find("=");
    if (args < EXEC.length())EXEC = EXEC.erase(args,std::string::npos);
    if (equals < EXEC.length())EXEC= EXEC.erase(0,equals+1);
   // std::cerr<<EXEC<<std::endl;
    return EXEC;
}
