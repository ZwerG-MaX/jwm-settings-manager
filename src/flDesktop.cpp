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
#ifdef DEBUG_TRACK
    std::cerr<<"[flDesktop]->"<<std::endl;
#endif // DEBUG
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDocument roxDoc;
    backgrounds = "/usr/share/backgrounds/";
    roxFileName = "pb_JWM";
    roxCommand = "rox -p pb_JWM";
    pcmanFMfilename = ".config/pcmanfm/default/pcmanfm.conf";
    pcmanFMdesktopfilename = ".config/pcmanfm/default/desktop-items-0.conf";
    pcmanAutostart = "pcmanfm --desktop";
    nautilusStart = "nautilus -n";
    thunarStart = "thunar --daemon";
    m_usePCmanFM = false;
    pcmanfm = "pcmanfm";
    thunar = "thunar";
    nautilus = "nautilus";
    bash = "/bin/bash -c '";//don't forget closing  '  when you use this!
    defaultBG = "#000000";
    defaultBGtype = "solid";
}
flDesktop::~flDesktop(){
#ifdef DEBUG_TRACK
    std::cerr<<"<-[flDesktop]"<<std::endl;
#endif // DEBUG

}
//************************************************* Background Functions *******************************************************************
//desktop
/*int flDesktop::showDesktop(){
    DesktopUI uiDesktop;
    uiDesktop.make_window()->show();
return Fl::run();
}*/

bool flDesktop::test(tinyxml2::XMLElement *element){
if(!testElement(element)){return false;}
    const char *tester = element->GetText();
    if (tester==NULL){
        recover();
        return false;
    }
    else return true;
}

void flDesktop::setFlImage(Fl_Box * o, const char * filename){
    #ifdef DEBUG_TRACK
        std::cerr <<"void flDesktop::setFlImage(Fl_Box * o,"<< filename<<")" << std::endl;
    #endif // DEBUG
    std::string extention, filenameStr, isColor;
    if(filename==NULL){errorJWM("NULL filename sent into flDesktop::setFlImage");return;}
    filenameStr = filename;
    unsigned int len=filenameStr.length();
    if(len<=4){errorJWM("Filename is too small");return;}
    Fl_Image* image = NULL;
    isColor = filenameStr.substr(0,1);

    if(isColor.compare("#")==0){return;}
    unsigned int found;
    found=filenameStr.find_last_of('.');
    if(found<len){
        extention = filenameStr.substr(found,4);
        std::cerr<<"extention="<<extention<<std::endl;
        std::transform(extention.begin(), extention.end(), extention.begin(), ::tolower);
        if (extention.compare(".png")==0){
            image = new Fl_PNG_Image(filename);
            Fl_Image * image2 = image->copy(345,270);
            o->image(image2);
            o->show();
            o->redraw();
        }
        else if(extention.compare(".jpg")==0){
            image = new Fl_JPEG_Image(filename);
            std::cerr<<"its ajpeg"<<std::endl;
            Fl_Image * image2 = image->copy(345,270);
            o->image(image2);
            o->show();
            o->redraw();
        }
        else{errorJWM("No extention on the filename");return;}
    }
    else{return;}
}
void flDesktop::FlBGColor(Fl_Box*o, unsigned int color){
  o->show();
  o->color(color);
  o->redraw();
}
///This function simply gets the Text of the element.
std::string flDesktop::getBackground(){
    std::string background;
    //check if ROX is being used
    if(!roxActive()){
        //does this exist in jwmrc???
        if(!testElement("Desktops","Background")){
            makeBackgroundElement();
            return defaultBG;
        }
        //point to the background
        tinyxml2::XMLElement* element=doc.FirstChildElement( "JWM" )->FirstChildElement( "Desktops" )->FirstChildElement("Background");
        // the element Text exists get the background
        if(!element->GetText()){return "";}
        //std::cout<<"element->GetText()--> "<<element->GetText()<<std::endl;
        //check real attributes... we don't want something that doesn't work...
        if(element->Attribute("type","image")){background = element->GetText();}
        else if(element->Attribute("type","tile")){background = element->GetText();}
        else if(element->Attribute("type","scale")){background = element->GetText();}
        else if(element->Attribute("type","solid")){background = element->GetText();}
        else if(element->Attribute("type","gradient")){background = element->GetText();}
        else if(element->Attribute("type","command")){background = element->GetText();}
        else{background = "";} //should not normally happen....

        //now we need to do some checking
        //which filemanager might be running?
        std::string fm = whichFileManagerRunning();

        //this will be used to test the background
        std::string testBG;

        //if the filemanager is running.... we need to get the background for testing
        if (fm.compare("unknown")!=0){
            //std::cout<<"filemanager = "<<fm<<std::endl;
            // this is pretty self explanitory, pcmanfm is pcmanfm and thunar is thunar, nautilus is nautilus
            //we don't need to check for rox again...  I don't support KDE... since... well this is JWM
            if(fm.compare(pcmanfm)==0){testBG=getPCmanFMbg();}
            else if((fm.compare(thunar))==0||(fm.compare(nautilus))==0){testBG=getGsettingsBG();}
            else{testBG="";}
            //std::cout<<"fmBG: "<<testBG<<" jwmBG: "<<background<<std::endl;
            // if the testBG  and background are empty... return black... because that is the default
            // I don't think this should ever happen... but just in case
            if((testBG.compare("")==0)&&(background.compare("")==0)){background = "#000000";}
            //if the background is empty or not the same as the running filemanager...
            if((background.compare(""))||(background.compare(testBG)!=0)){
                //make the background the test BG
                if(testFile(testBG.c_str())){
                    background = testBG;
                //set it as JWM background
                    setBackground("image",background.c_str());
                }
            }
        }
        //return the background so it can be displayed
        std::cerr<<"THE BG is: "<<background<<std::endl;
        return background;
    }
    ///ROX background
    else if (roxActive()){
        loadRox();
        return getRoxBackground();
    }
    else{
        errorJWM("You have discovered a bug in getBackground() regarding m_useRox, please report this message");
        return "";
    }
}

