/*                 Joe's Window Manager Configuration
 *
 * This program configures JWM using tinyxml2 and FLTK
 *
 *         Copyright (C) 2014  Israel <israel@torios.org>
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * This has been developed as a part of the ToriOS Project
 * This has been developed by Israel<israel@torios.org>
 *
 *
 * You may redistribute this, but you must keep this comment in place
 * Jesus is my Lord, and if you don't like it feel free to ignore it.
 */
#include "../include/flDesktop.h"
flDesktop::flDesktop(){
    roxPresent = roxExists();
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDocument roxDoc;
    m_useRox = false;
    m_useRox = roxActive();
    std::string backgrounds = "/usr/share/backgrounds/";
    std::string defaultWallpaper = homePathNoFile() + "Pictures/Wallpapers/dandyLion.png";
    roxFileName = "pb_JWM";
    roxCommand = "rox -p pb_JWM";
    pcmanFMfilename = ".config/pcmanfm/default/pcmanfm.conf";
    m_usePCmanFM = false;
}
flDesktop::~flDesktop(){

}
//************************************************* Background Functions *******************************************************************

bool flDesktop::test(tinyxml2::XMLElement *element){
    const char *tester = element->GetText();
    if (tester==NULL){
        recover();
        return false;
    }
    else return true;
}

void flDesktop::setFlImage(Fl_Box * o, const char * filename){
    std::string extention, noBg, filenameStr, isColor;
    noBg ="No Background Set\n";
    filenameStr = filename;
    if(filenameStr.compare(noBg)==0){
       // std::cout<<filenameStr;
       return;
       // o->hide();
    }
    Fl_Image* image;
    isColor = filenameStr.substr(0,1);
    if(isColor !="#"){
        extention = filenameStr.substr((strlen(filename)-4),4);
        std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
    }

    if (extention == ".png"){
		image = new Fl_PNG_Image(filename);
		Fl_Image * image2 = image->copy(345,270);
        o->image(image2);
        o->show();
        o->redraw();
    }

	else if(extention == ".jpg"){
		image = new Fl_JPEG_Image(filename);
		Fl_Image * image2 = image->copy(345,270);
        o->image(image2);
        o->show();
		o->redraw();
    }
}

