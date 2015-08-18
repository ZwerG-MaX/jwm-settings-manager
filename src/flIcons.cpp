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
#include "../include/flIcons.h"

flIcons::flIcons(){

#ifdef DEBUG_TRACK
  std::cerr<<"[flIcons]->"<<std::endl;
#endif // DEBUG

    tinyxml2::XMLDocument doc;
}

flIcons::~flIcons(){
    #ifdef DEBUG_TRACK
  std::cerr<<"<-[flIcons]"<<std::endl;
#endif // DEBUG

}

void flIcons::addIcons(std::string path){
    std::cout<<path<<std::endl;
    ///Make the rootNode
    tinyxml2::XMLNode *rootNode = doc.FirstChildElement( "JWM" );
    tinyxml2::XMLNode *iconNode = doc.FirstChildElement( "JWM" );
    ///make the new icon's node to hook onto (if the test doesn't fail)
    if (iconNode->LastChildElement("IconPath")){iconNode=iconNode->LastChildElement("IconPath");}
    ///Make the new icon node
    tinyxml2::XMLNode *node = doc.NewElement("IconPath");
    ///if there are other icons put it after them, otherwise just throw it at the end
    rootNode->InsertAfterChild(iconNode,node);
    ///make the text
    tinyxml2::XMLText *iconDir = doc.NewText(path.c_str());
    ///link the text to the icon node
    node->LinkEndChild(iconDir);
    /// save it temporarily incase the user decides to cancel
    saveChangesTemp();
}

void flIcons::getIcons(Fl_Browser *o){
    if(!testElement("IconPath")){return;}
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    for(node = node->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        std::string value  = node->GetText();
        if(value.c_str() !=NULL){
            const char * v = value.c_str();
            o->add(v);
        }
        //std::cout<<value<<std::endl;
    }
}

void flIcons::removeIcons(const char * icons){
    std::string fromProgram = icons;
    if(!testElement("IconPath")){return;}
    tinyxml2::XMLElement* node=doc.FirstChildElement("JWM");
    for(node = node->FirstChildElement("IconPath");node;node=node->NextSiblingElement("IconPath")){
        std::string fromDoc = node->GetText();
        const char* value  = fromDoc.c_str();
        if(DEBUG_ME){std::cerr<<"Value: "<<value<<" Icons: "<<fromProgram<<std::endl;}
        if(fromProgram.compare(value) ==0){
            node->DeleteChild(node);
            if(DEBUG_ME){std::cerr<<"deleted "<<fromProgram<<std::endl;}
        }

    }
    saveChangesTemp();
}
/// Icon theme FILES
std::string flIcons::currentIconTheme(){
    std::string gsett = "gsettings get org.gnome.desktop.interface icon-theme | sed \"s#'##g\" ";
    std::string result = returnTerminalOutput(gsett,"r");
    if(DEBUG_ME){std::cerr<<"current Icon Theme is: "<<result<<std::endl;}
    if(result.compare("")!=0){return result.erase((result.length()-1),std::string::npos);}
    return "";
}