///This function gets 2 colors.
//i.e. unsinged int color1 = getBackground(color2);
//you can use a dummy variable for  color2 for one color
unsigned int flDesktop::getBackground(unsigned int &color2){
    //does this exist???
    if(!testElement("Desktops","Background")){
            makeBackgroundElement();
            return 0;
    }
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement( "Desktops" )->FirstChildElement("Background");
    std::string background;
    //does it actually have text??
    if(element->GetText()){
        background = element->GetText();
        unsigned int bg = getColor(background, color2);
        return bg;
    }
    std::cerr<<"You have the Background tag, but it is empty... how did you do that???\nRecover it manually, or simply set a background"<<std::endl;
    return 0;
}

///One Color setter
void flDesktop::setBackground(const double* rgb){
    //std::cout<<"one color set background"<<std::endl;
    std::string color1 = colorToString(rgb);
    const char * type = "solid";
    svgGradient(rgb);
    setBackground(type,color1.c_str());
}

///Two Color setter
void flDesktop::setBackground(const double* rgb, const double* rgb2){
    //std::cout<<"two color set background"<<std::endl;
    std::string color1 = colorToString(rgb);
    std::string color2 = colorToString(rgb2);
    std::string colors = color1+':'+color2;
    const char * type = "gradient";
    svgGradient(rgb,rgb2);
    setBackground(type,colors.c_str());
}

///Image or command setter... technically you could set ANY value from here... as the other functions use it
void flDesktop::setBackground(const char* type, const char* value){
    //does this exist???
    if(!testElement("Desktops","Background")){
            makeBackgroundElement();
    }
    //point to it
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" )->FirstChildElement( "Desktops" )->FirstChildElement("Background");
    std::string fm = whichFileManagerRunning();
    //see if it is an image.... if so... set the BG in Rox/PCman/nautilus/thunar and maybe more :P
    std::string isImage =type;
    if (isImage.compare("image")==0||isImage.compare("tile")==0||isImage.compare("scale")==0){
        //look in Constructor (the variables are the same as the const char* name)
        if(fm.compare(pcmanfm)==0){setPCmanFMbg(value);}
        else if((fm.compare(thunar))==0||(fm.compare(nautilus))==0){setGsettingsBG(value);}
        else{
            if(testExec("rox-filer")){setRoxBackground(value);}
            else{std::cout<<"No known filemanager to handle the desktop is running\nOnly settings JWM background\nFeel free to contact us with a method to set the background for you Filemanager of choice!"<<std::endl;}
        }
    }
    element->SetAttribute("type",type);
    element->SetText(value);
    saveChangesTemp();
}

