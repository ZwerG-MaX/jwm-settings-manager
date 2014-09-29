#include "../include/Config.h"

Config::Config()
{
    file = ".jwmrc";
    home = getenv ("HOME");
    std::string homePathNoFiles = homePathNoFile();
    whichPanel = 1;
}

Config::~Config()
{
    //dtor
}

void Config::cancel(){
    load();
    saveChangesTemp();
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
    //std::cout<<"Temporary File saved\n";
    if(std::system("jwm -p")!=0){
        std::cout<<"Error checking JWM... please run jwm -p again\n";
    }
    doc.SaveFile((homePathTemp()).c_str());
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
        std::cout<<"jwmrc should be recovered now";
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

/// Autostart ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Config::addAutostart(const char * program){
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
 void Config::removeAutostart(const char * program){
    for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
        std::string fromDoc = node->GetText();
        ///What was I doing here???  why was I looking for a space?
        //unsigned found = fromDoc.find(" ");
        //fromDoc = fromDoc.erase(0,found+1);
        ///probably delete this, unless I find a bug that I needed this for...
        const char* value  = fromDoc.c_str();
        std::string fromProgram = program;
        //std::cout<<"Value: "<<value<<" Program: "<<program<<std::endl;
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            std::cout<<"deleted "<<program<<std::endl;
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


///Parse the document and count how many "Tray" elements there are.  return this number


//simply check if there are multiple panels
bool Config::multipanel(){
bool test = false;
    if(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Tray")->NextSiblingElement("Tray")){
        test = true;
    }
    return test;
}

//find out how many panels exist
unsigned int Config::numPanels(){
    //start from 0 panels
    unsigned int counter2 = 0;
    //make sure it is a multipanel
    bool test = multipanel();
    if(test){
        for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("Tray");node;node=node->NextSiblingElement("Tray")){
            //save the name of the NextSiblingElement
            std::string name = node->Name();
            //make an element to compare it too
            std::string element = "Tray";
            //check the two... if they are equal add it.
            if(name.compare(element)==0){
                counter2++;
            }
        }
    }
    //if the multipanel function fails there should only be 1 panel and return 0 so the numPanels (below) that calls this wont make a new entry for it.
    return counter2;
}

//find out how many panels exist and make a FLTK MenuItem for each one
unsigned int Config::numPanels(Fl_Menu_Button* o){
    //if this returns 0 it wont make a menu item.
    unsigned int total = numPanels();
    for (int i=1; i<total; i++){
        std::string label = "Panel ";
        int panel_num = i+1;
        std::string num = convert(panel_num);
        label+=num;
        //std::cout<<label<<'\n';//Debug
        const char* out = label.c_str();
        //Fl_Callback
        o->add(out,0,0,0,0);//label,shortcut,callback!!!!,userdata,flags
        ///TODO: add callback for each panel item...
    }
}

const char* Config::currentPanel(){
//    PanelUI p;
    return "yo"; //p.get_vh();
}

const char* Config::checkLayout(unsigned int panel){
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

const char* Config::getPanelLayout(unsigned int panel){
    tinyxml2::XMLElement* tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");
    bool test = multipanel();
    int i=1;
    if(test && panel != i ){
        while(tray->NextSiblingElement("Tray") && i!=panel){
            tray=tray->NextSiblingElement("Tray");
            i++;
        }
    }
    else{tray=doc.FirstChildElement("JWM")->FirstChildElement("Tray");}
    std::string layout = tray->Attribute("layout");
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
    if (stat(exec, &sb) == 0){
        // std::cout<<"Found "<<exec<<"\n";
        return true;
    }
    std::cout<<"Couldn't find "<<exec<<"\n";
    return false;
}


//########################################### END EXECUTABLES AND PATHS ###########################################