///This function simply gets the Text of the element.
const char* flDesktop::getBackground(){// , const char * rgb, const char* rgb2){
    std::string background;
    //check if ROX is being used
    if(!m_useRox){
    // && m_usePCmanFM){
    // getPCmanFMBG}
    //else if(!m_useRox){
        ///JWM background options
        tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Desktops" )->FirstChildElement("Background");
        if(element->Attribute("type","image")){
            if (test(element)){
                background = element->GetText();
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        else if(element->Attribute("type","solid")){
            if (test(element)){
                background = element->GetText();
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        else if(element->Attribute("type","gradient")){
            if (test(element)){
                background = element->GetText();
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        else if(element->Attribute("type","tile")){
            if (test(element)){
                background = element->GetText();
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        else if(element->Attribute("type","command")){
            if (test(element)){
                background = element->GetText();
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        else{
            if (test(element)){
                background ="No Background Set\n";
            }
            else return "Error... Don't hack around in the files so much ok? :D";
        }
        return background.c_str();
    }
    ///ROX background
    else if (m_useRox){
        loadRox();
        return getRoxBackground();
    }
    return "You have discovered a bug, please report this";
}
///This function gets 2 colors.
//i.e. unsinged int color1 = getBackground(color2);
//you can use a dummy variable for  color2 for one color
unsigned int flDesktop::getBackground(unsigned int &color2){
    tinyxml2::XMLElement* bgElement = doc.FirstChildElement( "JWM" )->
                            FirstChildElement( "Desktops" )->
                            FirstChildElement( "Background" );
    ///tester
    std::string background;
    if (test(bgElement)){
            background = bgElement->GetText();
        }
        else {std::cout<<"Error... Don't hack around in the files so much ok? :D"; return 42;}
    unsigned int bg = getColor(background, color2);
    return bg;
}
///One Color setter
void flDesktop::setBackground(const double* rgb){
    std::string color1 = colorToString(rgb);
    const char * type = "solid";
    setBackground(type,color1.c_str());
}
///Two Color setter
void flDesktop::setBackground(const double* rgb, const double* rgb2){
    std::string color1 = colorToString(rgb);
    std::string color2 = colorToString(rgb2);
    std::string colors = color1+':'+color2;
    const char * type = "gradient";
    setBackground(type,colors.c_str());
}

///Image or command setter... technically you could set ANY value from here... as the other functions use it
void flDesktop::setBackground(const char* type, const char* value){
    std::string filenameStr = value;
    std::string extention = filenameStr.substr((strlen(value)-4),4);
    std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->
                                        FirstChildElement( "Desktops" )->FirstChildElement("Background");
    element->SetAttribute("type",type);
    element->SetText(value);
    setRoxBackground(value);
    saveChangesTemp();
}
//################################################# END Background ###################################################################



//************************************************* ROX Functions *******************************************************************

///Set the string for the path to the Rox config file
std::string flDesktop::roxPath(){
    std::string fileName = homePathNoFile();
    fileName+=".config/rox.sourceforge.net/ROX-Filer/";
    fileName+=roxFileName;
    return fileName;
}
/// check to see if Rox is installed
bool flDesktop::roxExists(){
    const char* filemanager = whichFileManager();
    if (filemanager == "rox" || filemanager == "both" || filemanager == "rox-filer"){
        return true;
    }
    else{
        return false;
    }
}

///TODO handle other pb files
int flDesktop::loadRox(){
    std::string fileName = roxPath();
    bool test = configExists();
    if(test){
        roxDoc.LoadFile( fileName.c_str() );
        if (roxDoc.ErrorID() !=0){
            printf("The file %s was not found.\n", fileName.c_str());
            return roxDoc.ErrorID();
        }
    }
    else{recoverRox(); loadRox();}
    return 0;
}
/// check if Rox is the active background handler and return true or false
bool flDesktop::roxActive(){
    if (!roxPresent){return false;}
    loadTemp();
    bool testP = isAutostart("rox -p");
    bool testPinboard = isAutostart("rox --pinboard");
    if (testP || testPinboard){m_useRox = true;}
    else {
       // if(system("pkill rox")!=0){
        //std::cout<<"No Rox\n";
        //}
        m_useRox = false;
    }
    return m_useRox;
}

void flDesktop::useRox(bool rox){
    if (!roxPresent){
        /// //////////////////////////////////////////////////////call ERROR dialog
    }
    m_useRox=rox;
    loadTemp();
    bool configFileExists = configExists();
    bool tester = false;
    if(!rox){
        for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
            tester=true;
        }
        if(tester){
            for(tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
                std::string value = node->GetText();
                std::string fromDoc = value.substr(0,6);
                if(fromDoc.c_str() !=NULL){
                    if((fromDoc.compare("rox -p")==0)||(fromDoc.compare("rox --p")==0)){node->DeleteChild(node);}
                    if(system("pkill rox")!=0){//std::cout<<"No Rox\n";

                    }
                    if(!configFileExists){recoverRox();}
                    saveChangesTemp();
                }
            }
        }
    }
    else if(rox){
        std::string roxSystemCommand = roxCommand;
        roxSystemCommand += " &disown";
        bool exists = roxActive();
        if(!exists){
            if(configFileExists){
                int e = system(roxSystemCommand.c_str());
                if(e){/*do something*/}
                addAutostart(roxCommand);
            }
            else{recoverRox();}
        }
    }
}
bool flDesktop::configExists(){
    std::string filename = roxPath();
    std::ifstream ifile(filename.c_str());
        if (ifile) {
            return true;
        }
        else{return false;}
}
int flDesktop::addRoxFileAttribute(const char* element, const char* attribute, const char* value, const char* text){
    if (!roxPresent){return 42;}
    loadRox();
    tinyxml2::XMLElement* roxElement = roxDoc.FirstChildElement( "pinboard" )->FirstChildElement( element );
    if(roxElement){
        roxElement->Attribute(attribute,value);
        roxElement->SetText(text);
        saveRox();
    }
    else{
        tinyxml2::XMLNode * newNode = roxDoc.NewElement(element);
        roxElement= roxDoc.FirstChildElement( "pinboard" );
        roxElement->InsertFirstChild(newNode);
        tinyxml2::XMLText *bgText = doc.NewText(text);
        newNode->LinkEndChild(bgText);
        tinyxml2::XMLElement *node = newNode->ToElement();
        roxElement->SetAttribute(attribute,value);
        saveRox();
    }
}

void flDesktop::setRoxBackground(const char* value){int result = addRoxFileAttribute("backdrop","style","Stretched", value);std::cout<<result<<std::endl;}
void flDesktop::setRoxBackground(const char* style, const char* value){int result = addRoxFileAttribute("backdrop","style",style, value);std::cout<<result<<std::endl;}

const char * flDesktop::getRoxBackground(){
    const char* background;
    tinyxml2::XMLElement* element = roxDoc.FirstChildElement( "pinboard" )->
                                        FirstChildElement( "backdrop" );
    if(element){
        background = element->GetText();
        return background;
    }
}

void flDesktop::saveRox(){
    std::string fileName = roxPath();
    roxDoc.SaveFile(fileName.c_str());
}
void flDesktop::makeConfig(){
    std::string path = roxPath();
    std::string command = "cp /usr/share/jwm-settings-manager/";
    command += roxFileName;
    command += " ";
    command += path;
    int sys = system(command.c_str());
    if (sys != 0){}
}

void flDesktop::createRoxDir(){
    std::cout<< "Created rox diretory structure\n";
    int mkdirError = 0;
    std::string stringPath = homePathNoFile();
    stringPath+=".config/rox.sourceforge.net/ROX-Filer/";
    const char* path =stringPath.c_str();
    mkdirError = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(mkdirError == 0){makeConfig();}
    else {
        std::cout <<mkdirError<<'\n';
        errorJWM("Failed creating Rox directory");
    }
}

void flDesktop::recoverRox(){
    std::string stringPath = homePathNoFile();
    stringPath+=".config/rox.sourceforge.net/ROX-Filer/";
    const char* path =stringPath.c_str();
    struct stat sb;
    int mkdirError = 0;
    std::string confDir = homePathNoFile();
    confDir+=".config/";
    std::string sfDir = homePathNoFile();
    sfDir+=".config/rox.sourceforge.net/";
    ///TODO: write a function in Config that finds each directory name and separates it, checks and recreates the structure if it doesn't exist.
    /* i.e. /path/to/something
    becomes var[1]=path var[2]=to var[3]=something
    check /path
    if !exist mkdir ("/path", ...)
    check /path/to
    if !exist mkdir ("/path/to", ...)
    check /path/to/something
    if !exist mkdir ("/path/to/something", ...)
    */

    if (stat(confDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
        if (stat(sfDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
            if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)){
                makeConfig();
            }
            else{//Make the whole path, since the .config dir exists as well as rox.sourceforge.net.. all we need is ROX-Filer
                createRoxDir();
            }
        }
        else{ //the sourceforge dir doesn't exist AHHHH  create it and run createRoxDir
            mkdirError = mkdir(sfDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if(mkdirError == 0){createRoxDir();}
        }
    }
    else{ //Config directory doesn't exist!!  make it, the rox.sourceforge.net dir, and lastly run createRoxDir
        mkdirError = mkdir(confDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(mkdirError == 0){mkdirError = mkdir(sfDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);}
        if(mkdirError == 0){createRoxDir();}

    }
}
//################################################# END ROX Functions ###################################################################


//************************************************* Desktop Functions *******************************************************************

//multiple Desktops
void flDesktop::useMultiDesktop(bool &multiValue, int &height, int &width){
    if (!multiValue){
        setMultiDeskHeight(height);
        setMultiDeskWidth(width);
        saveChangesTemp();
    }
    else{
        return;
    }
}

//Gets the number of desktops wide
int flDesktop::getMultiDeskWidth(){return getIntAttribute("Desktops","width");}
//Gets the number of desktops high
int flDesktop::getMultiDeskHeight(){return getIntAttribute("Desktops","height");}

void flDesktop::setMultiDeskWidth(double width){setAttribute("Desktops","width",width);}
void flDesktop::setMultiDeskHeight(double height){setAttribute("Desktops","height",height);}

bool flDesktop::multipleDesktops(){
    int mdW = getMultiDeskWidth();
    int mdH = getMultiDeskHeight();
    //Check if it is a 1x1.. i.e. no multiple desktop, therefore false
    if(mdW==1 && mdH==1){return false;}

    // if it isn't 1x1 it is a MultiDesktop, of course :D
    return true;
}

//################################################# END Desktop Functions ###################################################################

///Which Filemanager
//TODO: find how xdg-open stores inode/directory
const char* flDesktop::whichFileManager(){
    std::string result;
    std::string inode ="inode/directory=";
    const char* defaults="/usr/share/applications/defaults.list";
    bool defaultsList = testFile(defaults);
    if (!defaultsList){
        bool roxInstalled = testExec("rox-filer");
        bool pcmanfmInstalled = testExec("pcmanfm");
        bool nautilusInstalled = testExec("nautilus");
        bool thunarInstalled = testExec("thunar");
        if (roxInstalled){result += "rox ";}
        else if (pcmanfmInstalled){result += "pcmanfm ";}
        else if (nautilusInstalled){result += "nautilus ";}
        else if (thunarInstalled){result += "thunar ";}
        else{result = "unknown ";}
        result += "INSTALLED";
        return result.c_str();
    }
    result = grep(inode.c_str(), defaults);
    //std::cout<<result<<std::endl;
    int len = inode.length();
    std::string testResult = result;
    if (len >= testResult.length()){return result.c_str();}
    std::string STRresult = result;
    STRresult = STRresult.substr(len, std::string::npos);
    //std::cout<<STRresult<<std::endl;
    int position = STRresult.find('.');
    STRresult = STRresult.erase(position, std::string::npos);
    std::cout<<STRresult<<std::endl;
    result=STRresult;
    //std::cout<<result<<"\n";
    return result.c_str();
}