void flIcons::loadTheme(Fl_Browser *o){
    o->clear();
    std::list<std::string> themeList;
    std::string testPATH,stringTHEME,dirToOpen,NEWpath,result;
    std::string testIndex, fullpath;
    std::string currentTheme = currentIconTheme();
    unsigned int found = 0;
    int sizer = 0;
    //initialize directory reading variables to NULL
    DIR *dir = NULL;
    struct dirent *entryPointer = NULL;

    // if we can't find the xdg paths... return without trying to read them
    if(num_XDG_PATHS==0){return;}

    //lets loop through the xdg paths
    for (int i = 1; i <= num_XDG_PATHS; i++){

        //get the string equvalent for the integer representation if of the xdg path
        // something like
        /*
        1=/usr/share/
        2=/usr/local/share
        etc...
        */
        testPATH = thisXDG_PATH(i);

        //make sure this isn't blank
        if(testPATH.compare("")!=0){

            //look to see if we have a / at the end... remove it if we do...
            found = testPATH.find_last_of('/');
            if (found == testPATH.length()-1){testPATH=testPATH.substr(0,testPATH.length()-1);}

            //see if there is an icon directory
            dirToOpen = testPATH + "/icons/";
            dir = opendir(dirToOpen.c_str());
            if (dir!=NULL){
                //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;
                while ((entryPointer=readdir(dir)) != NULL){
                    if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
                        result = entryPointer->d_name;
                        fullpath=dirToOpen+result;
                        testIndex=fullpath+"/index.theme";
                        if(testFile(testIndex.c_str())){themeList.push_back(result.c_str());}
                    }
                }
            }
            closedir(dir);
        }

    }
    themeList.sort();
    themeList.unique();
    std::list<std::string>::iterator it = std::unique (themeList.begin(), themeList.end());
    themeList.resize(std::distance(themeList.begin(),it));
    for(it = themeList.begin(); it != themeList.end(); ++it){
        if(DEBUG_ME){std::cerr << "item: " << *it << "\nCurrent theme: "<<currentTheme<<std::endl;}
        stringTHEME = *it;
        o->add(stringTHEME.c_str());
        if((currentTheme.compare(stringTHEME)==0)&&(currentTheme.compare("")!=0)){
            sizer = o->size();
            if(DEBUG_ME){std::cerr << "Line Number" << sizer << "\nContents: "<<o->text(sizer)<<std::endl;}
        }
    }

    /*TODO:
      find current theme via gtkrc 2.0, gtk 3.0 or gsettings
    */
    o->redraw();
    o->select(sizer);
}