void flDesktop::makeBackgroundElement(){
    errorJWM("Background tag did not exist.");
    tinyxml2::XMLElement* element = doc.FirstChildElement( "JWM" );
    if(!element->FirstChildElement( "Desktops" )){
    //width="2" height="1"
        createElement("Desktops");
        element=element->FirstChildElement( "Desktops" );
        element->SetAttribute("width",2);
        element->SetAttribute("height",1);
        saveChangesTemp();
    }
    createElement("Desktops","Background");
    loadTemp();
    std::cerr<<"Using "<<defaultBG<<" for the default background "<<defaultBGtype<<std::endl;
    element=doc.FirstChildElement( "JWM" )->FirstChildElement( "Desktops" )->FirstChildElement( "Background" );
    element->SetAttribute("type",defaultBGtype.c_str());
    element->SetText(defaultBG.c_str());
    saveChanges();
    saveChangesTemp();
}
//################################################# END Background ###################################################################

bool flDesktop::isPCmanFMconfig(){
    std::string pcmanconfig = homePathNoFile();
    pcmanconfig += pcmanFMfilename;
    std::string defaultConfig = homePathNoFile();
    defaultConfig+=pcmanFMdesktopfilename;
    bool pcmanTEST = testFile(pcmanconfig.c_str());
    bool defaultTEST = testFile(defaultConfig.c_str());
    if (pcmanTEST||defaultTEST){return true;}
    return false;
}
void flDesktop::setPCmanFMbg(const char* filename){
    bool exsits = testExec(pcmanfm.c_str());
    std::string FNAME = fixName(filename);
    if (exsits){
        std::string pcmanpid = returnTerminalOutput("pgrep pcmanfm","r");
        if (pcmanpid.compare("")==0){
            std::string pcmstart = bash;
            pcmstart +=pcmanAutostart;
            pcmstart+=" &disown'";
            int thissys = system(pcmstart.c_str());
            if(thissys !=0){std::cerr<< pcmstart << " command did not return 0"<<std::endl;}
        }
        //code to set the background
        const char* pcmanWP = " --wallpaper-mode=stretch --set-wallpaper=";
        std::string replaceBG = bash;
        replaceBG += pcmanfm;
        replaceBG += pcmanWP;
        replaceBG += FNAME;
        replaceBG +="'";
        //std::cout<<replaceBG<<std::endl;
        int i =system(replaceBG.c_str());
        if (i!=0){errorJWM("setting PCManFM background failed");}
    }
    return;
}

std::string flDesktop::getPCmanFMbg(){
    if(isPCmanFMconfig()){
        std::string pcmanconfig = homePathNoFile();
        std::string defaultConfig = homePathNoFile();
        pcmanconfig += pcmanFMfilename;
        defaultConfig+=pcmanFMdesktopfilename;
        std::string result = grep("wallpaper=",pcmanconfig);
        if (result.compare("")!=0){
            unsigned int found = result.find_first_of("=");
            if((found+1) < result.length()){
                result=result.erase(0,found+1);
                if (result.compare("")!=0){return result.c_str();}
            }
        }
        else {
            result = grep("wallpaper=",defaultConfig);
            if (result.compare("")!=0){
                unsigned int found2 = result.find_first_of("=");
                if((found2+1)< result.length()){
                    result=result.erase(0,found2+1);
                    if (result.compare("")!=0){return result.c_str();}
                }
            }
        }
        result = getBackground();
        setPCmanFMbg(result.c_str());
        return result.c_str();
        //remove wallpaper=  and return the rest
    }
    else{
        errorJWM("Desktop: getPCmanFMbg() couldn't find PCManFM config file");
        return "42";
    }
}