void flIcons::useTheme(Fl_Browser *o){
    //get the user's choice number
    int themeNumber = o->value();
    //get the text using the number
    const char * item = o->text(themeNumber);
    std::string command = "jwmIconFinder";
    if(testExec(command.c_str())){
        command += " -s 48 -j -t ";
        command +=item;
        int thissys = system(command.c_str());
        if(thissys !=0){std::cerr<< command << " command did not return 0"<<std::endl;}
    }
    else{std::cerr<<command<<" is not installed... please reinstall this program"<<std::endl;}
#if 0
    //make sure there is some path to look in
    if (xdg_paths==NULL){
        xdg_paths="/usr/local/share/:/usr/share/";
    }


    std::string testPATH,stringTHEME,dirToOpen,NEWpath,result;
    //used to make sure there is not a / on the end
    unsigned int found;
    //look in every path in the xdg data paths
    if(num_XDG_PATHS==0){return;}
    for (int i = 1; i <= num_XDG_PATHS; i++){
        //helper function to get the string path
        testPATH = thisXDG_PATH(i);

        //check to make sure there is no / on the end
        found = testPATH.find_last_of('/');
        //if it is.. erase it
        if (found == testPATH.length()-1){
            testPATH=testPATH.substr(0,testPATH.length()-1);
        }

        //make out variable from the xdg data dirs path and /icons/
        dirToOpen = testPATH + "/icons/";
        //make a dirent dir
        DIR *dir = NULL;
        //make directory entry pointer
        dirent *entryPointer = NULL;
        //std::cout << "Process directory: " << dirToOpen.c_str() << std::endl;
        if(dir = opendir(dirToOpen.c_str())){
            // it is an icon sub directory!!!
            //lets find out what is inside, are you excited?  I sure am!

            //if this is doesn't error or reach the end read the directory
            while((entryPointer = readdir(dir)) != NULL){

                // make sure it is a usable icon directory (not hidden or . or ..)
                if ((entryPointer->d_type == DT_DIR)&&(entryPointer->d_name[0] != '.')){
                    //get the text from the entry
                    result = entryPointer->d_name;
                    //is it the one they picked??
                    if(result.compare(item)==0){
                       //it is!!  lets make a full path to send
                       stringTHEME=dirToOpen+result;
                       //send the path to the IconPath maker
                       makeIcons(stringTHEME,32);
                       //stop looking
                       closedir(dir);
                       return;
                    }
                }
            }
            closedir(dir);
        }
    }
    #endif // 0
}
void flIcons::makeIcons(std::string fullpath, unsigned int icon_size){
#if 0
    std::string testIndex=fullpath+"/index.theme";
    std::string  HEADER = "";
    std::string  INHERITS = "";
    std::string  MIN = "";
    std::string  MAX = "";
    std::string  SIZE = "";
    std::string  TYPE = "";
    std::string  CONTEXT = "";
    std::string  THRESH = "";
    unsigned int minsize = 0;
    unsigned int maxsize = 0;
    unsigned int iconsize = 0;
    unsigned int threshold = 0;
    std::string Inherits ="Inherits=";
    std::string MinSize = "MinSize=";
    std::string MaxSize = "MaxSize=";
    std::string Size = "Size=";
    std::string Type = "Type=";
    std::string Context = "Context=";
    std::string Threshold ="Threshold=";
    std::string line;
    int counter = 0;
    unsigned int foundOpen = 0;
    unsigned int foundClose = 0;
    if(testFile(testIndex.c_str())){
    std::cout<<testIndex<<std::endl;
    //std::cout<<themegrep(Inherits.c_str(),testIndex.c_str(),1)<<std::endl;
    std::ifstream inputFileStrem (fullpath.c_str(), std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line)){
    //std::ifstream inputFileStrem;
    //inputFileStrem.open(fullpath.c_str(), std::ifstream::in);
    //while(inputFileStrem.good()){
        //std::cout<<"ifs is open"<<inputFileStrem.get()<<std::endl;
        //while (std::getline(inputFileStrem,line)){
            HEADER=strstr(line.c_str(),"[");
            std::cout<<"getline: "<<HEADER<<std::endl;

            HEADER=strstr(line.c_str(),"[");
            INHERITS=strstr(line.c_str(),Inherits.c_str());
            MIN=strstr(line.c_str(),MinSize.c_str());
            MAX=strstr(line.c_str(),MaxSize.c_str());
            SIZE=strstr(line.c_str(),Size.c_str());
            TYPE=strstr(line.c_str(),Type.c_str());
            CONTEXT=strstr(line.c_str(),Context.c_str());
            THRESH=strstr(line.c_str(),Threshold.c_str());
            if (HEADER.c_str()!=NULL){
                foundOpen = HEADER.find('[');
                foundClose = HEADER.find(']');
                HEADER=HEADER.substr(foundOpen+1,foundClose-1);
            }
            else{HEADER="";}

            if (INHERITS.c_str()!=NULL){
                INHERITS=INHERITS.substr(Inherits.length(),std::string::npos);
            }
            else{INHERITS="";}

            if (MIN.c_str()!=NULL){
                MIN=MIN.substr(MinSize.length(),std::string::npos);
                minsize = convert(MIN.c_str());
            }
            else{
                MIN="";
                minsize=0;
            }

            if (MAX.c_str()!=NULL){
                MAX=MAX.substr(MaxSize.length(),std::string::npos);
                maxsize = convert(MAX.c_str());
            }
            else{
                MAX="";
                maxsize=0;
            }

            if (SIZE.c_str()!=NULL){
                SIZE=SIZE.substr(Size.length(),std::string::npos);
                icon_size = convert(SIZE.c_str());
            }
            else{
                SIZE="";
                icon_size=0;
            }

            if (THRESH.c_str()!=NULL){
                THRESH=THRESH.substr(Threshold.length(),std::string::npos);
                threshold = convert(THRESH.c_str());
            }
            else{
                THRESH="";
                threshold=0;
            }
            std::cout<<HEADER<<":"<<INHERITS<<":"<<TYPE<<":"<<CONTEXT<<"\n"
                     <<MIN<<": "<<minsize<<"\n"
                     <<MAX<<": "<<maxsize<<"\n"
                     <<SIZE<<": "<<icon_size<<std::endl;

            }
            inputFileStrem.close();
        }
    }
#endif // 0
}
const char* flIcons::themegrep(const char* args, const char* filename,int line){
///Return the FIRST match of the 'args' from a file
// this is like  line=`grep $args $filename` that only returns one line
    std::string line2;
    const char* result;
    std::string lengthTEST = args;
    int lengthofARGS = lengthTEST.length();
    std::ifstream inputFileStrem (filename, std::ifstream::in);
    if(inputFileStrem.is_open()){
        while (getline(inputFileStrem,line2)){
           result=strstr(line2.c_str(),args);
           //std::cout<<line<<std::endl;
            if(result!=NULL){
                return line2.c_str();
            }
        }
    }
    return "";
}