std::string flDesktop::getGsettingsBG(){
///This function works, but has not been implemented yet
/*TODO:
 * do I want to use this to make JWM's background the same, or something else?
 * I do want to make sure that the backgrounds are the same for everything.
 * this will make it less jarring or confusing for new users
*/
    bool exsits = testExec("gsettings");
    if (exsits){
        std::string getGBG ="gsettings get org.gnome.desktop.background picture-uri";
        std::string testResult = returnTerminalOutput(getGBG,"r");
        if (testResult.compare("")!=0){
            unsigned int found = testResult.find_first_of(':');
            if (found==5){
                testResult=testResult.substr(8,std::string::npos);
                found=testResult.find_last_of("'");
                testResult=testResult.substr(0,found);
                found=testResult.find(".xml");
                if (found>testResult.length()){
                    std::cerr<<testResult<<"not xml file"<<std::endl;
                    if(testFile(testResult.c_str())){return testResult;}
                }
                else{
                    std::cerr<<testResult<<" <--XML file"<<std::endl;
                    std::string tmp=grep("file",testResult);
                    std::cerr<<"initial grep: "<<tmp<<std::endl;
                    found=tmp.find_first_of('>');
                    if(found<tmp.length()){
                        tmp=tmp.substr(found+1,std::string::npos);
                        std::cerr<<"first finder: "<<tmp<<std::endl;
                    }
                    found=tmp.find_first_of('<');
                    if(found<tmp.length()){
                        tmp=tmp.substr(0,found);
                        std::cerr<<tmp<<std::endl;
                    }
                    if(testFile(tmp.c_str())){return tmp;}
                }
            }
            std::cerr<<testResult<<std::endl;
        }
    }
    else{errorJWM("getGsettingsBG() failed, since gsettings is not in your $PATH,\nif you are not using thunar or nautilus this is no big deal");}
    return "";
}

void flDesktop::setGsettingsBG(const char* filename){
    // const char * functionName = "void flDesktop::setGsettingsBG(const char* filename)";
    bool exsits = testExec("gsettings");
    if (exsits){
        std::string FNAME = fixName(filename);
        const char* gsettings = " gsettings set org.gnome.desktop.background picture-uri file://";
        std::string replaceBG = bash;
        replaceBG += gsettings;
        replaceBG += FNAME; //filename;
        replaceBG +="'";
        int i =system(replaceBG.c_str());
        if (i!=0){errorJWM("failed setting gsettings wallpaper");}
    }
    else{errorJWM("setGsettingsBG() failed, since gsettings is not installed,\nif you are not using thunar or nautilus this is no big deal");}
    return;
}

///Which Filemanager
std::string flDesktop::whichFileManager(){
    //get the name of the desktop file used for directories
    std::string result = returnTerminalOutput("xdg-mime query default inode/directory","r");

    // get rid of the new line character
    int nl = result.find_last_of('\n');
    result=result.substr(0,nl);

    //look to see if
    std::string defaults="/usr/share/applications/";
    defaults+=result;

    //test the result file... does it exist
    const char* testResult = defaults.c_str();
    bool xdgMime=false;
    if(testResult!=NULL){xdgMime = testFile(testResult);}
    //if not, we will guess what you are using
    if (!xdgMime){
        result = "";

        //check to see what exists
        bool roxInstalled = testExec("rox-filer");
        bool pcmanfmInstalled = testExec(pcmanfm.c_str());
        bool nautilusInstalled = testExec(nautilus.c_str());
        bool thunarInstalled = testExec(thunar.c_str());

        //prefer pcmanfm
        if (pcmanfmInstalled){return "pcmanfm";}
        else if (thunarInstalled){return "thunar";}
        else if (nautilusInstalled){return "nautilus";}
        else if (roxInstalled){return "rox";}
        else{result = "unknown";}
        //worse case scenario return unknown
        return result.c_str();
    }
    //look for Exec= in our desktop file
    std::string executable = grep("Exec=", defaults);

    //make sure we have something usable
    if((executable.compare("")==0)||(executable.length()<=5)){return "unknown";}

    //substring to remove Exec= (5 characters)
    std::string STRresult = executable.substr(5, std::string::npos);

    //if the Exec= line was blank... return unknown
    if (STRresult.compare("")==0){return "unknown";}

    //if there are any extra bits like %U or whatever remove them
    unsigned int position = STRresult.find(' ');
    if(position<STRresult.length()){STRresult = STRresult.erase(position, std::string::npos);}
    result=STRresult;
    return result.c_str();
}
std::string flDesktop::whichFileManagerRunning(){
    std::string result;
    if(filemanagerRunning("pcmanfm")){return "pcmanfm";}
    else if (filemanagerRunning("thunar")){return "thunar";}
    else if (filemanagerRunning("nautilus")) {return "nautilus";}
    else if(filemanagerRunning("rox")) {return "rox";}
    else{return "unknown";}
}
bool flDesktop::filemanagerRunning(){return filemanagerRunning(whichFileManager());}
bool flDesktop::filemanagerRunning(std::string filemanagerToCheck){
    // this function determines whether icons are on the desktop or not...
    std::string current = filemanagerToCheck;
    if((current.compare("")==0)){return false;}
    //std::cout<<"checking: "<<current<<std::endl;
    //make an error message for errorJWM()  use the Filemanager we found
    std::string errorMessage = current;

    //we will check to see if the default filemanager is running
    bool fmRunning = false;
    //we will check for startup command as well
    bool startup = false;

    //we will be returning the Terminal output of pgrep $current  #filemanager
    std::string pgrep = bash;
    pgrep += "pgrep ";
    pgrep += current;
    pgrep += "'";
    pgrep=returnTerminalOutput(pgrep,"r");
    //if the result is not just the /n or nothing then it is running!!
        //std::cout<<"pgrep:"<<pgrep<<":"<<std::endl;
    if ((pgrep.compare("\n")==0)||(pgrep.compare("")==0)){
        fmRunning = false;
        //std::cout<<current<<" is not running"<<std::endl;
        return false;
    }
    else{return true;}
    //std::cout<<pgrep<<std::endl;
    loadTemp();
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");

    //make sure there are startup commmands
    if(node->FirstChildElement("StartupCommand")){startup = true;}

    //If there are no StartupCommand(s) and not running then it is not running
    if(!startup&&!fmRunning){return false;}

    //find current in StartupCommand... if it exists
    if(startup){
        //loop through all the startup command nodes
        for(node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
            //get the text from the document
            std::string fromDoc = node->GetText();
            //make sure there are no arguments passed to the startup command (like --desktop)
            //so look for the first space
            unsigned int position = fromDoc.find(' ');
            //is position the end???
            if (position < fromDoc.length()){
                //delete the arguments after the space
                fromDoc = fromDoc.erase(position, std::string::npos);
                //turn it into a char for comparing
                const char* value  = fromDoc.c_str();
                //does it compare?
                if(current.compare(value) ==0){
                    //if the filemanager is running the return true
                    if (fmRunning){return true;}
                    else{
                        // this is odd... they must have hand edited the file after startup
                        errorMessage += " was found in StartupCommands, but it is not running...\n This is rather unusual.";
                        errorJWM(errorMessage);
                        return false;
                    }
                }
            }
        }
    }
    // so it is not set to start automatically...
    // we could add it to autostart for the user... but that might be too intrusive
    // but it is still running... so lets give a useful message and return true
    if(fmRunning){
        errorMessage = current;
        errorMessage += " is running, but it is not set to handle the Desktop normally (i.e. auto startup command)";
        std::cerr<<errorMessage<<std::endl;
        //it is running after all, though it is not the default to handle icons on desktop
        return true;
    }
    return false;
}

void flDesktop::svgGradient(const double* color){
//see the other version below for more detailed explanation
//basically it just makes an svg file with a rectangle the size of the screen and the color we send it
    std::string svgHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
    <svg>\n\
    <rect x=\"0\" y=\"0\" width=\"";
    std::string width = convert(Fl::w());
    std::string svg2 = "\" height=\"";
    std::string height = convert(Fl::h());
    std::string svg3 = "\" fill=\"";
    //colorToString(color) goes here
    std::string svgFooter="\" />\n\
    </svg>";
    std::string result = svgHeader + width+svg2+height+svg3+colorToString(color)+svgFooter;
    std::cout<<result<<std::endl;
    std::string SVGpath = homePathNoFile();
    SVGpath += ".gradient.svg";
    std::ofstream out( SVGpath.c_str() );
    if (!out.fail()){
        out<<result;
        setRoxBackground(SVGpath.c_str());
        setPCmanFMbg(SVGpath.c_str());
        setGsettingsBG(SVGpath.c_str());
    }
}
void flDesktop::svgGradient(const double* color,const double* color2){
    // create a 2 color SVG file
    //here is the header
    std::string svgHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
    <svg>\n\
       <defs>\n\
	    <linearGradient id = \"g1\" x1 = \"50%\" y1 = \"0%\" x2 = \"50%\" y2 = \"100%\">\n\
            <stop stop-color = \"";
            //colorToString(color) will go here for the first color
    std::string svg1 = "\" offset = \"0%\"/>\n\
            <stop stop-color = \"";
            //colorToString(color2) will go here for the second color
    std::string svg2 = "\" offset = \"50%\"/>\n\
        </linearGradient>\n\
    </defs>\n\
    <rect x=\"0\" y=\"0\" width=\"";
    //get the screen width from FLTK for the width
    std::string width = convert(Fl::w());
    std::string svg3 = "\" height=\"";
    //get the screen height from FLTK for the height
    std::string height = convert(Fl::h());
    //fill the rect(angle) with the url of #g1... this is the linear gradient id above in the header
    std::string svgFooter="\" fill=\"url(#g1)\" />\n\
    </svg>";
    //put it all together
    std::string result = svgHeader+colorToString(color)+svg1+colorToString(color2)+svg2+width+svg3+height+svgFooter;
//    std::cout<<result<<std::endl;
    //make the path
    std::string SVGpath = homePathNoFile();
    //add the filename
    SVGpath += ".gradient.svg";
    //open the file stream to our file
    std::ofstream out( SVGpath.c_str() );
    if (!out.fail()){
        //pipe our string variable into the file
        out<<result;
        //set the backgrounds of everything
        setRoxBackground(SVGpath.c_str());
        ///TODO: figure out why PCMAN DOES NOT LIKE THIS!!!!!!!!!! yeeeeeeeeeeaaaaaaaaaaaaaaaaaaaaaaaaarrrrrrrrrrrrrrrrrrrrrrrggggggggggggggggggg :D
        // that was for dramatic, humourous effect... did it work????
        setPCmanFMbg(SVGpath.c_str());
        setGsettingsBG(SVGpath.c_str());
    }
}

void flDesktop::setIconsOnDesktop(){
    //find out which filemanager is running/autstarted
    std::string current = whichFileManager();
    //get the current wallpaper
    std::string currentWallpaper = getBackground();
    //no need to initialize this with a value, strings do not require this
    std::string fileManager;
    //get the bash command started
    std::string execLine = bash;

    //figure out which one it is, and add the right commands to the bash string
    if (current.compare(pcmanfm)==0){
        execLine += pcmanAutostart;
        fileManager=pcmanfm;
    }
    else if (current.compare(thunar)==0){
        execLine += thunarStart;
        fileManager=thunar;
    }
    else if (current.compare(nautilus)==0){
        execLine += nautilusStart;
        fileManager=nautilus;
    }
    else if (current.compare("rox")==0){
        execLine += roxCommand;
        fileManager=roxCommand;
    }
    else{execLine = "";}
    //figure out if there is a usable filemanager
    std::string unknown = bash;
    unknown +="unknown";
    if((execLine.compare(bash)==0)||(execLine.compare(unknown))==0){
        errorJWM("Unsupported default file handler");
        return;
    }
    //add &disown so we don't wait for it to exit...
    execLine +=" &disown'";
    //make sure it isn't running, and start it
    if (!filemanagerRunning()){
        int result = system(execLine.c_str());
        if(result!=0){errorJWM("system call did not return 0");}
        addAutostart(fileManager);
    }
    //set the background for whatever filemanager is running, if it isn't already
    setBackground("image",currentWallpaper.c_str());
}




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
    std::string filemanager = whichFileManager();
    if (testExec("rox-filer")){return true;}
    else{return false;}
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
    if (!roxExists()){return false;}
    loadTemp();
    bool use_rox = false;
    bool testP = isAutostart("rox -p");
    bool testPinboard = isAutostart("rox --pinboard");
    if (testP || testPinboard){use_rox = true;}
    return use_rox;
}

void flDesktop::useRox(bool rox){
    if (!roxExists()){
    return;
        /// //////////////////////////////////////////////////////call ERROR dialog
    }
    loadTemp();
    bool configFileExists = configExists();
    if(!rox){
        tinyxml2::XMLElement* node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");
        if(testElement(node)){
            for(node=doc.FirstChildElement("JWM")->FirstChildElement("StartupCommand");node;node=node->NextSiblingElement("StartupCommand")){
                std::string value = node->GetText();
                std::string fromDoc = value.substr(0,6);
                if(fromDoc.c_str() !=NULL){
                    if((fromDoc.compare("rox -p")==0)||(fromDoc.compare("rox --p")==0)){node->DeleteChild(node);}
                    if(system("/bin/bash -c 'pkill rox'")!=0){//std::cout<<"No Rox\n";

                    }
                    if(!configFileExists){recoverRox();}
                    saveChangesTemp();
                }
            }
        }
    }
    else if(rox){
        std::string roxSystemCommand = bash;
        roxSystemCommand += roxCommand;// /bin/bash -c '
        roxSystemCommand += " &disown'";
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
    if (ifile) {return true;}
    return false;
}
int flDesktop::addRoxFileAttribute(const char* element, const char* attribute, const char* value, const char* text){
    if (!roxExists()){
        errorJWM("Rox is not installed");
        return 42;
    }
    loadRox();
    tinyxml2::XMLElement* roxElement = roxDoc.FirstChildElement( "pinboard" )->FirstChildElement( element );
    if(roxElement){
        roxElement->Attribute(attribute,value);
        roxElement->SetText(text);
        saveRox();
        return 0;
    }
    else{
        tinyxml2::XMLNode * newNode = roxDoc.NewElement(element);
        roxElement= roxDoc.FirstChildElement( "pinboard" );
        roxElement->InsertFirstChild(newNode);
        tinyxml2::XMLText *bgText = doc.NewText(text);
        newNode->LinkEndChild(bgText);
        //tinyxml2::XMLElement *node = newNode->ToElement();
        roxElement->SetAttribute(attribute,value);
        saveRox();
        return 0;
    }
    errorJWM("This is not generally possible\naddRoxFileAttribute() shouldn't do this");
    return 42;
}

void flDesktop::setRoxBackground(const char* value){int result = addRoxFileAttribute("backdrop","style","Stretched", value);std::cout<<result<<std::endl;}
void flDesktop::setRoxBackground(const char* style, const char* value){int result = addRoxFileAttribute("backdrop","style",style, value);std::cout<<result<<std::endl;}

std::string flDesktop::getRoxBackground(){
    const char* background;
    tinyxml2::XMLElement* element = roxDoc.FirstChildElement( "pinboard" )->
                                        FirstChildElement( "backdrop" );
    if(testElement(element)){
        background = element->GetText();
        return background;
    }
    return "";
}

void flDesktop::saveRox(){
    std::string fileName = roxPath();
    roxDoc.SaveFile(fileName.c_str());
}
void flDesktop::makeConfig(){
    std::string path = roxPath();
    std::string command = "/bin/bash -c 'cp /usr/share/jwm-settings-manager/";
    command += roxFileName;
    command += " ";
    command += path;
    command +="'";
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
